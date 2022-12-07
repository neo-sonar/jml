#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

#include "Application/MenuBar.hpp"
#include "CodeEditor/CodeEditor.hpp"
#include "LookAndFeel/LuaSuculentaColors.hpp"
#include "LookAndFeel/LuaSuculentaLookAndFeel.hpp"
#include "Preview/ComponentContainer.hpp"
#include "Preview/ComponentTree.hpp"
#include "Preview/FileChangeListener.hpp"
#include "Preview/LuaPreview.hpp"

namespace mc {

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
    auto doReload(juce::File const& file) -> void;

    auto loadScriptPath() -> void;

    juce::ApplicationCommandManager _commandManager{};
    juce::UndoManager _undoManager;
    LuaSuculentaLookAndFeel _lnf;

    MenuBar _menuBar{_commandManager};
    juce::TabbedComponent _tabs{juce::TabbedButtonBar::TabsAtLeft};
    LuaPreview _preview;
    CodeEditor _editor;
    std::unique_ptr<juce::FileChooser> _fileChooser;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};

} // namespace mc