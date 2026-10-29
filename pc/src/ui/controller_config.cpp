#include "acgc/ui/controller_config.hpp"
#include <borealis/ui/config.hpp>
#include "acgc/ui/scrolling_background.hpp"
#include <borealis/ui/bool_button.hpp>
#include <borealis/ui/button.hpp>
#include <borealis/ui/component.hpp>
#include <borealis/ui/group_button.hpp>
#include <borealis/ui/modal.hpp>
#include <borealis/ui/number_button.hpp>
#include <borealis/ui/pane.hpp>
#include "acgc/ui/localization.hpp"
#include "acgc/input_profiles.hpp"
#include "acgc/controller_ports.hpp"
#include "acgc/settings.hpp"
#include <SDL3/SDL_gamepad.h>
#include <SDL3/SDL_keyboard.h>
#include <algorithm>
#include <optional>

namespace acgc::ui {
using namespace borealis::ui;

namespace {
using aurora::binding::Binding;
using aurora::binding::ControlId;
using aurora::binding::PhysicalInput;
using aurora::input::SourceId;
using aurora::pad::ProfileSettings;
using aurora::pad::ProfileTarget;

Rml::String tr(const char* key) {
    return localization::get(key);
}

SDL_Gamepad* gamepad(SourceId source) {
    return SDL_GetGamepadFromID(aurora::input::gamepad_for_source(source));
}

bool selected_half(const Binding& binding, int direction) {
    return direction == 0 || (binding.scale < 0.f) == (direction < 0);
}

void save_or_explain() {
    if (input::save_profiles()) {
        return;
    }
    push_document(
        std::make_unique<Modal>(Modal::Props{ .title = tr("controller.save_failed"),
                                              .bodyText = tr("controller.save_failed_help"),
                                              .actions = { { tr("common.ok"), [](Modal& modal) { modal.pop(); } } } }));
}

std::vector<SourceId> controllers() {
    std::vector<SourceId> result;
    for (const auto& source : aurora::input::sources()) {
        if (source.kind == aurora::input::InputSource::Kind::Controller) {
            result.push_back(source.id);
        }
    }
    return result;
}

void add_profile_percent(Pane& pane, ProfileTarget target, const char* key, float ProfileSettings::* field) {
    pane.add_child<NumberButton>(
        NumberButton::Props{ .key = tr(key),
                             .getValue =
                                 [target, field] {
                                     const auto* p = aurora::pad::profile(target);
                                     return p ? static_cast<int>(p->settings.*field * 100.f + .5f) : 0;
                                 },
                             .setValue =
                                 [target, field](int value) {
                                     if (const auto* p = aurora::pad::profile(target)) {
                                         auto settings = p->settings;
                                         settings.*field = value / 100.f;
                                         if (aurora::pad::set_settings(target, settings)) {
                                             save_or_explain();
                                         }
                                     }
                                 },
                             .min = 0,
                             .max = 100,
                             .suffix = "%" });
}
struct BindingControl {
    ControlId control;
    int direction;
    Rml::String label;
};

class BindingRow final : public Component {
  public:
    BindingRow(Rml::Element* parent, const BindingControl& control, ProfileTarget target,
               std::function<bool()> capturing, std::function<void()> startCapture,
               std::function<void(size_t)> removeBinding)
        : Component(append(parent, "binding-row")), mCapturing(std::move(capturing)) {
        mSummary = &add_child<ControlledSelectButton>(ControlledSelectButton::Props{
            .key = control.label, .getValue = [this, target, control] {
                if (mCapturing()) {
                    return tr("controller.binding.waiting");
                }
                Rml::String label;
                for (const auto& binding : input::editable_bindings(target, control.control, control.direction)) {
                    if (!selected_half(binding, control.direction)) {
                        continue;
                    }
                    if (!label.empty()) {
                        label += ", ";
                    }
                    label += aurora::binding::input_label(
                        binding.input, target.kind == ProfileTarget::Kind::Controller ? gamepad(target.id) : nullptr);
                }
                return label.empty() ? tr("controller.binding.not_bound") : label;
            } });
        mSummary->on_pressed(std::move(startCapture));
        mFocusTargets.push_back(mSummary->root());

        auto actions = std::make_unique<Component>(append(mRoot, "binding-actions"));
        const auto bindings = input::editable_bindings(target, control.control, control.direction);
        for (size_t i = 0; i < bindings.size(); ++i) {
            if (!selected_half(bindings[i], control.direction)) {
                continue;
            }
            const auto label = aurora::binding::input_label(
                bindings[i].input, target.kind == ProfileTarget::Kind::Controller ? gamepad(target.id) : nullptr);
            auto& button = actions->add_child<Button>(label + " ×");
            button.on_pressed([removeBinding, i] { removeBinding(i); });
            mFocusTargets.push_back(button.root());
        }
        mChildren.push_back(std::move(actions));
        listen(mRoot, kNavCommandEvent, [this](Rml::Event& event) {
            const auto command = nav_command(event);
            if (command != NavCommand::Left && command != NavCommand::Right) {
                return;
            }
            const auto found = std::find(mFocusTargets.begin(), mFocusTargets.end(), event.GetTargetElement());
            if (found == mFocusTargets.end()) {
                return;
            }
            const int index = static_cast<int>(found - mFocusTargets.begin());
            const int next = index + (command == NavCommand::Right ? 1 : -1);
            if (next >= 0 && next < static_cast<int>(mFocusTargets.size())) {
                mFocusTargets[next]->Focus();
                event.StopPropagation();
            }
        });
    }

