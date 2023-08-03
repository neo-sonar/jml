namespace lua_juce {
auto juce_LuaComponent(sol::table& state) -> void
{
    // clang-format off
    auto comp = state.new_usertype<LuaComponent>("Component",
        sol::constructors<LuaComponent()>(),
        sol::base_classes, sol::bases<juce::Component, juce::MouseListener>()
    );
    // clang-format on

    comp["paint"]            = &LuaComponent::lua_paint;
    comp["resized"]          = &LuaComponent::lua_resized;
    comp["mouseMove"]        = &LuaComponent::lua_mouseMove;
    comp["mouseEnter"]       = &LuaComponent::lua_mouseEnter;
    comp["mouseExit"]        = &LuaComponent::lua_mouseExit;
    comp["mouseDown"]        = &LuaComponent::lua_mouseDown;
    comp["mouseDrag"]        = &LuaComponent::lua_mouseDrag;
    comp["mouseUp"]          = &LuaComponent::lua_mouseUp;
    comp["mouseDoubleClick"] = &LuaComponent::lua_mouseDoubleClick;
    comp["mouseWheelMove"]   = &LuaComponent::lua_mouseWheelMove;
    comp["mouseMagnify"]     = &LuaComponent::lua_mouseMagnify;
}
} // namespace lua_juce
