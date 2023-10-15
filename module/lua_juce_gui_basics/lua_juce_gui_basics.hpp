/*
BEGIN_JUCE_MODULE_DECLARATION

    ID:                 lua_juce_gui_basics
    vendor:             neo-sonar
    version:            0.1.0
    name:               Lua bindings for juce_gui_basics
    description:        Lua/Sol2 bindings for juce_gui_basics
    dependencies:       lua_juce_graphics, lua_juce_data_structures, juce_gui_basics
    website:            http://github.com/neo-sonar/jml
    license:            GPL/Commercial
    minimumCppStandard: 20

END_JUCE_MODULE_DECLARATION
*/

#pragma once

#ifndef USE_LUA_JUCE_GUI_BASICS
    #define USE_LUA_JUCE_GUI_BASICS
#endif

#include <juce_gui_basics/juce_gui_basics.h>
#include <lua_juce_data_structures/lua_juce_data_structures.hpp>
#include <lua_juce_graphics/lua_juce_graphics.hpp>

struct LuaComponent final : juce::Component
{
    LuaComponent()           = default;
    ~LuaComponent() override = default;

    // juce::Component
    sol::safe_function lua_paint;
    sol::safe_function lua_resized;

    // juce::MouseListener
    sol::safe_function lua_mouseMove;
    sol::safe_function lua_mouseEnter;
    sol::safe_function lua_mouseExit;
    sol::safe_function lua_mouseDown;
    sol::safe_function lua_mouseDrag;
    sol::safe_function lua_mouseUp;
    sol::safe_function lua_mouseDoubleClick;
    sol::safe_function lua_mouseWheelMove;
    sol::safe_function lua_mouseMagnify;

private:
    auto self() -> std::reference_wrapper<LuaComponent> { return std::ref(*this); }

    // juce::Component
    auto paint(juce::Graphics& g) -> void override
    {
        if (lua_paint.valid()) { lua_paint(self(), std::ref(g)); }
    }

    auto resized() -> void override
    {
        if (lua_resized.valid()) { lua_resized(self()); }
    }

    // juce::MouseListener
    auto mouseMove(juce::MouseEvent const& event) -> void override
    {
        if (lua_mouseMove.valid()) { lua_mouseMove(self(), std::cref(event)); }
    }
    auto mouseEnter(juce::MouseEvent const& event) -> void override
    {
        if (lua_mouseEnter.valid()) { lua_mouseEnter(self(), std::cref(event)); }
    }
    auto mouseExit(juce::MouseEvent const& event) -> void override
    {
        if (lua_mouseExit.valid()) { lua_mouseExit(self(), std::cref(event)); }
    }
    auto mouseDown(juce::MouseEvent const& event) -> void override
    {
        if (lua_mouseDown.valid()) { lua_mouseDown(self(), std::cref(event)); }
    }
    auto mouseDrag(juce::MouseEvent const& event) -> void override
    {
        if (lua_mouseDrag.valid()) { lua_mouseDrag(self(), std::cref(event)); }
    }
    auto mouseUp(juce::MouseEvent const& event) -> void override
    {
        if (lua_mouseUp.valid()) { lua_mouseUp(self(), std::cref(event)); }
    }
    auto mouseDoubleClick(juce::MouseEvent const& event) -> void override
    {
        if (lua_mouseDoubleClick.valid()) { lua_mouseDoubleClick(self(), std::cref(event)); }
    }
    auto mouseWheelMove(juce::MouseEvent const& event, juce::MouseWheelDetails const& wheel) -> void override
    {
        if (lua_mouseWheelMove.valid()) { lua_mouseWheelMove(self(), std::cref(event), std::cref(wheel)); }
    }
    auto mouseMagnify(juce::MouseEvent const& event, float scaleFactor) -> void override
    {
        if (lua_mouseMagnify.valid()) { lua_mouseMagnify(self(), std::cref(event), scaleFactor); }
    }
};

struct LuaListBoxModel final : juce::ListBoxModel
{
    LuaListBoxModel()           = default;
    ~LuaListBoxModel() override = default;

