#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

namespace jml::viewer {
struct CommandIDs
{
    enum Values
    {
        quit        = juce::StandardApplicationCommandIDs::quit,
        del         = juce::StandardApplicationCommandIDs::del,
        cut         = juce::StandardApplicationCommandIDs::cut,
        copy        = juce::StandardApplicationCommandIDs::copy,
        paste       = juce::StandardApplicationCommandIDs::paste,
        selectAll   = juce::StandardApplicationCommandIDs::selectAll,
        deselectAll = juce::StandardApplicationCommandIDs::deselectAll,
        undo        = juce::StandardApplicationCommandIDs::undo,
        redo        = juce::StandardApplicationCommandIDs::redo,

        // File
        open,
        reload,
        save,
        saveAs,
        settings,

        // Edit

        // Help
        about,
    };
};
} // namespace jml::viewer
