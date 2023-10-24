#pragma once

namespace jml {

struct Theme
{
    struct SchemeColor
    {
        juce::LookAndFeel_V4::ColourScheme::UIColour id;
        juce::Colour color;
    };

    struct ComponentColor
    {
        int id;
        juce::Colour color;
    };

    std::vector<SchemeColor> schemeColors;
    std::vector<ComponentColor> componentColors;
};

[[nodiscard]] auto getCurrentTheme(juce::LookAndFeel& lookAndFeel) -> Theme;
[[nodiscard]] auto makeTheme(juce::ValueTree const& tree) -> std::optional<Theme>;
[[nodiscard]] auto loadTheme(juce::File const& file) -> std::optional<Theme>;
[[nodiscard]] auto toValueTree(Theme const& theme) -> juce::ValueTree;
auto apply(Theme const& theme, juce::LookAndFeel& lookAndFeel) -> void;

} // namespace jml
