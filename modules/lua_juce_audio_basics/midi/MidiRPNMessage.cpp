namespace lua_juce {

auto juce_MidiRPNMessage(sol::table& state) -> void
{
    auto midiSequence = state.new_usertype<juce::MidiRPNMessage>("MidiRPNMessage", sol::default_constructor);

    midiSequence["channel"]         = LUA_JUCE_C_CALL(&juce::MidiRPNMessage::channel);
    midiSequence["parameterNumber"] = LUA_JUCE_C_CALL(&juce::MidiRPNMessage::parameterNumber);
    midiSequence["value"]           = LUA_JUCE_C_CALL(&juce::MidiRPNMessage::value);
    midiSequence["isNRPN"]          = LUA_JUCE_C_CALL(&juce::MidiRPNMessage::isNRPN);
    midiSequence["is14BitValue"]    = LUA_JUCE_C_CALL(&juce::MidiRPNMessage::is14BitValue);
}

} // namespace lua_juce
