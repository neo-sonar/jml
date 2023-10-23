namespace lua_juce {

auto juce_CPlusPlusCodeTokeniser(sol::table& state) -> void
{
    // clang-format off
    auto tokeniser = state.new_usertype<juce::CPlusPlusCodeTokeniser>("CPlusPlusCodeTokeniser",
        sol::constructors<juce::CPlusPlusCodeTokeniser()>(),
        sol::base_classes, sol::bases<juce::CodeTokeniser>()
    );
    // clang-format on
    tokeniser["isReservedKeyword"] = &juce::CPlusPlusCodeTokeniser::isReservedKeyword;
}

} // namespace lua_juce
