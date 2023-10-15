/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 lua_juce_gui_extra
    vendor:             neo-sonar
    version:            0.1.0
    name:               Lua bindings for juce_gui_extra
    description:        Lua/Sol2 bindings for juce_gui_extra
    dependencies:       lua_juce_gui_basics, juce_gui_extra
    website:            http://github.com/neo-sonar/jml
    license:            GPL/Commercial
    minimumCppStandard: 20

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_LUA_JUCE_GUI_EXTRA
    #define USE_LUA_JUCE_GUI_EXTRA
#endif

#include <juce_gui_extra/juce_gui_extra.h>
#include <lua_juce_gui_basics/lua_juce_gui_basics.hpp>

namespace lua_juce {
auto juce_CodeDocument(sol::table& state) -> void;
auto juce_CodeTokeniser(sol::table& state) -> void;
auto juce_CPlusPlusCodeTokeniser(sol::table& state) -> void;
auto juce_LuaTokeniser(sol::table& state) -> void;
auto juce_XmlTokeniser(sol::table& state) -> void;
} // namespace lua_juce
