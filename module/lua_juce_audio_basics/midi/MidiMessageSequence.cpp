namespace lua_juce {

auto juce_MidiMessageSequence(sol::table& state) -> void
{
    auto midiSequence = state.new_usertype<juce::MidiMessageSequence>("MidiMessageSequence", sol::constructors<juce::MidiMessageSequence()>());

    midiSequence["clear"]                          = LUA_JUCE_C_CALL(&juce::MidiMessageSequence::clear);
    midiSequence["getNumEvents"]                   = LUA_JUCE_C_CALL(&juce::MidiMessageSequence::getNumEvents);
    midiSequence["getEventPointer"]                = LUA_JUCE_C_CALL(&juce::MidiMessageSequence::getEventPointer);
    midiSequence["getTimeOfMatchingKeyUp"]         = LUA_JUCE_C_CALL(&juce::MidiMessageSequence::getTimeOfMatchingKeyUp);
    midiSequence["getIndexOfMatchingKeyUp"]        = LUA_JUCE_C_CALL(&juce::MidiMessageSequence::getIndexOfMatchingKeyUp);
    midiSequence["getIndexOf"]                     = LUA_JUCE_C_CALL(&juce::MidiMessageSequence::getIndexOf);
    midiSequence["getNextIndexAtTime"]             = LUA_JUCE_C_CALL(&juce::MidiMessageSequence::getNextIndexAtTime);
    midiSequence["getStartTime"]                   = LUA_JUCE_C_CALL(&juce::MidiMessageSequence::getStartTime);
    midiSequence["getEndTime"]                     = LUA_JUCE_C_CALL(&juce::MidiMessageSequence::getEndTime);
    midiSequence["getEventTime"]                   = LUA_JUCE_C_CALL(&juce::MidiMessageSequence::getEventTime);
    midiSequence["deleteEvent"]                    = LUA_JUCE_C_CALL(&juce::MidiMessageSequence::deleteEvent);
    midiSequence["updateMatchedPairs"]             = LUA_JUCE_C_CALL(&juce::MidiMessageSequence::updateMatchedPairs);
    midiSequence["sort"]                           = LUA_JUCE_C_CALL(&juce::MidiMessageSequence::sort);
    midiSequence["extractMidiChannelMessages"]     = LUA_JUCE_C_CALL(&juce::MidiMessageSequence::extractMidiChannelMessages);
    midiSequence["extractSysExMessages"]           = LUA_JUCE_C_CALL(&juce::MidiMessageSequence::extractSysExMessages);
    midiSequence["deleteMidiChannelMessages"]      = LUA_JUCE_C_CALL(&juce::MidiMessageSequence::deleteMidiChannelMessages);
    midiSequence["deleteSysExMessages"]            = LUA_JUCE_C_CALL(&juce::MidiMessageSequence::deleteSysExMessages);
    midiSequence["addTimeToMessages"]              = LUA_JUCE_C_CALL(&juce::MidiMessageSequence::addTimeToMessages);
    midiSequence["createControllerUpdatesForTime"] = LUA_JUCE_C_CALL(&juce::MidiMessageSequence::createControllerUpdatesForTime);
    midiSequence["swapWith"]                       = LUA_JUCE_C_CALL(&juce::MidiMessageSequence::swapWith);

    // midiSequence["begin"]       = LUA_JUCE_C_CALL(&juce::MidiMessageSequence::begin);
    // midiSequence["begin"]       = LUA_JUCE_C_CALL(&juce::MidiMessageSequence::begin);
    // midiSequence["end"]         = LUA_JUCE_C_CALL(&juce::MidiMessageSequence::end);
    // midiSequence["end"]         = LUA_JUCE_C_CALL(&juce::MidiMessageSequence::end);
    // midiSequence["addEvent"]    = LUA_JUCE_C_CALL(&juce::MidiMessageSequence::addEvent);
    // midiSequence["addEvent"]    = LUA_JUCE_C_CALL(&juce::MidiMessageSequence::addEvent);
    // midiSequence["addSequence"] = LUA_JUCE_C_CALL(&juce::MidiMessageSequence::addSequence);
    // midiSequence["addSequence"] = LUA_JUCE_C_CALL(&juce::MidiMessageSequence::addSequence);
}

} // namespace lua_juce
