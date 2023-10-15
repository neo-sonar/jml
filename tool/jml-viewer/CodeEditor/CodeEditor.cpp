#include "CodeEditor.hpp"

#include "LookAndFeel/JmlViewerColors.hpp"

namespace jml::viewer {

namespace {
auto makeCodeEditorColorScheme() -> juce::CodeEditorComponent::ColourScheme
{
    using TokenType         = juce::CodeEditorComponent::ColourScheme::TokenType;
    static auto const types = std::array{
        TokenType{"Error", juce::Colour(0xffcc0000)},      TokenType{"Comment", OneLightColors::codeComment},
        TokenType{"Keyword", OneLightColors::codeKeyword}, TokenType{"Operator", OneLightColors::codeOperator},
        TokenType{"Identifier", juce::Colour(0xff000000)}, TokenType{"Integer", OneLightColors::codeInteger},
        TokenType{"Float", OneLightColors::codeFloat},     TokenType{"String", OneLightColors::codeString},
        TokenType{"Bracket", OneLightColors::codeBracket}, TokenType{"Punctuation", juce::Colour(0xff004400)},
    };

    auto cs = juce::CodeEditorComponent::ColourScheme{};
    for (auto const& t : types) { cs.set(t.name, t.colour); }
    return cs;
}
} // namespace
CodeEditor::CodeEditor()
{
    _editor.setLineNumbersShown(true);
    _editor.setColourScheme(makeCodeEditorColorScheme());
    addAndMakeVisible(_editor);
}

auto CodeEditor::file(juce::File file) -> void
{
    _file = std::move(file);
    if (auto stream = _file.createInputStream(); stream) { _document.loadFromStream(*stream); }
}

auto CodeEditor::paint(juce::Graphics& g) -> void { g.fillAll(JmlViewerColors::whiteDirt); }
auto CodeEditor::resized() -> void { _editor.setBounds(getLocalBounds().reduced(16)); }

} // namespace jml::viewer
