namespace lua_juce {

auto juce_CodeTokeniser(sol::table& state) -> void
{
    auto tokeniser                      = state.new_usertype<juce::CodeTokeniser>("InternalCodeTokeniser", sol::no_constructor);
    tokeniser["readNextToken"]          = &juce::CodeTokeniser::readNextToken;
    tokeniser["getDefaultColourScheme"] = &juce::CodeTokeniser::getDefaultColourScheme;
}

} // namespace lua_juce
