#pragma once

#include "Application/MainComponent.hpp"

#include "LookAndFeel/LookAndFeel.hpp"

namespace jml::designer {

struct Application final : juce::JUCEApplication
{
    Application()           = default;
    ~Application() override = default;

    [[nodiscard]] auto getApplicationName() -> juce::String const override;
    [[nodiscard]] auto getApplicationVersion() -> juce::String const override;
    [[nodiscard]] auto moreThanOneInstanceAllowed() -> bool override;

    auto initialise(juce::String const& commandLine) -> void override;
    auto shutdown() -> void override;
    auto systemRequestedQuit() -> void override;
    auto anotherInstanceStarted(juce::String const& commandLine) -> void override;

private:
    juce::LookAndFeel_V4 _lnf{makeColorScheme(defaultColorScheme)};
    std::unique_ptr<juce::DocumentWindow> _mainWindow{nullptr};
};

} // namespace jml::designer
