#include "ScriptPanel.hpp"

#include <jml_tools/jml_tools.hpp>

namespace jml::viewer {

ScriptPanel::ScriptPanel(juce::ApplicationCommandManager& commandManager)
    : juce::Component{"Script Panel"}
    , _editor{commandManager}
{
    _tabs.setTabBarDepth(50);
    _tabs.addTab("Viewer", getSchemeWidgetBackgroundColour(), &_preview, false);
    _tabs.addTab("Code", getSchemeWidgetBackgroundColour(), &_editor, false);
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
    , _openIcon{getIcon("launch_black_48dp_svg")}
{
    setLayoutMode(juce::MultiDocumentPanel::LayoutMode::MaximisedWindowsWithTabs);
    setBackgroundColour(getSchemeWindowBackgroundColour());
    useFullscreenWhenOneDocument(true);
}

auto MultiScriptPanel::openScript(juce::File const& script) -> void
{
    auto panel = std::make_unique<ScriptPanel>(_commandManager);
    panel->setScriptFile(script);
    addDocument(panel.release(), getSchemeWindowBackgroundColour(), true);
}

auto MultiScriptPanel::reloadActiveScript() -> void
{
    if (auto* panel = dynamic_cast<ScriptPanel*>(getActiveDocument()); panel != nullptr) {
        panel->reloadScriptFile();
    }
}

auto MultiScriptPanel::paint(juce::Graphics& g) -> void
{
    jassert(_openIcon != nullptr);

    MultiDocumentPanel::paint(g);

    if (getNumDocuments() != 0) {
        return;
    }

    auto area = getLocalBounds().reduced(proportionOfWidth(0.25F), proportionOfHeight(0.25F));

    auto const iconArea = area.removeFromTop(area.proportionOfHeight(0.5));
    auto const text     = juce::String{R"(Drop lua script or go to File -> Open)"};

    _openIcon->drawWithin(g, iconArea.toFloat(), juce::RectanglePlacement::centred, 1.0);
    g.setColour(getSchemeDefaultTextColour());
    g.setFont(32.0F);
    g.drawText(text, area, juce::Justification::centred, false);
}

auto MultiScriptPanel::tryToCloseDocumentAsync(
    juce::Component* component,
    std::function<void(bool)> callback
) -> void
{
    callback(component != nullptr);
}

} // namespace jml::viewer
