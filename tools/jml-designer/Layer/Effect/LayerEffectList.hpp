#pragma once

#include "Core/ValueTreeObjectList.hpp"
#include "Layer/Effect/LayerEffect.hpp"

namespace jml::designer {

struct LayerEffectList final : ValueTreeObjectList<LayerEffect>
{
    LayerEffectList(juce::ValueTree v, juce::UndoManager& undoManager);
    ~LayerEffectList() override;

    std::function<void(LayerEffect*)> onAdded{};
    std::function<void(LayerEffect*)> onRemoved{};
    std::function<void()> onOrderChanged{};

private:
    [[nodiscard]] auto isSuitableType(juce::ValueTree const& v) const -> bool override;
    auto createNewObject(juce::ValueTree const& v) -> LayerEffect* override;
    auto deleteObject(LayerEffect* layer) -> void override;
    auto newObjectAdded(LayerEffect* layer) -> void override;
    auto objectRemoved(LayerEffect* layer) -> void override;
    auto objectOrderChanged() -> void override;

    juce::UndoManager& _undoManager;
};

} // namespace jml::designer
