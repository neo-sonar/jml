#pragma once

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

SOL_BASE_CLASSES(LuaListBox, juce::ListBox, juce::Component, juce::MouseListener, juce::SettableTooltipClient, juce::TooltipClient);

namespace lua_juce {
auto juce_ListBox(sol::table& state) -> void;
}
