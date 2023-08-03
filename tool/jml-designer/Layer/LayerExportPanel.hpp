#pragma once

#include "Layer/Export/ImageExporter.hpp"
#include "Layer/LayerSelection.hpp"

#include <mc_gui_extra/mc_gui_extra.hpp>

namespace jml::designer {

struct LayerExportPanel final : juce::Component
{
    explicit LayerExportPanel(LayerSelection& selection);
    ~LayerExportPanel() override = default;

    auto resized() -> void override;

private:
    auto launchExportFileChooser() -> void;
    auto exportToImage(juce::File const& file, ImageExporter::Format format) -> void;

    juce::Value _format{mc::toVar(ImageExporter::Format::png)};
    juce::Value _scale{juce::var{1.0F}};
    LayerSelection& _selection;
    juce::PropertyPanel _panel;

    std::unique_ptr<juce::FileChooser> _fileChooser{nullptr};
};

} // namespace jml::designer
