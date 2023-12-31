#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

namespace jml::viewer {

struct CodeEditor : juce::Component
{
    explicit CodeEditor(juce::ApplicationCommandManager& commandManager);
    ~CodeEditor() override = default;

    auto file(juce::File file) -> void;

    auto paint(juce::Graphics& g) -> void override;
    auto resized() -> void override;

private:
    juce::File _file;
    juce::CodeDocument _document;
    juce::LuaTokeniser _tokenizer;
    juce::CodeEditorComponent _editor{_document, &_tokenizer};
};

} // namespace jml::viewer
