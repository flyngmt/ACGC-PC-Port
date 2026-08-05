#pragma once

#include "acgc/disc.hpp"
#include "button.hpp"
#include "document.hpp"

#include <memory>
#include <string>
#include <vector>

namespace acgc::ui {

class Prelaunch final : public Document {
public:
    Prelaunch();

    void show() override;
    void hide(bool close) override;
    void update() override;
    bool focus() override;
    bool visible() const override;
    bool obscures_game() const override { return true; }

protected:
    bool handle_nav_command(Rml::Event& event, NavCommand cmd) override;

private:
    bool mEntranceAnimationStarted = false;
    std::vector<std::unique_ptr<Button>> mMenuButtons;
    Rml::Element* mRoot = nullptr;
    Rml::Element* mDiscStatus = nullptr;
    Rml::Element* mDiscDetail = nullptr;
    Rml::Element* mVersion = nullptr;
    Rml::Element* mUpdateStatus = nullptr;
    Rml::Element* mUpdateMessage = nullptr;
    Rml::Element* mUpdateDownload = nullptr;
    Rml::Element* mUpdateDownloadLabel = nullptr;
};

struct PrelaunchState {
    bool initialized = false;
    std::string configuredDiscPath;
    bool configuredDiscCanLaunch = false;
    disc::DiscInfo configuredDiscInfo{};
    disc::ValidationError configuredDiscValidation = disc::ValidationError::Unknown;
    std::string activeDiscPath;
    disc::DiscInfo activeDiscInfo{};
    bool launchRequested = false;
    bool quitRequested = false;
    std::string errorString;
    std::string pendingDiscPath;
    disc::DiscInfo pendingDiscInfo{};
    disc::ValidationError pendingDiscValidation = disc::ValidationError::Unknown;
};

PrelaunchState& prelaunch_state() noexcept;
void ensure_prelaunch_initialized() noexcept;
void refresh_configured_disc_state() noexcept;
void open_disc_picker() noexcept;
void try_push_verification_modal(Document& host);

} // namespace acgc::ui
