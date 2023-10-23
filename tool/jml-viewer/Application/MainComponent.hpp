#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

#include "Application/MenuBar.hpp"
#include "Core/Graphics.hpp"
#include "LookAndFeel/Colours.hpp"
#include "Viewer/ScriptPanel.hpp"

namespace jml::viewer {

struct SettingsWindow final : juce::PreferencesPanel
{
    SettingsWindow()
    {
        auto code = getIcon("data_object_black_48dp_svg");
        auto look = getIcon("palette_black_48dp_svg");
        addSettingsPage("Code", code.get(), code.get(), code.get());
        addSettingsPage("Look", look.get(), look.get(), look.get());
    }

    ~SettingsWindow() override = default;

    auto createComponentForPage(juce::String const& pageName) -> juce::Component* override
    {
        if (pageName == "Look") {
            auto num  = tree.getPropertyAsValue("num", nullptr);
            auto text = tree.getPropertyAsValue("text", nullptr);

            auto panel = std::make_unique<juce::PropertyPanel>();
            panel->addProperties(juce::Array<juce::PropertyComponent*>{
                std::make_unique<juce::SliderPropertyComponent>(num, "Num", 0.0, 1.0, 0.0).release(),
                std::make_unique<juce::TextPropertyComponent>(text, "Text", 32, false).release(),
            });
            return panel.release();
        }

        auto foo = tree.getPropertyAsValue("foo", nullptr);
        auto bar = tree.getPropertyAsValue("bar", nullptr);

        auto panel = std::make_unique<juce::PropertyPanel>();
        panel->addProperties(juce::Array<juce::PropertyComponent*>{
            std::make_unique<juce::SliderPropertyComponent>(foo, "Foo", 0.0, 1.0, 0.0).release(),
            std::make_unique<juce::TextPropertyComponent>(bar, "Bar", 32, false).release(),
        });
        return panel.release();
    }

private:
    juce::ValueTree tree{"Settings"};
};

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
    SettingsWindow _settings;
    std::unique_ptr<juce::FileChooser> _fileChooser;

    JUCE_LEAK_DETECTOR(MainComponent) // NOLINT
};

} // namespace jml::viewer