    bool focus() override {
        return mSummary->focus();
    }

    void update() override {
        const bool expanded = mCapturing() || contains(mRoot->GetContext()->GetFocusElement());
        mRoot->SetClass("expanded", expanded);
        mRoot->SetClass("capturing", mCapturing());
        Component::update();
    }

  private:
    ControlledSelectButton* mSummary = nullptr;
    std::function<bool()> mCapturing;
    std::vector<Rml::Element*> mFocusTargets;
};

} // namespace

class BindingsPane final : public Pane {
  public:
    BindingsPane(Rml::Element* parent, ProfileTarget target, bool& allowConflicts)
        : Pane(parent, Type::Uncontrolled), mTarget(target), mAllowConflicts(allowConflicts),
          mCapture(std::make_shared<Capture>()) {
        root()->SetClass("bindings-pane", true);
    }

    ~BindingsPane() override {
        cancel_capture();
    }

    void cancel_capture() {
        if (mCapturing >= 0) {
            aurora::binding::cancel_capture();
        }
        mCapturing = -1;
        mCapture->physical.reset();
    }

    void show_group(int group) {
        cancel_capture();
        mControls.clear();
        const auto add = [this](ControlId control, int direction, Rml::String label) {
            mControls.push_back({ control, direction, std::move(label) });
        };
        const auto& controls = aurora::pad::controls();
        if (group == 0 || group == 1) {
            const std::vector<PADButton> buttons =
                group == 0
                    ? std::vector<PADButton>{ PAD_BUTTON_A, PAD_BUTTON_B,     PAD_BUTTON_X,
                                              PAD_BUTTON_Y, PAD_BUTTON_START, PAD_TRIGGER_Z }
                    : std::vector<PADButton>{ PAD_BUTTON_UP, PAD_BUTTON_DOWN, PAD_BUTTON_LEFT, PAD_BUTTON_RIGHT };
            for (const auto button : buttons) {
                add(aurora::pad::control_for_button(button), 0, PADGetButtonName(button));
            }
        } else if (group == 2) {
            add(aurora::pad::control_for_button(PAD_TRIGGER_L), 0, tr("controller.input.left_click"));
            add(aurora::pad::control_for_button(PAD_TRIGGER_R), 0, tr("controller.input.right_click"));
            add(controls.triggerL, 0, tr("controller.input.left_trigger"));
            add(controls.triggerR, 0, tr("controller.input.right_trigger"));
        } else {
            const auto x = group == 3 ? controls.leftX : controls.rightX;
            const auto y = group == 3 ? controls.leftY : controls.rightY;
            add(x, -1, tr("controller.input.left"));
            add(x, 1, tr("controller.input.right"));
            add(y, 1, tr("controller.input.up"));
            add(y, -1, tr("controller.input.down"));
        }
        rebuild();
    }

