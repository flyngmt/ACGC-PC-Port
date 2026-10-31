#include "acgc/ui/prelaunch.hpp"

#include "acgc/app_info.hpp"
#include "acgc/settings.hpp"
#include "acgc/ui/controller_config.hpp"
#include <borealis/ui/modal.hpp>
#include "acgc/ui/settings.hpp"
#include "acgc/ui/localization.hpp"
#include "acgc/ui/ui.hpp"

#include <SDL3/SDL_error.h>
#include <SDL3/SDL_misc.h>
#include <borealis/file_select.hpp>
#include <borealis/io.hpp>
#include <borealis/log.hpp>
#include <borealis/update.hpp>
#include <borealis/version.h>
#include <fmt/format.h>
#include "extern/aurora/lib/window.hpp"

#include <algorithm>
#include <atomic>
#include <exception>
#include <memory>
#include <optional>
#include <string_view>
#include <thread>
#include <utility>

namespace acgc::ui {
using namespace borealis::ui;

namespace {

constexpr borealis::Log Log{ "acgc::ui::prelaunch" };

#if defined(_WIN32)
constexpr const char* kLogoPath = "res/logos/windows.png";
#elif defined(__ANDROID__)
constexpr const char* kLogoPath = "res/logos/android.png";
#elif defined(__APPLE__) && TARGET_OS_IOS
constexpr const char* kLogoPath = "res/logos/ios.png";
#elif defined(__APPLE__)
constexpr const char* kLogoPath = "res/logos/macos.png";
#else
constexpr const char* kLogoPath = "res/logos/linux.png";
#endif

Rml::String document_source() {
    return R"RML(
<rml>
<head>
    <link type="text/rcss" href="res/rml/theme.rcss" />
    <link type="text/rcss" href="res/rml/controls.rcss" />
    <link type="text/rcss" href="res/rml/scrolling_background.rcss" />
    <link type="text/rcss" href="res/rml/prelaunch.rcss" />
</head>
<body>
    <div class="background">
        <scrolling-pattern id="background-pattern" />
    </div>
    <content id="root">
        <menu>
            <hero class="intro-item delay-0">
                <img src=")RML" + Rml::String(kLogoPath) + R"RML(" />
            </hero>
            <div id="menu-list" />
        </menu>
        <disc-info class="intro-item delay-4">
            <div id="disc-status">
                <icon />
                <span id="disc-status-label" />
            </div>
            <span id="disc-version" class="detail" />
        </disc-info>
        <version-info class="intro-item delay-5">
            <div class="version">)RML" +
           escape(localization::get("prelaunch.version")) + R"RML( <span id="version-text"></span></div>
            <div id="update-status" class="update">
                <span id="update-message"></span>
                <button id="update-download">
                    <span id="update-download-label"></span>
                    <icon />
                </button>
            </div>
        </version-info>
    </content>
</body>
</rml>
)RML";
}

std::vector<borealis::file_select::Filter> disc_file_filters() {
    return {
        { localization::get("prelaunch.file_filter.disc_images"), "iso;gcm;ciso;gcz;nfs;rvz;wbfs;wia;tgc" },
        { localization::get("prelaunch.file_filter.all_files"), "*" },
    };
}

struct DiscVerificationResult {
    std::string path;
    disc::DiscInfo info;
    disc::ValidationError validation = disc::ValidationError::Unknown;
};

struct DiscVerificationTask {
    explicit DiscVerificationTask(std::string discPath) : path(std::move(discPath)) {
        worker = std::thread([this] {
            try {
                validation = disc::verify(path, status, info);
            } catch (const std::exception& error) {
                Log.error("Disc verification failed for '{}': {}", path, error.what());
                validation = disc::ValidationError::Unknown;
            } catch (...) {
                Log.error("Disc verification failed for '{}' with an unknown exception", path);
                validation = disc::ValidationError::Unknown;
            }
            done.store(true, std::memory_order_release);
        });
    }

    ~DiscVerificationTask() {
        status.cancelRequested.store(true, std::memory_order_relaxed);
        join();
    }

    void join() {
        if (worker.joinable()) {
            worker.join();
        }
    }

    [[nodiscard]] bool finished() const {
        return done.load(std::memory_order_acquire);
    }

