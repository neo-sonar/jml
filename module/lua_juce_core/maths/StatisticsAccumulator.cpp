namespace lua_juce {
template<typename T>
auto juce_StatisticsAccumulatorImpl(sol::table& state, char const* name) -> void
{
    using Accumulator            = juce::StatisticsAccumulator<T>;
    auto type                    = state.new_usertype<Accumulator>(name, sol::constructors<Accumulator()>());
    type["getAverage"]           = LUA_JUCE_C_CALL(&Accumulator::getAverage);
    type["getVariance"]          = LUA_JUCE_C_CALL(&Accumulator::getVariance);
    type["getStandardDeviation"] = LUA_JUCE_C_CALL(&Accumulator::getStandardDeviation);
    type["getMinValue"]          = LUA_JUCE_C_CALL(&Accumulator::getMinValue);
    type["getMaxValue"]          = LUA_JUCE_C_CALL(&Accumulator::getMaxValue);
    type["getCount"]             = LUA_JUCE_C_CALL(&Accumulator::getCount);
}

auto juce_StatisticsAccumulator(sol::table& state) -> void
{
    juce_StatisticsAccumulatorImpl<float>(state, "StatisticsAccumulatorFloat");
    juce_StatisticsAccumulatorImpl<double>(state, "StatisticsAccumulatorDouble");
}
} // namespace lua_juce
