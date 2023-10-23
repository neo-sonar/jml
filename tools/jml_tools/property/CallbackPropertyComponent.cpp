#include "CallbackPropertyComponent.hpp"

namespace jml {

CallbackPropertyComponent::CallbackPropertyComponent(
    juce::String const& name,
    std::function<void()> callback
)
    : ButtonPropertyComponent{name, true}
    , _callback(std::move(callback))
{
    jassert(_callback != nullptr);
}

auto CallbackPropertyComponent::buttonClicked() -> void { _callback(); }

auto CallbackPropertyComponent::getButtonText() const -> juce::String { return "Run"; }

} // namespace jml