    std::string path;
    disc::DiscInfo info;
    disc::VerificationStatus status;
    disc::ValidationError validation = disc::ValidationError::Unknown;
    std::atomic_bool done = false;
    std::thread worker;
};

std::unique_ptr<DiscVerificationTask> sDiscVerificationTask;
bool sDiscVerificationModalPushed = false;

borealis::Task<borealis::update::Result> sUpdateCheckTask;
std::optional<borealis::update::Result> sUpdateCheckResult;
PrelaunchState sPrelaunchState;

bool verification_allows_launch(disc::ValidationError validation) noexcept {
    return validation == disc::ValidationError::Success || validation == disc::ValidationError::HashMismatch;
}

disc::ValidationError verification_from_config(DiscVerificationState value) noexcept {
    switch (value) {
        case DiscVerificationState::Success:
            return disc::ValidationError::Success;
        case DiscVerificationState::HashMismatch:
            return disc::ValidationError::HashMismatch;
        case DiscVerificationState::Unknown:
        default:
            return disc::ValidationError::Unknown;
    }
}

DiscVerificationState verification_to_config(disc::ValidationError validation) noexcept {
    switch (validation) {
        case disc::ValidationError::Success:
            return DiscVerificationState::Success;
        case disc::ValidationError::HashMismatch:
            return DiscVerificationState::HashMismatch;
        default:
            return DiscVerificationState::Unknown;
    }
}

std::string format_bytes(std::uint64_t bytes) {
    constexpr double KiB = 1024.0;
    constexpr double MiB = KiB * 1024.0;
    constexpr double GiB = MiB * 1024.0;
    if (bytes >= static_cast<std::uint64_t>(GiB)) {
        return fmt::format("{:.2f} GiB", static_cast<double>(bytes) / GiB);
    }
    if (bytes >= static_cast<std::uint64_t>(MiB)) {
        return fmt::format("{:.0f} MiB", static_cast<double>(bytes) / MiB);
    }
    if (bytes >= static_cast<std::uint64_t>(KiB)) {
        return fmt::format("{:.0f} KiB", static_cast<double>(bytes) / KiB);
    }
    return fmt::format("{} B", bytes);
}

void begin_disc_verification(std::string path) {
    if (path.empty()) {
        return;
    }
    if (sDiscVerificationTask != nullptr) {
        sDiscVerificationTask->status.cancelRequested.store(true, std::memory_order_relaxed);
        sDiscVerificationTask.reset();
    }
    sDiscVerificationTask = std::make_unique<DiscVerificationTask>(std::move(path));
    sDiscVerificationModalPushed = false;
}

std::optional<DiscVerificationResult> take_finished_disc_verification() {
    if (sDiscVerificationTask == nullptr || !sDiscVerificationTask->finished()) {
        return std::nullopt;
    }
    DiscVerificationResult result{
        .path = sDiscVerificationTask->path,
        .info = sDiscVerificationTask->info,
        .validation = sDiscVerificationTask->validation,
    };
    sDiscVerificationTask->join();
    sDiscVerificationTask.reset();
    sDiscVerificationModalPushed = false;
    return result;
}

void begin_update_check() {
    if (!settings().backend.checkForUpdates.get() || sUpdateCheckTask || sUpdateCheckResult.has_value()) {
        return;
    }
    sUpdateCheckTask =
        borealis::update::check_latest_github_release(AppInfo, {
                                                                   .currentVersion = BOREALIS_APP_DESCRIBE,
                                                                   .includePrereleases = true,
                                                               });
}

std::optional<borealis::update::Result> take_finished_update_check() {
    if (!sUpdateCheckTask.ready()) {
        return std::nullopt;
    }
    std::optional<borealis::update::Result> result;
    try {
        result = sUpdateCheckTask.try_take();
    } catch (const std::exception& e) { result = borealis::update::Result{ .message = e.what() }; } catch (...) {
        result = borealis::update::Result{ .message = "Unknown error" };
    }
    sUpdateCheckTask = {};
    return result;
}

std::string update_release_label(const borealis::update::Release& release) {
    std::string_view label = release.tagName;
    if (!label.empty() && label.front() == 'v') {
        label.remove_prefix(1);
    }
    return std::string(label);
}

