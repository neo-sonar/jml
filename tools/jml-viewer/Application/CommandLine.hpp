#pragma once

#include <lua_juce/lua_juce.hpp>

JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wimplicit-int-float-conversion")
#include <CLI/CLI.hpp>
JUCE_END_IGNORE_WARNINGS_GCC_LIKE

namespace jml::viewer {

struct CommandLine
{
    // "root"
    CLI::App app{"jml-viewer"};
    bool verbose{false};

    // "test"
    std::string scriptPath{};
};

[[nodiscard]] auto parseCommandLine(juce::String const& args)
    -> std::pair<std::unique_ptr<CommandLine>, bool>;

} // namespace jml::viewer
