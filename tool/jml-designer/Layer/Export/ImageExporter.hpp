#pragma once

#include "Layer/Export/Exporter.hpp"

namespace jml::designer {

struct ImageExporter final : Exporter
{
    enum struct Format
    {
        invalid,
        jpg,
        png,
    };

    explicit ImageExporter(Format format);
    ~ImageExporter() override = default;

    [[nodiscard]] auto exportLayer(juce::OutputStream& out, Layer& layer, float scale)
        -> juce::Result override;

private:
    Format _format{Format::invalid};
};

} // namespace jml::designer

template<>
struct juce::VariantConverter<jml::designer::ImageExporter::Format>
{
    [[nodiscard]] static auto toVar(jml::designer::ImageExporter::Format const& format) -> juce::var;
    [[nodiscard]] static auto fromVar(juce::var const& v) -> jml::designer::ImageExporter::Format;
};
