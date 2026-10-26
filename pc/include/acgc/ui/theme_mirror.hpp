#pragma once

#include <RmlUi/Core/Types.h>

namespace Rml {
class Context;
class Element;
class ElementDocument;
class StyleSheetContainer;
} // namespace Rml

namespace acgc::ui::theme {

class DocumentSweep {
public:
	DocumentSweep(Rml::Context& context, Rml::ElementDocument& source, bool justOpened);
	~DocumentSweep();

	DocumentSweep(const DocumentSweep&)            = delete;
	DocumentSweep& operator=(const DocumentSweep&) = delete;

	Rml::ElementDocument* source() const noexcept { return mSource; }
	Rml::ElementDocument* document() const noexcept { return mDocument; }
	void source_destroyed() noexcept { mSourceAlive = false; }
	void context_destroyed() noexcept;
	void sync();
	void set_masks(const Rml::String& source, const Rml::String& copy);

private:
	Rml::ElementPtr create(Rml::Element& source);
	void sync_element(Rml::Element& source, Rml::Element& mirror, bool root);
	void sync_children(Rml::Element& source, Rml::Element& mirror);

	Rml::ElementDocument* mSource;
	Rml::ElementDocument* mDocument;
	const Rml::StyleSheetContainer* mStyleSheetSource = nullptr;
	bool mDeferOpen;
	bool mRebuilt     = false;
	bool mSourceAlive = true;
};

} // namespace acgc::ui::theme