void open_update_release() {
    if (!sUpdateCheckResult.has_value() || sUpdateCheckResult->status != borealis::update::Status::UpdateAvailable) {
        return;
    }
    const std::string& url = sUpdateCheckResult->latest.htmlUrl;
    if (url.empty()) {
        Log.warn("The available update did not include a release URL");
    } else if (!SDL_OpenURL(url.c_str())) {
        Log.warn("Failed to open update URL '{}': {}", url, SDL_GetError());
    }
}

std::string verification_error_message(disc::ValidationError error) {
    switch (error) {
        case disc::ValidationError::IOError:
            return localization::get("prelaunch.verification.error.io");
        case disc::ValidationError::InvalidImage:
            return localization::get("prelaunch.verification.error.invalid_image");
        case disc::ValidationError::WrongGame:
            return localization::get("prelaunch.verification.error.wrong_game");
        case disc::ValidationError::WrongVersion:
            return localization::get("prelaunch.verification.error.wrong_version");
        case disc::ValidationError::Canceled:
            return localization::get("prelaunch.verification.error.canceled");
        case disc::ValidationError::HashMismatch:
            return localization::get("prelaunch.verification.error.hash_mismatch");
        case disc::ValidationError::Success:
            return localization::get("prelaunch.verification.success");
        case disc::ValidationError::Unknown:
        default:
            return localization::get("prelaunch.verification.error.unknown");
    }
}

void persist_disc_choice(const std::string& path, disc::ValidationError validation) {
    auto& backend = settings().backend;
    const auto savedVerification = verification_to_config(validation);
    const bool changed = backend.discPath.get() != path || backend.discVerification.get() != savedVerification;
    backend.discPath.set(path);
    backend.discVerification.set(savedVerification);
    save_settings();
    if (changed) {
        disc::log_verification_state(path, savedVerification);
    }
}

void apply_valid_disc_result(const std::string& path, const disc::DiscInfo& info, disc::ValidationError validation) {
    auto& state = prelaunch_state();
    state.configuredDiscPath = path;
    state.configuredDiscCanLaunch = true;
    state.configuredDiscInfo = info;
    state.configuredDiscValidation = validation;
    state.activeDiscPath = path;
    state.activeDiscInfo = info;
    persist_disc_choice(path, validation);
}

void apply_disc_verification_result(const DiscVerificationResult& result) {
    auto& state = prelaunch_state();
    if (result.validation == disc::ValidationError::HashMismatch) {
        state.pendingDiscPath = result.path;
        state.pendingDiscInfo = result.info;
        state.pendingDiscValidation = result.validation;
        state.errorString = escape(verification_error_message(result.validation));
        return;
    }
    if (result.validation == disc::ValidationError::Success) {
        apply_valid_disc_result(result.path, result.info, result.validation);
        state.errorString.clear();
        state.pendingDiscPath.clear();
        state.pendingDiscInfo = {};
        state.pendingDiscValidation = disc::ValidationError::Unknown;
        return;
    }
    state.pendingDiscPath.clear();
    state.pendingDiscInfo = {};
    state.pendingDiscValidation = disc::ValidationError::Unknown;
    state.errorString = escape(verification_error_message(result.validation));
}

class DiscVerificationModal final : public WindowSmall {
  public:
    DiscVerificationModal() : WindowSmall({ .windowClass = "modal" }) {
        auto* header = append(mDialog, "modal-header");
        header->SetClass("modal-header", true);
        auto* title = append(header, "modal-title");
        title->SetClass("modal-title", true);
        title->SetInnerRML(escape(localization::get("prelaunch.verification.title")));
        auto* icon = append(header, "icon");
        icon->SetClass("verifying", true);

        auto* body = append(mDialog, "modal-body");
        body->SetClass("modal-body", true);
        auto* content = append(body, "div");
        content->SetClass("verification-progress", true);
        mFileName = append(content, "div");
        mFileName->SetClass("verification-file", true);
        mProgress = append(content, "progress");
        mProgress->SetClass("progress-ongoing", true);
        mProgress->SetClass("verification-progress-bar", true);
        mProgress->SetAttribute("value", 0.0f);
        mDetail = append(content, "div");
        mDetail->SetClass("verification-detail", true);

        auto* actions = append(mDialog, "modal-actions");
        actions->SetClass("modal-actions", true);
        mCancelButton = std::make_unique<Button>(actions, localization::get("common.cancel"));
        mCancelButton->root()->SetClass("modal-btn", true);
        mCancelButton->on_pressed([this] { request_cancel(); });
        refresh();
    }

