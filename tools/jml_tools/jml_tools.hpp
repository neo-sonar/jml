/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 jml_tools
    vendor:             neo-sonar
    version:            0.1.0
    name:               JML Tools
    description:        Utility classes for JML tools
    dependencies:       lua_juce
    website:            http://github.com/neo-sonar/jml
    license:            GPL/Commercial
    minimumCppStandard: 20

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_JML_TOOLS
    #define USE_JML_TOOLS
#endif

#include <lua_juce/lua_juce.hpp>

// clang-format off
#include "graphics/Color.hpp"
#include "graphics/Drawable.hpp"
#include "value/ValueTree.hpp"
#include "property/ValuePropertyComponent.hpp"
#include "property/ColourPropertyComponent.hpp"
#include "property/FilePropertyComponent.hpp"
// clang-format on
