#include "LuaTokeniser.hpp"

#include <juce_gui_extra/juce_gui_extra.h>

namespace lua_juce {

auto juce_LuaTokeniser(sol::table& state) -> void
{
    // clang-format off
    state.new_usertype<juce::LuaTokeniser>("LuaTokeniser",
        sol::constructors<juce::LuaTokeniser()>(),
        sol::base_classes, sol::bases<juce::CodeTokeniser>()
    );
    // clang-format on
}

} // namespace lua_juce
