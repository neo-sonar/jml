#include "ValuePropertyComponent.hpp"

namespace jml {

ValuePropertyComponent::ValuePropertyComponent(juce::Value value, juce::String const& name)
    : PropertyComponent(name)
    , _value(std::move(value))
{
    _value.addListener(this);
}

auto ValuePropertyComponent::getValue() -> juce::Value& { return _value; }

auto ValuePropertyComponent::getValue() const -> juce::Value const& { return _value; }

auto ValuePropertyComponent::valueChanged(juce::Value& /*value*/) -> void { refresh(); }

} // namespace jml
