#pragma once

#include "acgc/ui/touch_controls.hpp"

#include <borealis/ui/document.hpp>

#include <SDL3/SDL_touch.h>

#include <array>
#include <cstddef>
#include <cstdint>

namespace acgc::ui {

class TouchControlsEditor final : public borealis::ui::Document {
public:
    TouchControlsEditor();

    void show() override;
    void hide(bool close) override;
    void update() override;
    bool focus() override;

protected:
    bool handle_nav_command(Rml::Event& event, borealis::ui::NavCommand cmd) override;

private:
    enum class Handle {
        Move,
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight,
    };

    struct Edit {
        size_t index = 0;
        SDL_FingerID finger = 0;
        Rml::Vector2f startPointer;
        TouchRect startVisual;
        TouchPlacement startPlacement;
        Handle handle = Handle::Move;
        bool active = false;
        bool touch = false;
        bool dragging = false;
    };

    bool begin_edit(size_t index, Handle handle, Rml::Vector2f position, bool touch, SDL_FingerID finger);
    bool continue_edit(Rml::Vector2f position);
    bool end_edit(bool touch, SDL_FingerID finger, bool cancelled);
    void select(size_t index);
    void sync_selection();
    Rml::Vector2f area_position(Rml::Vector2f position) const;
    TouchRect edited_rect(Rml::Vector2f pointer, float& scale) const;
    void activate(size_t command);
    void save();
    void reset_layout();
    void cancel();

    Rml::Element* mArea = nullptr;
    Rml::Element* mSelection = nullptr;
    std::array<Rml::Element*, 3> mCommands{};
    TouchLayoutView mLayout;
    TouchLayout mWorking;
    TouchLayout mBeforeEdit;
    borealis::ui::Insets mInsets;
    Edit mEdit;
    size_t mSelected = SIZE_MAX;
    size_t mFocusedCommand = 0;
};

} // namespace acgc::ui
