auto LuaComponent::self() -> std::reference_wrapper<LuaComponent> { return std::ref(*this); }

auto LuaComponent::paint(juce::Graphics& g) -> void
{
    if (lua_paint.valid()) { lua_paint(self(), std::ref(g)); }
}

auto LuaComponent::resized() -> void
{
    if (lua_resized.valid()) { lua_resized(self()); }
}

auto LuaComponent::mouseMove(juce::MouseEvent const& event) -> void
{
    if (lua_mouseMove.valid()) { lua_mouseMove(self(), std::cref(event)); }
}
auto LuaComponent::mouseEnter(juce::MouseEvent const& event) -> void
{
    if (lua_mouseEnter.valid()) { lua_mouseEnter(self(), std::cref(event)); }
}
auto LuaComponent::mouseExit(juce::MouseEvent const& event) -> void
{
    if (lua_mouseExit.valid()) { lua_mouseExit(self(), std::cref(event)); }
}
auto LuaComponent::mouseDown(juce::MouseEvent const& event) -> void
{
    if (lua_mouseDown.valid()) { lua_mouseDown(self(), std::cref(event)); }
}
auto LuaComponent::mouseDrag(juce::MouseEvent const& event) -> void
{
    if (lua_mouseDrag.valid()) { lua_mouseDrag(self(), std::cref(event)); }
}
auto LuaComponent::mouseUp(juce::MouseEvent const& event) -> void
{
    if (lua_mouseUp.valid()) { lua_mouseUp(self(), std::cref(event)); }
}
auto LuaComponent::mouseDoubleClick(juce::MouseEvent const& event) -> void
{
    if (lua_mouseDoubleClick.valid()) { lua_mouseDoubleClick(self(), std::cref(event)); }
}
auto LuaComponent::mouseWheelMove(juce::MouseEvent const& event, juce::MouseWheelDetails const& wheel) -> void
{
    if (lua_mouseWheelMove.valid()) { lua_mouseWheelMove(self(), std::cref(event), std::cref(wheel)); }
}
auto LuaComponent::mouseMagnify(juce::MouseEvent const& event, float scaleFactor) -> void
{
    if (lua_mouseMagnify.valid()) { lua_mouseMagnify(self(), std::cref(event), scaleFactor); }
}

namespace lua_juce {
struct SolObjectSet final : juce::ReferenceCountedObject
{
    using Ptr = juce::ReferenceCountedObjectPtr<SolObjectSet>;

    SolObjectSet()           = default;
    ~SolObjectSet() override = default;

    auto contains(sol::object obj) -> bool { return _objects.count(obj) == 1U; }

    auto add(sol::object obj) -> void
    {
        if (_objects.count(obj) == 1U) { return; }
        _objects.insert(std::move(obj));
    }
    auto remove(sol::object obj) -> void
    {
        jassert(_objects.count(obj) == 1U);
        _objects.erase(obj);
    }

private:
    std::unordered_set<sol::object, sol::reference_hash> _objects;
};

static auto getSolObjectSet(juce::NamedValueSet& properties) -> SolObjectSet&
{
    if (properties.contains("lua-objects")) {
        auto const& v = properties["lua-objects"];
        auto* objects = dynamic_cast<SolObjectSet*>(v.getObject());
        jassert(objects != nullptr);
        return *objects;
    }

    auto* objects = new SolObjectSet{};
    properties.set("lua-objects", objects);
    return *objects;
}

auto juce_Component(sol::table& state) -> void
{
    // clang-format off
    auto comp = state.new_usertype<juce::Component>("InternalComponent", sol::base_classes, sol::bases<juce::MouseListener>());
    // comp.set_function("addAndMakeVisible", sol::overload(
    //         static_cast<void (juce::Component::*)(juce::Component*, int)>(&juce::Component::addAndMakeVisible),
    //         static_cast<void (juce::Component::*)(juce::Component&, int)>(&juce::Component::addAndMakeVisible),
    //         [](juce::Component* self, juce::Component* child) -> void { self->addAndMakeVisible(child, -1); }
    //     )
    // );
    comp.set_function("setBounds", sol::overload(
            static_cast<void (juce::Component::*)(int,int,int,int)>(&juce::Component::setBounds),
            static_cast<void (juce::Component::*)(juce::Rectangle<int>)>(&juce::Component::setBounds)
        )
    );
    comp.set_function("repaint", sol::overload(
            static_cast<void (juce::Component::*)()>(&juce::Component::repaint),
            static_cast<void (juce::Component::*)(juce::Rectangle<int>)>(&juce::Component::repaint),
            static_cast<void (juce::Component::*)(int, int, int, int)>(&juce::Component::repaint)
        )
    );
    // clang-format on

    comp["setColour"]         = LUA_JUCE_C_CALL(&juce::Component::setColour);
    comp["paint"]             = LUA_JUCE_C_CALL(&juce::Component::paint);
    comp["resized"]           = LUA_JUCE_C_CALL(&juce::Component::resized);
    comp["setSize"]           = LUA_JUCE_C_CALL(&juce::Component::setSize);
    comp["getName"]           = LUA_JUCE_C_CALL(&juce::Component::getName);
    comp["setName"]           = LUA_JUCE_C_CALL(&juce::Component::setName);
    comp["getComponentID"]    = LUA_JUCE_C_CALL(&juce::Component::getComponentID);
    comp["setComponentID"]    = LUA_JUCE_C_CALL(&juce::Component::setComponentID);
    comp["setVisible"]        = LUA_JUCE_C_CALL(&juce::Component::setVisible);
    comp["isVisible"]         = LUA_JUCE_C_CALL(&juce::Component::isVisible);
    comp["getBounds"]         = LUA_JUCE_C_CALL(&juce::Component::getBounds);
    comp["getLocalBounds"]    = LUA_JUCE_C_CALL(&juce::Component::getLocalBounds);
    comp["getBoundsInParent"] = LUA_JUCE_C_CALL(&juce::Component::getBoundsInParent);
    comp["getLookAndFeel"]    = LUA_JUCE_C_CALL(&juce::Component::getLookAndFeel);
    comp["setLookAndFeel"]    = [](juce::Component* self, sol::object obj) -> void {
        auto& objects = getSolObjectSet(self->getProperties());
        objects.add(obj);

        auto* lnf = obj.as<juce::LookAndFeel*>();
        self->setLookAndFeel(lnf);
    };
    comp["addAndMakeVisible"] = [](juce::Component* self, sol::object obj) -> void {
        auto& objects = getSolObjectSet(self->getProperties());
        objects.add(obj);

        auto* component = obj.as<juce::Component*>();
        self->addAndMakeVisible(component);
    };
}
} // namespace lua_juce
