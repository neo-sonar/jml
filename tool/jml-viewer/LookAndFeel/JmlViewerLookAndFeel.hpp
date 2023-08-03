#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

namespace jml::viewer {

struct JmlViewerLookAndFeel final : juce::LookAndFeel_V4
{
    JmlViewerLookAndFeel();
    ~JmlViewerLookAndFeel() override = default;
};

} // namespace jml::viewer
