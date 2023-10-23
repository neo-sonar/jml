#pragma once

#include "Tool/Tool.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

namespace jml::designer {
struct AbstractShape;

struct ToolBar final : juce::Component
{
    ToolBar();
    ~ToolBar() override = default;

    auto resized() -> void override;

    std::function<void(ToolType)> onToolChange{};

private:
    auto updateTool() -> void;

    juce::DrawableButton _select{"Select", juce::DrawableButton::ImageFitted};
    juce::DrawableButton _rectangle{"Drawable", juce::DrawableButton::ImageFitted};
    juce::DrawableButton _ellipse{"Ellipse", juce::DrawableButton::ImageFitted};
};

} // namespace jml::designer
