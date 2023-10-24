#pragma once

namespace jml {

[[nodiscard]] auto getIcon(char const* name) -> std::unique_ptr<juce::Drawable>;
[[nodiscard]] auto getIcon(char const* name, juce::Colour colour) -> std::unique_ptr<juce::Drawable>;

} // namespace jml
