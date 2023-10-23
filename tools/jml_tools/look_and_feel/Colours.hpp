#pragma once

namespace jml {

struct Colours
{
    static juce::Colour const black;
    static juce::Colour const transparent;
    static juce::Colour const white;
    static juce::Colour const whiteDirt;
};

struct OneLightColours
{
    static juce::Colour const editorBackground;
    static juce::Colour const editorForeground;
    static juce::Colour const editorHighlight;
    static juce::Colour const editorLineNumber;

    static juce::Colour const codeError;
    static juce::Colour const codeKeyword;
    static juce::Colour const codeComment;
    static juce::Colour const codeOperator;
    static juce::Colour const codeIdentifier;
    static juce::Colour const codeInteger;
    static juce::Colour const codeFloat;
    static juce::Colour const codeString;
    static juce::Colour const codeBracket;
    static juce::Colour const codePunctuation;
};

} // namespace jml
