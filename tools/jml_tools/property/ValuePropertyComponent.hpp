#pragma once

namespace jml {

struct ValuePropertyComponent
    : juce::PropertyComponent
    , private juce::Value::Listener
{

    ValuePropertyComponent(juce::Value value, juce::String const& name);
    ~ValuePropertyComponent() override = default;

    [[nodiscard]] auto getValue() -> juce::Value&;
    [[nodiscard]] auto getValue() const -> juce::Value const&;

private:
    auto valueChanged(juce::Value& /*value*/) -> void override;

    juce::Value _value;
};

} // namespace jml
