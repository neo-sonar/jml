#pragma once

#include "Application/CommandLine.hpp"

#include <juce_audio_processors/juce_audio_processors.h>

namespace jml::viewer {

struct NullAudioProcessor final : juce::AudioProcessor
{
    NullAudioProcessor()           = default;
    ~NullAudioProcessor() override = default;

    auto getName() const -> juce::String const override { return "Null"; }

    auto prepareToPlay(double /*sampleRate*/, int /*maximumExpectedSamplesPerBlock*/) -> void override
    {}

    using juce::AudioProcessor::processBlock;

    auto processBlock(juce::AudioBuffer<float>& /*buffer*/, juce::MidiBuffer& /*midiMessages*/)
        -> void override
    {}

    auto releaseResources() -> void override {}

    auto getTailLengthSeconds() const -> double override { return 0.0; }

    auto acceptsMidi() const -> bool override { return false; }

    auto producesMidi() const -> bool override { return false; }

    auto createEditor() -> juce::AudioProcessorEditor* override { return nullptr; }

    auto hasEditor() const -> bool override { return false; }

    auto getNumPrograms() -> int override { return 1; }

    auto getCurrentProgram() -> int override { return 1; }

    auto setCurrentProgram(int /*index*/) -> void override {}

    auto getProgramName(int /*index*/) -> juce::String const override { return {}; }

    auto changeProgramName(int /*index*/, juce::String const& /*newName*/) -> void override {}

    auto getStateInformation(juce::MemoryBlock& /*destData*/) -> void override {}

    auto setStateInformation(void const* /*data*/, int /*sizeInBytes*/) -> void override {}
};

inline auto runTestScript(CommandLine const& cli) -> juce::Result
{
    auto state = sol::state{};
    state.open_libraries(
        sol::lib::base,
        sol::lib::debug,
        sol::lib::io,
        sol::lib::math,
        sol::lib::os,
        sol::lib::package,
        sol::lib::string,
        sol::lib::table
    );
    lua_juce::allModules(state);

    auto in     = juce::MemoryInputStream{juce::MemoryBlock{32}, true};
    auto out    = juce::MemoryOutputStream{0};
    auto button = juce::TextButton{};
    auto& lnf   = juce::Desktop::getInstance().getDefaultLookAndFeel();
    auto proc   = NullAudioProcessor{};

    auto doc                  = state[sol::create_if_nil]["juce"]["abstract"];
    doc["MemoryInputStream"]  = static_cast<juce::MemoryInputStream*>(&in);
    doc["MemoryOutputStream"] = static_cast<juce::MemoryOutputStream*>(&out);
    doc["InputStream"]        = static_cast<juce::InputStream*>(&in);
    doc["OutputStream"]       = static_cast<juce::OutputStream*>(&out);
    doc["Button"]             = static_cast<juce::Button*>(&button);
    doc["LookAndFeel"]        = static_cast<juce::LookAndFeel*>(&lnf);
    doc["AudioProcessor"]     = static_cast<juce::AudioProcessor*>(&proc);

    auto const scriptFile = juce::File{cli.scriptPath};
    if (cli.verbose) {
        std::cout << "Run test: " << scriptFile.getFileNameWithoutExtension().toStdString() << '\n';
    }
    scriptFile.getParentDirectory().setAsCurrentWorkingDirectory();

    auto script = state.load_file(scriptFile.getFullPathName().toStdString());
    if (not script.valid()) {
        sol::error const error = script;
        return juce::Result::fail(error.what());
    }

    auto factory = script.get<sol::protected_function>();
    auto result  = factory();
    if (not result.valid()) {
        sol::error const error = result;
        return juce::Result::fail(error.what());
    }

    if (cli.verbose) {
        std::cout << "Done test: " << scriptFile.getFileNameWithoutExtension().toStdString() << '\n';
    }
    return juce::Result::ok();
}
} // namespace jml::viewer