    void update() override {
        if (mFinished) {
            return;
        }
        if (auto result = take_finished_disc_verification()) {
            mFinished = true;
            apply_disc_verification_result(*result);
            pop();
            return;
        }
        if (sDiscVerificationTask == nullptr) {
            mFinished = true;
            pop();
            return;
        }
        refresh();
    }

    bool focus() override {
        return mCancelButton != nullptr && mCancelButton->focus();
    }

  protected:
    bool handle_nav_command(Rml::Event& event, NavCommand cmd) override {
        if (cmd == NavCommand::Cancel || cmd == NavCommand::Menu) {
            request_cancel();
            event.StopPropagation();
            return true;
        }
        return cmd == NavCommand::Left || cmd == NavCommand::Right;
    }

  private:
    void request_cancel() {
        if (sDiscVerificationTask == nullptr || mCancelRequested) {
            return;
        }
        mCancelRequested = true;
        sDiscVerificationTask->status.cancelRequested.store(true, std::memory_order_relaxed);
        mCancelButton->set_text(localization::get("prelaunch.verification.cancelling"));
        mCancelButton->set_disabled(true);
    }

    void refresh() {
        if (sDiscVerificationTask == nullptr || mCancelRequested) {
            return;
        }
        std::string fileName = borealis::io::display_name(sDiscVerificationTask->path);
        if (fileName.empty()) {
            fileName = sDiscVerificationTask->path;
        }
        mFileName->SetInnerRML(escape(fileName));

        const std::uint64_t bytesRead = sDiscVerificationTask->status.bytesRead.load(std::memory_order_relaxed);
        const std::uint64_t bytesTotal = sDiscVerificationTask->status.bytesTotal.load(std::memory_order_relaxed);
        if (bytesTotal == 0) {
            mProgress->SetAttribute("value", 0.0f);
            mDetail->SetInnerRML(escape(localization::get("prelaunch.verification.opening")));
            return;
        }
        const float fraction = std::clamp(static_cast<float>(bytesRead) / static_cast<float>(bytesTotal), 0.0f, 1.0f);
        mProgress->SetAttribute("value", fraction);
        mDetail->SetInnerRML(escape(
            fmt::format("{} / {} ({:.0f}%)", format_bytes(bytesRead), format_bytes(bytesTotal), fraction * 100.0f)));
    }

    Rml::Element* mFileName = nullptr;
    Rml::Element* mProgress = nullptr;
    Rml::Element* mDetail = nullptr;
    std::unique_ptr<Button> mCancelButton;
    bool mCancelRequested = false;
    bool mFinished = false;
};

void file_dialog_callback(borealis::file_select::Result result) {
    if (result.status == borealis::file_select::Status::Selected && !result.locations.empty()) {
        begin_disc_verification(result.locations.front());
    } else if (result.status == borealis::file_select::Status::Failed ||
               result.status == borealis::file_select::Status::Unsupported) {
        Log.warn("File selection failed: {}", result.message);
        auto& state = prelaunch_state();
        state.errorString = escape(localization::get("prelaunch.file_picker_unavailable"));
    }
}

void apply_intro_animation(Rml::Element* element, const char* delayClass) {
    if (element == nullptr) {
        return;
    }
    element->SetClass("intro-item", true);
    element->SetClass(delayClass, true);
}

} // namespace

PrelaunchState& prelaunch_state() noexcept {
    return sPrelaunchState;
}

void refresh_configured_disc_state() noexcept {
    auto& state = prelaunch_state();
    if (state.configuredDiscPath.empty()) {
        state.configuredDiscCanLaunch = false;
        state.configuredDiscInfo = {};
        state.configuredDiscValidation = disc::ValidationError::Unknown;
        return;
    }

    disc::DiscInfo info{};
    const auto inspection = disc::inspect(state.configuredDiscPath, info);
    if (inspection != disc::ValidationError::Success) {
        state.configuredDiscCanLaunch = false;
        state.configuredDiscInfo = {};
        state.configuredDiscValidation = inspection;
        return;
    }

    auto verification = disc::ValidationError::Unknown;
    if (state.configuredDiscPath == settings().backend.discPath.get()) {
        verification = verification_from_config(settings().backend.discVerification.get());
    }
    if (verification_allows_launch(verification)) {
        state.configuredDiscCanLaunch = true;
        state.configuredDiscInfo = info;
        state.configuredDiscValidation = verification;
        if (state.configuredDiscPath == state.activeDiscPath) {
            state.activeDiscInfo = info;
        }
        return;
    }

    state.configuredDiscCanLaunch = false;
    state.configuredDiscInfo = {};
    state.configuredDiscValidation = disc::ValidationError::Unknown;
}

