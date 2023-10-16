#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

#include "Application/MenuBar.hpp"
#include "LookAndFeel/Colours.hpp"
#include "LookAndFeel/LookAndFeel.hpp"
#include "Viewer/ScriptPanel.hpp"

namespace jml::viewer {

struct MainComponent
    : juce::Component
    , juce::ApplicationCommandTarget
{
    MainComponent();
    ~MainComponent() override;

    auto paint(juce::Graphics& g) -> void override;
    auto resized() -> void override;

    auto getNextCommandTarget() -> juce::ApplicationCommandTarget* override;
    auto getAllCommands(juce::Array<juce::CommandID>& commands) -> void override;
    auto getCommandInfo(juce::CommandID commandID, juce::ApplicationCommandInfo& result) -> void override;
    auto perform(juce::ApplicationCommandTarget::InvocationInfo const& info) -> bool override;

private:
    auto showAboutWindow() -> void;
    auto loadScriptPath() -> void;

    juce::ApplicationCommandManager _commandManager{};
    juce::UndoManager _undoManager;
    LookAndFeel _lnf;

    MenuBar _menuBar{_commandManager};
    MultiScriptPanel _documents;
    std::unique_ptr<juce::FileChooser> _fileChooser;

    JUCE_LEAK_DETECTOR(MainComponent) // NOLINT
};

} // namespace jml::viewer
