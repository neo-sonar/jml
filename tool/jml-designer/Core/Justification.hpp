#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

namespace jml::designer {
[[nodiscard]] auto makeJustificationProperty(juce::Value value, juce::String const& name)
    -> std::unique_ptr<juce::PropertyComponent>;
}

template<>
struct juce::VariantConverter<juce::Justification>
{
    [[nodiscard]] static auto toVar(juce::Justification const& justification) -> juce::var;
    [[nodiscard]] static auto fromVar(juce::var const& v) -> juce::Justification;
};
