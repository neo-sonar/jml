#pragma once

#include <jml_tools/jml_tools.hpp>

namespace jml::viewer {

struct Settings
{
    Settings();

    [[nodiscard]] auto getRecentFiles() -> juce::StringArray;
    auto appendToRecentFiles(juce::File const& file) -> void;
    auto clearRecentFiles() -> void;

    [[nodiscard]] auto getKeyMapping() -> std::unique_ptr<juce::XmlElement>;
    auto setKeyMapping(juce::XmlElement const& xml) -> void;

    [[nodiscard]] auto getThemeFile() -> juce::File;
    auto setThemeFile(juce::File const& file) -> void;

private:
    auto saveRecentFiles() -> void;
    juce::ApplicationProperties _settings;
    juce::RecentlyOpenedFilesList _recentFiles;
};

struct SettingsWindow final
    : juce::PreferencesPanel
    , juce::ChangeListener
{
    explicit SettingsWindow(juce::ApplicationCommandManager& commandManager);
    ~SettingsWindow() override;

    auto createComponentForPage(juce::String const& pageName) -> juce::Component* override;
    auto changeListenerCallback(juce::ChangeBroadcaster* source) -> void override;

    std::function<void()> onThemeChange;

private:
    auto remapColours() -> void;

    juce::ApplicationCommandManager& _commandManager;
    juce::ValueTree _tree{"Settings"};
};

} // namespace jml::viewer
