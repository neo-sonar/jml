#pragma once

#include <juce_core/juce_core.h>

namespace jml::designer {

struct Layer;

struct Exporter
{
    virtual ~Exporter() = default;

    [[nodiscard]] virtual auto exportLayer(juce::OutputStream& out, Layer& layer, float scale) -> juce::Result = 0;
};

} // namespace jml::designer
