#pragma once

namespace jml {

struct CallbackPropertyComponent final : juce::ButtonPropertyComponent
{
    CallbackPropertyComponent(juce::String const& name, std::function<void()> callback);
    ~CallbackPropertyComponent() override = default;

    [[nodiscard]] auto getButtonText() const -> juce::String override;

    auto buttonClicked() -> void override;

private:
    std::function<void()> _callback;
};

} // namespace jml
