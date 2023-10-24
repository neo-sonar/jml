#include "MainComponent.hpp"

#include "Application/Application.hpp"
#include "Application/CommandIDs.hpp"

#include <jml_tools/jml_tools.hpp>

namespace jml::viewer {

MainComponent::MainComponent()
{
    _menuBar.onFileLoad = [this](auto const& file) { _documents.openScript(file); };

    _commandManager.registerAllCommandsForTarget(this);
    addKeyListener(_commandManager.getKeyMappings());
    setWantsKeyboardFocus(true);

    addAndMakeVisible(_menuBar);
    addAndMakeVisible(_documents);

    setSize(1280, 720);
}

MainComponent::~MainComponent() = default;

auto MainComponent::paint(juce::Graphics& g) -> void { g.fillAll(getSchemeWindowBackgroundColour()); }

auto MainComponent::resized() -> void
{
    auto area = getLocalBounds();
    _menuBar.setBounds(area.removeFromTop(getLookAndFeel().getDefaultMenuBarHeight()));
    _documents.setBounds(area);
}

auto MainComponent::getNextCommandTarget() -> juce::ApplicationCommandTarget*
{
    return findFirstTargetParentComponent();
}

auto MainComponent::getAllCommands(juce::Array<juce::CommandID>& c) -> void
{
    c.addArray({
        CommandIDs::open,
        CommandIDs::reload,
        CommandIDs::save,
        CommandIDs::saveAs,
        CommandIDs::settings,
        CommandIDs::quit,
        CommandIDs::undo,
        CommandIDs::redo,
        CommandIDs::cut,
        CommandIDs::copy,
        CommandIDs::paste,
        CommandIDs::selectAll,
        // CommandIDs::deselectAll,
        CommandIDs::redo,
        CommandIDs::undo,
        CommandIDs::about,
    });
}

auto MainComponent::getCommandInfo(juce::CommandID commandID, juce::ApplicationCommandInfo& result)
    -> void
{
    using juce::KeyPress;
    using juce::ModifierKeys;

    auto const cmd   = ModifierKeys::commandModifier;
    auto const shift = ModifierKeys::shiftModifier;

    switch (commandID) {
        case CommandIDs::open: {
            result.setInfo("Open", "Opens a script file", "File", 0);
            result.addDefaultKeypress('o', cmd);
            break;
        }
        case CommandIDs::reload: {
            result.setInfo("Reload", "Reload script file", "File", 0);
            result.addDefaultKeypress('r', cmd);
            break;
        }
        case CommandIDs::save: {
            result.setInfo("Save", "Saves a script file", "File", 0);
            result.addDefaultKeypress('s', cmd);
            break;
        }
        case CommandIDs::saveAs: {
            result.setInfo("Save As", "Saves a script file to a new location", "File", 0);
            result.addDefaultKeypress('s', cmd | shift);
            break;
        }
        case CommandIDs::settings: {
            result.setInfo("Settings", "Open settings", "File", 0);
            result.addDefaultKeypress('p', cmd);
            break;
        }
        case CommandIDs::quit: {
            result.setInfo("Quit", "Quit application", "File", 0);
            result.addDefaultKeypress('q', cmd);
            break;
        }
        case CommandIDs::undo: {
            result.setInfo("Undo", "Undo one step", "Edit", 0);
            result.addDefaultKeypress('z', cmd);
            break;
        }
        case CommandIDs::redo: {
            result.setInfo("Redo", "Redo one step", "Edit", 0);
            result.addDefaultKeypress('z', cmd | shift);
            break;
        }
        case CommandIDs::cut: {
            result.setInfo("Cut", "Cut to clipboard", "Edit", 0);
            result.addDefaultKeypress('x', cmd);
            break;
        }
        case CommandIDs::copy: {
            result.setInfo("Copy", "Copy to clipboard", "Edit", 0);
            result.addDefaultKeypress('c', cmd);
            break;
        }
        case CommandIDs::paste: {
            result.setInfo("Paste", "Paste from clipboard", "Edit", 0);
            result.addDefaultKeypress('v', cmd);
            break;
        }
        case CommandIDs::selectAll: {
            result.setInfo("Select All", "Select all text", "Edit", 0);
            result.addDefaultKeypress('a', cmd);
            break;
        }
        case CommandIDs::about: {
            result.setInfo("About", "Show debug info", "Help", 0);
            break;
        }
        default: break;
    }
}

auto MainComponent::perform(juce::ApplicationCommandTarget::InvocationInfo const& info) -> bool
{
    switch (info.commandID) {
        case CommandIDs::open: loadScriptPath(); break;
        case CommandIDs::reload: _documents.reloadActiveScript(); break;
        case CommandIDs::save:
        case CommandIDs::saveAs: /*saveProject();*/ break;
        case CommandIDs::settings: showSettingsWindow(); break;
        case CommandIDs::quit: getApplication().quit(); break;
        case CommandIDs::undo: _undoManager.undo(); break;
        case CommandIDs::redo: _undoManager.redo(); break;
        case CommandIDs::about: showAboutWindow(); break;
        default: return false;
    }

    return true;
}

auto MainComponent::isInterestedInFileDrag(juce::StringArray const& files) -> bool
{
    if (files.size() != 1) {
        return false;
    }

    auto const file = juce::File{files[0]};
    return file.existsAsFile() and file.hasFileExtension(".lua");
}

auto MainComponent::filesDropped(juce::StringArray const& files, int /*x*/, int /*y*/) -> void
{
    jassert(files.size() == 1);
    _documents.openScript(juce::File{files[0]});
}

auto MainComponent::showSettingsWindow() -> void
{
    auto const background = getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId);
    _settings.showInDialogBox("Settings", 640, 400, background);
}

auto MainComponent::showAboutWindow() -> void
{
    auto const options = juce::MessageBoxOptions()
                             .withTitle("About")
                             .withMessage("JML-Viewer - 0.1.0")
                             .withIconType(juce::MessageBoxIconType::InfoIcon)
                             .withButton("Ok")
                             .withParentComponent(this);

    juce::AlertWindow::showAsync(options, [](int /*button*/) {});
}

auto MainComponent::loadScriptPath() -> void
{
    using juce::FileBrowserComponent;

    auto const* msg = "Please select the lua script you want to load...";
    auto const dir  = juce::File::getSpecialLocation(juce::File::currentApplicationFile);
    auto const mode = FileBrowserComponent::openMode | FileBrowserComponent::canSelectFiles;

    _fileChooser = std::make_unique<juce::FileChooser>(msg, dir, "*.lua");
    _fileChooser->launchAsync(mode, [this](auto const& chooser) {
        if (auto const result = chooser.getResult(); result.existsAsFile()) {
            _documents.openScript(result);
            getApplicationSettings().appendToRecentOpenFiles(result);
        }
    });
}
} // namespace jml::viewer
