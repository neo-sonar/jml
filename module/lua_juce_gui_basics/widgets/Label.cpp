namespace lua_juce {
auto juce_Label(sol::table& state) -> void
{
    // clang-format off
    auto label = state.new_usertype<juce::Label>("Label",
        sol::constructors<juce::Label(juce::String const&, juce::String const&)>(),
        sol::base_classes,
        sol::bases<
            juce::MouseListener,
            juce::Component,
            juce::TooltipClient,
            juce::SettableTooltipClient
        >()
    );
    // clang-format on

    label["setText"]                       = LUA_JUCE_C_CALL(&juce::Label::setText);
    label["getText"]                       = LUA_JUCE_C_CALL(&juce::Label::getText);
    label["getTextValue"]                  = LUA_JUCE_C_CALL(&juce::Label::getTextValue);
    label["setFont"]                       = LUA_JUCE_C_CALL(&juce::Label::setFont);
    label["getFont"]                       = LUA_JUCE_C_CALL(&juce::Label::getFont);
    label["setJustificationType"]          = LUA_JUCE_C_CALL(&juce::Label::setJustificationType);
    label["getJustificationType"]          = LUA_JUCE_C_CALL(&juce::Label::getJustificationType);
    label["setBorderSize"]                 = LUA_JUCE_C_CALL(&juce::Label::setBorderSize);
    label["getBorderSize"]                 = LUA_JUCE_C_CALL(&juce::Label::getBorderSize);
    label["attachToComponent"]             = LUA_JUCE_C_CALL(&juce::Label::attachToComponent);
    label["getAttachedComponent"]          = LUA_JUCE_C_CALL(&juce::Label::getAttachedComponent);
    label["isAttachedOnLeft"]              = LUA_JUCE_C_CALL(&juce::Label::isAttachedOnLeft);
    label["setMinimumHorizontalScale"]     = LUA_JUCE_C_CALL(&juce::Label::setMinimumHorizontalScale);
    label["getMinimumHorizontalScale"]     = LUA_JUCE_C_CALL(&juce::Label::getMinimumHorizontalScale);
    label["setKeyboardType"]               = LUA_JUCE_C_CALL(&juce::Label::setKeyboardType);
    label["addListener"]                   = LUA_JUCE_C_CALL(&juce::Label::addListener);
    label["removeListener"]                = LUA_JUCE_C_CALL(&juce::Label::removeListener);
    label["setEditable"]                   = LUA_JUCE_C_CALL(&juce::Label::setEditable);
    label["isEditableOnSingleClick"]       = LUA_JUCE_C_CALL(&juce::Label::isEditableOnSingleClick);
    label["isEditableOnDoubleClick"]       = LUA_JUCE_C_CALL(&juce::Label::isEditableOnDoubleClick);
    label["doesLossOfFocusDiscardChanges"] = LUA_JUCE_C_CALL(&juce::Label::doesLossOfFocusDiscardChanges);
    label["isEditable"]                    = LUA_JUCE_C_CALL(&juce::Label::isEditable);
    label["showEditor"]                    = LUA_JUCE_C_CALL(&juce::Label::showEditor);
    label["hideEditor"]                    = LUA_JUCE_C_CALL(&juce::Label::hideEditor);
    label["isBeingEdited"]                 = LUA_JUCE_C_CALL(&juce::Label::isBeingEdited);
    label["getCurrentTextEditor"]          = LUA_JUCE_C_CALL(&juce::Label::getCurrentTextEditor);
}
} // namespace lua_juce
