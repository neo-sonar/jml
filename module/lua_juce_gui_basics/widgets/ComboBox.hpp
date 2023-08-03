#pragma once

SOL_BASE_CLASSES(juce::ComboBox, juce::Component, juce::MouseListener, juce::SettableTooltipClient, juce::TooltipClient,
                 juce::Value::Listener);

namespace lua_juce {
auto juce_ComboBox(sol::table& state) -> void;
}
