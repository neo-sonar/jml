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
