namespace lua_juce {
auto juce_MidiMessage(sol::table& state) -> void
{
    auto msg = state.new_usertype<juce::MidiMessage>("MidiMessage", sol::constructors<juce::MidiMessage()>());

    // member
    msg["getRawData"]                           = LUA_JUCE_C_CALL(&juce::MidiMessage::getRawData);
    msg["getRawDataSize"]                       = LUA_JUCE_C_CALL(&juce::MidiMessage::getRawDataSize);
    msg["getDescription"]                       = LUA_JUCE_C_CALL(&juce::MidiMessage::getDescription);
    msg["getTimeStamp"]                         = LUA_JUCE_C_CALL(&juce::MidiMessage::getTimeStamp);
    msg["setTimeStamp"]                         = LUA_JUCE_C_CALL(&juce::MidiMessage::setTimeStamp);
    msg["addToTimeStamp"]                       = LUA_JUCE_C_CALL(&juce::MidiMessage::addToTimeStamp);
    msg["withTimeStamp"]                        = LUA_JUCE_C_CALL(&juce::MidiMessage::withTimeStamp);
    msg["getChannel"]                           = LUA_JUCE_C_CALL(&juce::MidiMessage::getChannel);
    msg["isForChannel"]                         = LUA_JUCE_C_CALL(&juce::MidiMessage::isForChannel);
    msg["setChannel"]                           = LUA_JUCE_C_CALL(&juce::MidiMessage::setChannel);
    msg["isSysEx"]                              = LUA_JUCE_C_CALL(&juce::MidiMessage::isSysEx);
    msg["getSysExData"]                         = LUA_JUCE_C_CALL(&juce::MidiMessage::getSysExData);
    msg["getSysExDataSize"]                     = LUA_JUCE_C_CALL(&juce::MidiMessage::getSysExDataSize);
    msg["isNoteOn"]                             = LUA_JUCE_C_CALL(&juce::MidiMessage::isNoteOn);
    msg["isNoteOff"]                            = LUA_JUCE_C_CALL(&juce::MidiMessage::isNoteOff);
    msg["isNoteOnOrOff"]                        = LUA_JUCE_C_CALL(&juce::MidiMessage::isNoteOnOrOff);
    msg["getNoteNumber"]                        = LUA_JUCE_C_CALL(&juce::MidiMessage::getNoteNumber);
    msg["setNoteNumber"]                        = LUA_JUCE_C_CALL(&juce::MidiMessage::setNoteNumber);
    msg["getVelocity"]                          = LUA_JUCE_C_CALL(&juce::MidiMessage::getVelocity);
    msg["getFloatVelocity"]                     = LUA_JUCE_C_CALL(&juce::MidiMessage::getFloatVelocity);
    msg["setVelocity"]                          = LUA_JUCE_C_CALL(&juce::MidiMessage::setVelocity);
    msg["multiplyVelocity"]                     = LUA_JUCE_C_CALL(&juce::MidiMessage::multiplyVelocity);
    msg["isSustainPedalOn"]                     = LUA_JUCE_C_CALL(&juce::MidiMessage::isSustainPedalOn);
    msg["isSustainPedalOff"]                    = LUA_JUCE_C_CALL(&juce::MidiMessage::isSustainPedalOff);
    msg["isSostenutoPedalOn"]                   = LUA_JUCE_C_CALL(&juce::MidiMessage::isSostenutoPedalOn);
    msg["isSostenutoPedalOff"]                  = LUA_JUCE_C_CALL(&juce::MidiMessage::isSostenutoPedalOff);
    msg["isSoftPedalOn"]                        = LUA_JUCE_C_CALL(&juce::MidiMessage::isSoftPedalOn);
    msg["isSoftPedalOff"]                       = LUA_JUCE_C_CALL(&juce::MidiMessage::isSoftPedalOff);
    msg["isProgramChange"]                      = LUA_JUCE_C_CALL(&juce::MidiMessage::isProgramChange);
    msg["getProgramChangeNumber"]               = LUA_JUCE_C_CALL(&juce::MidiMessage::getProgramChangeNumber);
    msg["isPitchWheel"]                         = LUA_JUCE_C_CALL(&juce::MidiMessage::isPitchWheel);
    msg["getPitchWheelValue"]                   = LUA_JUCE_C_CALL(&juce::MidiMessage::getPitchWheelValue);
    msg["isAftertouch"]                         = LUA_JUCE_C_CALL(&juce::MidiMessage::isAftertouch);
    msg["getAfterTouchValue"]                   = LUA_JUCE_C_CALL(&juce::MidiMessage::getAfterTouchValue);
    msg["isChannelPressure"]                    = LUA_JUCE_C_CALL(&juce::MidiMessage::isChannelPressure);
    msg["getChannelPressureValue"]              = LUA_JUCE_C_CALL(&juce::MidiMessage::getChannelPressureValue);
    msg["isController"]                         = LUA_JUCE_C_CALL(&juce::MidiMessage::isController);
    msg["getControllerNumber"]                  = LUA_JUCE_C_CALL(&juce::MidiMessage::getControllerNumber);
    msg["getControllerValue"]                   = LUA_JUCE_C_CALL(&juce::MidiMessage::getControllerValue);
    msg["isControllerOfType"]                   = LUA_JUCE_C_CALL(&juce::MidiMessage::isControllerOfType);
    msg["isAllNotesOff"]                        = LUA_JUCE_C_CALL(&juce::MidiMessage::isAllNotesOff);
    msg["isAllSoundOff"]                        = LUA_JUCE_C_CALL(&juce::MidiMessage::isAllSoundOff);
    msg["isResetAllControllers"]                = LUA_JUCE_C_CALL(&juce::MidiMessage::isResetAllControllers);
    msg["isMetaEvent"]                          = LUA_JUCE_C_CALL(&juce::MidiMessage::isMetaEvent);
    msg["getMetaEventType"]                     = LUA_JUCE_C_CALL(&juce::MidiMessage::getMetaEventType);
    msg["getMetaEventData"]                     = LUA_JUCE_C_CALL(&juce::MidiMessage::getMetaEventData);
    msg["getMetaEventLength"]                   = LUA_JUCE_C_CALL(&juce::MidiMessage::getMetaEventLength);
    msg["isTrackMetaEvent"]                     = LUA_JUCE_C_CALL(&juce::MidiMessage::isTrackMetaEvent);
    msg["isEndOfTrackMetaEvent"]                = LUA_JUCE_C_CALL(&juce::MidiMessage::isEndOfTrackMetaEvent);
    msg["isTrackNameEvent"]                     = LUA_JUCE_C_CALL(&juce::MidiMessage::isTrackNameEvent);
    msg["isTextMetaEvent"]                      = LUA_JUCE_C_CALL(&juce::MidiMessage::isTextMetaEvent);
    msg["getTextFromTextMetaEvent"]             = LUA_JUCE_C_CALL(&juce::MidiMessage::getTextFromTextMetaEvent);
    msg["isTempoMetaEvent"]                     = LUA_JUCE_C_CALL(&juce::MidiMessage::isTempoMetaEvent);
    msg["getTempoMetaEventTickLength"]          = LUA_JUCE_C_CALL(&juce::MidiMessage::getTempoMetaEventTickLength);
    msg["getTempoSecondsPerQuarterNote"]        = LUA_JUCE_C_CALL(&juce::MidiMessage::getTempoSecondsPerQuarterNote);
    msg["isTimeSignatureMetaEvent"]             = LUA_JUCE_C_CALL(&juce::MidiMessage::isTimeSignatureMetaEvent);
    msg["isKeySignatureMetaEvent"]              = LUA_JUCE_C_CALL(&juce::MidiMessage::isKeySignatureMetaEvent);
    msg["getKeySignatureNumberOfSharpsOrFlats"] = LUA_JUCE_C_CALL(&juce::MidiMessage::getKeySignatureNumberOfSharpsOrFlats);
    msg["isKeySignatureMajorKey"]               = LUA_JUCE_C_CALL(&juce::MidiMessage::isKeySignatureMajorKey);
    msg["isMidiChannelMetaEvent"]               = LUA_JUCE_C_CALL(&juce::MidiMessage::isMidiChannelMetaEvent);
    msg["getMidiChannelMetaEventChannel"]       = LUA_JUCE_C_CALL(&juce::MidiMessage::getMidiChannelMetaEventChannel);
    msg["isActiveSense"]                        = LUA_JUCE_C_CALL(&juce::MidiMessage::isActiveSense);
    msg["isMidiStart"]                          = LUA_JUCE_C_CALL(&juce::MidiMessage::isMidiStart);
    msg["isMidiContinue"]                       = LUA_JUCE_C_CALL(&juce::MidiMessage::isMidiContinue);
    msg["isMidiStop"]                           = LUA_JUCE_C_CALL(&juce::MidiMessage::isMidiStop);
    msg["isMidiClock"]                          = LUA_JUCE_C_CALL(&juce::MidiMessage::isMidiClock);
    msg["isSongPositionPointer"]                = LUA_JUCE_C_CALL(&juce::MidiMessage::isSongPositionPointer);
    msg["getSongPositionPointerMidiBeat"]       = LUA_JUCE_C_CALL(&juce::MidiMessage::getSongPositionPointerMidiBeat);
    msg["isQuarterFrame"]                       = LUA_JUCE_C_CALL(&juce::MidiMessage::isQuarterFrame);
    msg["getQuarterFrameSequenceNumber"]        = LUA_JUCE_C_CALL(&juce::MidiMessage::getQuarterFrameSequenceNumber);
    msg["getQuarterFrameValue"]                 = LUA_JUCE_C_CALL(&juce::MidiMessage::getQuarterFrameValue);
    msg["isFullFrame"]                          = LUA_JUCE_C_CALL(&juce::MidiMessage::isFullFrame);
    msg["isMidiMachineControlMessage"]          = LUA_JUCE_C_CALL(&juce::MidiMessage::isMidiMachineControlMessage);
    msg["getMidiMachineControlCommand"]         = LUA_JUCE_C_CALL(&juce::MidiMessage::getMidiMachineControlCommand);

    // static
    msg["programChange"]          = LUA_JUCE_C_CALL(&juce::MidiMessage::programChange);
    msg["pitchWheel"]             = LUA_JUCE_C_CALL(&juce::MidiMessage::pitchWheel);
    msg["aftertouchChange"]       = LUA_JUCE_C_CALL(&juce::MidiMessage::aftertouchChange);
    msg["channelPressureChange"]  = LUA_JUCE_C_CALL(&juce::MidiMessage::channelPressureChange);
    msg["controllerEvent"]        = LUA_JUCE_C_CALL(&juce::MidiMessage::controllerEvent);
    msg["allNotesOff"]            = LUA_JUCE_C_CALL(&juce::MidiMessage::allNotesOff);
    msg["allSoundOff"]            = LUA_JUCE_C_CALL(&juce::MidiMessage::allSoundOff);
    msg["allControllersOff"]      = LUA_JUCE_C_CALL(&juce::MidiMessage::allControllersOff);
    msg["endOfTrack"]             = LUA_JUCE_C_CALL(&juce::MidiMessage::endOfTrack);
    msg["textMetaEvent"]          = LUA_JUCE_C_CALL(&juce::MidiMessage::textMetaEvent);
    msg["tempoMetaEvent"]         = LUA_JUCE_C_CALL(&juce::MidiMessage::tempoMetaEvent);
    msg["timeSignatureMetaEvent"] = LUA_JUCE_C_CALL(&juce::MidiMessage::timeSignatureMetaEvent);
    msg["keySignatureMetaEvent"]  = LUA_JUCE_C_CALL(&juce::MidiMessage::keySignatureMetaEvent);
    msg["midiChannelMetaEvent"]   = LUA_JUCE_C_CALL(&juce::MidiMessage::midiChannelMetaEvent);
    msg["midiStart"]              = LUA_JUCE_C_CALL(&juce::MidiMessage::midiStart);
    msg["midiContinue"]           = LUA_JUCE_C_CALL(&juce::MidiMessage::midiContinue);
    msg["midiStop"]               = LUA_JUCE_C_CALL(&juce::MidiMessage::midiStop);
    msg["midiClock"]              = LUA_JUCE_C_CALL(&juce::MidiMessage::midiClock);
    msg["songPositionPointer"]    = LUA_JUCE_C_CALL(&juce::MidiMessage::songPositionPointer);
    msg["quarterFrame"]           = LUA_JUCE_C_CALL(&juce::MidiMessage::quarterFrame);
    msg["fullFrame"]              = LUA_JUCE_C_CALL(&juce::MidiMessage::fullFrame);
    msg["midiMachineControlGoto"] = LUA_JUCE_C_CALL(&juce::MidiMessage::midiMachineControlGoto);
    msg["masterVolume"]           = LUA_JUCE_C_CALL(&juce::MidiMessage::masterVolume);

    // TODO
    // msg["getTimeSignatureInfo"] = LUA_JUCE_C_CALL(&juce::MidiMessage::getTimeSignatureInfo);
    // msg["getFullFrameParameters"] = LUA_JUCE_C_CALL(&juce::MidiMessage::getFullFrameParameters);
    // msg["isMidiMachineControlGoto"] = LUA_JUCE_C_CALL(&juce::MidiMessage::isMidiMachineControlGoto);
}

} // namespace lua_juce
