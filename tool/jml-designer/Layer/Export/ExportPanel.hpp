#pragma once

#include "Core/ValueTree.hpp"
#include "Layer/Export/ImageExporter.hpp"
#include "Layer/LayerSelection.hpp"

#include <mc_gui_extra/mc_gui_extra.hpp>

namespace jml::designer {

struct ExportPanel final : juce::Component
{
    explicit ExportPanel(LayerSelection& selection);
    ~ExportPanel() override = default;

    auto resized() -> void override;

private:
    auto launchExportFileChooser() -> void;
    auto exportToImage(juce::File const& file, ImageExporter::Format format) -> void;

    juce::Value _format{toVar(ImageExporter::Format::png)};
    juce::Value _scale{juce::var{1.0F}};
    LayerSelection& _selection;
    juce::PropertyPanel _panel;

    std::unique_ptr<juce::FileChooser> _fileChooser{nullptr};
};

} // namespace jml::designer
