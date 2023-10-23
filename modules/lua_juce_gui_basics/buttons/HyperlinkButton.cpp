namespace lua_juce {
auto juce_HyperlinkButton(sol::table& state) -> void
{
    // clang-format off
    auto button = state.new_usertype<juce::HyperlinkButton>("HyperlinkButton",
        sol::constructors<
            juce::HyperlinkButton(),
            juce::HyperlinkButton(juce::String const&, juce::URL const&)
        >(),
        sol::base_classes,
        sol::bases<
            juce::MouseListener,
            juce::Component,
            juce::Button,
            juce::TooltipClient,
            juce::SettableTooltipClient
        >()
    );
    // clang-format on

    button["setFont"]              = LUA_JUCE_C_CALL(&juce::HyperlinkButton::setFont);
    button["setURL"]               = LUA_JUCE_C_CALL(&juce::HyperlinkButton::setURL);
    button["getURL"]               = LUA_JUCE_C_CALL(&juce::HyperlinkButton::getURL);
    button["changeWidthToFitText"] = LUA_JUCE_C_CALL(&juce::HyperlinkButton::changeWidthToFitText);
    button["setJustificationType"] = LUA_JUCE_C_CALL(&juce::HyperlinkButton::setJustificationType);
    button["getJustificationType"] = LUA_JUCE_C_CALL(&juce::HyperlinkButton::getJustificationType);
}
} // namespace lua_juce
