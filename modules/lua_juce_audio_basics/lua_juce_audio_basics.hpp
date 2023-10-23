/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 lua_juce_audio_basics
    vendor:             neo-sonar
    version:            0.1.0
    name:               Lua bindings for juce_audio_basics
    description:        Lua/Sol2 bindings for juce_audio_basics
    dependencies:       lua_juce_core, juce_audio_basics
    website:            http://github.com/neo-sonar/jml
    license:            BSL-1.0
    minimumCppStandard: 20

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_LUA_JUCE_AUDIO_BASICS
    #define USE_LUA_JUCE_AUDIO_BASICS
#endif

#include <juce_audio_basics/juce_audio_basics.h>
#include <lua_juce_core/lua_juce_core.hpp>

namespace lua_juce {
auto juce_AudioPlayHead(sol::table& state) -> void;
auto juce_MidiFile(sol::table& state) -> void;
auto juce_MidiMessage(sol::table& state) -> void;
auto juce_MidiRPNDetector(sol::table& state) -> void;
auto juce_MidiRPNMessage(sol::table& state) -> void;
auto juce_MidiMessageSequence(sol::table& state) -> void;
} // namespace lua_juce
