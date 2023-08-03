namespace lua_juce {
auto juce_ImageButton(sol::table& state) -> void
{
    // clang-format off
    auto button = state.new_usertype<juce::ImageButton>("ImageButton",
        sol::constructors<
            juce::ImageButton(juce::String const&)
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

    button["setImages"]      = &juce::ImageButton::setImages;
    button["getNormalImage"] = &juce::ImageButton::getNormalImage;
    button["getOverImage"]   = &juce::ImageButton::getOverImage;
    button["getDownImage"]   = &juce::ImageButton::getDownImage;
}
} // namespace lua_juce
