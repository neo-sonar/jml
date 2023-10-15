#pragma once

#include "Core/ValueTreeObjectList.hpp"

namespace jml::designer {

struct Layer;

struct LayerList final : ValueTreeObjectList<Layer>
{
    LayerList(juce::ValueTree v, juce::UndoManager& undoManager);
    ~LayerList() override;

    std::function<void(Layer*)> onAdded{};
    std::function<void(Layer*)> onRemoved{};
    std::function<void()> onOrderChanged{};

private:
    [[nodiscard]] auto isSuitableType(juce::ValueTree const& v) const -> bool override;
    auto createNewObject(juce::ValueTree const& v) -> Layer* override;
    auto deleteObject(Layer* layer) -> void override;
    auto newObjectAdded(Layer* layer) -> void override;
    auto objectRemoved(Layer* layer) -> void override;
    auto objectOrderChanged() -> void override;

    juce::UndoManager& _undoManager;
};

} // namespace jml::designer
