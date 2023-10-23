#include "CodeEditor.hpp"

#include "LookAndFeel/Colours.hpp"

namespace jml::viewer {

namespace {
auto makeCodeEditorColorScheme() -> juce::CodeEditorComponent::ColourScheme
{
    using TokenType         = juce::CodeEditorComponent::ColourScheme::TokenType;
    static auto const types = std::array{
        TokenType{"Error",       juce::Colour(0xffcc0000)     },
        TokenType{"Comment",     OneLightColours::codeComment },
        TokenType{"Keyword",     OneLightColours::codeKeyword },
        TokenType{"Operator",    OneLightColours::codeOperator},
        TokenType{"Identifier",  juce::Colour(0xff000000)     },
        TokenType{"Integer",     OneLightColours::codeInteger },
        TokenType{"Float",       OneLightColours::codeFloat   },
        TokenType{"String",      OneLightColours::codeString  },
        TokenType{"Bracket",     OneLightColours::codeBracket },
        TokenType{"Punctuation", juce::Colour(0xff004400)     },
    };

    auto cs = juce::CodeEditorComponent::ColourScheme{};
    for (auto const& t : types) {
        cs.set(t.name, t.colour);
    }
    return cs;
}
} // namespace

CodeEditor::CodeEditor(juce::ApplicationCommandManager& commandManager)
{
    _editor.setLineNumbersShown(true);
    _editor.setColourScheme(makeCodeEditorColorScheme());
    _editor.setCommandManager(&commandManager);
    addAndMakeVisible(_editor);
}

auto CodeEditor::file(juce::File file) -> void
{
    _file = std::move(file);
    if (auto stream = _file.createInputStream(); stream) {
        _document.loadFromStream(*stream);
    }
}

auto CodeEditor::paint(juce::Graphics& g) -> void { g.fillAll(Colours::whiteDirt); }

auto CodeEditor::resized() -> void { _editor.setBounds(getLocalBounds().reduced(16)); }

} // namespace jml::viewer
