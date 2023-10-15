#include "MenuBar.hpp"

// #include "BinaryData.hpp"
#include "Application/CommandIDs.hpp"

namespace jml::viewer {
MenuBar::MenuBar(juce::ApplicationCommandManager& commandManager) : _commandManager{commandManager}
{
    setApplicationCommandManagerToWatch(&_commandManager);
    addAndMakeVisible(_menu);
}

auto MenuBar::resized() -> void { _menu.setBounds(getLocalBounds()); }

auto MenuBar::getMenuBarNames() -> juce::StringArray
{
    return {
        "File",
        "Edit",
        "Help",
    };
}

auto MenuBar::getMenuForIndex(int menuIndex, juce::String const& /*menuName*/) -> juce::PopupMenu
{
    auto const index = static_cast<MenuIndex>(menuIndex);

    if (index == MenuIndex::File) {
        auto menu = juce::PopupMenu{};
        menu.addCommandItem(&_commandManager, CommandIDs::open, "Open", {} /*openIcon->createCopy()*/);
        menu.addCommandItem(&_commandManager, CommandIDs::reload, "Reload", {} /*openIcon->createCopy()*/);
        menu.addSeparator();
        menu.addCommandItem(&_commandManager, CommandIDs::save, "Save", {} /*saveIcon->createCopy()*/);
        menu.addCommandItem(&_commandManager, CommandIDs::saveAs, "Save As", {} /*saveIcon->createCopy()*/);
        return menu;
    }

    if (index == MenuIndex::Edit) {
        auto menu = juce::PopupMenu{};
        menu.addCommandItem(&_commandManager, CommandIDs::undo, "Undo", {} /*undoIcon->createCopy()*/);
        menu.addCommandItem(&_commandManager, CommandIDs::redo, "Redo", {} /*redoIcon->createCopy()*/);
        return menu;
    }

    if (index == MenuIndex::Help) {
        auto menu = juce::PopupMenu{};
        menu.addCommandItem(&_commandManager, CommandIDs::about, "About", {});
        return menu;
    }

    jassertfalse;
    return {};
}

auto MenuBar::menuItemSelected(int /*menuItemID*/, int /*topLevelMenuIndex*/) -> void {}

} // namespace jml::viewer