void ensure_prelaunch_initialized() noexcept {
    auto& state = prelaunch_state();
    if (state.initialized) {
        return;
    }
    state.configuredDiscPath = settings().backend.discPath.get();
    state.activeDiscPath = state.configuredDiscPath;
    state.configuredDiscValidation = verification_from_config(settings().backend.discVerification.get());
    state.initialized = true;
    refresh_configured_disc_state();
    if (!state.configuredDiscPath.empty() && !state.configuredDiscCanLaunch &&
        state.configuredDiscValidation == disc::ValidationError::Unknown) {
        begin_disc_verification(state.configuredDiscPath);
    }
}

void open_disc_picker() noexcept {
    ensure_prelaunch_initialized();
    borealis::file_select::open_file(
        {
            .parentWindow = aurora::window::get_sdl_window(),
            .filters = disc_file_filters(),
            .defaultLocation = prelaunch_state().configuredDiscPath,
        },
        &file_dialog_callback);
}

void try_push_verification_modal(Document& host) {
    auto& state = prelaunch_state();
    if (sDiscVerificationTask != nullptr && !sDiscVerificationModalPushed) {
        sDiscVerificationModalPushed = true;
        host.push(std::make_unique<DiscVerificationModal>());
        return;
    }
    if (state.errorString.empty()) {
        return;
    }

    auto dismiss = [](Modal& modal) {
        auto& current = prelaunch_state();
        current.errorString.clear();
        current.pendingDiscPath.clear();
        current.pendingDiscInfo = {};
        current.pendingDiscValidation = disc::ValidationError::Unknown;
        modal.pop();
    };

    if (!state.pendingDiscPath.empty()) {
        const Rml::String body =
            state.errorString + "<br/><br/>" + escape(localization::get("prelaunch.verification.continue_risk"));
        auto accept = [](Modal& modal) {
            auto& current = prelaunch_state();
            const std::string path = std::move(current.pendingDiscPath);
            const auto info = current.pendingDiscInfo;
            const auto validation = current.pendingDiscValidation;
            current.pendingDiscInfo = {};
            current.pendingDiscValidation = disc::ValidationError::Unknown;
            current.errorString.clear();
            apply_valid_disc_result(path, info, validation);
            refresh_configured_disc_state();
            modal.pop();
        };
        host.push(std::make_unique<Modal>(Modal::Props{
            .title = escape(localization::get("prelaunch.verification.warning_title")),
            .bodyRml = body,
            .actions = { { localization::get("common.cancel"), dismiss },
                         { localization::get("prelaunch.verification.continue"), accept } },
            .onDismiss = dismiss,
            .variant = "danger",
            .icon = "warning",
        }));
        return;
    }

    host.push(std::make_unique<Modal>(Modal::Props{
        .title = escape(localization::get("prelaunch.verification.error_title")),
        .bodyRml = state.errorString,
        .actions = { { localization::get("common.ok"), dismiss } },
        .onDismiss = dismiss,
        .icon = "error",
    }));
}

