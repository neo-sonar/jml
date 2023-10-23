#include "ShapeLayer.hpp"

#include "Component/PropertyPanel.hpp"

namespace jml::designer {

ShapeLayer::ShapeLayer(juce::ValueTree vt, juce::UndoManager& um) : Layer{std::move(vt), um} {}

auto ShapeLayer::paintLayer(juce::Graphics& g) -> void { juce::ignoreUnused(g); }

auto ShapeLayer::addLayerProperties(juce::PropertyPanel& panel) -> void { juce::ignoreUnused(panel); }
} // namespace jml::designer
