namespace lua_juce {
auto juce_RelativeTime(sol::table& state) -> void
{
    auto t = state.new_usertype<juce::RelativeTime>("RelativeTime", sol::constructors<juce::RelativeTime(double)>());

    // members
    t["inMilliseconds"]            = LUA_JUCE_C_CALL(&juce::RelativeTime::inMilliseconds);
    t["inSeconds"]                 = LUA_JUCE_C_CALL(&juce::RelativeTime::inSeconds);
    t["inMinutes"]                 = LUA_JUCE_C_CALL(&juce::RelativeTime::inMinutes);
    t["inHours"]                   = LUA_JUCE_C_CALL(&juce::RelativeTime::inHours);
    t["inDays"]                    = LUA_JUCE_C_CALL(&juce::RelativeTime::inDays);
    t["inWeeks"]                   = LUA_JUCE_C_CALL(&juce::RelativeTime::inWeeks);
    t["getDescription"]            = LUA_JUCE_C_CALL(&juce::RelativeTime::getDescription);
    t["getApproximateDescription"] = LUA_JUCE_C_CALL(&juce::RelativeTime::getApproximateDescription);

    // static
    t["milliseconds"] = [](double v) { return juce::RelativeTime::milliseconds(static_cast<juce::int64>(v)); };
    t["seconds"]      = LUA_JUCE_C_CALL(&juce::RelativeTime::seconds);
    t["minutes"]      = LUA_JUCE_C_CALL(&juce::RelativeTime::minutes);
    t["hours"]        = LUA_JUCE_C_CALL(&juce::RelativeTime::hours);
    t["days"]         = LUA_JUCE_C_CALL(&juce::RelativeTime::days);
    t["weeks"]        = LUA_JUCE_C_CALL(&juce::RelativeTime::weeks);
}
} // namespace lua_juce
