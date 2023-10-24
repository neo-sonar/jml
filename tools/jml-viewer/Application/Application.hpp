#pragma once

#include "Application/Settings.hpp"

#include <jml_tools/jml_tools.hpp>
#include <juce_gui_basics/juce_gui_basics.h>

namespace jml::viewer {

struct Application final : juce::JUCEApplication
{
    Application()           = default;
    ~Application() override = default;

    auto getSettings() -> Settings&;

    auto getApplicationName() -> juce::String const override;
    auto getApplicationVersion() -> juce::String const override;

    auto initialise(juce::String const& commandLine) -> void override;
    auto shutdown() -> void override;
    auto systemRequestedQuit() -> void override;

    auto moreThanOneInstanceAllowed() -> bool override;
    auto anotherInstanceStarted(juce::String const& commandLine) -> void override;

    struct MainWindow : juce::DocumentWindow
    {
        explicit MainWindow(juce::String const& name);
        ~MainWindow() override = default;

        auto closeButtonPressed() -> void override;
    };

private:
    Settings _settings;
    jml::LookAndFeel _lnf;
    std::unique_ptr<MainWindow> _mainWindow;
};

[[nodiscard]] auto getApplication() -> Application&;
[[nodiscard]] auto getApplicationSettings() -> Settings&;

} // namespace jml::viewer
