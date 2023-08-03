#pragma once

#include "Layer/Layer.hpp"
#include "Layer/LayerSelection.hpp"

#include <juce_data_structures/juce_data_structures.h>

namespace jml::designer {

struct Document
{
    Document(juce::ValueTree valueTree, juce::UndoManager* um);

    [[nodiscard]] auto getRootLayer() const -> Layer*;
    [[nodiscard]] auto getLayerSelection() -> LayerSelection&;
    [[nodiscard]] auto getLayerSelection() const -> LayerSelection const&;

    [[nodiscard]] auto getValueTree() -> juce::ValueTree&;
    [[nodiscard]] auto getValueTree() const -> juce::ValueTree const&;
    [[nodiscard]] auto getUndoManager() const -> juce::UndoManager*;

    auto save(juce::File const& file) -> void;
    [[nodiscard]] static auto load(juce::File const& file, juce::UndoManager* um) -> std::unique_ptr<Document>;

private:
    juce::ValueTree _valueTree;
    juce::UndoManager* _undoManager;

    std::unique_ptr<Layer> _root;
    LayerSelection _layerSelection;
};

} // namespace jml::designer
