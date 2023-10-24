#include "ScriptViewport.hpp"

#include <jml_tools/jml_tools.hpp>

namespace jml::viewer {

ScriptViewport::ScriptViewport() : _background{getSchemeWidgetBackgroundColour()} {}

auto ScriptViewport::setViewedComponent(juce::Component* component) -> void
{
    if (_component != nullptr) {
        removeChildComponent(_component);
    }
    if (_component = component; _component != nullptr) {
        addAndMakeVisible(_component);
        resized();
    }
}

auto ScriptViewport::setBackgroundColour(juce::Colour colour) -> void
{
    _background = colour;
    repaint();
}

auto ScriptViewport::paint(juce::Graphics& g) -> void { g.fillAll(_background); }

auto ScriptViewport::resized() -> void
{
    if (_component == nullptr) {
        return;
    }

    auto const area = getLocalBounds();
    auto const size = juce::Rectangle<int>{0, 0, _component->getWidth(), _component->getHeight()};
    _component->setBounds(size.withCentre(area.getCentre()));
}

} // namespace jml::viewer
