#pragma once

#include <mc_data_structures/mc_data_structures.hpp>
#include <mc_graphics/mc_graphics.hpp>
#include <mc_gui_basics/mc_gui_basics.hpp>

namespace mc {

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
    auto deleteObject(Layer* c) -> void override;
    auto newObjectAdded(Layer* layer) -> void override;
    auto objectRemoved(Layer* layer) -> void override;
    auto objectOrderChanged() -> void override;

    juce::UndoManager& _undoManager;
};

struct LayerListener
{
    virtual ~LayerListener() = default;

    virtual auto layerChildrenChanged(Layer* layer) -> void;
    virtual auto layerBeingDeleted(Layer* layer) -> void;
};

struct LayerCanvas final
    : juce::Component
    , juce::ValueTree::Listener
{
    ~LayerCanvas() override;

    [[nodiscard]] auto layer() -> Layer&;
    [[nodiscard]] auto layer() const -> Layer const&;

    auto paint(juce::Graphics& g) -> void override;
    auto valueTreePropertyChanged(juce::ValueTree& tree, juce::Identifier const& property) -> void override;

private:
    explicit LayerCanvas(Layer& layer);

    friend Layer;
    Layer& _layer;
};

struct LayerIDs
{
    inline static constexpr auto const* uuid = "uuid";
    inline static constexpr auto const* name = "name";

    inline static constexpr auto const* x      = "x";
    inline static constexpr auto const* y      = "y";
    inline static constexpr auto const* width  = "width";
    inline static constexpr auto const* height = "height";

    inline static constexpr auto const* background = "background";
    inline static constexpr auto const* opacity    = "opacity";
};

struct Layer : ValueTreeObject
{
    using IDs      = LayerIDs;
    using Listener = LayerListener;
    using Canvas   = LayerCanvas;

    Layer(juce::ValueTree vt, juce::UndoManager& um);
    virtual ~Layer();

    [[nodiscard]] virtual auto mightHaveChildren() -> bool;
    virtual auto paintLayer(juce::Graphics& g) -> void;

    [[nodiscard]] auto getCanvas() -> Canvas&;
    [[nodiscard]] auto getCanvas() const -> Canvas const&;

    [[nodiscard]] auto getUUID() const -> juce::String;

    auto setName(juce::String const& newName) -> void;
    [[nodiscard]] auto getName() const -> juce::String;

    auto setBackground(juce::Colour newColor) -> void;
    [[nodiscard]] auto getBackground() const -> juce::Colour;

    auto setOpacity(float newOpacity) -> void;
    [[nodiscard]] auto getOpacity() const -> float;

    auto setX(float x) -> void;
    [[nodiscard]] auto getX() const -> float;

    auto setY(float y) -> void;
    [[nodiscard]] auto getY() const -> float;

    auto setWidth(float width) -> void;
    [[nodiscard]] auto getWidth() const -> float;

    auto setHeight(float height) -> void;
    [[nodiscard]] auto getHeight() const -> float;

    [[nodiscard]] auto getBounds() const -> juce::Rectangle<float>;

    [[nodiscard]] auto getNumChildren() const -> int;
    [[nodiscard]] auto getChildren() const -> juce::Array<Layer*> const&;

    auto addListener(Listener* listener) -> void;
    auto removeListener(Listener* listener) -> void;

private:
    Canvas _canvas{*this};
    LayerList _children{valueTree(), *undoManager()};
    juce::ListenerList<Listener> _listeners;

    juce::WeakReference<Layer>::Master masterReference; // NOLINT
    friend class juce::WeakReference<Layer>;
};

} // namespace mc
