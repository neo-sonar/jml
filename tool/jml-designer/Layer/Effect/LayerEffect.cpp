#include "LayerEffect.hpp"

namespace jml::designer {

LayerEffect::LayerEffect(juce::ValueTree vt, juce::UndoManager& um)
    : ValueTreeObject{std::move(vt), &um}
{}

} // namespace jml::designer
