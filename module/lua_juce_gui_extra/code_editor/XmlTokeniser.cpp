namespace lua_juce {

auto juce_XmlTokeniser(sol::table& state) -> void
{
    // clang-format off
    state.new_usertype<juce::XmlTokeniser>("XmlTokeniser",
        sol::constructors<juce::XmlTokeniser()>(),
        sol::base_classes, sol::bases<juce::CodeTokeniser>()
    );
    // clang-format on
}

} // namespace lua_juce
