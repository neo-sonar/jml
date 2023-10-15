#include "LookAndFeel.hpp"

#include "LookAndFeel/Colours.hpp"

namespace jml::viewer {
LookAndFeel::LookAndFeel()
    : juce::LookAndFeel_V4{{
        Colours::whiteDirt,              // windowBackground
        Colours::white,                  // widgetBackground
        Colours::white,                  // menuBackground
        juce::Colours::transparentBlack, // outline
        Colours::black,                  // defaultText
        Colours::white.darker(),         // defaultFill
        Colours::black,                  // highlightedText
        Colours::whiteDirt,              // highlightedFill
        Colours::black,                  // menuText
    }}
{
    setColour(juce::CodeEditorComponent::backgroundColourId, OneLightColours::editorBackground);
    setColour(juce::CodeEditorComponent::highlightColourId, OneLightColours::editorHighlight);
    setColour(juce::CodeEditorComponent::defaultTextColourId, OneLightColours::editorForeground);
    setColour(juce::CodeEditorComponent::lineNumberBackgroundId, Colours::transparent);
    setColour(juce::CodeEditorComponent::lineNumberTextId, OneLightColours::editorLineNumber);

    // setColour(juce::TextEditor::ColourIds::, OneLightColours::editorLineNumber);
    // setColour(juce::ComboBox::backgroundColourId, Colours::bg3);

    // setColour(juce::DrawableButton::backgroundColourId, Colours::transparent);
    // setColour(juce::DrawableButton::backgroundOnColourId, Colours::transparent);

    // setColour(juce::Slider::backgroundColourId, Colours::fg2);
    // setColour(juce::Slider::rotarySliderOutlineColourId, Colours::fg2);
    // setColour(juce::Slider::rotarySliderFillColourId, Colours::whiteDirt);
    // setColour(juce::Slider::thumbColourId, Colours::black);
}

} // namespace jml::viewer
