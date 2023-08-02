#include "LayerTree.hpp"

#include "Layer/LayerTreeItem.hpp"

namespace mc {

LayerTree::LayerTree(Document& document)
    : _document{document}, _root{std::make_unique<LayerTreeItem>(*document.getRootLayer())}
{
    // setRootItemVisible(false);
    setMultiSelectEnabled(true);
    setRootItem(_root.get());
    setIndentSize(16);
}

LayerTree::~LayerTree() { setRootItem(nullptr); }

} // namespace mc
