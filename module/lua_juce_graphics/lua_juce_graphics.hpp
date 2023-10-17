/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 lua_juce_graphics
    vendor:             neo-sonar
    version:            0.1.0
    name:               Lua bindings for juce_graphics
    description:        Lua/Sol2 bindings for juce_graphics
    dependencies:       lua_juce_events, juce_graphics
    website:            http://github.com/neo-sonar/jml
    license:            GPL/Commercial
    minimumCppStandard: 20

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_LUA_JUCE_GRAPHICS
    #define USE_LUA_JUCE_GRAPHICS
#endif

#include <lua_juce_events/lua_juce_events.hpp>

JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wfloat-equal")
#include <juce_graphics/juce_graphics.h>
JUCE_END_IGNORE_WARNINGS_GCC_LIKE

namespace lua_juce {
auto juce_Colour(sol::table& state) -> void;
auto juce_ColourGradient(sol::table& state) -> void;
auto juce_Colours(sol::table& state) -> void;
auto juce_DropShadow(sol::table& state) -> void;
auto juce_Graphics(sol::table& state) -> void;
auto juce_FillType(sol::table& state) -> void;
auto juce_Font(sol::table& state) -> void;
auto juce_AffineTransform(sol::table& state) -> void;
auto juce_Line(sol::table& state) -> void;
auto juce_Path(sol::table& state) -> void;
auto juce_Point(sol::table& state) -> void;
auto juce_Rectangle(sol::table& state) -> void;
auto juce_Image(sol::table& state) -> void;
auto juce_ImageCache(sol::table& state) -> void;
auto juce_Justification(sol::table& state) -> void;
} // namespace lua_juce
