namespace lua_juce {
auto juce_LookAndFeel_V4(sol::table& state) -> void
{
    // clang-format off
    auto lnf = state.new_usertype<juce::LookAndFeel_V4>("InternalLookAndFeel_V4",
        sol::constructors<
            juce::LookAndFeel_V4(),
            juce::LookAndFeel_V4(juce::LookAndFeel_V4::ColourScheme)
        >(),
        sol::base_classes,
        sol::bases<
            juce::LookAndFeel,
            juce::LookAndFeel_V2,
            juce::LookAndFeel_V3
        >()
    );
    // clang-format on

    // lnf["setColourScheme"]         = juce::LookAndFeel_V4::setColourScheme;
    // lnf["getCurrentColourScheme"]  = juce::LookAndFeel_V4::getCurrentColourScheme;
    lnf["getDarkColourScheme"]     = LUA_JUCE_C_CALL(&juce::LookAndFeel_V4::getDarkColourScheme);
    lnf["getMidnightColourScheme"] = LUA_JUCE_C_CALL(&juce::LookAndFeel_V4::getMidnightColourScheme);
    lnf["getGreyColourScheme"]     = LUA_JUCE_C_CALL(&juce::LookAndFeel_V4::getGreyColourScheme);
    lnf["getLightColourScheme"]    = LUA_JUCE_C_CALL(&juce::LookAndFeel_V4::getLightColourScheme);
}
} // namespace lua_juce
