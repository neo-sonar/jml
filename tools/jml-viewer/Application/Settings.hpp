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

private:
    juce::ApplicationCommandManager& _commandManager;
    juce::ValueTree tree{"Settings"};
};

} // namespace jml::viewer
