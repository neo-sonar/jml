namespace jml {

auto getIcon(char const* name) -> std::unique_ptr<juce::Drawable>
{
    auto size        = 0;
    auto const* data = BinaryData::getNamedResource(name, size);
    jassert(data != nullptr);

    auto svg = juce::Drawable::createFromImageData(data, static_cast<size_t>(size));
    jassert(svg != nullptr);
    return svg;
}

auto getIcon(char const* name, juce::Colour colour) -> std::unique_ptr<juce::Drawable>
{
    auto icon = getIcon(name);
    icon->replaceColour(juce::Colours::black, colour);
    return icon;
}

} // namespace jml
