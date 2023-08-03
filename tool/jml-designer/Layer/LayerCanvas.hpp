#pragma once

#include "Layer/LayerListener.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

namespace jml::designer {

struct Layer;

struct LayerCanvas final
    : juce::Component
    , LayerListener
{
    ~LayerCanvas() override;

    [[nodiscard]] auto layer() -> Layer&;
    [[nodiscard]] auto layer() const -> Layer const&;

    auto paint(juce::Graphics& g) -> void override;
    auto paintOverChildren(juce::Graphics& g) -> void override;
    auto layerPropertyChanged(Layer* layer, juce::Identifier const& property) -> void override;

private:
    explicit LayerCanvas(Layer& layer);

    friend Layer;
    Layer& _layer;
};

} // namespace jml::designer
