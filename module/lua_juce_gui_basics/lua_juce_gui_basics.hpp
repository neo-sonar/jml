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

namespace lua_juce {

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
    auto self() -> std::reference_wrapper<LuaComponent>;

    // juce::Component
    auto paint(juce::Graphics& g) -> void override;
    auto resized() -> void override;

    // juce::MouseListener
    auto mouseMove(juce::MouseEvent const& event) -> void override;
    auto mouseEnter(juce::MouseEvent const& event) -> void override;
    auto mouseExit(juce::MouseEvent const& event) -> void override;
    auto mouseDown(juce::MouseEvent const& event) -> void override;
    auto mouseDrag(juce::MouseEvent const& event) -> void override;
    auto mouseUp(juce::MouseEvent const& event) -> void override;
    auto mouseDoubleClick(juce::MouseEvent const& event) -> void override;
    auto mouseWheelMove(juce::MouseEvent const& event, juce::MouseWheelDetails const& wheel) -> void override;
    auto mouseMagnify(juce::MouseEvent const& event, float scaleFactor) -> void override;
};

struct LuaComponentListener final : juce::ComponentListener
{
    LuaComponentListener()           = default;
    ~LuaComponentListener() override = default;

    auto componentMovedOrResized(juce::Component& component, bool wasMoved, bool wasResized) -> void override;
    auto componentBroughtToFront(juce::Component& component) -> void override;
    auto componentVisibilityChanged(juce::Component& component) -> void override;
    auto componentChildrenChanged(juce::Component& component) -> void override;
    auto componentParentHierarchyChanged(juce::Component& component) -> void override;
    auto componentNameChanged(juce::Component& component) -> void override;
    auto componentBeingDeleted(juce::Component& component) -> void override;
    auto componentEnablementChanged(juce::Component& component) -> void override;

    sol::safe_function lua_componentMovedOrResized;
    sol::safe_function lua_componentBroughtToFront;
    sol::safe_function lua_componentVisibilityChanged;
    sol::safe_function lua_componentChildrenChanged;
    sol::safe_function lua_componentParentHierarchyChanged;
    sol::safe_function lua_componentNameChanged;
    sol::safe_function lua_componentBeingDeleted;
    sol::safe_function lua_componentEnablementChanged;
};

struct LuaListBoxModel final : juce::ListBoxModel
{
    LuaListBoxModel()           = default;
    ~LuaListBoxModel() override = default;

    auto self() -> std::reference_wrapper<LuaListBoxModel>;

    auto getNumRows() -> int override;
    auto paintListBoxItem(int rowNumber, juce::Graphics& g, int width, int height, bool rowIsSelected) -> void override;
    auto refreshComponentForRow(int rowNumber, bool isRowSelected, juce::Component* existingComponentToUpdate) -> juce::Component* override;
    auto getNameForRow(int rowNumber) -> juce::String override;
    auto listBoxItemClicked(int row, juce::MouseEvent const& event) -> void override;
    auto listBoxItemDoubleClicked(int row, juce::MouseEvent const& event) -> void override;
    auto backgroundClicked(juce::MouseEvent const& event) -> void override;
    auto selectedRowsChanged(int lastRowSelected) -> void override;
    auto deleteKeyPressed(int lastRowSelected) -> void override;
    auto returnKeyPressed(int lastRowSelected) -> void override;
    auto listWasScrolled() -> void override;
    auto getDragSourceDescription(juce::SparseSet<int> const& rowsToDescribe) -> juce::var override;
    auto getTooltipForRow(int row) -> juce::String override;
    auto getMouseCursorForRow(int row) -> juce::MouseCursor override;

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

    auto internal_setModel(std::shared_ptr<LuaListBoxModel> m) -> void;

private:
    std::shared_ptr<LuaListBoxModel> _model;
};

struct LuaLookAndFeel_V4 final : juce::LookAndFeel_V4
{
    LuaLookAndFeel_V4()           = default;
    ~LuaLookAndFeel_V4() override = default;

    // juce::Button
    auto getTextButtonFont(juce::TextButton& btn, int buttonHeight) -> juce::Font override;
    auto drawButtonBackground(juce::Graphics& g, juce::Button& btn, juce::Colour const& color, bool isHighlighted, bool isDown) -> void override;
    auto drawToggleButton(juce::Graphics& g, juce::ToggleButton& btn, bool isHighlighted, bool isDown) -> void override;

    sol::safe_function lua_getTextButtonFont;
    sol::safe_function lua_drawButtonBackground;
    sol::safe_function lua_drawToggleButton;

private:
    auto self() -> std::reference_wrapper<LuaLookAndFeel_V4>;
};

} // namespace lua_juce

SOL_BASE_CLASSES(juce::Button, juce::Component, juce::MouseListener, juce::SettableTooltipClient, juce::TooltipClient);

SOL_BASE_CLASSES(juce::TextButton, juce::Button, juce::Component, juce::MouseListener, juce::SettableTooltipClient, juce::TooltipClient);
SOL_DERIVED_CLASSES(juce::Button, juce::TextButton);

SOL_BASE_CLASSES(juce::ComboBox, juce::Component, juce::MouseListener, juce::SettableTooltipClient, juce::TooltipClient, juce::Value::Listener);

SOL_BASE_CLASSES(juce::Label, juce::Component, juce::MouseListener, juce::SettableTooltipClient, juce::TooltipClient);

SOL_BASE_CLASSES(juce::Slider, juce::MouseListener, juce::Component, juce::TooltipClient, juce::SettableTooltipClient);

SOL_BASE_CLASSES(lua_juce::LuaComponent, juce::Component, juce::MouseListener);
SOL_DERIVED_CLASSES(juce::Component, lua_juce::LuaComponent);

SOL_BASE_CLASSES(lua_juce::LuaListBoxModel, juce::ListBoxModel);
SOL_DERIVED_CLASSES(juce::ListBoxModel, lua_juce::LuaListBoxModel);

SOL_BASE_CLASSES(lua_juce::LuaListBox, juce::ListBox, juce::Component, juce::MouseListener, juce::SettableTooltipClient, juce::TooltipClient);

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
