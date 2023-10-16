#pragma once

#include <juce_gui_extra/juce_gui_extra.h>
#include <lua_juce_core/lua_juce_core.hpp>

#include "Application/MenuBar.hpp"
#include "Viewer/ComponentTree.hpp"
#include "Viewer/FileChangeListener.hpp"
#include "Viewer/ScriptViewport.hpp"

namespace jml::viewer {

struct LuaScriptViewer final
    : juce::Component
    , juce::Timer
{
    LuaScriptViewer();
    ~LuaScriptViewer() override = default;

    [[nodiscard]] auto getScriptFile() const -> juce::File { return _scriptFile; }

    auto setScriptFile(juce::File const& file) -> void;

    auto paint(juce::Graphics& g) -> void override;
    auto resized() -> void override;
    auto timerCallback() -> void override;

private:
    struct LuaState
    {
        sol::state state;
        sol::object obj;
        juce::Component::SafePointer<juce::Component> component{nullptr};
    };

    auto reloadLuaState() -> void;
    static auto handleLuaError(sol::error const& error) -> void;

    std::unique_ptr<LuaState> _lua;
    ScriptViewport _viewport;
    ComponentTree _componentTree;

    juce::File _scriptFile;
    std::unique_ptr<FileChangeListener> _fileListener;

    JUCE_LEAK_DETECTOR(LuaScriptViewer) // NOLINT
};

} // namespace jml::viewer
