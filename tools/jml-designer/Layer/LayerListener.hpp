#pragma once

#include <juce_core/juce_core.h>

namespace jml::designer {

struct Layer;

struct LayerListener
{
    virtual ~LayerListener() = default;

    virtual auto layerPropertyChanged(Layer* layer, juce::Identifier const& property) -> void;
    virtual auto layerChildrenChanged(Layer* layer) -> void;
    virtual auto layerSelectionChanged(Layer* layer) -> void;
    virtual auto layerBeingDeleted(Layer* layer) -> void;
};

} // namespace jml::designer
