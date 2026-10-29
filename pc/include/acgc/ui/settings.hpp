#pragma once

#include <borealis/ui/window.hpp>

namespace acgc::ui {

class SettingsWindow final : public borealis::ui::Window {
public:
    SettingsWindow();
    void hide(bool close) override;
};

} // namespace acgc::ui