    void restore_defaults() {
        cancel_capture();
        aurora::pad::reset_to_defaults(mTarget);
        persist();
        mRebuild = true;
    }

    void update() override {
        if (mCapture->physical) {
            const auto physical = std::exchange(mCapture->physical, std::nullopt).value();
            const int index = std::exchange(mCapturing, -1);
            const auto* key = physical.control.get_if<PhysicalInput::Key>();
            const auto* button = physical.control.get_if<PhysicalInput::GamepadButton>();
            const bool keyboard = mTarget.kind == ProfileTarget::Kind::Keyboard;
            const bool matches = keyboard ? (key != nullptr || physical.control.is<PhysicalInput::MouseButton>())
                                          : physical.source == mTarget.id;
            const bool cancelled = (key != nullptr && key->scancode == SDL_SCANCODE_ESCAPE) ||
                                   (matches && button != nullptr && button->button == SDL_GAMEPAD_BUTTON_BACK);
            if (index >= 0 && !cancelled) {
                if (!matches) {
                    start_capture(index);
                } else {
                    const auto& control = mControls[index];
                    if (input::append_binding(mTarget, control.control, control.direction, physical,
                                              mAllowConflicts ? aurora::pad::ConflictPolicy::Allow
                                                              : aurora::pad::ConflictPolicy::Unbind)) {
                        persist();
                    }
                    mRebuild = true;
                    mFocusRow = index;
                }
            }
        }
        if (mRebuild) {
            mRebuild = false;
            rebuild();
            if (mFocusRow >= 0 && mFocusRow < static_cast<int>(mRows.size())) {
                mRows[mFocusRow]->focus();
            }
            mFocusRow = -1;
        }
        root()->SetClass("save-failed", mSaveFailed);
        set_text_content(mStatus,
                         mSaveFailed ? tr("controller.save_failed_help") : tr("controller.binding.inline_help"));
        Pane::update();
    }

  private:
    struct Capture {
        std::optional<PhysicalInput> physical;
    };

    void start_capture(int index) {
        cancel_capture();
        mCapturing = index;
        const std::weak_ptr<Capture> state = mCapture;
        aurora::binding::capture_next([state](const PhysicalInput& physical) {
            if (const auto capture = state.lock()) {
                capture->physical = physical;
            }
        });
    }

    void persist() {
        mSaveFailed = !input::save_profiles();
    }

    void rebuild() {
        clear();
        mRows.clear();
        for (size_t index = 0; index < mControls.size(); ++index) {
            auto& row = add_child<BindingRow>(
                mControls[index], mTarget, [this, index] { return mCapturing == static_cast<int>(index); },
                [this, index] { start_capture(static_cast<int>(index)); },
                [this, index](size_t bindingIndex) {
                    const auto& control = mControls[index];
                    auto bindings = input::editable_bindings(mTarget, control.control, control.direction);
                    if (bindingIndex < bindings.size()) {
                        bindings.erase(bindings.begin() + static_cast<std::ptrdiff_t>(bindingIndex));
                        aurora::pad::set_binding(mTarget, control.control, std::move(bindings));
                        persist();
                        mRebuild = true;
                        mFocusRow = static_cast<int>(index);
                    }
                });
            mRows.push_back(&row);
        }
        mStatus = add_text(tr("controller.binding.inline_help"));
        mStatus->SetClass("binding-help", true);
        auto& retry = add_button(tr("controller.binding.save"));
        retry.root()->SetClass("binding-save-retry", true);
        retry.on_pressed([this] { persist(); });
    }

