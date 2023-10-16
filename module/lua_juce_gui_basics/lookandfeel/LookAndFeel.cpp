namespace lua_juce {
auto juce_LookAndFeel(sol::table& state) -> void
{
    auto lnf = state.new_usertype<juce::LookAndFeel>("LookAndFeel", sol::meta_function::construct, sol::no_constructor);

    lnf["findColour"]                      = LUA_JUCE_C_CALL(&juce::LookAndFeel::findColour);
    lnf["setColour"]                       = LUA_JUCE_C_CALL(&juce::LookAndFeel::setColour);
    lnf["isColourSpecified"]               = LUA_JUCE_C_CALL(&juce::LookAndFeel::isColourSpecified);
    lnf["setDefaultSansSerifTypeface"]     = LUA_JUCE_C_CALL(&juce::LookAndFeel::setDefaultSansSerifTypeface);
    lnf["setDefaultSansSerifTypefaceName"] = LUA_JUCE_C_CALL(&juce::LookAndFeel::setDefaultSansSerifTypefaceName);
    lnf["getMouseCursorFor"]               = LUA_JUCE_C_CALL(&juce::LookAndFeel::getMouseCursorFor);
    lnf["createGraphicsContext"]           = LUA_JUCE_C_CALL(&juce::LookAndFeel::createGraphicsContext);
    lnf["setUsingNativeAlertWindows"]      = LUA_JUCE_C_CALL(&juce::LookAndFeel::setUsingNativeAlertWindows);
    lnf["isUsingNativeAlertWindows"]       = LUA_JUCE_C_CALL(&juce::LookAndFeel::isUsingNativeAlertWindows);
    lnf["drawSpinningWaitAnimation"]       = LUA_JUCE_C_CALL(&juce::LookAndFeel::drawSpinningWaitAnimation);
    lnf["getTickShape"]                    = LUA_JUCE_C_CALL(&juce::LookAndFeel::getTickShape);
    lnf["getCrossShape"]                   = LUA_JUCE_C_CALL(&juce::LookAndFeel::getCrossShape);
    lnf["createDropShadowerForComponent"]  = LUA_JUCE_C_CALL(&juce::LookAndFeel::createDropShadowerForComponent);
    lnf["playAlertSound"]                  = LUA_JUCE_C_CALL(&juce::LookAndFeel::playAlertSound);
    // lnf["getTypefaceForFont"]           = &juce::LookAndFeel::getTypefaceForFont;
}
} // namespace lua_juce
