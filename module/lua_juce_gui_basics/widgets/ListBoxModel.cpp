auto LuaListBoxModel::self() -> std::reference_wrapper<LuaListBoxModel> { return std::ref(*this); }

auto LuaListBoxModel::getNumRows() -> int
{
    if (lua_getNumRows.valid()) { return lua_getNumRows(self()); }
    return 0;
}

auto LuaListBoxModel::paintListBoxItem(int rowNumber, juce::Graphics& g, int width, int height, bool rowIsSelected) -> void
{
    if (lua_paintListBoxItem.valid()) { lua_paintListBoxItem(self(), rowNumber, std::ref(g), width, height, rowIsSelected); }
}

auto LuaListBoxModel::refreshComponentForRow(int rowNumber, bool isRowSelected, juce::Component* existingComponentToUpdate)
    -> juce::Component*
{
    if (lua_refreshComponentForRow.valid()) { lua_refreshComponentForRow(self(), rowNumber, isRowSelected, existingComponentToUpdate); }
    return juce::ListBoxModel::refreshComponentForRow(rowNumber, isRowSelected, existingComponentToUpdate);
}

auto LuaListBoxModel::getNameForRow(int rowNumber) -> juce::String
{
    if (lua_getNameForRow.valid()) { return lua_getNameForRow(self(), rowNumber); }
    return juce::ListBoxModel::getNameForRow(rowNumber);
}

auto LuaListBoxModel::listBoxItemClicked(int row, juce::MouseEvent const& event) -> void
{
    if (lua_listBoxItemClicked.valid()) { lua_listBoxItemClicked(self(), row, std::cref(event)); }
    return juce::ListBoxModel::listBoxItemClicked(row, event);
}

auto LuaListBoxModel::listBoxItemDoubleClicked(int row, juce::MouseEvent const& event) -> void
{
    if (lua_listBoxItemDoubleClicked.valid()) { lua_listBoxItemDoubleClicked(self(), row, std::cref(event)); }
    return juce::ListBoxModel::listBoxItemDoubleClicked(row, event);
}

auto LuaListBoxModel::backgroundClicked(juce::MouseEvent const& event) -> void
{
    if (lua_backgroundClicked.valid()) { lua_backgroundClicked(self(), std::cref(event)); }
    return juce::ListBoxModel::backgroundClicked(event);
}

auto LuaListBoxModel::selectedRowsChanged(int lastRowSelected) -> void
{
    if (lua_selectedRowsChanged.valid()) { lua_selectedRowsChanged(self(), lastRowSelected); }
    return juce::ListBoxModel::selectedRowsChanged(lastRowSelected);
}

auto LuaListBoxModel::deleteKeyPressed(int lastRowSelected) -> void
{
    if (lua_deleteKeyPressed.valid()) { lua_deleteKeyPressed(self(), lastRowSelected); }
    return juce::ListBoxModel::deleteKeyPressed(lastRowSelected);
}

auto LuaListBoxModel::returnKeyPressed(int lastRowSelected) -> void
{
    if (lua_returnKeyPressed.valid()) { lua_returnKeyPressed(self(), lastRowSelected); }
    return juce::ListBoxModel::returnKeyPressed(lastRowSelected);
}

auto LuaListBoxModel::listWasScrolled() -> void
{
    if (lua_listWasScrolled.valid()) { lua_listWasScrolled(self()); }
    return juce::ListBoxModel::listWasScrolled();
}

auto LuaListBoxModel::getDragSourceDescription(juce::SparseSet<int> const& rowsToDescribe) -> juce::var
{
    if (lua_getDragSourceDescription.valid()) { return lua_getDragSourceDescription(self(), std::cref(rowsToDescribe)); }
    return juce::ListBoxModel::getDragSourceDescription(rowsToDescribe);
}

auto LuaListBoxModel::getTooltipForRow(int row) -> juce::String
{
    if (lua_getTooltipForRow.valid()) { return lua_getTooltipForRow(self(), row); }
    return juce::ListBoxModel::getTooltipForRow(row);
}