    ProfileTarget mTarget;
    bool& mAllowConflicts;
    std::shared_ptr<Capture> mCapture;
    std::vector<BindingControl> mControls;
    std::vector<BindingRow*> mRows;
    Rml::Element* mStatus = nullptr;
    int mCapturing = -1;
    int mFocusRow = -1;
    bool mRebuild = false;
    bool mSaveFailed = false;
};

ControllerConfigWindow::ControllerConfigWindow()
    : Window({
          .styleSheets = { "res/rml/scrolling_background.rcss" },
          .background = scrolling_background,
      }),
      mController(aurora::pad::port_controller(0)), mSources(controllers()) {
    add_tab(tr("controller.page.device"), [this](auto* content) { build_device(content); });
    add_tab(tr("controller.section.controller"), [this](auto* content) { build_bindings(content, false); });
    if (SDL_HasKeyboard()) {
        add_tab(tr("controller.section.keyboard"), [this](auto* content) { build_bindings(content, true); });
    }
}

ControllerConfigWindow::~ControllerConfigWindow() {
    stop_rumble();
}

void ControllerConfigWindow::stop_rumble() {
    if (mRumble) {
        if (auto* device = gamepad(mController)) {
            SDL_RumbleGamepad(device, 0, 0, 0);
        }
        PADControlMotor(0, PAD_MOTOR_STOP_HARD);
        mRumble = false;
    }
}

void ControllerConfigWindow::hide(bool close) {
    stop_rumble();
    if (mBindings != nullptr) {
        mBindings->cancel_capture();
    }
    Window::hide(close);
}

void ControllerConfigWindow::update() {
    const auto current = aurora::pad::port_controller(0);
    const auto sources = controllers();
    if (current != mController || sources != mSources) {
        stop_rumble();
        mController = current;
        mSources = sources;
        refresh_active_tab();
    }
    Window::update();
}

void ControllerConfigWindow::build_device(Rml::Element* content) {
    mBindings = nullptr;
    auto& devices = add_child<Pane>(content, Pane::Type::Uncontrolled);
    auto& options = add_child<Pane>(content, Pane::Type::Uncontrolled);
    devices.add_section(tr("controller.section.controller"));
    devices
        .add_button(ControlledButton::Props{
            .text = tr("controller.device.automatic"),
            .isSelected = [] { return !aurora::pad::port_controller(0) && controller_ports::auto_assign(); } })
        .on_pressed([] { controller_ports::select_automatic(); });
    if (SDL_HasKeyboard()) {
        devices
            .add_button(ControlledButton::Props{
                .text = tr("controller.device.none"),
                .isSelected = [] { return !aurora::pad::port_controller(0) && !controller_ports::auto_assign(); } })
            .on_pressed([] { controller_ports::select_none(); });
    }
    for (auto source : controllers()) {
        const auto identity = aurora::pad::controller_identity(source);
        devices
            .add_button(
                ControlledButton::Props{ .text = identity ? identity->name : tr("common.unknown"),
                                         .isSelected = [source] { return aurora::pad::port_controller(0) == source; } })
            .on_pressed([source] { controller_ports::select_controller(source); });
    }
    devices.add_text(tr("controller.device.automatic_help"));
    if (SDL_HasKeyboard()) {
        devices.add_text(tr("controller.device.keyboard_help"));
    }

    options.add_section(tr("controller.page.sticks"));
    const auto deadzone = [&](const char* label, auto& setting) {
        options.add_child<NumberButton>(bind(setting, {
                                                          .key = tr(label),
                                                          .suffix = "%",
                                                      }));
    };
    deadzone("controller.section.control_stick", settings().input.stickDeadzone);
    deadzone("controller.section.c_stick", settings().input.cstickDeadzone);
    if (!mController) {
        return;
    }
    const auto target = ProfileTarget::controller(mController);
    options.add_section(tr("controller.section.trigger_thresholds"));
    options.add_child<BoolButton>(BoolButton::Props{ .key = tr("controller.options.emulate_triggers"),
                                                     .getValue =
                                                         [target] {
                                                             const auto* p = aurora::pad::profile(target);
                                                             return p && p->settings.emulateTriggers;
                                                         },
                                                     .setValue =
                                                         [target](bool value) {
                                                             if (const auto* p = aurora::pad::profile(target)) {
                                                                 auto settings = p->settings;
                                                                 settings.emulateTriggers = value;
                                                                 if (aurora::pad::set_settings(target, settings)) {
                                                                     save_or_explain();
                                                                 }
                                                             }
                                                         } });
    add_profile_percent(options, target, "controller.trigger.left_threshold", &ProfileSettings::leftTriggerThreshold);
    add_profile_percent(options, target, "controller.trigger.right_threshold", &ProfileSettings::rightTriggerThreshold);
    options.add_section(tr("controller.page.rumble"));
    add_profile_percent(options, target, "controller.rumble.low_frequency", &ProfileSettings::rumbleIntensityLow);
    add_profile_percent(options, target, "controller.rumble.high_frequency", &ProfileSettings::rumbleIntensityHigh);
    options.add_child<BoolButton>(BoolButton::Props{ .key = tr("controller.rumble.use_device_haptics"),
                                                     .getValue =
                                                         [target] {
                                                             const auto* p = aurora::pad::profile(target);
                                                             return p && p->settings.forceDeviceRumble;
                                                         },
                                                     .setValue =
                                                         [target](bool value) {
                                                             if (const auto* p = aurora::pad::profile(target)) {
                                                                 auto settings = p->settings;
                                                                 settings.forceDeviceRumble = value;
                                                                 if (aurora::pad::set_settings(target, settings)) {
                                                                     save_or_explain();
                                                                 }
                                                             }
                                                         } });
    options.add_button(tr("controller.rumble.test")).on_pressed([this] {
        stop_rumble();
        PADControlMotor(0, PAD_MOTOR_RUMBLE);
        mRumble = true;
    });
    options.add_button(tr("common.stop")).on_pressed([this] { stop_rumble(); });
}

void ControllerConfigWindow::build_bindings(Rml::Element* content, bool keyboard) {
    mBindings = nullptr;
    auto& categories = add_child<Pane>(content, Pane::Type::Controlled);
    if (!keyboard && !mController) {
        auto& details = add_child<Pane>(content, Pane::Type::Uncontrolled);
        categories.add_section(tr("controller.section.controller"));
        details.add_text(tr("controller.device.none_selected"));
        return;
    }
    const auto target = keyboard ? ProfileTarget::keyboard(0) : ProfileTarget::controller(mController);
    auto& bindings = add_child<BindingsPane>(content, target, mAllowConflicts);
    mBindings = &bindings;
    const char* groups[] = { "controller.page.buttons", "controller.section.dpad", "controller.section.analog",
                             "controller.section.control_stick", "controller.section.c_stick" };
    for (int group = 0; group < 5; ++group) {
        categories.register_control(categories.add_group_button({ .text = tr(groups[group]) }), bindings,
                                    [&bindings, group](Pane&) { bindings.show_group(group); });
    }
    categories.add_section(tr("controller.options.section"));
    categories.add_child<BoolButton>(BoolButton::Props{
        .key = tr("controller.binding.allow_conflicts"),
        .getValue = [this] { return mAllowConflicts; },
        .setValue = [this](bool value) { mAllowConflicts = value; },
    });
    categories.add_button(tr("controller.options.restore_defaults")).on_pressed([&bindings] {
        bindings.restore_defaults();
    });
    bindings.show_group(0);
}
} // namespace acgc::ui
