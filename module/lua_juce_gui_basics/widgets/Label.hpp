#pragma once

SOL_BASE_CLASSES(juce::Label, juce::Component, juce::MouseListener, juce::SettableTooltipClient, juce::TooltipClient);

namespace lua_juce {
auto juce_Label(sol::table& state) -> void;
}