auto LuaListBoxModel::getMouseCursorForRow(int row) -> juce::MouseCursor
{
    if (lua_getMouseCursorForRow.valid()) { return lua_getMouseCursorForRow(self(), row); }
    return juce::ListBoxModel::getMouseCursorForRow(row);
}

namespace lua_juce {

namespace {
auto juce_LuaListBoxModel(sol::table& state) -> void
{
    // clang-format off
    auto model = state.new_usertype<LuaListBoxModel>("ListBoxModel",
        sol::factories([] { return std::make_shared<LuaListBoxModel>(); }),
        sol::base_classes, sol::bases<juce::ListBoxModel>{}
    );
    // clang-format on

    model["getNumRows"]               = &LuaListBoxModel::lua_getNumRows;
    model["paintListBoxItem"]         = &LuaListBoxModel::lua_paintListBoxItem;
    model["refreshComponentForRow"]   = &LuaListBoxModel::lua_refreshComponentForRow;
    model["getNameForRow"]            = &LuaListBoxModel::lua_getNameForRow;
    model["listBoxItemClicked"]       = &LuaListBoxModel::lua_listBoxItemClicked;
    model["listBoxItemDoubleClicked"] = &LuaListBoxModel::lua_listBoxItemDoubleClicked;
    model["backgroundClicked"]        = &LuaListBoxModel::lua_backgroundClicked;
    model["selectedRowsChanged"]      = &LuaListBoxModel::lua_selectedRowsChanged;
    model["deleteKeyPressed"]         = &LuaListBoxModel::lua_deleteKeyPressed;
    model["returnKeyPressed"]         = &LuaListBoxModel::lua_returnKeyPressed;
    model["listWasScrolled"]          = &LuaListBoxModel::lua_listWasScrolled;
    model["getDragSourceDescription"] = &LuaListBoxModel::lua_getDragSourceDescription;
    model["getTooltipForRow"]         = &LuaListBoxModel::lua_getTooltipForRow;
    model["getMouseCursorForRow"]     = &LuaListBoxModel::lua_getMouseCursorForRow;
}
} // namespace

auto juce_ListBoxModel(sol::table& state) -> void
{
    auto model                        = state.new_usertype<juce::ListBoxModel>("InternalListBoxModel", sol::no_constructor);
    model["getNumRows"]               = LUA_JUCE_C_CALL(&juce::ListBoxModel::getNumRows);
    model["paintListBoxItem"]         = LUA_JUCE_C_CALL(&juce::ListBoxModel::paintListBoxItem);
    model["refreshComponentForRow"]   = LUA_JUCE_C_CALL(&juce::ListBoxModel::refreshComponentForRow);
    model["getNameForRow"]            = LUA_JUCE_C_CALL(&juce::ListBoxModel::getNameForRow);
    model["listBoxItemClicked"]       = LUA_JUCE_C_CALL(&juce::ListBoxModel::listBoxItemClicked);
    model["listBoxItemDoubleClicked"] = LUA_JUCE_C_CALL(&juce::ListBoxModel::listBoxItemDoubleClicked);
    model["backgroundClicked"]        = LUA_JUCE_C_CALL(&juce::ListBoxModel::backgroundClicked);
    model["selectedRowsChanged"]      = LUA_JUCE_C_CALL(&juce::ListBoxModel::selectedRowsChanged);
    model["deleteKeyPressed"]         = LUA_JUCE_C_CALL(&juce::ListBoxModel::deleteKeyPressed);
    model["returnKeyPressed"]         = LUA_JUCE_C_CALL(&juce::ListBoxModel::returnKeyPressed);
    model["listWasScrolled"]          = LUA_JUCE_C_CALL(&juce::ListBoxModel::listWasScrolled);
    model["getDragSourceDescription"] = LUA_JUCE_C_CALL(&juce::ListBoxModel::getDragSourceDescription);
    model["getTooltipForRow"]         = LUA_JUCE_C_CALL(&juce::ListBoxModel::getTooltipForRow);
    model["getMouseCursorForRow"]     = LUA_JUCE_C_CALL(&juce::ListBoxModel::getMouseCursorForRow);

    juce_LuaListBoxModel(state);
}
} // namespace lua_juce
