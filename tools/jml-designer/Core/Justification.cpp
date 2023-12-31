#include "Justification.hpp"

#include <jml_tools/jml_tools.hpp>

namespace jml::designer {

auto makeJustificationProperty(juce::Value const& value, juce::String const& name)
    -> std::unique_ptr<juce::PropertyComponent>
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
        toVar(juce::Justification::left),
        toVar(juce::Justification::right),
        toVar(juce::Justification::horizontallyCentred),
        toVar(juce::Justification::top),
        toVar(juce::Justification::bottom),
        toVar(juce::Justification::verticallyCentred),
        toVar(juce::Justification::horizontallyJustified),
        toVar(juce::Justification::centred),
        toVar(juce::Justification::centredLeft),
        toVar(juce::Justification::centredRight),
        toVar(juce::Justification::centredTop),
        toVar(juce::Justification::centredBottom),
        toVar(juce::Justification::topLeft),
        toVar(juce::Justification::topRight),
        toVar(juce::Justification::bottomLeft),
        toVar(juce::Justification::bottomRight),
    };

    return std::make_unique<juce::ChoicePropertyComponent>(value, name, optionNames, optionValues);
}

} // namespace jml::designer

auto juce::VariantConverter<juce::Justification>::toVar(juce::Justification const& justification)
    -> juce::var
{
    return justification.getFlags();
}

auto juce::VariantConverter<juce::Justification>::fromVar(juce::var const& v) -> juce::Justification
{
    jassert(v.isInt());
    return static_cast<int>(v);
}
