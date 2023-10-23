#include "ScriptViewport.hpp"

#include <jml_tools/jml_tools.hpp>

namespace jml::viewer {

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

auto ScriptViewport::paint(juce::Graphics& g) -> void
{
    g.fillAll(getSchemeWidgetBackgroundColour());
}

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