    auto getNumRows() -> int override
    {
        if (lua_getNumRows.valid()) { return lua_getNumRows(self()); }
        return 0;
    }

    auto paintListBoxItem(int rowNumber, juce::Graphics& g, int width, int height, bool rowIsSelected) -> void override
    {
        if (lua_paintListBoxItem.valid()) { lua_paintListBoxItem(self(), rowNumber, std::ref(g), width, height, rowIsSelected); }
    }

    auto refreshComponentForRow(int rowNumber, bool isRowSelected, juce::Component* existingComponentToUpdate) -> juce::Component* override
    {
        if (lua_refreshComponentForRow.valid()) { lua_refreshComponentForRow(self(), rowNumber, isRowSelected, existingComponentToUpdate); }
        return juce::ListBoxModel::refreshComponentForRow(rowNumber, isRowSelected, existingComponentToUpdate);
    }

    auto getNameForRow(int rowNumber) -> juce::String override
    {
        if (lua_getNameForRow.valid()) { return lua_getNameForRow(self(), rowNumber); }
        return juce::ListBoxModel::getNameForRow(rowNumber);
    }

    auto listBoxItemClicked(int row, juce::MouseEvent const& event) -> void override
    {
        if (lua_listBoxItemClicked.valid()) { lua_listBoxItemClicked(self(), row, std::cref(event)); }
        return juce::ListBoxModel::listBoxItemClicked(row, event);
    }

    auto listBoxItemDoubleClicked(int row, juce::MouseEvent const& event) -> void override
    {
        if (lua_listBoxItemDoubleClicked.valid()) { lua_listBoxItemDoubleClicked(self(), row, std::cref(event)); }
        return juce::ListBoxModel::listBoxItemDoubleClicked(row, event);
    }

    auto backgroundClicked(juce::MouseEvent const& event) -> void override
    {
        if (lua_backgroundClicked.valid()) { lua_backgroundClicked(self(), std::cref(event)); }
        return juce::ListBoxModel::backgroundClicked(event);
    }

    auto selectedRowsChanged(int lastRowSelected) -> void override
    {
        if (lua_selectedRowsChanged.valid()) { lua_selectedRowsChanged(self(), lastRowSelected); }
        return juce::ListBoxModel::selectedRowsChanged(lastRowSelected);
    }

    auto deleteKeyPressed(int lastRowSelected) -> void override
    {
        if (lua_deleteKeyPressed.valid()) { lua_deleteKeyPressed(self(), lastRowSelected); }
        return juce::ListBoxModel::deleteKeyPressed(lastRowSelected);
    }

    auto returnKeyPressed(int lastRowSelected) -> void override
    {
        if (lua_returnKeyPressed.valid()) { lua_returnKeyPressed(self(), lastRowSelected); }
        return juce::ListBoxModel::returnKeyPressed(lastRowSelected);
    }

    auto listWasScrolled() -> void override
    {
        if (lua_listWasScrolled.valid()) { lua_listWasScrolled(self()); }
        return juce::ListBoxModel::listWasScrolled();
    }

    auto getDragSourceDescription(juce::SparseSet<int> const& rowsToDescribe) -> juce::var override
    {
        if (lua_getDragSourceDescription.valid()) { return lua_getDragSourceDescription(self(), std::cref(rowsToDescribe)); }
        return juce::ListBoxModel::getDragSourceDescription(rowsToDescribe);
    }

    auto getTooltipForRow(int row) -> juce::String override
    {
        if (lua_getTooltipForRow.valid()) { return lua_getTooltipForRow(self(), row); }
        return juce::ListBoxModel::getTooltipForRow(row);
    }

    auto getMouseCursorForRow(int row) -> juce::MouseCursor override
    {
        if (lua_getMouseCursorForRow.valid()) { return lua_getMouseCursorForRow(self(), row); }
        return juce::ListBoxModel::getMouseCursorForRow(row);
    }

    auto self() -> std::reference_wrapper<LuaListBoxModel> { return std::ref(*this); }

