#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

namespace jml::viewer {

struct ScriptViewport final : juce::Component
{
    ScriptViewport()           = default;
    ~ScriptViewport() override = default;

    auto setViewedComponent(juce::Component* component) -> void;

    auto paint(juce::Graphics& g) -> void override;
    auto resized() -> void override;

private:
    juce::Component* _component{nullptr};
};

} // namespace jml::viewer
