#pragma once

SOL_BASE_CLASSES(juce::Slider, juce::MouseListener, juce::Component, juce::TooltipClient, juce::SettableTooltipClient);

namespace lua_juce {
auto juce_Slider(sol::table& state) -> void;
}
