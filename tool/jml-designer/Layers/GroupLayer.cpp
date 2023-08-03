#include "GroupLayer.hpp"

namespace jml::designer {

GroupLayer::GroupLayer(juce::ValueTree const& v, juce::UndoManager& undoManager) : Layer{v, undoManager} {}

auto GroupLayer::mightHaveChildren() -> bool { return true; }

} // namespace jml::designer
