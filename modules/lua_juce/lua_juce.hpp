/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 lua_juce
    vendor:             neo-sonar
    version:            0.1.0
    name:               Lua bindings for all JUCE modules
    description:        Lua/Sol2 bindings for all JUCE modules
    dependencies:       lua_juce_gui_extra, lua_juce_audio_processors
    website:            http://github.com/neo-sonar/jml
    license:            GPL/Commercial
    minimumCppStandard: 20

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_LUA_JUCE
    #define USE_LUA_JUCE
#endif

#include <lua_juce_audio_basics/lua_juce_audio_basics.hpp>
#include <lua_juce_audio_processors/lua_juce_audio_processors.hpp>
#include <lua_juce_core/lua_juce_core.hpp>
#include <lua_juce_data_structures/lua_juce_data_structures.hpp>
#include <lua_juce_events/lua_juce_events.hpp>
#include <lua_juce_graphics/lua_juce_graphics.hpp>
#include <lua_juce_gui_basics/lua_juce_gui_basics.hpp>
#include <lua_juce_gui_extra/lua_juce_gui_extra.hpp>

namespace lua_juce {
auto allModules(sol::state& lua) -> void;
}
