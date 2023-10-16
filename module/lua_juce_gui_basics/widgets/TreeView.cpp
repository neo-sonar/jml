namespace lua_juce {

auto juce_TreeView(sol::table& state) -> void
{
    // clang-format off
    auto treeView = state.new_usertype<juce::TreeView>("TreeView",
        sol::constructors<juce::TreeView(juce::String const&)>(),
        sol::base_classes,
        sol::bases<
            juce::FileDragAndDropTarget,
            juce::DragAndDropTarget,
            juce::MouseListener,
            juce::Component,
            juce::TooltipClient,
            juce::SettableTooltipClient
        >()
    );
    // clang-format on

    treeView["setRootItem"]                  = LUA_JUCE_C_CALL(&juce::TreeView::setRootItem);
    treeView["getRootItem"]                  = LUA_JUCE_C_CALL(&juce::TreeView::getRootItem);
    treeView["deleteRootItem"]               = LUA_JUCE_C_CALL(&juce::TreeView::deleteRootItem);
    treeView["setRootItemVisible"]           = LUA_JUCE_C_CALL(&juce::TreeView::setRootItemVisible);
    treeView["isRootItemVisible"]            = LUA_JUCE_C_CALL(&juce::TreeView::isRootItemVisible);
    treeView["setDefaultOpenness"]           = LUA_JUCE_C_CALL(&juce::TreeView::setDefaultOpenness);
    treeView["areItemsOpenByDefault"]        = LUA_JUCE_C_CALL(&juce::TreeView::areItemsOpenByDefault);
    treeView["setMultiSelectEnabled"]        = LUA_JUCE_C_CALL(&juce::TreeView::setMultiSelectEnabled);
    treeView["isMultiSelectEnabled"]         = LUA_JUCE_C_CALL(&juce::TreeView::isMultiSelectEnabled);
    treeView["setOpenCloseButtonsVisible"]   = LUA_JUCE_C_CALL(&juce::TreeView::setOpenCloseButtonsVisible);
    treeView["areOpenCloseButtonsVisible"]   = LUA_JUCE_C_CALL(&juce::TreeView::areOpenCloseButtonsVisible);
    treeView["clearSelectedItems"]           = LUA_JUCE_C_CALL(&juce::TreeView::clearSelectedItems);
    treeView["getNumSelectedItems"]          = LUA_JUCE_C_CALL(&juce::TreeView::getNumSelectedItems);
    treeView["getSelectedItem"]              = LUA_JUCE_C_CALL(&juce::TreeView::getSelectedItem);
    treeView["moveSelectedRow"]              = LUA_JUCE_C_CALL(&juce::TreeView::moveSelectedRow);
    treeView["getNumRowsInTree"]             = LUA_JUCE_C_CALL(&juce::TreeView::getNumRowsInTree);
    treeView["getItemOnRow"]                 = LUA_JUCE_C_CALL(&juce::TreeView::getItemOnRow);
    treeView["getItemAt"]                    = LUA_JUCE_C_CALL(&juce::TreeView::getItemAt);
    treeView["scrollToKeepItemVisible"]      = LUA_JUCE_C_CALL(&juce::TreeView::scrollToKeepItemVisible);
    treeView["getViewport"]                  = LUA_JUCE_C_CALL(&juce::TreeView::getViewport);
    treeView["getIndentSize"]                = LUA_JUCE_C_CALL(&juce::TreeView::getIndentSize);
    treeView["setIndentSize"]                = LUA_JUCE_C_CALL(&juce::TreeView::setIndentSize);
    treeView["findItemFromIdentifierString"] = LUA_JUCE_C_CALL(&juce::TreeView::findItemFromIdentifierString);
    treeView["getItemComponent"]             = LUA_JUCE_C_CALL(&juce::TreeView::getItemComponent);
    treeView["getOpennessState"]             = LUA_JUCE_C_CALL(&juce::TreeView::getOpennessState);
    treeView["restoreOpennessState"]         = LUA_JUCE_C_CALL(&juce::TreeView::restoreOpennessState);
}

} // namespace lua_juce
