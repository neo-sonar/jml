namespace lua_juce {

auto juce_CodeTokeniser(sol::table& state) -> void
{
    auto tokeniser                      = state.new_usertype<juce::CodeTokeniser>("InternalCodeTokeniser", sol::no_constructor);
    tokeniser["readNextToken"]          = LUA_JUCE_C_CALL(&juce::CodeTokeniser::readNextToken);
    tokeniser["getDefaultColourScheme"] = LUA_JUCE_C_CALL(&juce::CodeTokeniser::getDefaultColourScheme);
}

} // namespace lua_juce