Prelaunch::Prelaunch()
    : Document(document_source(), false, kScopePrelaunch),
      mRoot(mDocument != nullptr ? mDocument->GetElementById("root") : nullptr),
      mScrollingBackground(mDocument != nullptr ? mDocument->GetElementById("background-pattern") : nullptr) {
    ensure_prelaunch_initialized();
    begin_update_check();

    if (mDocument == nullptr || mRoot == nullptr) {
        return;
    }
    if (auto* menuList = mDocument->GetElementById("menu-list")) {
        const bool ready = prelaunch_state().configuredDiscCanLaunch;
        mMenuButtons.push_back(std::make_unique<Button>(menuList, ready ? localization::get("prelaunch.play")
                                                                        : localization::get("prelaunch.select_disc")));
        mMenuButtons.back()->on_pressed([this] {
            auto& state = prelaunch_state();
            if (!state.configuredDiscCanLaunch) {
                open_disc_picker();
                return;
            }
            state.activeDiscPath = state.configuredDiscPath;
            state.activeDiscInfo = state.configuredDiscInfo;
            state.launchRequested = true;
            hide(true);
        });
        apply_intro_animation(mMenuButtons.back()->root(), "delay-1");

        mMenuButtons.push_back(std::make_unique<Button>(menuList, localization::get("common.settings")));
        mMenuButtons.back()->on_pressed([this] { push(std::make_unique<SettingsWindow>()); });
        apply_intro_animation(mMenuButtons.back()->root(), "delay-2");

        mMenuButtons.push_back(std::make_unique<Button>(menuList, localization::get("menu.controls")));
        mMenuButtons.back()->on_pressed([this] { push(std::make_unique<ControllerConfigWindow>()); });
        apply_intro_animation(mMenuButtons.back()->root(), "delay-3");

        mMenuButtons.push_back(std::make_unique<Button>(menuList, localization::get("common.quit")));
        mMenuButtons.back()->on_pressed([] { prelaunch_state().quitRequested = true; });
        apply_intro_animation(mMenuButtons.back()->root(), "delay-4");
    }

    mDiscStatus = mDocument->GetElementById("disc-status");
    mDiscDetail = mDocument->GetElementById("disc-version");
    mVersion = mDocument->GetElementById("version-text");
    mUpdateStatus = mDocument->GetElementById("update-status");
    mUpdateMessage = mDocument->GetElementById("update-message");
    mUpdateDownload = mDocument->GetElementById("update-download");
    mUpdateDownloadLabel = mDocument->GetElementById("update-download-label");

    if (mUpdateDownload != nullptr) {
        listen(mUpdateDownload, Rml::EventId::Click, [](Rml::Event& event) {
            open_update_release();
            event.StopPropagation();
        });
        listen(mUpdateDownload, kNavCommandEvent, [](Rml::Event& event) {
            if (nav_command(event) == NavCommand::Confirm) {
                open_update_release();
                event.StopPropagation();
            }
        });
    }
    listen(mDocument, Rml::EventId::Transitionend, [this](Rml::Event& event) {
        if (event.GetTargetElement() == mDocument && !mDocument->HasAttribute("open")) {
            Document::hide(true);
        }
    });
}

void Prelaunch::show() {
    Document::show();
    if (mDocument != nullptr) {
        mDocument->SetAttribute("open", "");
    }
    if (mRoot != nullptr) {
        mRoot->SetAttribute("open", "");
    }
}

void Prelaunch::hide(bool close) {
    if (mDocument == nullptr || mRoot == nullptr) {
        Document::hide(close);
        return;
    }
    if (close) {
        if (!mEntranceAnimationStarted) {
            Document::hide(true);
        } else {
            mPendingClose = true;
        }
        mDocument->RemoveAttribute("open");
    } else {
        mRoot->RemoveAttribute("open");
    }
}

