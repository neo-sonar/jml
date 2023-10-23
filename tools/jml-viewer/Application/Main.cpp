#include "Application/CommandLine.hpp"
#include "Application/MainComponent.hpp"
#include "Command/Snapshot.hpp"
#include "Command/Test.hpp"

#include <jml_tools/jml_tools.hpp>

namespace {
auto runCommand(auto const func, auto const& cli) -> void
{
    auto& app = *juce::JUCEApplication::getInstance();
    app.setApplicationReturnValue(EXIT_SUCCESS);

    if (auto const result = func(cli); result.failed()) {
        std::cerr << result.getErrorMessage() << '\n';
        app.setApplicationReturnValue(EXIT_FAILURE);
    }

    app.quit();
}
} // namespace

struct GuiAppApplication final : juce::JUCEApplication
{

    GuiAppApplication() = default;

    auto getApplicationName() -> juce::String const override { return JUCE_APPLICATION_NAME_STRING; }

    auto getApplicationVersion() -> juce::String const override
    {
        return JUCE_APPLICATION_VERSION_STRING;
    }

    auto moreThanOneInstanceAllowed() -> bool override { return true; }

    auto initialise(juce::String const& commandLine) -> void override
    {
        auto const [cli, shouldExit] = jml::viewer::parseCommandLine(commandLine);
        if (cli == nullptr or shouldExit) {
            setApplicationReturnValue(cli == nullptr ? EXIT_FAILURE : EXIT_SUCCESS);
            quit();
            return;
        }

        if (cli->app.got_subcommand("test")) {
            return runCommand(jml::viewer::runTestScript, *cli);
        }
        if (cli->app.got_subcommand("snapshot")) {
            return runCommand(jml::viewer::runSnapshotScript, *cli);
        }

        juce::LookAndFeel::setDefaultLookAndFeel(&_lnf);
        _mainWindow = std::make_unique<MainWindow>(getApplicationName());
    }

    auto shutdown() -> void override
    {
        _mainWindow = nullptr;
        juce::LookAndFeel::setDefaultLookAndFeel(nullptr);
    }

    auto systemRequestedQuit() -> void override { quit(); }

    auto anotherInstanceStarted(juce::String const& commandLine) -> void override
    {
        juce::ignoreUnused(commandLine);
    }

    struct MainWindow : juce::DocumentWindow
    {

        explicit MainWindow(juce::String const& name)
            : DocumentWindow(
                name,
                juce::Desktop::getInstance().getDefaultLookAndFeel().findColour(
                    ResizableWindow::backgroundColourId
                ),
                DocumentWindow::allButtons
            )
        {
            setUsingNativeTitleBar(true);
            setContentOwned(std::make_unique<jml::viewer::MainComponent>().release(), true);

#if JUCE_IOS || JUCE_ANDROID
            setFullScreen(true);
#else
            setResizable(true, true);
            centreWithSize(getWidth(), getHeight());
#endif

            setVisible(true);
        }

        auto closeButtonPressed() -> void override
        {
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow) // NOLINT
    };

private:
    jml::LookAndFeel _lnf;
    std::unique_ptr<MainWindow> _mainWindow;
};

// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION(GuiAppApplication) // NOLINT
