namespace lua_juce {
auto juce_Random(sol::table& state) -> void
{
    auto rand = state.new_usertype<juce::Random>("Random");

    rand["getSystemRandom"] = LUA_JUCE_C_CALL(&juce::Random::getSystemRandom);
    rand["setSeed"]         = LUA_JUCE_C_CALL(&juce::Random::setSeed);
    rand["getSeed"]         = LUA_JUCE_C_CALL(&juce::Random::getSeed);
    rand["nextBool"]        = LUA_JUCE_C_CALL(&juce::Random::nextBool);
    rand["nextFloat"]       = LUA_JUCE_C_CALL(&juce::Random::nextFloat);
    rand["nextDouble"]      = LUA_JUCE_C_CALL(&juce::Random::nextDouble);
    rand["nextInt64"]       = LUA_JUCE_C_CALL(&juce::Random::nextInt64);

    rand["nextInt"] = sol::c_call<                                                                           //
        LUA_JUCE_WRAP(static_cast<int (juce::Random::*)() noexcept>(&juce::Random::nextInt)),                //
        LUA_JUCE_WRAP(static_cast<int (juce::Random::*)(int) noexcept>(&juce::Random::nextInt)),             //
        LUA_JUCE_WRAP(static_cast<int (juce::Random::*)(juce::Range<int>) noexcept>(&juce::Random::nextInt)) //
        >;
}
} // namespace lua_juce
