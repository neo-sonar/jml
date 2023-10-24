#include "Application.hpp"

#include "Application/CommandLine.hpp"
#include "Application/MainComponent.hpp"
#include "Command/Snapshot.hpp"
#include "Command/Test.hpp"

#include <jml_tools/jml_tools.hpp>

namespace jml::viewer {

namespace {

auto createSettingsOptions() -> juce::PropertiesFile::Options
{
    auto const name = getApplication().getApplicationName();

    auto options                     = juce::PropertiesFile::Options{};
    options.applicationName          = "settings";
    options.filenameSuffix           = ".xml";
    options.commonToAllUsers         = false;
    options.ignoreCaseOfKeyNames     = false;
    options.doNotSave                = false;
    options.millisecondsBeforeSaving = 3'000;
    options.storageFormat            = juce::PropertiesFile::StorageFormat::storeAsXML;
    options.processLock              = nullptr;
    options.osxLibrarySubFolder      = "Application Support";

#if JUCE_LINUX
    options.folderName = ".config/neo-sonar/" + juce::String{name};
#else
    options.folderName = "neo-sonar/" + juce::String{name};
#endif

    DBG(options.getDefaultFile().getFullPathName());
    return options;
}

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

Application::Application() { _settings.setStorageParameters(createSettingsOptions()); }

auto Application::getSettings() -> juce::ApplicationProperties& { return _settings; }

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

auto getApplicationSettings() -> juce::PropertiesFile&
{
    auto* settings = getApplication().getSettings().getUserSettings();
    jassert(settings != nullptr);
    return *settings;
}

auto getRecentOpenFiles() -> juce::StringArray
{
    auto& settings      = getApplicationSettings();
    auto const property = settings.getValue("recent_open_files", "");
    return juce::StringArray::fromTokens(property, ";", "");
}

auto appendToRecentOpenFiles(juce::File const& file) -> void
{
    auto fileList = getRecentOpenFiles();
    fileList.addIfNotAlreadyThere(file.getFullPathName());
    getApplicationSettings().setValue("recent_open_files", fileList.joinIntoString(";"));
}

auto clearRecentOpenFiles() -> void { getApplicationSettings().setValue("recent_open_files", ""); }

} // namespace jml::viewer
