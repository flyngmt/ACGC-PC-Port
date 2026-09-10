#include "select_button.hpp"

#include "ui.hpp"

#include <utility>

namespace acgc::ui {
namespace {

Rml::Element* createRoot(Rml::Element* parent)
{
	auto* doc = parent->GetOwnerDocument();
	auto elem = doc->CreateElement("select-button");
	return parent->AppendChild(std::move(elem));
}

} // namespace

SelectButton::SelectButton(Rml::Element* parent, Props props)
    : FluentComponent(createRoot(parent))
{
	mKeyElem        = append(mRoot, "key");
	mIconElem       = append(mRoot, "icon");
	mValueElem      = append(mRoot, "value");
	mValueLabelElem = mValueElem;
	update_props(std::move(props));
	on_nav_command([this](Rml::Event&, NavCommand cmd) { return handle_nav_command(cmd); });
}

bool SelectButton::modified() const
{
	return mProps.modified;
}

void SelectButton::set_adjustable()
{
	if (mLeftArrowElem != nullptr) {
		return;
	}
	mRoot->SetClass("adjustable", true);
	mValueElem->SetInnerRML("");
	auto add_arrow = [this](NavCommand cmd, const char* glyph) {
		auto* arrow = append(mValueElem, "span");
		arrow->SetClass("adjust-arrow", true);
		arrow->SetInnerRML(glyph);
		Component::listen(arrow, Rml::EventId::Click, [this, arrow, cmd](Rml::Event& event) {
			if (!disabled() && !arrow->IsClassSet("unavailable")) {
				handle_nav_command(cmd);
			}
			event.StopPropagation();
		});
		return arrow;
	};
	// Arrow_left and arrow_right
	mLeftArrowElem  = add_arrow(NavCommand::Left, "&#xe5de;");
	mValueLabelElem = append(mValueElem, "span");
	mValueLabelElem->SetClass("value-label", true);
	mRightArrowElem = add_arrow(NavCommand::Right, "&#xe5df;");
	update_value_label();
}

void SelectButton::set_adjustment_enabled(bool left, bool right)
{
	mLeftArrowElem->SetClass("unavailable", !left);
	mRightArrowElem->SetClass("unavailable", !right);
}

void SelectButton::update_value_label()
{
	mValueLabelElem->SetInnerRML(escape(mProps.value));
}

void SelectButton::set_modified(bool value)
{
	if (mProps.modified != value) {
		mValueElem->SetClass("modified", value);
		mProps.modified = value;
	}
}

void SelectButton::set_value_label(const Rml::String& value)
{
	if (mProps.value != value) {
		mProps.value = value;
		update_value_label();
	}
}

SelectButton& SelectButton::on_pressed(SelectButtonCallback callback)
{
	if (!callback) {
		return *this;
	}
	listen(Rml::EventId::Submit, [this, callback = std::move(callback)](Rml::Event& event) {
		if (!disabled() && event.GetTargetElement() == mRoot) {
			callback();
			event.StopPropagation();
		}
	});
	return *this;
}

void SelectButton::update_props(Props props)
{
	if (mProps.key != props.key) {
		mKeyElem->SetInnerRML(escape(props.key));
	}
	if (mProps.icon != props.icon) {
		Rml::StringList iconClasses;
		Rml::StringUtilities::ExpandString(iconClasses, mIconElem->GetClassNames(), ' ', true);
		for (const auto& className : iconClasses) {
			mIconElem->SetClass(className, false);
		}
		if (!props.icon.empty()) {
			mIconElem->SetClass(props.icon, true);
		}
	}
	set_value_label(props.value);
	set_modified(props.modified);
	mProps = std::move(props);
}

bool SelectButton::handle_nav_command(NavCommand cmd)
{
	if (cmd == NavCommand::Confirm && mProps.submit) {
		mRoot->DispatchEvent(Rml::EventId::Submit, { });
		return true;
	}
	return false;
}

void BaseControlledSelectButton::update()
{
	set_disabled(disabled());
	set_value_label(format_value());
	set_modified(modified());
	SelectButton::update();
}

bool ControlledSelectButton::modified() const
{
	if (mIsModified) {
		return mIsModified();
	}
	return BaseControlledSelectButton::modified();
}

bool ControlledSelectButton::disabled() const
{
	if (mIsDisabled) {
		return mIsDisabled();
	}
	return BaseControlledSelectButton::disabled();
}

Rml::String ControlledSelectButton::format_value()
{
	if (!mGetValue) {
		return "";
	}
	return mGetValue();
}

} // namespace acgc::ui
