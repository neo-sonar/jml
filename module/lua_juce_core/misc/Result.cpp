namespace lua_juce {
auto juce_Result(sol::table& state) -> void
{
    auto result               = state.new_usertype<juce::Result>("Result");
    result["wasOk"]           = LUA_JUCE_C_CALL(&juce::Result::wasOk);
    result["failed"]          = LUA_JUCE_C_CALL(&juce::Result::failed);
    result["getErrorMessage"] = LUA_JUCE_C_CALL(&juce::Result::getErrorMessage);
    result["ok"]              = LUA_JUCE_C_CALL(&juce::Result::ok);
    result["fail"]            = LUA_JUCE_C_CALL(&juce::Result::fail);
}
} // namespace lua_juce