void Prelaunch::update() {
    ensure_prelaunch_initialized();
    mScrollingBackground.update(mDocument != nullptr ? mDocument->GetContext() : nullptr);
    if (top_document() == this) {
        try_push_verification_modal(*this);
    }
    const auto& state = prelaunch_state();
    if (!mEntranceAnimationStarted && mDocument != nullptr) {
        mDocument->SetClass("animate-in", true);
        mEntranceAnimationStarted = true;
    }
    if (!mMenuButtons.empty()) {
        mMenuButtons.front()->set_text(state.configuredDiscCanLaunch ? localization::get("prelaunch.play")
                                                                     : localization::get("prelaunch.select_disc"));
    }

    auto* statusLabel = mDiscStatus != nullptr ? mDiscStatus->GetElementById("disc-status-label") : nullptr;
    if (mDiscStatus != nullptr && statusLabel != nullptr) {
        if (sDiscVerificationTask != nullptr) {
            mDiscStatus->SetAttribute("status", "verifying");
            statusLabel->SetInnerRML(escape(localization::get("prelaunch.status.verifying")));
        } else if (state.configuredDiscCanLaunch && state.configuredDiscValidation == disc::ValidationError::Success) {
            mDiscStatus->SetAttribute("status", "good");
            statusLabel->SetInnerRML(escape(localization::get("prelaunch.status.ready")));
        } else if (state.configuredDiscCanLaunch &&
                   state.configuredDiscValidation == disc::ValidationError::HashMismatch) {
            mDiscStatus->SetAttribute("status", "mismatch");
            statusLabel->SetInnerRML(escape(localization::get("prelaunch.status.hash_mismatch")));
        } else {
            mDiscStatus->SetAttribute("status", "bad");
            statusLabel->SetInnerRML(escape(localization::get("prelaunch.status.select_disc")));
        }
    }
    if (mDiscDetail != nullptr) {
        if (state.configuredDiscCanLaunch) {
            mDiscDetail->SetProperty(Rml::PropertyId::Display, Rml::Style::Display::Block);
            mDiscDetail->SetInnerRML(escape(
                localization::format("prelaunch.disc_detail", borealis::io::display_name(state.configuredDiscPath),
                                     state.configuredDiscInfo.gameId, state.configuredDiscInfo.revision)));
        } else {
            mDiscDetail->SetProperty(Rml::PropertyId::Display, Rml::Style::Display::None);
        }
    }
    if (mVersion != nullptr) {
        std::string_view version = BOREALIS_APP_DESCRIBE;
        if (!version.empty() && version.front() == 'v') {
            version.remove_prefix(1);
        }
        mVersion->SetInnerRML(escape(version));
    }
    if (mUpdateStatus != nullptr && mUpdateMessage != nullptr) {
        if (auto result = take_finished_update_check()) {
            if (result->status == borealis::update::Status::Failed) {
                Log.warn("Update check failed: {}", result->message);
            }
            sUpdateCheckResult = std::move(*result);
        }
        if (sUpdateCheckTask) {
            mUpdateStatus->SetAttribute("state", "checking");
            mUpdateMessage->SetInnerRML(escape(localization::get("prelaunch.update.checking")));
        } else if (!sUpdateCheckResult.has_value() ||
                   sUpdateCheckResult->status == borealis::update::Status::UpToDate ||
                   sUpdateCheckResult->status == borealis::update::Status::Disabled) {
            mUpdateStatus->RemoveAttribute("state");
            mUpdateMessage->SetInnerRML("");
        } else if (sUpdateCheckResult->status == borealis::update::Status::UpdateAvailable) {
            mUpdateStatus->SetAttribute("state", "available");
            mUpdateMessage->SetInnerRML(escape(localization::get("prelaunch.update.available")));
            if (mUpdateDownloadLabel != nullptr) {
                mUpdateDownloadLabel->SetInnerRML(escape(
                    localization::format("prelaunch.update.get", update_release_label(sUpdateCheckResult->latest))));
            }
        } else {
            mUpdateStatus->SetAttribute("state", "failed");
            mUpdateMessage->SetInnerRML(escape(localization::get("prelaunch.update.failed")));
        }
    }
    Document::update();
}

bool Prelaunch::focus() {
    return !mMenuButtons.empty() && mMenuButtons.front()->focus();
}

bool Prelaunch::visible() const {
    return mDocument != nullptr && mRoot != nullptr && mDocument->HasAttribute("open") && mRoot->HasAttribute("open");
}

bool Prelaunch::handle_nav_command(Rml::Event& event, NavCommand cmd) {
    int direction = 0;
    if (cmd == NavCommand::Right) {
        direction = 1;
    } else if (cmd == NavCommand::Left) {
        direction = -1;
    } else {
        return false;
    }
    if (mMenuButtons.empty()) {
        return false;
    }
    int focused = -1;
    for (int index = 0; index < static_cast<int>(mMenuButtons.size()); ++index) {
        if (mMenuButtons[index]->contains(event.GetTargetElement())) {
            focused = index;
            break;
        }
    }
    const int count = static_cast<int>(mMenuButtons.size());
    for (int attempts = 0; attempts < count; ++attempts) {
        focused = ((focused + direction) % count + count) % count;
        if (mMenuButtons[focused]->focus()) {
            play_nav_sound(NavSound::ItemFocus);
            event.StopPropagation();
            return true;
        }
    }
    return false;
}

} // namespace acgc::ui
