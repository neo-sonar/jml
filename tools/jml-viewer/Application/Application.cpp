#include "Application.hpp"

#include "Application/CommandLine.hpp"
#include "Application/MainComponent.hpp"
#include "Command/Snapshot.hpp"
#include "Command/Test.hpp"

#include <jml_tools/jml_tools.hpp>

namespace jml::viewer {

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

auto Application::getSettings() -> Settings& { return _settings; }

auto Application::getApplicationName() -> juce::String const { return JUCE_APPLICATION_NAME_STRING; }

auto Application::getApplicationVersion() -> juce::String const
{
    return JUCE_APPLICATION_VERSION_STRING;
}

auto Application::moreThanOneInstanceAllowed() -> bool { return true; }

auto Application::initialise(juce::String const& commandLine) -> void
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
    if (auto const theme = loadTheme(getApplicationSettings().getThemeFile()); theme) {
        apply(*theme, _lnf);
    }

    _mainWindow = std::make_unique<MainWindow>(getApplicationName());
}

auto Application::shutdown() -> void
{
    _mainWindow = nullptr;
    juce::LookAndFeel::setDefaultLookAndFeel(nullptr);
}

auto Application::systemRequestedQuit() -> void { quit(); }

auto Application::anotherInstanceStarted(juce::String const& commandLine) -> void
{
    juce::ignoreUnused(commandLine);
}

Application::MainWindow::MainWindow(juce::String const& name)
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

auto Application::MainWindow::closeButtonPressed() -> void
{
    JUCEApplication::getInstance()->systemRequestedQuit();
}

auto getApplication() -> Application&
{
    auto* app = dynamic_cast<Application*>(juce::JUCEApplication::getInstance());
    jassert(app != nullptr);
    return *app;
}

auto getApplicationSettings() -> Settings& { return getApplication().getSettings(); }

} // namespace jml::viewer
