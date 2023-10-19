namespace lua_juce {

auto juce_StatisticsAccumulator(sol::table& state) -> void
{
    using Accumulator = juce::StatisticsAccumulator<double>;
    auto type         = state.new_usertype<Accumulator>("StatisticsAccumulator", sol::constructors<Accumulator()>());

    type["getAverage"]           = LUA_JUCE_C_CALL(&Accumulator::getAverage);
    type["getVariance"]          = LUA_JUCE_C_CALL(&Accumulator::getVariance);
    type["getStandardDeviation"] = LUA_JUCE_C_CALL(&Accumulator::getStandardDeviation);
    type["getMinValue"]          = LUA_JUCE_C_CALL(&Accumulator::getMinValue);
    type["getMaxValue"]          = LUA_JUCE_C_CALL(&Accumulator::getMaxValue);
    type["getCount"]             = LUA_JUCE_C_CALL(&Accumulator::getCount);
}

} // namespace lua_juce
