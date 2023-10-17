namespace lua_juce {
auto juce_String(sol::table& state) -> void
{
    auto str = state.new_usertype<juce::String>("String", sol::constructors<juce::String(), juce::String(char const*)>());

    str["isEmpty"]     = LUA_JUCE_C_CALL(&juce::String::isEmpty);
    str["isNotEmpty"]  = LUA_JUCE_C_CALL(&juce::String::isNotEmpty);
    str["clear"]       = LUA_JUCE_C_CALL(&juce::String::clear);
    str["hashCode"]    = LUA_JUCE_C_CALL(&juce::String::hashCode);
    str["hashCode64"]  = LUA_JUCE_C_CALL(&juce::String::hashCode64);
    str["hash"]        = LUA_JUCE_C_CALL(&juce::String::hash);
    str["length"]      = LUA_JUCE_C_CALL(&juce::String::length);
    str["trim"]        = LUA_JUCE_C_CALL(&juce::String::trim);
    str["toStdString"] = LUA_JUCE_C_CALL(&juce::String::toStdString);
}
} // namespace lua_juce
