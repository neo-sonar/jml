#pragma once

#include "Application/MainComponent.hpp"

#include <jml_tools/jml_tools.hpp>

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
    jml::LookAndFeel _lnf;
    std::unique_ptr<juce::DocumentWindow> _mainWindow{nullptr};
};

} // namespace jml::designer
