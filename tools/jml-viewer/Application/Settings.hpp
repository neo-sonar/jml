#pragma once

#include <jml_tools/jml_tools.hpp>

namespace jml::viewer {

struct Settings
{
    Settings();

    [[nodiscard]] auto getRecentFiles() -> juce::StringArray;
    auto appendToRecentOpenFiles(juce::File const& file) -> void;
    auto clearRecentOpenFiles() -> void;

private:
    auto saveRecentFiles() -> void;
    juce::ApplicationProperties _settings;
    juce::RecentlyOpenedFilesList _recentFiles;
};

struct SettingsWindow final : juce::PreferencesPanel
{
    explicit SettingsWindow(juce::ApplicationCommandManager& commandManager)
        : _commandManager{commandManager}
    {
        auto code     = getIcon("data_object_black_48dp_svg");
        auto look     = getIcon("palette_black_48dp_svg");
        auto shortcut = getIcon("keyboard_black_48dp_svg");
        addSettingsPage("Code", code.get(), code.get(), code.get());
        addSettingsPage("Look", look.get(), look.get(), look.get());
        addSettingsPage("Shortcut", shortcut.get(), shortcut.get(), shortcut.get());
    }

    ~SettingsWindow() override
    {
        DBG(_commandManager.getKeyMappings()->createXml(false)->toString());
    }

    auto createComponentForPage(juce::String const& pageName) -> juce::Component* override
    {
        if (pageName == "Code") {
            auto foo   = tree.getPropertyAsValue("foo", nullptr);
            auto bar   = tree.getPropertyAsValue("bar", nullptr);
            auto panel = std::make_unique<juce::PropertyPanel>();
            panel->addProperties(juce::Array<juce::PropertyComponent*>{
                std::make_unique<juce::SliderPropertyComponent>(foo, "Foo", 0.0, 1.0, 0.0).release(),
                std::make_unique<juce::TextPropertyComponent>(bar, "Bar", 32, false).release(),
            });
            return panel.release();
        }

        if (pageName == "Shortcut") {
            auto& mappings = *_commandManager.getKeyMappings();
            return std::make_unique<juce::KeyMappingEditorComponent>(mappings, true).release();
        }

        if (pageName == "Look") {
            auto theme        = tree.getPropertyAsValue("theme", nullptr);
            auto themeOptions = FilePropertyComponent::Options{.pattern = "*.lua"};

            auto panel = std::make_unique<juce::PropertyPanel>();
            panel->addProperties(juce::Array<juce::PropertyComponent*>{
                std::make_unique<FilePropertyComponent>(theme, "Theme", themeOptions).release(),
                std::make_unique<CallbackPropertyComponent>("Reload", [] {}).release(),
            });
            return panel.release();
        }

        jassertfalse;
        return nullptr;
    }

private:
    juce::ApplicationCommandManager& _commandManager;
    juce::ValueTree tree{"Settings"};
};

} // namespace jml::viewer
