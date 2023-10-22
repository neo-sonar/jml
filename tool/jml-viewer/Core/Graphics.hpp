#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

namespace jml::viewer {

[[nodiscard]] auto getIcon(char const* name) -> std::unique_ptr<juce::Drawable>;

} // namespace jml::viewer
