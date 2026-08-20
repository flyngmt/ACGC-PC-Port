#pragma once

#include <string>

namespace Rml {
class Context;
class Element;
}

namespace acgc::ui {

class ScrollingBackground {
public:
	explicit ScrollingBackground(
	    Rml::Element* root = nullptr,
	    std::string texturePath = "res/backgrounds/scrolling_texture.png");

	void update(Rml::Context* context);
	void set_texture(std::string texturePath);

private:
	Rml::Element* mRoot = nullptr;
	std::string mTexturePath;
	int mColumns = 0;
	int mRows = 0;
};

} // namespace acgc::ui
