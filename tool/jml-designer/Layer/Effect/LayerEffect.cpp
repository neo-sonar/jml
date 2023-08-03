#include "LayerEffect.hpp"

namespace jml::designer {

LayerEffect::LayerEffect(juce::ValueTree vt, juce::UndoManager& um) : mc::ValueTreeObject{std::move(vt), &um} {}

} // namespace jml::designer
