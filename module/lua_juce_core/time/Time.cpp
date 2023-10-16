namespace lua_juce {
auto juce_Time(sol::table& state) -> void
{
    auto t = state.new_usertype<juce::Time>("Time", sol::constructors<juce::Time(), juce::Time(juce::int64)>());

    t["toMilliseconds"]                   = LUA_JUCE_C_CALL(&juce::Time::toMilliseconds);
    t["getYear"]                          = LUA_JUCE_C_CALL(&juce::Time::getYear);
    t["getMonth"]                         = LUA_JUCE_C_CALL(&juce::Time::getMonth);
    t["getDayOfMonth"]                    = LUA_JUCE_C_CALL(&juce::Time::getDayOfMonth);
    t["getDayOfWeek"]                     = LUA_JUCE_C_CALL(&juce::Time::getDayOfWeek);
    t["getDayOfYear"]                     = LUA_JUCE_C_CALL(&juce::Time::getDayOfYear);
    t["getHours"]                         = LUA_JUCE_C_CALL(&juce::Time::getHours);
    t["isAfternoon"]                      = LUA_JUCE_C_CALL(&juce::Time::isAfternoon);
    t["getHoursInAmPmFormat"]             = LUA_JUCE_C_CALL(&juce::Time::getHoursInAmPmFormat);
    t["getMinutes"]                       = LUA_JUCE_C_CALL(&juce::Time::getMinutes);
    t["getSeconds"]                       = LUA_JUCE_C_CALL(&juce::Time::getSeconds);
    t["getMilliseconds"]                  = LUA_JUCE_C_CALL(&juce::Time::getMilliseconds);
    t["isDaylightSavingTime"]             = LUA_JUCE_C_CALL(&juce::Time::isDaylightSavingTime);
    t["getTimeZone"]                      = LUA_JUCE_C_CALL(&juce::Time::getTimeZone);
    t["getUTCOffsetSeconds"]              = LUA_JUCE_C_CALL(&juce::Time::getUTCOffsetSeconds);
    t["getUTCOffsetString"]               = LUA_JUCE_C_CALL(&juce::Time::getUTCOffsetString);
    t["toString"]                         = LUA_JUCE_C_CALL(&juce::Time::toString);
    t["formatted"]                        = LUA_JUCE_C_CALL(&juce::Time::formatted);
    t["toISO8601"]                        = LUA_JUCE_C_CALL(&juce::Time::toISO8601);
    t["fromISO8601"]                      = LUA_JUCE_C_CALL(&juce::Time::fromISO8601);
    t["setSystemTimeToThisTime"]          = LUA_JUCE_C_CALL(&juce::Time::setSystemTimeToThisTime);
    t["currentTimeMillis"]                = LUA_JUCE_C_CALL(&juce::Time::currentTimeMillis);
    t["getMillisecondCounter"]            = LUA_JUCE_C_CALL(&juce::Time::getMillisecondCounter);
    t["getMillisecondCounterHiRes"]       = LUA_JUCE_C_CALL(&juce::Time::getMillisecondCounterHiRes);
    t["waitForMillisecondCounter"]        = LUA_JUCE_C_CALL(&juce::Time::waitForMillisecondCounter);
    t["getApproximateMillisecondCounter"] = LUA_JUCE_C_CALL(&juce::Time::getApproximateMillisecondCounter);
    t["getHighResolutionTicks"]           = LUA_JUCE_C_CALL(&juce::Time::getHighResolutionTicks);
    t["getHighResolutionTicksPerSecond"]  = LUA_JUCE_C_CALL(&juce::Time::getHighResolutionTicksPerSecond);
    t["highResolutionTicksToSeconds"]     = LUA_JUCE_C_CALL(&juce::Time::highResolutionTicksToSeconds);
    t["secondsToHighResolutionTicks"]     = LUA_JUCE_C_CALL(&juce::Time::secondsToHighResolutionTicks);
    t["getCompilationDate"]               = LUA_JUCE_C_CALL(&juce::Time::getCompilationDate);

    // t["getMonthName"]                     = &juce::Time::getMonthName;
    // t["getWeekdayName"]                   = &juce::Time::getWeekdayName;
    // t["getWeekdayName"]                   = &juce::Time::getWeekdayName;
    // t["getMonthName"]                     = &juce::Time::getMonthName;
}
} // namespace lua_juce
