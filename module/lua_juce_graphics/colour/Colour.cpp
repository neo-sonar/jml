namespace lua_juce {
auto juce_Colour(sol::table& state) -> void
{
    // clang-format off
    state.new_usertype<juce::Colour>("Colour",
        sol::constructors<
            juce::Colour(),
            juce::Colour(juce::uint8, juce::uint8, juce::uint8, juce::uint8)
        >()
    );
    // clang-format on
}
} // namespace lua_juce
