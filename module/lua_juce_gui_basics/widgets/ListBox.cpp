namespace lua_juce {

auto juce_ListBox(sol::table& state) -> void
{
    // clang-format off
    auto listBox = state.new_usertype<juce::ListBox>("InternalListBox",
        sol::no_construction{},
        sol::base_classes,
        sol::bases<
            juce::MouseListener,
            juce::Component,
            juce::TooltipClient,
            juce::SettableTooltipClient
        >()
    );
    // clang-format on

    listBox["getListBoxModel"]                = LUA_JUCE_C_CALL(&juce::ListBox::getListBoxModel);
    listBox["updateContent"]                  = LUA_JUCE_C_CALL(&juce::ListBox::updateContent);
    listBox["setMultipleSelectionEnabled"]    = LUA_JUCE_C_CALL(&juce::ListBox::setMultipleSelectionEnabled);
    listBox["setClickingTogglesRowSelection"] = LUA_JUCE_C_CALL(&juce::ListBox::setClickingTogglesRowSelection);
    listBox["setRowSelectedOnMouseDown"]      = LUA_JUCE_C_CALL(&juce::ListBox::setRowSelectedOnMouseDown);
    listBox["setMouseMoveSelectsRows"]        = LUA_JUCE_C_CALL(&juce::ListBox::setMouseMoveSelectsRows);
    listBox["selectRow"]                      = LUA_JUCE_C_CALL(&juce::ListBox::selectRow);
    listBox["selectRangeOfRows"]              = LUA_JUCE_C_CALL(&juce::ListBox::selectRangeOfRows);
    listBox["deselectRow"]                    = LUA_JUCE_C_CALL(&juce::ListBox::deselectRow);
    listBox["deselectAllRows"]                = LUA_JUCE_C_CALL(&juce::ListBox::deselectAllRows);
    listBox["flipRowSelection"]               = LUA_JUCE_C_CALL(&juce::ListBox::flipRowSelection);
    listBox["getSelectedRows"]                = LUA_JUCE_C_CALL(&juce::ListBox::getSelectedRows);
    listBox["isRowSelected"]                  = LUA_JUCE_C_CALL(&juce::ListBox::isRowSelected);
    listBox["getNumSelectedRows"]             = LUA_JUCE_C_CALL(&juce::ListBox::getNumSelectedRows);
    listBox["getSelectedRow"]                 = LUA_JUCE_C_CALL(&juce::ListBox::getSelectedRow);
    listBox["getLastRowSelected"]             = LUA_JUCE_C_CALL(&juce::ListBox::getLastRowSelected);
    listBox["selectRowsBasedOnModifierKeys"]  = LUA_JUCE_C_CALL(&juce::ListBox::selectRowsBasedOnModifierKeys);
    listBox["setVerticalPosition"]            = LUA_JUCE_C_CALL(&juce::ListBox::setVerticalPosition);
    listBox["getVerticalPosition"]            = LUA_JUCE_C_CALL(&juce::ListBox::getVerticalPosition);
    listBox["scrollToEnsureRowIsOnscreen"]    = LUA_JUCE_C_CALL(&juce::ListBox::scrollToEnsureRowIsOnscreen);
    listBox["getVerticalScrollBar"]           = LUA_JUCE_C_CALL(&juce::ListBox::getVerticalScrollBar);
    listBox["getHorizontalScrollBar"]         = LUA_JUCE_C_CALL(&juce::ListBox::getHorizontalScrollBar);
    listBox["getRowContainingPosition"]       = LUA_JUCE_C_CALL(&juce::ListBox::getRowContainingPosition);
    listBox["getInsertionIndexForPosition"]   = LUA_JUCE_C_CALL(&juce::ListBox::getInsertionIndexForPosition);
    listBox["getRowPosition"]                 = LUA_JUCE_C_CALL(&juce::ListBox::getRowPosition);
    listBox["getComponentForRowNumber"]       = LUA_JUCE_C_CALL(&juce::ListBox::getComponentForRowNumber);
    listBox["getRowNumberOfComponent"]        = LUA_JUCE_C_CALL(&juce::ListBox::getRowNumberOfComponent);
    listBox["getVisibleRowWidth"]             = LUA_JUCE_C_CALL(&juce::ListBox::getVisibleRowWidth);
    listBox["setRowHeight"]                   = LUA_JUCE_C_CALL(&juce::ListBox::setRowHeight);
    listBox["getRowHeight"]                   = LUA_JUCE_C_CALL(&juce::ListBox::getRowHeight);
    listBox["getNumRowsOnScreen"]             = LUA_JUCE_C_CALL(&juce::ListBox::getNumRowsOnScreen);
    listBox["setOutlineThickness"]            = LUA_JUCE_C_CALL(&juce::ListBox::setOutlineThickness);
    listBox["getOutlineThickness"]            = LUA_JUCE_C_CALL(&juce::ListBox::getOutlineThickness);
    listBox["getHeaderComponent"]             = LUA_JUCE_C_CALL(&juce::ListBox::getHeaderComponent);
    listBox["setMinimumContentWidth"]         = LUA_JUCE_C_CALL(&juce::ListBox::setMinimumContentWidth);
    listBox["getVisibleContentWidth"]         = LUA_JUCE_C_CALL(&juce::ListBox::getVisibleContentWidth);
    listBox["repaintRow"]                     = LUA_JUCE_C_CALL(&juce::ListBox::repaintRow);
    listBox["getViewport"]                    = LUA_JUCE_C_CALL(&juce::ListBox::getViewport);
    // listBox["createSnapshotOfRows"]           = &juce::ListBox::createSnapshotOfRows;

    listBox["setHeaderComponent"] = [](juce::ListBox* lb, std::unique_ptr<juce::Component>& h) { lb->setHeaderComponent(std::move(h)); };
    listBox["setSelectedRows"]    = sol::overload(
        [](juce::ListBox* lb, juce::SparseSet<int> const& rows) { lb->setSelectedRows(rows, juce::NotificationType::sendNotification); },
        [](juce::ListBox* lb, juce::SparseSet<int> const& rows, juce::NotificationType n) { lb->setSelectedRows(rows, n); });

    // clang-format off
    auto luaListBox = state.new_usertype<LuaListBox>("ListBox",
        sol::constructors<LuaListBox()>(),
        sol::base_classes,
        sol::bases<
            juce::MouseListener,
            juce::Component,
            juce::TooltipClient,
            juce::SettableTooltipClient,
            juce::ListBox
        >()
    );
    // clang-format on

    luaListBox["setModel"] = &LuaListBox::internal_setModel;
}
} // namespace lua_juce
