namespace lua_juce {

auto juce_MidiRPNDetector(sol::table& state) -> void
{
    auto detector        = state.new_usertype<juce::MidiRPNDetector>("MidiRPNDetector", sol::default_constructor);
    detector["reset"]    = LUA_JUCE_C_CALL(&juce::MidiRPNDetector::reset);
    detector["tryParse"] = LUA_JUCE_C_CALL(&juce::MidiRPNDetector::tryParse);
}

} // namespace lua_juce
