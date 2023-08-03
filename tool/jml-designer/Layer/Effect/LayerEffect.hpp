#pragma once

#include "Core/ValueTreeObject.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

namespace jml::designer {

struct LayerEffect : ValueTreeObject
{
    LayerEffect(juce::ValueTree vt, juce::UndoManager& um);
    virtual ~LayerEffect() = default;

    [[nodiscard]] virtual auto getName() -> juce::String                    = 0;
    [[nodiscard]] virtual auto getImageEffect() -> juce::ImageEffectFilter* = 0;
};

} // namespace jml::designer
