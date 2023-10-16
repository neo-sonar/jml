#include "ComponentTree.hpp"

namespace jml::viewer {

ComponentTree::~ComponentTree() { setRootComponent(nullptr); }

auto ComponentTree::setRootComponent(juce::Component* root) -> void
{
    setRootItem(nullptr);
    if (root == nullptr) {
        return;
    }

    _rootItem = std::make_unique<Item>(root);
    setRootItem(_rootItem.get());
}

ComponentTree::Item::Item(juce::Component* root) // NOLINT(misc-no-recursion)
    : _root{root}
{
    auto const& children = root->getChildren();
    for (auto* child : children) {
        addSubItem(std::make_unique<ComponentTree::Item>(child).release());
    }
}

auto ComponentTree::Item::mightContainSubItems() -> bool
{
    if (_root == nullptr) {
        return false;
    }
    return _root->getNumChildComponents() > 0;
}

auto ComponentTree::Item::getUniqueName() const -> juce::String
{
    if (_root == nullptr) {
        return {};
    }
    if (_root->getComponentID().isEmpty()) {
        return "unknown";
    }
    return _root->getComponentID();
}

auto ComponentTree::Item::itemSelectionChanged(bool isNowSelected) -> void
{
    juce::ignoreUnused(isNowSelected);
}

auto ComponentTree::Item::paintItem(juce::Graphics& g, int width, int height) -> void
{
    auto const bounds = juce::Rectangle{0, 0, width, height}.reduced(1);
    g.setColour(Colours::whiteDirt);
    g.fillRect(bounds);

    g.setColour(Colours::black);
    g.drawText(getUniqueName(), bounds.toFloat(), juce::Justification::centred, false);
}

} // namespace jml::viewer
