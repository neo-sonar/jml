namespace lua_juce {
auto juce_Button(sol::table& state) -> void
{
    // clang-format off
    auto button = state.new_usertype<juce::Button>("Button",
        sol::no_constructor,
        sol::base_classes,
        sol::bases<
            juce::MouseListener,
            juce::Component,
            juce::TooltipClient,
            juce::SettableTooltipClient
        >()
    );
    // clang-format on

    button["onClick"]   = &juce::Button::onClick;
    button["getBounds"] = LUA_JUCE_C_CALL(&juce::Component::getBounds);
    button["getWidth"]  = LUA_JUCE_C_CALL(&juce::Component::getWidth);
    button["getHeight"] = LUA_JUCE_C_CALL(&juce::Component::getHeight);
    button["getX"]      = LUA_JUCE_C_CALL(&juce::Component::getX);
    button["getY"]      = LUA_JUCE_C_CALL(&juce::Component::getY);
}
} // namespace lua_juce
