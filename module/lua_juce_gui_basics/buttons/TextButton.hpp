#pragma once

SOL_BASE_CLASSES(juce::TextButton, juce::Button, juce::Component, juce::MouseListener, juce::SettableTooltipClient, juce::TooltipClient);
SOL_DERIVED_CLASSES(juce::Button, juce::TextButton);
namespace lua_juce {
auto juce_TextButton(sol::table& state) -> void;
}
