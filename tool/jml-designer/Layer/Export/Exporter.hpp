#pragma once

#include <mc_core/mc_core.hpp>

namespace jml::designer {

struct Layer;

struct Exporter
{
    virtual ~Exporter() = default;

    [[nodiscard]] virtual auto exportLayer(juce::OutputStream& out, Layer& layer, float scale) -> juce::Result = 0;
};

} // namespace jml::designer
