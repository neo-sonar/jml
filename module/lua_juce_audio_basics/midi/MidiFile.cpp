namespace lua_juce {

auto juce_MidiFile(sol::table& state) -> void
{
    auto midiFile = state.new_usertype<juce::MidiFile>("MidiFile", sol::constructors<juce::MidiFile()>());

    midiFile["getNumTracks"]                   = LUA_JUCE_C_CALL(&juce::MidiFile::getNumTracks);
    midiFile["getTrack"]                       = LUA_JUCE_C_CALL(&juce::MidiFile::getTrack);
    midiFile["addTrack"]                       = LUA_JUCE_C_CALL(&juce::MidiFile::addTrack);
    midiFile["clear"]                          = LUA_JUCE_C_CALL(&juce::MidiFile::clear);
    midiFile["getTimeFormat"]                  = LUA_JUCE_C_CALL(&juce::MidiFile::getTimeFormat);
    midiFile["setTicksPerQuarterNote"]         = LUA_JUCE_C_CALL(&juce::MidiFile::setTicksPerQuarterNote);
    midiFile["setSmpteTimeFormat"]             = LUA_JUCE_C_CALL(&juce::MidiFile::setSmpteTimeFormat);
    midiFile["findAllTempoEvents"]             = LUA_JUCE_C_CALL(&juce::MidiFile::findAllTempoEvents);
    midiFile["findAllTimeSigEvents"]           = LUA_JUCE_C_CALL(&juce::MidiFile::findAllTimeSigEvents);
    midiFile["findAllKeySigEvents"]            = LUA_JUCE_C_CALL(&juce::MidiFile::findAllKeySigEvents);
    midiFile["getLastTimestamp"]               = LUA_JUCE_C_CALL(&juce::MidiFile::getLastTimestamp);
    midiFile["readFrom"]                       = LUA_JUCE_C_CALL(&juce::MidiFile::readFrom);
    midiFile["writeTo"]                        = LUA_JUCE_C_CALL(&juce::MidiFile::writeTo);
    midiFile["convertTimestampTicksToSeconds"] = LUA_JUCE_C_CALL(&juce::MidiFile::convertTimestampTicksToSeconds);
}

} // namespace lua_juce
