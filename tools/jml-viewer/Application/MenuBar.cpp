#include "MenuBar.hpp"

#include "Application/Application.hpp"
#include "Application/CommandIDs.hpp"

#include <jml_tools/jml_tools.hpp>

namespace jml::viewer {

MenuBar::MenuBar(juce::ApplicationCommandManager& commandManager) : _commands{commandManager}
{
    setApplicationCommandManagerToWatch(&_commands);
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
    using IDs = CommandIDs;

    auto* cmd        = &_commands;
    auto const index = static_cast<MenuIndex>(menuIndex);

    if (index == MenuIndex::File) {
        auto files = juce::PopupMenu{};
        for (auto const& filePath : getApplicationSettings().getRecentFiles()) {
            auto const file = juce::File{filePath};
            files.addItem(file.getFileNameWithoutExtension(), [this, file] {
                if (onFileLoad) {
                    onFileLoad(file);
                }
            });
        }
        files.addSeparator();
        files.addItem("Clear", [] { getApplicationSettings().clearRecentOpenFiles(); });

        auto menu = juce::PopupMenu{};
        menu.addCommandItem(cmd, IDs::open, "Open", getIcon("launch_black_48dp_svg"));
        menu.addCommandItem(cmd, IDs::reload, "Reload", getIcon("autorenew_black_48dp_svg"));
        menu.addSubMenu("Recent Files", files, true, getIcon("restore_black_48dp_svg"));
        menu.addSeparator();
        menu.addCommandItem(cmd, IDs::save, "Save", getIcon("save_black_48dp_svg"));
        menu.addCommandItem(cmd, IDs::saveAs, "Save As", getIcon("save_as_black_48dp_svg"));
        menu.addSeparator();
        menu.addCommandItem(cmd, IDs::settings, "Settings", getIcon("settings_black_48dp_svg"));
        menu.addSeparator();
        menu.addCommandItem(cmd, IDs::quit, "Quit", getIcon("close_black_48dp_svg"));
        return menu;
    }

    if (index == MenuIndex::Edit) {
        auto menu = juce::PopupMenu{};
        menu.addCommandItem(cmd, IDs::undo, "Undo", getIcon("undo_black_48dp_svg"));
        menu.addCommandItem(cmd, IDs::redo, "Redo", getIcon("redo_black_48dp_svg"));
        menu.addSeparator();
        menu.addCommandItem(cmd, IDs::cut, "Cut", getIcon("content_cut_black_48dp_svg"));
        menu.addCommandItem(cmd, IDs::copy, "Copy", getIcon("content_copy_black_48dp_svg"));
        menu.addCommandItem(cmd, IDs::paste, "Paste", getIcon("content_paste_black_48dp_svg"));
        menu.addSeparator();
        menu.addCommandItem(cmd, IDs::selectAll, "Select All", getIcon("select_all_black_48dp_svg"));
        menu.addCommandItem(cmd, IDs::deselectAll, "Deselect", getIcon("deselect_black_48dp_svg"));
        return menu;
    }

    if (index == MenuIndex::Help) {
        auto menu = juce::PopupMenu{};
        menu.addCommandItem(cmd, IDs::about, "About", getIcon("info_black_48dp_svg"));
        return menu;
    }

    jassertfalse;
    return {};
}

auto MenuBar::menuItemSelected(int /*menuItemID*/, int /*topLevelMenuIndex*/) -> void {}

} // namespace jml::viewer