    sol::safe_function lua_getNumRows;
    sol::safe_function lua_paintListBoxItem;
    sol::safe_function lua_refreshComponentForRow;
    sol::safe_function lua_getNameForRow;
    sol::safe_function lua_listBoxItemClicked;
    sol::safe_function lua_listBoxItemDoubleClicked;
    sol::safe_function lua_backgroundClicked;
    sol::safe_function lua_selectedRowsChanged;
    sol::safe_function lua_deleteKeyPressed;
    sol::safe_function lua_returnKeyPressed;
    sol::safe_function lua_listWasScrolled;
    sol::safe_function lua_getDragSourceDescription;
    sol::safe_function lua_getTooltipForRow;
    sol::safe_function lua_getMouseCursorForRow;
};

struct LuaListBox final : juce::ListBox
{
    LuaListBox() : juce::ListBox({}, nullptr) {}
    ~LuaListBox() override { setModel(nullptr); }

    auto internal_setModel(std::shared_ptr<LuaListBoxModel> m) -> void
    {
        if (m == _model) { return; }
        if (m == nullptr) { return; }
        setModel(m.get());
        _model = std::move(m);
    }

private:
    std::shared_ptr<LuaListBoxModel> _model;
};

SOL_BASE_CLASSES(juce::Button, juce::Component, juce::MouseListener, juce::SettableTooltipClient, juce::TooltipClient);

SOL_BASE_CLASSES(juce::TextButton, juce::Button, juce::Component, juce::MouseListener, juce::SettableTooltipClient, juce::TooltipClient);
SOL_DERIVED_CLASSES(juce::Button, juce::TextButton);

SOL_BASE_CLASSES(juce::ComboBox, juce::Component, juce::MouseListener, juce::SettableTooltipClient, juce::TooltipClient,
                 juce::Value::Listener);

SOL_BASE_CLASSES(juce::Label, juce::Component, juce::MouseListener, juce::SettableTooltipClient, juce::TooltipClient);

SOL_BASE_CLASSES(juce::Slider, juce::MouseListener, juce::Component, juce::TooltipClient, juce::SettableTooltipClient);

SOL_BASE_CLASSES(LuaComponent, juce::Component, juce::MouseListener);
SOL_DERIVED_CLASSES(juce::Component, LuaComponent);

SOL_BASE_CLASSES(LuaListBoxModel, juce::ListBoxModel);
SOL_DERIVED_CLASSES(juce::ListBoxModel, LuaListBoxModel);

SOL_BASE_CLASSES(LuaListBox, juce::ListBox, juce::Component, juce::MouseListener, juce::SettableTooltipClient, juce::TooltipClient);

namespace lua_juce {
auto juce_ArrowButton(sol::table& state) -> void;
auto juce_Button(sol::table& state) -> void;
auto juce_HyperlinkButton(sol::table& state) -> void;
auto juce_ImageButton(sol::table& state) -> void;
auto juce_ShapeButton(sol::table& state) -> void;
auto juce_TextButton(sol::table& state) -> void;
auto juce_ToggleButton(sol::table& state) -> void;
auto juce_Component(sol::table& state) -> void;
auto juce_ComponentListener(sol::table& state) -> void;
auto juce_LuaComponent(sol::table& state) -> void;
auto juce_Grid(sol::table& state) -> void;
auto juce_LookAndFeel_V4(sol::table& state) -> void;
auto juce_LookAndFeel(sol::table& state) -> void;
auto juce_LuaLookAndFeel_V4(sol::table& state) -> void;
auto juce_MouseEvent(sol::table& state) -> void;
auto juce_MouseWheelDetails(sol::table& state) -> void;
auto juce_ComboBox(sol::table& state) -> void;
auto juce_ImageComponent(sol::table& state) -> void;
auto juce_Label(sol::table& state) -> void;
auto juce_ListBox(sol::table& state) -> void;
auto juce_ListBoxModel(sol::table& state) -> void;
auto juce_Slider(sol::table& state) -> void;
auto juce_TextEditor(sol::table& state) -> void;
auto juce_TreeView(sol::table& state) -> void;
} // namespace lua_juce
