auto LuaComponentListener::componentMovedOrResized(juce::Component& component, bool wasMoved, bool wasResized) -> void
{
    if (not lua_componentMovedOrResized.valid()) { return; }
    lua_componentMovedOrResized(std::ref(*this), component, wasMoved, wasResized);
}

auto LuaComponentListener::componentBroughtToFront(juce::Component& component) -> void
{
    if (not lua_componentBroughtToFront.valid()) { return; }
    lua_componentBroughtToFront(std::ref(*this), component);
}

auto LuaComponentListener::componentVisibilityChanged(juce::Component& component) -> void
{
    if (not lua_componentVisibilityChanged.valid()) { return; }
    lua_componentVisibilityChanged(std::ref(*this), component);
}

auto LuaComponentListener::componentChildrenChanged(juce::Component& component) -> void
{
    if (not lua_componentChildrenChanged.valid()) { return; }
    lua_componentChildrenChanged(std::ref(*this), component);
}

auto LuaComponentListener::componentParentHierarchyChanged(juce::Component& component) -> void
{
    if (not lua_componentParentHierarchyChanged.valid()) { return; }
    lua_componentParentHierarchyChanged(std::ref(*this), component);
}

auto LuaComponentListener::componentNameChanged(juce::Component& component) -> void
{
    if (not lua_componentNameChanged.valid()) { return; }
    lua_componentNameChanged(std::ref(*this), component);
}

auto LuaComponentListener::componentBeingDeleted(juce::Component& component) -> void
{
    if (not lua_componentBeingDeleted.valid()) { return; }
    lua_componentBeingDeleted(std::ref(*this), component);
}

auto LuaComponentListener::componentEnablementChanged(juce::Component& component) -> void
{
    if (not lua_componentEnablementChanged.valid()) { return; }
    lua_componentEnablementChanged(std::ref(*this), component);
}

namespace lua_juce {

auto juce_ComponentListener(sol::table& state) -> void
{
    auto cl                               = state.new_usertype<juce::ComponentListener>("InternalComponentListener", sol::no_constructor);
    cl["componentMovedOrResized"]         = &juce::ComponentListener::componentMovedOrResized;
    cl["componentBroughtToFront"]         = &juce::ComponentListener::componentBroughtToFront;
    cl["componentVisibilityChanged"]      = &juce::ComponentListener::componentVisibilityChanged;
    cl["componentChildrenChanged"]        = &juce::ComponentListener::componentChildrenChanged;
    cl["componentParentHierarchyChanged"] = &juce::ComponentListener::componentParentHierarchyChanged;
    cl["componentNameChanged"]            = &juce::ComponentListener::componentNameChanged;
    cl["componentBeingDeleted"]           = &juce::ComponentListener::componentBeingDeleted;
    cl["componentEnablementChanged"]      = &juce::ComponentListener::componentEnablementChanged;

    auto luaCL = state.new_usertype<LuaComponentListener>(       //
        "ComponentListener",                                     //
        sol::constructors<LuaComponentListener()>(),             //
        sol::base_classes, sol::bases<juce::ComponentListener>() //
    );

    luaCL["componentMovedOrResized"]         = &LuaComponentListener::lua_componentMovedOrResized;
    luaCL["componentBroughtToFront"]         = &LuaComponentListener::lua_componentBroughtToFront;
    luaCL["componentVisibilityChanged"]      = &LuaComponentListener::lua_componentVisibilityChanged;
    luaCL["componentChildrenChanged"]        = &LuaComponentListener::lua_componentChildrenChanged;
    luaCL["componentParentHierarchyChanged"] = &LuaComponentListener::lua_componentParentHierarchyChanged;
    luaCL["componentNameChanged"]            = &LuaComponentListener::lua_componentNameChanged;
    luaCL["componentBeingDeleted"]           = &LuaComponentListener::lua_componentBeingDeleted;
    luaCL["componentEnablementChanged"]      = &LuaComponentListener::lua_componentEnablementChanged;
}
} // namespace lua_juce
