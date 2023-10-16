namespace lua_juce {
auto juce_ShapeButton(sol::table& state) -> void
{
    // clang-format off
    auto button = state.new_usertype<juce::ShapeButton>("ShapeButton",
        sol::constructors<
            juce::ShapeButton(juce::String const&, juce::Colour, juce::Colour, juce::Colour)
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

    button["setShape"]           = LUA_JUCE_C_CALL(&juce::ShapeButton::setShape);
    button["setColours"]         = LUA_JUCE_C_CALL(&juce::ShapeButton::setColours);
    button["setOnColours"]       = LUA_JUCE_C_CALL(&juce::ShapeButton::setOnColours);
    button["shouldUseOnColours"] = LUA_JUCE_C_CALL(&juce::ShapeButton::shouldUseOnColours);
    button["setOutline"]         = LUA_JUCE_C_CALL(&juce::ShapeButton::setOutline);
    button["setBorderSize"]      = LUA_JUCE_C_CALL(&juce::ShapeButton::setBorderSize);
}
} // namespace lua_juce
