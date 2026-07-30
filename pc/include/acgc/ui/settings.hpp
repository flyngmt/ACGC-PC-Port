#pragma once

#include "window.hpp"

namespace acgc::ui {

class SettingsWindow final : public Window {
public:
    SettingsWindow();
    void hide(bool close) override;
};

} // namespace acgc::ui
