#pragma once

#include <string>
#include <borealis/ui/component.hpp>

namespace Rml {
class Context;
class Element;
}

namespace acgc::ui {

class ScrollingBackground : public borealis::ui::Component {
public:
	explicit ScrollingBackground(
	    Rml::Element* root = nullptr,
	    std::string texturePath = "res/backgrounds/scrolling_texture.png");

	void update() override;
	void update(Rml::Context* context);
	void set_texture(std::string texturePath);

private:
	std::string mTexturePath;
	int mColumns = 0;
	int mRows = 0;
};

std::unique_ptr<borealis::ui::Component> scrolling_background(Rml::Element* root);

} // namespace acgc::ui
