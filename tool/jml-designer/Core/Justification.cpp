#include "Justification.hpp"

namespace jml::designer {

auto makeJustificationProperty(juce::Value value, juce::String const& name) -> std::unique_ptr<juce::PropertyComponent>
{
    auto const optionNames = juce::StringArray{
        "Left",
        "Right",
        "HorizontallyCentred",
        "Top",
        "Bottom",
        "VerticallyCentred",
        "HorizontallyJustified",
        "Centred",
        "CentredLeft",
        "CentredRight",
        "CentredTop",
        "CentredBottom",
        "TopLeft",
        "TopRight",
        "BottomLeft",
        "BottomRight",
    };

    auto const optionValues = juce::Array{
        mc::toVar(juce::Justification::left),
        mc::toVar(juce::Justification::right),
        mc::toVar(juce::Justification::horizontallyCentred),
        mc::toVar(juce::Justification::top),
        mc::toVar(juce::Justification::bottom),
        mc::toVar(juce::Justification::verticallyCentred),
        mc::toVar(juce::Justification::horizontallyJustified),
        mc::toVar(juce::Justification::centred),
        mc::toVar(juce::Justification::centredLeft),
        mc::toVar(juce::Justification::centredRight),
        mc::toVar(juce::Justification::centredTop),
        mc::toVar(juce::Justification::centredBottom),
        mc::toVar(juce::Justification::topLeft),
        mc::toVar(juce::Justification::topRight),
        mc::toVar(juce::Justification::bottomLeft),
        mc::toVar(juce::Justification::bottomRight),
    };

    return std::make_unique<juce::ChoicePropertyComponent>(value, name, optionNames, optionValues);
}

} // namespace jml::designer

auto juce::VariantConverter<juce::Justification>::toVar(juce::Justification const& justification) -> juce::var
{
    return justification.getFlags();
}

auto juce::VariantConverter<juce::Justification>::fromVar(juce::var const& v) -> juce::Justification
{
    jassert(v.isInt());
    return static_cast<int>(v);
}
