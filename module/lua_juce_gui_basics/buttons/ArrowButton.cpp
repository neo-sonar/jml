namespace lua_juce {
auto juce_ArrowButton(sol::table& state) -> void
{
    // clang-format off
    auto button = state.new_usertype<juce::ArrowButton>("ArrowButton",
        sol::constructors<
            juce::ArrowButton(juce::String const&, float, juce::Colour)
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
}
} // namespace lua_juce
