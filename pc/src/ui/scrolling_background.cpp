#include "acgc/ui/scrolling_background.hpp"

#include <RmlUi/Core.h>

#include <algorithm>
#include <cmath>
#include <utility>

namespace acgc::ui {
using namespace borealis::ui;

namespace {

// Keep this synchronized with the tile dimensions in scrolling_background.rcss.
constexpr float BackgroundTileSizeDp = 512.0f;

} // namespace

ScrollingBackground::ScrollingBackground(Rml::Element* root, std::string texturePath)
    : Component(root), mTexturePath(std::move(texturePath)) {
}

std::unique_ptr<Component> scrolling_background(Rml::Element* root) {
    auto* pattern = append(root, "scrolling-pattern");
    return std::make_unique<ScrollingBackground>(pattern);
}

void ScrollingBackground::update() {
    update(mRoot ? mRoot->GetContext() : nullptr);
}

void ScrollingBackground::update(Rml::Context* context) {
    if (mRoot == nullptr || context == nullptr) {
        return;
    }

    const auto dimensions = context->GetDimensions();
    const float dpRatio = std::max(context->GetDensityIndependentPixelRatio(), 0.01f);
    const float widthDp = static_cast<float>(dimensions.x) / dpRatio;
    const float heightDp = static_cast<float>(dimensions.y) / dpRatio;
    const int columns = std::max(1, static_cast<int>(std::ceil(widthDp / BackgroundTileSizeDp)) + 2);
    const int rows = std::max(1, static_cast<int>(std::ceil(heightDp / BackgroundTileSizeDp)) + 2);

    if (columns == mColumns && rows == mRows) {
        return;
    }

    Rml::String tile = "<pattern-tile><img class=\"scrolling-texture\" src=\"";
    tile += mTexturePath;
    tile += "\" /></pattern-tile>";

    Rml::String pattern;
    pattern.reserve(static_cast<std::size_t>(rows * (columns * tile.size() + 31)));
    for (int row = 0; row < rows; ++row) {
        pattern += "<pattern-row>";
        for (int column = 0; column < columns; ++column) {
            pattern += tile;
        }
        pattern += "</pattern-row>";
    }

    mRoot->SetInnerRML(pattern);
    mColumns = columns;
    mRows = rows;
}

void ScrollingBackground::set_texture(std::string texturePath) {
    if (texturePath == mTexturePath) {
        return;
    }

    mTexturePath = std::move(texturePath);
    mColumns = 0;
    mRows = 0;
}

} // namespace acgc::ui
