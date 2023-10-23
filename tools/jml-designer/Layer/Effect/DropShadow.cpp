#include "DropShadow.hpp"

namespace jml::designer {

DropShadow::DropShadow(juce::ValueTree vt, juce::UndoManager& um) : LayerEffect{std::move(vt), um} {}

auto DropShadow::getName() -> juce::String { return IDs::type; }

auto DropShadow::getImageEffect() -> juce::ImageEffectFilter* { return &_effect; }

} // namespace jml::designer
