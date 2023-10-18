#pragma once

#include "Application/CommandLine.hpp"

namespace jml::viewer {
inline auto runTestScript(CommandLine const& cli) -> juce::Result
{
    auto state = sol::state{};
    state.open_libraries(
        sol::lib::base,
        sol::lib::debug,
        sol::lib::io,
        sol::lib::math,
        sol::lib::os,
        sol::lib::package,
        sol::lib::string,
        sol::lib::table
    );
    lua_juce::allModules(state);

    auto const scriptFile = juce::File{cli.scriptPath};
    if (cli.verbose) {
        std::cout << "Run test: " << scriptFile.getFileNameWithoutExtension().toStdString() << '\n';
    }
    scriptFile.getParentDirectory().setAsCurrentWorkingDirectory();

    auto script = state.load_file(scriptFile.getFullPathName().toStdString());
    if (not script.valid()) {
        sol::error const error = script;
        return juce::Result::fail(error.what());
    }

    auto factory = script.get<sol::protected_function>();
    auto result  = factory();
    if (not result.valid()) {
        sol::error const error = result;
        return juce::Result::fail(error.what());
    }

    if (cli.verbose) {
        std::cout << "Done test: " << scriptFile.getFileNameWithoutExtension().toStdString() << '\n';
    }
    return juce::Result::ok();
}
} // namespace jml::viewer
