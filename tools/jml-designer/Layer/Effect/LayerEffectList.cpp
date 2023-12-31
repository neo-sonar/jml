#include "LayerEffectList.hpp"

#include "Layer/Effect/DropShadow.hpp"
#include "Layer/Effect/GlowEffect.hpp"

namespace jml::designer {

LayerEffectList::LayerEffectList(juce::ValueTree v, juce::UndoManager& undoManager)
    : ValueTreeObjectList<LayerEffect>(std::move(v))
    , _undoManager{undoManager}
{
    rebuildObjects();
}

LayerEffectList::~LayerEffectList() { freeObjects(); }

auto LayerEffectList::isSuitableType(juce::ValueTree const& v) const -> bool
{
    auto const type = v.getType().toString();
    if (type == DropShadow::IDs::type) {
        return true;
    }
    if (type == GlowEffect::IDs::type) {
        return true;
    }
    return false;
}

auto LayerEffectList::createNewObject(juce::ValueTree const& v) -> LayerEffect*
{
    auto const type = v.getType().toString();
    if (type == DropShadow::IDs::type) {
        return new DropShadow{v, _undoManager};
    }
    if (type == GlowEffect::IDs::type) {
        return new GlowEffect{v, _undoManager};
    }
    return nullptr;
}

auto LayerEffectList::deleteObject(LayerEffect* layer) -> void
{
    delete layer; // NOLINT
}

auto LayerEffectList::newObjectAdded(LayerEffect* layer) -> void
{
    if (onAdded) {
        onAdded(layer);
    }
}

auto LayerEffectList::objectRemoved(LayerEffect* layer) -> void
{
    if (onRemoved) {
        onRemoved(layer);
    }
}

auto LayerEffectList::objectOrderChanged() -> void
{
    if (onOrderChanged) {
        onOrderChanged();
    }
}

} // namespace jml::designer
