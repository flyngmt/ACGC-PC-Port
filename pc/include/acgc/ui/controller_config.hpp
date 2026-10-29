#pragma once
#include <borealis/ui/window.hpp>
#include <aurora/pad.hpp>

namespace acgc::ui {
class BindingsPane;
class ControllerConfigWindow : public borealis::ui::Window {
public:
    ControllerConfigWindow();
    ~ControllerConfigWindow() override;
    void update() override;
    void hide(bool close) override;

private:
    void build_device(Rml::Element* content);
    void build_bindings(Rml::Element* content, bool keyboard);
    void stop_rumble();
    aurora::input::SourceId mController = 0;
    std::vector<aurora::input::SourceId> mSources;
    bool mRumble = false;
    bool mAllowConflicts = false;
    BindingsPane* mBindings = nullptr;
};
} // namespace acgc::ui
