#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

namespace jml::viewer {

struct MenuBar final
    : juce::Component
    , juce::MenuBarModel
{
    explicit MenuBar(juce::ApplicationCommandManager& commandManager);
    ~MenuBar() override = default;

    auto resized() -> void override;

    auto getMenuBarNames() -> juce::StringArray override;
    auto getMenuForIndex(int menuIndex, juce::String const& /*menuName*/) -> juce::PopupMenu override;
    auto menuItemSelected(int /*menuItemID*/, int /*topLevelMenuIndex*/) -> void override;

    std::function<void(juce::File const&)> onFileLoad;

private:
    enum struct MenuIndex
    {
        File = 0,
        Edit,
        Help,
    };

    juce::ApplicationCommandManager& _commands;
    juce::MenuBarComponent _menu{this};
};

} // namespace jml::viewer
