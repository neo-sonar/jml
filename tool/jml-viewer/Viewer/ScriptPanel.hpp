#pragma once

#include "CodeEditor/CodeEditor.hpp"
#include "Viewer/LuaScriptViewer.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

namespace jml::viewer {

struct ScriptPanel final : juce::Component
{
    ScriptPanel();
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
    MultiScriptPanel();
    ~MultiScriptPanel() override = default;

    auto openScript(juce::File const& script) -> void;
    auto reloadActiveScript() -> void;

    auto tryToCloseDocumentAsync(juce::Component* component, std::function<void(bool)> callback) -> void override;

private:
};

} // namespace jml::viewer
