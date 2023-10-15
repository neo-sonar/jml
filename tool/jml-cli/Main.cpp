#include "JmlCommandline.hpp"

#include "Command/Snapshot.hpp"
#include "Command/Test.hpp"

#include <lua_juce/lua_juce.hpp>

namespace {
[[nodiscard]] auto run(auto const func, auto const& app) -> int
{
    if (auto const result = func(app); result.failed()) {
        std::cerr << result.getErrorMessage() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
} // namespace

auto main(int argc, char* argv[]) -> int // NOLINT(bugprone-exception-escape)
{
    auto init = juce::ScopedJuceInitialiser_GUI{};

    auto cli = jml::cli::makeJmlCommandline();
    CLI11_PARSE(cli->app, argc, argv);

    if (cli->app.got_subcommand("test")) { return run(jml::cli::runTestScript, *cli); }
    if (cli->app.got_subcommand("snapshot")) { return run(jml::cli::runSnapshotScript, *cli); }
    return EXIT_SUCCESS;
}
