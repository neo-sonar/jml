#pragma once

#include "Layer/Layer.hpp"

#include <juce_data_structures/juce_data_structures.h>

namespace jml::designer {

struct GroupLayer final : Layer
{
    struct IDs
    {
        inline static constexpr auto const* type = "Group";
    };

    GroupLayer(juce::ValueTree const& v, juce::UndoManager& undoManager);
    ~GroupLayer() override = default;

    auto mightHaveChildren() -> bool override;
};

} // namespace jml::designer
