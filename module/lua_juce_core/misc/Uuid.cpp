namespace lua_juce {
auto juce_Uuid(sol::table& state) -> void
{
    // clang-format off
    auto uuid = state.new_usertype<juce::Uuid>("Uuid",
        sol::constructors<juce::Uuid(), juce::Uuid(juce::String const&)>()
    );
    // clang-format on
    uuid["isNull"]                 = LUA_JUCE_C_CALL(&juce::Uuid::isNull);
    uuid["toString"]               = LUA_JUCE_C_CALL(&juce::Uuid::toString);
    uuid["toDashedString"]         = LUA_JUCE_C_CALL(&juce::Uuid::toDashedString);
    uuid["getTimeLow"]             = LUA_JUCE_C_CALL(&juce::Uuid::getTimeLow);
    uuid["getTimeMid"]             = LUA_JUCE_C_CALL(&juce::Uuid::getTimeMid);
    uuid["getTimeHighAndVersion"]  = LUA_JUCE_C_CALL(&juce::Uuid::getTimeHighAndVersion);
    uuid["getClockSeqAndReserved"] = LUA_JUCE_C_CALL(&juce::Uuid::getClockSeqAndReserved);
    uuid["getClockSeqLow"]         = LUA_JUCE_C_CALL(&juce::Uuid::getClockSeqLow);
    uuid["getNode"]                = LUA_JUCE_C_CALL(&juce::Uuid::getNode);
    uuid["hash"]                   = LUA_JUCE_C_CALL(&juce::Uuid::hash);
    uuid["getRawData"]             = LUA_JUCE_C_CALL(&juce::Uuid::getRawData);
}
} // namespace lua_juce
