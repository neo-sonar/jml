#include "LookAndFeel.hpp"

namespace jml {

juce::Colour const Colours::black       = juce::Colours::black;
juce::Colour const Colours::transparent = juce::Colours::transparentBlack;
juce::Colour const Colours::white       = juce::Colours::white;
juce::Colour const Colours::whiteDirt   = juce::Colour::fromRGB(240, 240, 240);

juce::Colour const OneLightColours::editorBackground = juce::Colour(0xFFFAFAFA);
juce::Colour const OneLightColours::editorForeground = juce::Colour(0xFF383A42);
juce::Colour const OneLightColours::editorHighlight  = juce::Colour(0xFFE5E5E6);
juce::Colour const OneLightColours::editorLineNumber = juce::Colour(0xFF9D9D9F);

juce::Colour const OneLightColours::codeError       = juce::Colour(0xFFFF1414);
juce::Colour const OneLightColours::codeKeyword     = juce::Colour(0xFFA626A4);
juce::Colour const OneLightColours::codeComment     = juce::Colour(0xFFA0A1A7);
juce::Colour const OneLightColours::codeOperator    = juce::Colour(0xFF383A42);
juce::Colour const OneLightColours::codeIdentifier  = juce::Colour(0xFFC18401);
juce::Colour const OneLightColours::codeInteger     = juce::Colour(0xFF986801);
juce::Colour const OneLightColours::codeFloat       = juce::Colour(0xFF986801);
juce::Colour const OneLightColours::codeString      = juce::Colour(0xFF50A14F);
juce::Colour const OneLightColours::codeBracket     = juce::Colour(0xFF383A42);
juce::Colour const OneLightColours::codePunctuation = juce::Colour(0xFF383A42);

namespace {

auto makeColourScheme(bool custom) -> juce::LookAndFeel_V4::ColourScheme
{
    if (custom) {
        return {
            Colours::whiteDirt,              // windowBackground
            Colours::white,                  // widgetBackground
            Colours::white,                  // menuBackground
            juce::Colours::transparentBlack, // outline
            Colours::black,                  // defaultText
            Colours::white.darker(),         // defaultFill
            Colours::black,                  // highlightedText
            Colours::whiteDirt,              // highlightedFill
            Colours::black,                  // menuText
        };
    }

    return juce::LookAndFeel_V4::getDarkColourScheme();
}

} // namespace

LookAndFeel::LookAndFeel() : juce::LookAndFeel_V4{makeColourScheme(true)}
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

auto getSchemeColour(juce::LookAndFeel_V4::ColourScheme::UIColour id) -> juce::Colour
{
    auto& lnf = juce::LookAndFeel::getDefaultLookAndFeel();
    if (auto* v4 = dynamic_cast<juce::LookAndFeel_V4*>(&lnf); v4 != nullptr) {
        return v4->getCurrentColourScheme().getUIColour(id);
    }

    // You need juce::LookAndFeel_V4 to be a base of the global LNF
    jassertfalse;
    return {};
}

auto getSchemeWindowBackgroundColour() -> juce::Colour
{
    return getSchemeColour(juce::LookAndFeel_V4::ColourScheme::windowBackground);
}

auto getSchemeWidgetBackgroundColour() -> juce::Colour
{
    return getSchemeColour(juce::LookAndFeel_V4::ColourScheme::widgetBackground);
}

auto getSchemeDefaultFillColour() -> juce::Colour
{
    return getSchemeColour(juce::LookAndFeel_V4::ColourScheme::defaultFill);
}

auto getSchemeDefaultTextColour() -> juce::Colour
{
    return getSchemeColour(juce::LookAndFeel_V4::ColourScheme::defaultText);
}

auto getSchemeHighlightFillColour() -> juce::Colour
{
    return getSchemeColour(juce::LookAndFeel_V4::ColourScheme::highlightedFill);
}

auto getSchemeHighlightTextColour() -> juce::Colour
{
    return getSchemeColour(juce::LookAndFeel_V4::ColourScheme::highlightedText);
}

} // namespace jml
