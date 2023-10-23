/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 lua_juce_audio_processors
    vendor:             neo-sonar
    version:            0.1.0
    name:               Lua bindings for juce_audio_processors
    description:        Lua/Sol2 bindings for juce_audio_processors
    dependencies:       lua_juce_gui_basics, lua_juce_audio_basics, juce_audio_processors
    website:            http://github.com/neo-sonar/jml
    license:            BSL-1.0
    minimumCppStandard: 20

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_LUA_JUCE_AUDIO_PROCESSORS
    #define USE_LUA_JUCE_AUDIO_PROCESSORS
#endif

#include <juce_audio_processors/juce_audio_processors.h>
#include <lua_juce_audio_basics/lua_juce_audio_basics.hpp>
#include <lua_juce_gui_basics/lua_juce_gui_basics.hpp>

namespace lua_juce {
auto juce_AudioProcessor(sol::table& state) -> void;
} // namespace lua_juce
