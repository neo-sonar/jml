/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 lua_juce_events
    vendor:             neo-sonar
    version:            0.1.0
    name:               Lua bindings for juce_events
    description:        Lua/Sol2 bindings for juce_events
    dependencies:       lua_juce_core, juce_events
    website:            http://github.com/neo-sonar/jml
    license:            BSL-1.0
    minimumCppStandard: 20

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_LUA_JUCE_EVENTS
    #define USE_LUA_JUCE_EVENTS
#endif

#include <juce_events/juce_events.h>
#include <lua_juce_core/lua_juce_core.hpp>

namespace lua_juce {
auto juce_Timer(sol::table& state) -> void;
auto juce_LuaTimer(sol::table& state) -> void;
} // namespace lua_juce
