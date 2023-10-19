namespace lua_juce {

auto juce_AudioProcessor(sol::table& state) -> void
{
    auto proc = state.new_usertype<juce::AudioProcessor>("AudioProcessor", sol::no_constructor);

    proc["getName"]                             = LUA_JUCE_C_CALL(&juce::AudioProcessor::getName);
    proc["getAlternateDisplayNames"]            = LUA_JUCE_C_CALL(&juce::AudioProcessor::getAlternateDisplayNames);
    proc["prepareToPlay"]                       = LUA_JUCE_C_CALL(&juce::AudioProcessor::prepareToPlay);
    proc["releaseResources"]                    = LUA_JUCE_C_CALL(&juce::AudioProcessor::releaseResources);
    proc["memoryWarningReceived"]               = LUA_JUCE_C_CALL(&juce::AudioProcessor::memoryWarningReceived);
    proc["getBusCount"]                         = LUA_JUCE_C_CALL(&juce::AudioProcessor::getBusCount);
    proc["canAddBus"]                           = LUA_JUCE_C_CALL(&juce::AudioProcessor::canAddBus);
    proc["canRemoveBus"]                        = LUA_JUCE_C_CALL(&juce::AudioProcessor::canRemoveBus);
    proc["addBus"]                              = LUA_JUCE_C_CALL(&juce::AudioProcessor::addBus);
    proc["removeBus"]                           = LUA_JUCE_C_CALL(&juce::AudioProcessor::removeBus);
    proc["setBusesLayout"]                      = LUA_JUCE_C_CALL(&juce::AudioProcessor::setBusesLayout);
    proc["setBusesLayoutWithoutEnabling"]       = LUA_JUCE_C_CALL(&juce::AudioProcessor::setBusesLayoutWithoutEnabling);
    proc["getBusesLayout"]                      = LUA_JUCE_C_CALL(&juce::AudioProcessor::getBusesLayout);
    proc["getChannelLayoutOfBus"]               = LUA_JUCE_C_CALL(&juce::AudioProcessor::getChannelLayoutOfBus);
    proc["setChannelLayoutOfBus"]               = LUA_JUCE_C_CALL(&juce::AudioProcessor::setChannelLayoutOfBus);
    proc["getChannelCountOfBus"]                = LUA_JUCE_C_CALL(&juce::AudioProcessor::getChannelCountOfBus);
    proc["enableAllBuses"]                      = LUA_JUCE_C_CALL(&juce::AudioProcessor::enableAllBuses);
    proc["disableNonMainBuses"]                 = LUA_JUCE_C_CALL(&juce::AudioProcessor::disableNonMainBuses);
    proc["getChannelIndexInProcessBlockBuffer"] = LUA_JUCE_C_CALL(&juce::AudioProcessor::getChannelIndexInProcessBlockBuffer);
    proc["checkBusesLayoutSupported"]           = LUA_JUCE_C_CALL(&juce::AudioProcessor::checkBusesLayoutSupported);
    proc["supportsDoublePrecisionProcessing"]   = LUA_JUCE_C_CALL(&juce::AudioProcessor::supportsDoublePrecisionProcessing);
    proc["getProcessingPrecision"]              = LUA_JUCE_C_CALL(&juce::AudioProcessor::getProcessingPrecision);
    proc["isUsingDoublePrecision"]              = LUA_JUCE_C_CALL(&juce::AudioProcessor::isUsingDoublePrecision);
    proc["setProcessingPrecision"]              = LUA_JUCE_C_CALL(&juce::AudioProcessor::setProcessingPrecision);
    proc["getPlayHead"]                         = LUA_JUCE_C_CALL(&juce::AudioProcessor::getPlayHead);
    proc["getTotalNumInputChannels"]            = LUA_JUCE_C_CALL(&juce::AudioProcessor::getTotalNumInputChannels);
    proc["getTotalNumOutputChannels"]           = LUA_JUCE_C_CALL(&juce::AudioProcessor::getTotalNumOutputChannels);
    proc["getMainBusNumInputChannels"]          = LUA_JUCE_C_CALL(&juce::AudioProcessor::getMainBusNumInputChannels);
    proc["getMainBusNumOutputChannels"]         = LUA_JUCE_C_CALL(&juce::AudioProcessor::getMainBusNumOutputChannels);
    proc["getSampleRate"]                       = LUA_JUCE_C_CALL(&juce::AudioProcessor::getSampleRate);
    proc["getBlockSize"]                        = LUA_JUCE_C_CALL(&juce::AudioProcessor::getBlockSize);
    proc["getLatencySamples"]                   = LUA_JUCE_C_CALL(&juce::AudioProcessor::getLatencySamples);
    proc["setLatencySamples"]                   = LUA_JUCE_C_CALL(&juce::AudioProcessor::setLatencySamples);
    proc["getTailLengthSeconds"]                = LUA_JUCE_C_CALL(&juce::AudioProcessor::getTailLengthSeconds);
    proc["acceptsMidi"]                         = LUA_JUCE_C_CALL(&juce::AudioProcessor::acceptsMidi);
    proc["producesMidi"]                        = LUA_JUCE_C_CALL(&juce::AudioProcessor::producesMidi);

    // proc["getBus"] = LUA_JUCE_C_CALL(&juce::AudioProcessor::getBus);
    // proc["getOffsetInBusBufferForAbsoluteChannelIndex"] = LUA_JUCE_C_CALL(&juce::AudioProcessor::getOffsetInBusBufferForAbsoluteChannelIndex);
}

} // namespace lua_juce
