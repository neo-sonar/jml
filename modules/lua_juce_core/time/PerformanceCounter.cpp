
namespace lua_juce {
auto juce_PerformanceCounter(sol::table& state) -> void
{
    // clang-format off
    auto pc = state.new_usertype<juce::PerformanceCounter>(
        "PerformanceCounter",
        sol::constructors<juce::PerformanceCounter(juce::String const&, int, juce::File const&)>()
    );
    // clang-format on

    pc["start"]                 = LUA_JUCE_C_CALL(&juce::PerformanceCounter::start);
    pc["stop"]                  = LUA_JUCE_C_CALL(&juce::PerformanceCounter::stop);
    pc["printStatistics"]       = LUA_JUCE_C_CALL(&juce::PerformanceCounter::printStatistics);
    pc["getStatisticsAndReset"] = LUA_JUCE_C_CALL(&juce::PerformanceCounter::getStatisticsAndReset);
}
} // namespace lua_juce
