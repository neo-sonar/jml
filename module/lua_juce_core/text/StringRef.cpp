namespace lua_juce {
auto juce_StringRef(sol::table& state) -> void
{
    auto str = state.new_usertype<juce::StringRef>("StringRef", sol::constructors<                                 //
                                                                    juce::StringRef(),                             //
                                                                    juce::StringRef(char const*),                  //
                                                                    juce::StringRef(juce::String const&),          //
                                                                    juce::StringRef(std::string const&),           //
                                                                    juce::StringRef(juce::String::CharPointerType) //
                                                                    >());

    str["isEmpty"]    = LUA_JUCE_C_CALL(&juce::StringRef::isEmpty);
    str["isNotEmpty"] = LUA_JUCE_C_CALL(&juce::StringRef::isNotEmpty);
    str["length"]     = LUA_JUCE_C_CALL(&juce::StringRef::length);
    str["text"]       = LUA_JUCE_C_CALL(&juce::StringRef::text);
}
} // namespace lua_juce
