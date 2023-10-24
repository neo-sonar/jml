#pragma once

#include "Application/MenuBar.hpp"
#include "Application/Settings.hpp"
#include "Viewer/ScriptPanel.hpp"

#include <jml_tools/jml_tools.hpp>

namespace jml::viewer {

struct MainComponent
    : juce::Component
    , juce::ApplicationCommandTarget
    , juce::FileDragAndDropTarget
{
    MainComponent();
    ~MainComponent() override;

    // juce::Component
    auto paint(juce::Graphics& g) -> void override;
    auto resized() -> void override;

    // juce::ApplicationCommandTarget
    auto getNextCommandTarget() -> juce::ApplicationCommandTarget* override;
    auto getAllCommands(juce::Array<juce::CommandID>& commands) -> void override;
    auto getCommandInfo(juce::CommandID id, juce::ApplicationCommandInfo& result) -> void override;
    auto perform(juce::ApplicationCommandTarget::InvocationInfo const& info) -> bool override;

    // juce::FileDragAndDropTarget
    auto isInterestedInFileDrag(juce::StringArray const& files) -> bool override;
    auto filesDropped(juce::StringArray const& files, int x, int y) -> void override;

private:
    auto showSettingsWindow() -> void;
    auto showAboutWindow() -> void;
    auto loadScriptPath() -> void;

    juce::ApplicationCommandManager _commandManager{};
    juce::UndoManager _undoManager;

    MenuBar _menuBar{_commandManager};
    MultiScriptPanel _documents{_commandManager};
    SettingsWindow _settings{_commandManager};
    std::unique_ptr<juce::FileChooser> _fileChooser;

    JUCE_LEAK_DETECTOR(MainComponent) // NOLINT
};

} // namespace jml::viewer
