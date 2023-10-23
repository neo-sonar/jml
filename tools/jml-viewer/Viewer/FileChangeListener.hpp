#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

namespace jml::viewer {
struct FileChangeListener final : juce::Timer
{
    explicit FileChangeListener(juce::File file);
    ~FileChangeListener() override = default;

    std::function<void()> onChange{};

private:
    auto timerCallback() -> void override;

    juce::File _file;
    juce::Time _writeTime;
};

} // namespace jml::viewer
