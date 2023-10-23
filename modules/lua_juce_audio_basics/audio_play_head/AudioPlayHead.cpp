namespace lua_juce {
auto juce_AudioPlayHead(sol::table& state) -> void
{
    auto ts           = state.new_usertype<juce::AudioPlayHead::TimeSignature>("AudioPlayHeadTimeSignature");
    ts["numerator"]   = &juce::AudioPlayHead::TimeSignature::numerator;
    ts["denominator"] = &juce::AudioPlayHead::TimeSignature::denominator;

    auto playHead                   = state.new_usertype<juce::AudioPlayHead>("AudioPlayHead", sol::no_constructor);
    playHead["canControlTransport"] = LUA_JUCE_C_CALL(&juce::AudioPlayHead::canControlTransport);
    playHead["transportPlay"]       = LUA_JUCE_C_CALL(&juce::AudioPlayHead::transportPlay);
    playHead["transportRecord"]     = LUA_JUCE_C_CALL(&juce::AudioPlayHead::transportRecord);
    playHead["transportRewind"]     = LUA_JUCE_C_CALL(&juce::AudioPlayHead::transportRewind);
}

} // namespace lua_juce
