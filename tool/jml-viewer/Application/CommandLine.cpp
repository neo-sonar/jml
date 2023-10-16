#include "CommandLine.hpp"

namespace jml::viewer {

auto parseCommandLine(juce::String const& args) -> std::pair<std::unique_ptr<CommandLine>, bool>
{
    auto cli = std::make_unique<CommandLine>();
    cli->app.add_flag("--verbose,-v", cli->verbose, "Print verbose output");

    auto* test = cli->app.add_subcommand("test", "Run test script");
    test->add_option("--script,-s", cli->scriptPath)
        ->description("Path to lua script")
        ->check(CLI::ExistingFile);

    auto* snapshot = cli->app.add_subcommand("snapshot", "Run snapshot script");
    snapshot->add_option("--script,-s", cli->scriptPath)
        ->description("Path to lua script")
        ->check(CLI::ExistingFile);

    try {
        cli->app.parse(args.toStdString());
    } catch (CLI::CallForHelp const& e) {
        std::cout << cli->app.help({}, CLI::AppFormatMode::Normal) << '\n';
        return std::pair{std::move(cli), true};
    } catch (CLI::ParseError const& e) {
        std::cout << e.what() << '\n';
        return std::pair{nullptr, true};
    }

    return std::pair{std::move(cli), false};
}

} // namespace jml::viewer
