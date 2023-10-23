namespace lua_juce {
auto juce_ComboBox(sol::table& state) -> void
{
    // clang-format off
    state.new_enum("ComboBoxColourIds",
        "arrowColourId",            juce::ComboBox::ColourIds::arrowColourId,
        "backgroundColourId",       juce::ComboBox::ColourIds::backgroundColourId,
        "buttonColourId",           juce::ComboBox::ColourIds::buttonColourId,
        "focusedOutlineColourId",   juce::ComboBox::ColourIds::focusedOutlineColourId,
        "outlineColourId",          juce::ComboBox::ColourIds::outlineColourId,
        "textColourId",             juce::ComboBox::ColourIds::textColourId
    );

    auto combo = state.new_usertype<juce::ComboBox>("ComboBox",
        sol::constructors<juce::ComboBox(juce::String const&)>(),
        sol::base_classes,
        sol::bases<
            juce::MouseListener,
            juce::Component,
            juce::TooltipClient,
            juce::SettableTooltipClient,
            juce::Value::Listener
        >()
    );
    // clang-format on

    // combo["getRootMenu"]                   = &juce::ComboBox::getRootMenu;
    // combo["getRootMenu"]                   = &juce::ComboBox::getRootMenu;
    // combo["clear"]                         = &juce::ComboBox::clear;
    // combo["setSelectedId"]                 = &juce::ComboBox::setSelectedId;
    // combo["setSelectedItemIndex"]          = &juce::ComboBox::setSelectedItemIndex;
    // combo["setText"]                       = &juce::ComboBox::setText;

    combo["setEditableText"]               = LUA_JUCE_C_CALL(&juce::ComboBox::setEditableText);
    combo["isTextEditable"]                = LUA_JUCE_C_CALL(&juce::ComboBox::isTextEditable);
    combo["setJustificationType"]          = LUA_JUCE_C_CALL(&juce::ComboBox::setJustificationType);
    combo["getJustificationType"]          = LUA_JUCE_C_CALL(&juce::ComboBox::getJustificationType);
    combo["addItem"]                       = LUA_JUCE_C_CALL(&juce::ComboBox::addItem);
    combo["addItemList"]                   = LUA_JUCE_C_CALL(&juce::ComboBox::addItemList);
    combo["addSeparator"]                  = LUA_JUCE_C_CALL(&juce::ComboBox::addSeparator);
    combo["addSectionHeading"]             = LUA_JUCE_C_CALL(&juce::ComboBox::addSectionHeading);
    combo["setItemEnabled"]                = LUA_JUCE_C_CALL(&juce::ComboBox::setItemEnabled);
    combo["isItemEnabled"]                 = LUA_JUCE_C_CALL(&juce::ComboBox::isItemEnabled);
    combo["changeItemText"]                = LUA_JUCE_C_CALL(&juce::ComboBox::changeItemText);
    combo["getNumItems"]                   = LUA_JUCE_C_CALL(&juce::ComboBox::getNumItems);
    combo["getItemText"]                   = LUA_JUCE_C_CALL(&juce::ComboBox::getItemText);
    combo["getItemId"]                     = LUA_JUCE_C_CALL(&juce::ComboBox::getItemId);
    combo["indexOfItemId"]                 = LUA_JUCE_C_CALL(&juce::ComboBox::indexOfItemId);
    combo["getSelectedId"]                 = LUA_JUCE_C_CALL(&juce::ComboBox::getSelectedId);
    combo["getSelectedIdAsValue"]          = LUA_JUCE_C_CALL(&juce::ComboBox::getSelectedIdAsValue);
    combo["getSelectedItemIndex"]          = LUA_JUCE_C_CALL(&juce::ComboBox::getSelectedItemIndex);
    combo["getText"]                       = LUA_JUCE_C_CALL(&juce::ComboBox::getText);
    combo["showEditor"]                    = LUA_JUCE_C_CALL(&juce::ComboBox::showEditor);
    combo["showPopup"]                     = LUA_JUCE_C_CALL(&juce::ComboBox::showPopup);
    combo["hidePopup"]                     = LUA_JUCE_C_CALL(&juce::ComboBox::hidePopup);
    combo["isPopupActive"]                 = LUA_JUCE_C_CALL(&juce::ComboBox::isPopupActive);
    combo["addListener"]                   = LUA_JUCE_C_CALL(&juce::ComboBox::addListener);
    combo["removeListener"]                = LUA_JUCE_C_CALL(&juce::ComboBox::removeListener);
    combo["setTextWhenNothingSelected"]    = LUA_JUCE_C_CALL(&juce::ComboBox::setTextWhenNothingSelected);
    combo["getTextWhenNothingSelected"]    = LUA_JUCE_C_CALL(&juce::ComboBox::getTextWhenNothingSelected);
    combo["setTextWhenNoChoicesAvailable"] = LUA_JUCE_C_CALL(&juce::ComboBox::setTextWhenNoChoicesAvailable);
    combo["getTextWhenNoChoicesAvailable"] = LUA_JUCE_C_CALL(&juce::ComboBox::getTextWhenNoChoicesAvailable);
    combo["setTooltip"]                    = LUA_JUCE_C_CALL(&juce::ComboBox::setTooltip);
    combo["setScrollWheelEnabled"]         = LUA_JUCE_C_CALL(&juce::ComboBox::setScrollWheelEnabled);
    combo["onChange"]                      = &juce::ComboBox::onChange;
}
} // namespace lua_juce
