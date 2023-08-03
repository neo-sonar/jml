#pragma once

#include "Layer/LayerExportPanel.hpp"
#include "Layer/LayerSelection.hpp"

namespace jml::designer {

struct LayerPropertyPanel final
    : juce::Component
    , LayerSelection::Listener
{
    explicit LayerPropertyPanel(LayerSelection& selection);
    ~LayerPropertyPanel() override;

    auto resized() -> void override;
    auto layerSelectionChanged(LayerSelection* selection) -> void override;

private:
    LayerSelection& _selection;
    juce::PropertyPanel _panel;
    LayerExportPanel _export{_selection};
};

} // namespace jml::designer
