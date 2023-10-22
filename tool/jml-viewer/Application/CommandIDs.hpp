#pragma once

namespace jml::viewer {
struct CommandIDs
{
    enum Values
    {
        unknown,
        // File
        open,
        reload,
        save,
        saveAs,
        settings,

        // Edit
        undo,
        redo,

        // Help
        about,
    };
};
} // namespace jml::viewer
