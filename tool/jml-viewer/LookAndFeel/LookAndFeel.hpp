#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

namespace jml::viewer {

struct LookAndFeel final : juce::LookAndFeel_V4
{
    LookAndFeel();
    ~LookAndFeel() override = default;
};

} // namespace jml::viewer
