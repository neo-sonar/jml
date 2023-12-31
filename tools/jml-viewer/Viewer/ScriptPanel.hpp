#pragma once

#include "CodeEditor/CodeEditor.hpp"
#include "Viewer/LuaScriptViewer.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

namespace jml::viewer {

struct ScriptPanel final : juce::Component
{
    explicit ScriptPanel(juce::ApplicationCommandManager& commandManager);
    ~ScriptPanel() override = default;

    auto setScriptFile(juce::File const& file) -> void;
    auto reloadScriptFile() -> void;

    auto resized() -> void override;

private:
    juce::TabbedComponent _tabs{juce::TabbedButtonBar::TabsAtLeft};
    LuaScriptViewer _preview;
    CodeEditor _editor;
};

struct MultiScriptPanel final : juce::MultiDocumentPanel
{
    explicit MultiScriptPanel(juce::ApplicationCommandManager& commandManager);
    ~MultiScriptPanel() override = default;

    auto openScript(juce::File const& script) -> void;
    auto reloadActiveScript() -> void;

    // juce::MultiDocumentPanel
    auto paint(juce::Graphics& g) -> void override;
    auto tryToCloseDocumentAsync(juce::Component* component, std::function<void(bool)> callback)
        -> void override;

private:
    juce::ApplicationCommandManager& _commandManager;
    std::unique_ptr<juce::Drawable> _openIcon;
};

} // namespace jml::viewer
