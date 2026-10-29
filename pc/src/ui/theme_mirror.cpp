#include "acgc/ui/theme_mirror.hpp"

#include <RmlUi/Core/ComputedValues.h>
#include <RmlUi/Core/Context.h>
#include <RmlUi/Core/ElementDocument.h>
#include <RmlUi/Core/ElementText.h>
#include <RmlUi/Core/Elements/ElementFormControlSelect.h>
#include <RmlUi/Core/StyleSheetContainer.h>

#include <algorithm>
#include <vector>

namespace acgc::ui::theme {
namespace {

bool mirror_owned(Rml::PropertyId id, bool root)
{
	if (id == Rml::PropertyId::Animation || id == Rml::PropertyId::Focus || id == Rml::PropertyId::TabIndex) {
		return true;
	}
	return root
	    && (id == Rml::PropertyId::PointerEvents || id == Rml::PropertyId::MaskImage || id == Rml::PropertyId::Color);
}

bool transitioned(Rml::Element& element, Rml::PropertyId id)
{
	const Rml::TransitionList* transitions = element.GetComputedValues().transition();
	if (transitions == nullptr || transitions->none) {
		return false;
	}
	return transitions->all
	    || std::ranges::any_of(transitions->transitions, [id](const Rml::Transition& transition) {
		       return transition.id == id;
	       });
}

bool palette_dependent(const Rml::Property& property)
{
	return property.unit == Rml::Unit::COLOUR;
}

bool skipped_attribute(const Rml::String& name, bool deferOpen)
{
	return name == "style" || name == "class" || (deferOpen && name == "open");
}

void make_inert(Rml::Element& element)
{
	element.SetProperty("animation", "none");
	element.SetProperty("focus", "none");
	element.SetProperty("tab-index", "none");
}

void sync_attributes(Rml::Element& source, Rml::Element& mirror, bool deferOpen)
{
	Rml::ElementAttributes changed;
	for (const auto& [name, value] : source.GetAttributes()) {
		const Rml::Variant* current = mirror.GetAttribute(name);
		if (!skipped_attribute(name, deferOpen) && (current == nullptr || !(*current == value))) {
			changed[name] = value;
		}
	}
	if (!changed.empty()) {
		mirror.SetAttributes(changed);
	}

	std::vector<Rml::String> removed;
	for (const auto& [name, value] : mirror.GetAttributes()) {
		if (!skipped_attribute(name, deferOpen) && source.GetAttribute(name) == nullptr) {
			removed.push_back(name);
		}
	}
	for (const auto& name : removed) {
		mirror.RemoveAttribute(name);
	}
}

void sync_style(Rml::Element& source, Rml::Element& mirror, bool root)
{
	const auto copied = [&source, root](Rml::PropertyId id) {
		return !mirror_owned(id, root) && !transitioned(source, id);
	};

	const Rml::PropertyMap& wanted = source.GetLocalStyleProperties();
	for (const auto& [id, property] : wanted) {
		const Rml::Property* current = mirror.GetLocalProperty(id);
		if (copied(id) && !palette_dependent(property) && (current == nullptr || !(*current == property))) {
			mirror.SetProperty(id, property);
		}
	}

	std::vector<Rml::PropertyId> removed;
	for (const auto& [id, property] : mirror.GetLocalStyleProperties()) {
		const auto found = wanted.find(id);
		if (copied(id) && (found == wanted.end() || palette_dependent(found->second))) {
			removed.push_back(id);
		}
	}
	for (const auto id : removed) {
		mirror.RemoveProperty(id);
	}
}

void sync_state(Rml::Element& source, Rml::Element& mirror)
{
	const Rml::StringList active = source.GetActivePseudoClasses();
	for (const Rml::String& pseudoClass : mirror.GetActivePseudoClasses()) {
		if (std::ranges::find(active, pseudoClass) == active.end()) {
			mirror.SetPseudoClass(pseudoClass, false);
		}
	}
	for (const Rml::String& pseudoClass : active) {
		if (!mirror.IsPseudoClassSet(pseudoClass)) {
			mirror.SetPseudoClass(pseudoClass, true);
		}
	}
	if (mirror.GetScrollTop() != source.GetScrollTop()) {
		mirror.SetScrollTop(source.GetScrollTop());
	}
	if (mirror.GetScrollLeft() != source.GetScrollLeft()) {
		mirror.SetScrollLeft(source.GetScrollLeft());
	}
}

const Rml::String* option_text(Rml::Element& option)
{
	if (option.GetNumChildren() != 1) {
		return nullptr;
	}
	const auto* text = rmlui_dynamic_cast<Rml::ElementText*>(option.GetFirstChild());
	return text != nullptr ? &text->GetText() : nullptr;
}

bool same_value(Rml::Element& source, Rml::Element& mirror)
{
	const Rml::Variant* wanted  = source.GetAttribute("value");
	const Rml::Variant* current = mirror.GetAttribute("value");
	return wanted == nullptr || current == nullptr ? wanted == current : *wanted == *current;
}

bool same_option(Rml::Element& source, Rml::Element& mirror)
{
	if (!same_value(source, mirror)) {
		return false;
	}
	const Rml::String* sourceText = option_text(source);
	const Rml::String* mirrorText = option_text(mirror);
	if (sourceText != nullptr && mirrorText != nullptr) {
		return *sourceText == *mirrorText;
	}
	return source.GetInnerRML() == mirror.GetInnerRML();
}

void sync_select(Rml::ElementFormControlSelect& source, Rml::ElementFormControlSelect& mirror)
{
	const int count = source.GetNumOptions();
	bool matches    = mirror.GetNumOptions() == count;
	for (int i = 0; matches && i < count; ++i) {
		matches = same_option(*source.GetOption(i), *mirror.GetOption(i));
	}
	if (!matches) {
		mirror.RemoveAll();
		for (int i = 0; i < count; ++i) {
			Rml::Element* option = source.GetOption(i);
			mirror.Add(option->GetInnerRML(), option->GetAttribute<Rml::String>("value", ""));
		}
	}
	if (mirror.GetSelection() != source.GetSelection()) {
		mirror.SetSelection(source.GetSelection());
	}
	if (mirror.IsSelectBoxVisible() != source.IsSelectBoxVisible()) {
		if (source.IsSelectBoxVisible()) {
			mirror.ShowSelectBox();
		} else {
			mirror.HideSelectBox();
		}
	}
	for (int i = 0; i < count; ++i) {
		sync_state(*source.GetOption(i), *mirror.GetOption(i));
	}
	if (count > 0) {
		sync_state(*source.GetOption(0)->GetParentNode(), *mirror.GetOption(0)->GetParentNode());
	}
}

} // namespace

DocumentSweep::DocumentSweep(Rml::Context& context, Rml::ElementDocument& source, bool justOpened)
    : mSource(&source)
    , mDocument(context.CreateDocument())
    , mDeferOpen(justOpened)
{
	if (mDocument == nullptr) {
		return;
	}
	make_inert(*mDocument);
	mDocument->SetProperty("pointer-events", "none");
	mDocument->SetProperty("color", "var(--color-text)");
	mDocument->Show(Rml::ModalFlag::None, Rml::FocusFlag::None);
}

DocumentSweep::~DocumentSweep()
{
	if (mDocument != nullptr) {
		mDocument->Close();
	}
	if (mSourceAlive) {
		mSource->RemoveProperty(Rml::PropertyId::MaskImage);
	}
}

void DocumentSweep::context_destroyed() noexcept
{
	mSourceAlive = false;
	mDocument    = nullptr;
}

void DocumentSweep::sync()
{
	if (mDocument == nullptr) {
		return;
	}
	const Rml::StyleSheetContainer* sheets = mSource->GetStyleSheetContainer();
	if (sheets != mStyleSheetSource) {
		mStyleSheetSource = sheets;
		mDocument->SetStyleSheetContainer(
		    sheets != nullptr ? sheets->CombineStyleSheetContainer(Rml::StyleSheetContainer { }) : nullptr);
	}
	sync_element(*mSource, *mDocument, true);
	if (mRebuilt) {
		mRebuilt = false;
		mDocument->UpdateDocument();
		sync_element(*mSource, *mDocument, true);
	}
	mDeferOpen = false;
}

void DocumentSweep::set_masks(const Rml::String& source, const Rml::String& copy)
{
	if (mDocument == nullptr) {
		return;
	}
	mSource->SetProperty("mask-image", source);
	mDocument->SetProperty("mask-image", copy);
}

Rml::ElementPtr DocumentSweep::create(Rml::Element& source)
{
	if (auto* text = rmlui_dynamic_cast<Rml::ElementText*>(&source)) {
		return mDocument->CreateTextNode(text->GetText());
	}
	Rml::ElementPtr element = mDocument->CreateElement(source.GetTagName());
	make_inert(*element);
	return element;
}

void DocumentSweep::sync_element(Rml::Element& source, Rml::Element& mirror, bool root)
{
	if (auto* text = rmlui_dynamic_cast<Rml::ElementText*>(&source)) {
		auto* mirrorText = rmlui_static_cast<Rml::ElementText*>(&mirror);
		if (mirrorText->GetText() != text->GetText()) {
			mirrorText->SetText(text->GetText());
		}
		return;
	}

	sync_attributes(source, mirror, mDeferOpen);
	const Rml::String classes = source.GetClassNames();
	if (mirror.GetClassNames() != classes) {
		mirror.SetClassNames(classes);
	}
	sync_style(source, mirror, root);
	sync_state(source, mirror);
	auto* sourceSelect = rmlui_dynamic_cast<Rml::ElementFormControlSelect*>(&source);
	auto* mirrorSelect = rmlui_dynamic_cast<Rml::ElementFormControlSelect*>(&mirror);
	if (sourceSelect != nullptr && mirrorSelect != nullptr) {
		sync_select(*sourceSelect, *mirrorSelect);
	}
	sync_children(source, mirror);
}

void DocumentSweep::sync_children(Rml::Element& source, Rml::Element& mirror)
{
	const int count = source.GetNumChildren();
	bool matches    = mirror.GetNumChildren() == count;
	for (int i = 0; matches && i < count; ++i) {
		matches = mirror.GetChild(i)->GetTagName() == source.GetChild(i)->GetTagName();
	}
	if (!matches) {
		while (mirror.GetNumChildren() > 0) {
			mirror.RemoveChild(mirror.GetFirstChild());
		}
		for (int i = 0; i < count; ++i) {
			mirror.AppendChild(create(*source.GetChild(i)));
		}
		mRebuilt = true;
	}
	for (int i = 0; i < count; ++i) {
		sync_element(*source.GetChild(i), *mirror.GetChild(i), false);
	}
}

} // namespace acgc::ui::theme
