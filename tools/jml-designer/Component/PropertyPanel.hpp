#pragma once

#include "Component/ColorPropertyComponent.hpp"

#include <juce_gui_extra/juce_gui_extra.h>

namespace jml::designer {
auto makeTextProperty(auto& vt, auto const& id, auto const& name, bool editable)
{
    auto value = vt.getPropertyAsValue(id, nullptr);
    return std::make_unique<juce::TextPropertyComponent>(value, name, 64, false, editable);
}

auto makeSliderProperty(
    auto& vt,
    auto const& id,
    auto const& name,
    double minVal,
    double maxVal,
    double interval
)
{
    auto value = vt.getPropertyAsValue(id, nullptr);
    return std::make_unique<juce::SliderPropertyComponent>(value, name, minVal, maxVal, interval);
}

auto makeColorProperty(auto& vt, auto const& id, auto const& name, bool showAlpha)
{
    auto value = vt.getPropertyAsValue(id, nullptr);
    return std::make_unique<ColorPropertyComponent>(value, name, showAlpha);
}

} // namespace jml::designer
