#pragma once

#include "Tool/Tool.hpp"

namespace mc {

enum struct Shape
{
    Drawable,
    Ellipse,
};

struct ShapeTool final
    : Tool
    , juce::MouseListener
{
    ShapeTool(DocumentCanvas& canvas, Shape shape) noexcept;
    ~ShapeTool() override;

    auto paintTool(juce::Graphics& g) -> void override;
    auto mouseDrag(juce::MouseEvent const& event) -> void override;
    auto mouseUp(juce::MouseEvent const& event) -> void override;

private:
    Shape _shape;
    std::optional<juce::Point<float>> _start;
    std::optional<juce::Point<float>> _current;
};

} // namespace mc
