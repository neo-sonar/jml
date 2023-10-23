#include "ScriptPanel.hpp"

#include "LookAndFeel/Colours.hpp"

namespace jml::viewer {

ScriptPanel::ScriptPanel(juce::ApplicationCommandManager& commandManager)
    : juce::Component{"Script Panel"}
    , _editor{commandManager}
{
    _tabs.setTabBarDepth(50);
    _tabs.addTab("Viewer", Colours::black, &_preview, false);
    _tabs.addTab("Code", Colours::black, &_editor, false);
    addAndMakeVisible(_tabs);
}

auto ScriptPanel::setScriptFile(juce::File const& file) -> void
{
    _preview.setScriptFile(file);
    _editor.file(file);
    setName(file.getFileNameWithoutExtension());
}

auto ScriptPanel::reloadScriptFile() -> void { setScriptFile(_preview.getScriptFile()); }

auto ScriptPanel::resized() -> void { _tabs.setBounds(getLocalBounds()); }

MultiScriptPanel::MultiScriptPanel(juce::ApplicationCommandManager& commandManager)
    : _commandManager{commandManager}
{
    setLayoutMode(juce::MultiDocumentPanel::LayoutMode::MaximisedWindowsWithTabs);
    setBackgroundColour(juce::Colours::white);
    useFullscreenWhenOneDocument(true);
}

auto MultiScriptPanel::openScript(juce::File const& script) -> void
{
    auto panel = std::make_unique<ScriptPanel>(_commandManager);
    panel->setScriptFile(script);
    addDocument(panel.release(), juce::Colours::white, true);
}

auto MultiScriptPanel::reloadActiveScript() -> void
{
    if (auto* panel = dynamic_cast<ScriptPanel*>(getActiveDocument()); panel != nullptr) {
        panel->reloadScriptFile();
    }
}

auto MultiScriptPanel::tryToCloseDocumentAsync(
    juce::Component* component,
    std::function<void(bool)> callback
) -> void
{
    callback(component != nullptr);
}

} // namespace jml::viewer
