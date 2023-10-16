#pragma once

#include "Document/Document.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

namespace jml::designer {

struct LayerTreeItem;

struct LayerTree final
    : juce::TreeView
    , juce::ChangeBroadcaster
{
    explicit LayerTree(Document& document);
    ~LayerTree() override;

    [[nodiscard]] auto getDocument() -> Document& { return _document; }

    [[nodiscard]] auto getDocument() const -> Document const& { return _document; }

private:
    Document& _document;
    std::unique_ptr<LayerTreeItem> _root;
};

} // namespace jml::designer
