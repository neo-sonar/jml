namespace lua_juce {
auto juce_Timer(sol::table& state) -> void
{
    auto timer = state.new_usertype<juce::Timer>("InternalTimer", sol::meta_function::construct, sol::no_constructor);

    timer["timerCallback"]                  = LUA_JUCE_C_CALL(&juce::Timer::timerCallback);
    timer["startTimer"]                     = LUA_JUCE_C_CALL(&juce::Timer::startTimer);
    timer["startTimerHz"]                   = LUA_JUCE_C_CALL(&juce::Timer::startTimerHz);
    timer["stopTimer"]                      = LUA_JUCE_C_CALL(&juce::Timer::stopTimer);
    timer["isTimerRunning"]                 = LUA_JUCE_C_CALL(&juce::Timer::isTimerRunning);
    timer["getTimerInterval"]               = LUA_JUCE_C_CALL(&juce::Timer::getTimerInterval);
    timer["callAfterDelay"]                 = LUA_JUCE_C_CALL(&juce::Timer::callAfterDelay);
    timer["callPendingTimersSynchronously"] = LUA_JUCE_C_CALL(&juce::Timer::callPendingTimersSynchronously);
}
} // namespace lua_juce
