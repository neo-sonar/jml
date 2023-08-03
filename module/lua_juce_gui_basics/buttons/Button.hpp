#pragma once

SOL_BASE_CLASSES(juce::Button, juce::Component, juce::MouseListener, juce::SettableTooltipClient, juce::TooltipClient);

namespace lua_juce {
auto juce_Button(sol::table& state) -> void;
}
