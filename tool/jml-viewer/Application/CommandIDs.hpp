#pragma once

namespace jml::viewer {
struct CommandIDs
{
    enum Values
    {
        unknown,
        open,
        reload,
        save,
        saveAs,
        undo,
        redo,
    };
};
} // namespace jml::viewer
