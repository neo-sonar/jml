#include "ImageExporter.hpp"

#include "Layer/Layer.hpp"

#include <mc_graphics/mc_graphics.hpp>

namespace jml::designer {

[[nodiscard]] static auto makeImageFileFormatForExporter(ImageExporter::Format format)
    -> std::unique_ptr<juce::ImageFileFormat>
{
    if (format == ImageExporter::Format::jpg) { return std::make_unique<juce::JPEGImageFormat>(); }
    if (format == ImageExporter::Format::png) { return std::make_unique<juce::PNGImageFormat>(); }
    return nullptr;
}

ImageExporter::ImageExporter(Format format) : _format{format} {}

auto ImageExporter::exportLayer(juce::OutputStream& out, Layer& layer, float scale) -> juce::Result
{
    auto& canvas = layer.getCanvas();
    auto image   = canvas.createComponentSnapshot(canvas.getLocalBounds(), true, scale);
    if (not image.isValid()) { return mc::fail("invalid image returned for layer: {}", layer.getName()); }

    auto format = makeImageFileFormatForExporter(_format);
    if (format == nullptr) { return mc::fail("failed to create image format writer"); }
    if (not format->writeImageToStream(image, out)) {
        return mc::fail("couldn't write image for: {}", layer.getName());
    }

    return juce::Result::ok();
}

} // namespace jml::designer

auto juce::VariantConverter<jml::designer::ImageExporter::Format>::toVar(
    jml::designer::ImageExporter::Format const& format) -> juce::var
{
    if (format == jml::designer::ImageExporter::Format::invalid) { return "invalid"; }
    if (format == jml::designer::ImageExporter::Format::jpg) { return "jpg"; }
    if (format == jml::designer::ImageExporter::Format::png) { return "png"; }

    jassertfalse;
    return {};
}

auto juce::VariantConverter<jml::designer::ImageExporter::Format>::fromVar(juce::var const& v)
    -> jml::designer::ImageExporter::Format
{
    if (v == "invalid") { return jml::designer::ImageExporter::Format::invalid; }
    if (v == "jpg") { return jml::designer::ImageExporter::Format::jpg; }
    if (v == "png") { return jml::designer::ImageExporter::Format::png; }

    jassertfalse;
    return jml::designer::ImageExporter::Format::invalid;
}
