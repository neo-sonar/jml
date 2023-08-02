#pragma once

#include "Document/DocumentEditor.hpp"
#include "Menu/MenuBar.hpp"

#include <juce_gui_extra/juce_gui_extra.h>

namespace mc {
struct MainComponent final
    : juce::Component
    , juce::DragAndDropContainer
    , juce::ApplicationCommandTarget
{
    MainComponent();
    ~MainComponent() override;

    auto getNextCommandTarget() -> juce::ApplicationCommandTarget* override;
    auto getAllCommands(juce::Array<juce::CommandID>& commands) -> void override;
    auto getCommandInfo(juce::CommandID commandID, juce::ApplicationCommandInfo& result) -> void override;
    auto perform(juce::ApplicationCommandTarget::InvocationInfo const& info) -> bool override;

    auto paint(juce::Graphics& /*g*/) -> void override;
    auto resized() -> void override;

private:
    auto documentLoad() -> void;
    auto documentSaveAs() -> void;

    juce::UndoManager _undoManager;
    juce::ApplicationCommandManager _commandManager{};
    std::unique_ptr<juce::FileChooser> _fileChooser{};
    MenuBar _menuBar{_commandManager};

    juce::File _documentFile;
    std::unique_ptr<Document> _document{std::make_unique<Document>(juce::ValueTree{"JML"}, &_undoManager)};
    std::unique_ptr<DocumentEditor> _editor{std::make_unique<DocumentEditor>(*_document)};
};

} // namespace mc
