#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

namespace jml::designer {

enum struct ColorScheme
{
    light,
    juce,
};

inline static constexpr auto DefaultColorScheme = ColorScheme::light;

inline auto makeColorScheme(ColorScheme scheme)
{
    if (scheme == ColorScheme::light) {
        return juce::LookAndFeel_V4::ColourScheme{
            juce::Colours::lightgrey,        // windowBackground
            juce::Colours::white,            // widgetBackground
            juce::Colours::white,            // menuBackground
            juce::Colours::transparentBlack, // outline
            juce::Colours::black,            // defaultText
            juce::Colours::white,            // defaultFill
            juce::Colours::black,            // highlightedText
            juce::Colours::lightgrey,        // highlightedFill
            juce::Colours::black,            // menuText
        };
    }

    jassert(scheme == ColorScheme::juce);
    return juce::LookAndFeel_V4::getDarkColourScheme();
}

inline auto setComponentColors(juce::LookAndFeel& lnf, ColorScheme scheme)
{
    if (scheme == ColorScheme::light) {
        lnf.setColour(juce::DrawableButton::backgroundColourId, juce::Colours::transparentBlack);
        lnf.setColour(juce::DrawableButton::backgroundOnColourId, juce::Colours::transparentBlack);
        lnf.setColour(juce::ResizableWindow::backgroundColourId, juce::Colours::white);
        lnf.setColour(juce::PropertyComponent::backgroundColourId, juce::Colours::transparentBlack);
        lnf.setColour(juce::Slider::textBoxTextColourId, juce::Colours::black);
        lnf.setColour(juce::Slider::textBoxOutlineColourId, juce::Colours::transparentBlack);
        lnf.setColour(juce::TreeView::dragAndDropIndicatorColourId, juce::Colours::black);
    }
}
} // namespace jml::designer
