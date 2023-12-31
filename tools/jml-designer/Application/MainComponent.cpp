#include "MainComponent.hpp"

#include "Menu/CommandIDs.hpp"

namespace jml::designer {

MainComponent::MainComponent()
{
    _commandManager.registerAllCommandsForTarget(this);
    addKeyListener(_commandManager.getKeyMappings());
    setWantsKeyboardFocus(true);

    addAndMakeVisible(_menuBar);
    addAndMakeVisible(*_editor);

    setSize(1280, 720);
}

MainComponent::~MainComponent() { DBG(_document->getValueTree().toXmlString()); }

auto MainComponent::paint(juce::Graphics& g) -> void
{
    g.fillAll(getLookAndFeel().findColour(juce::ResizableWindow::backgroundColourId));
}

auto MainComponent::resized() -> void
{
    auto area = getLocalBounds();
    _menuBar.setBounds(area.removeFromTop(getLookAndFeel().getDefaultMenuBarHeight()));
    _editor->setBounds(area);
}

auto MainComponent::getNextCommandTarget() -> juce::ApplicationCommandTarget*
{
    return findFirstTargetParentComponent();
}

auto MainComponent::getAllCommands(juce::Array<juce::CommandID>& c) -> void
{
    c.addArray({
        CommandIDs::open,
        CommandIDs::save,
        CommandIDs::saveAs,
        CommandIDs::redo,
        CommandIDs::undo,
    });
}

auto MainComponent::getCommandInfo(juce::CommandID commandID, juce::ApplicationCommandInfo& result)
    -> void
{
    using juce::KeyPress;
    using juce::ModifierKeys;

    switch (commandID) {
        case CommandIDs::open:
            result.setInfo("Open", "Opens a project file", "File", 0);
            result.addDefaultKeypress('o', ModifierKeys::commandModifier);
            break;
        case CommandIDs::save:
            result.setInfo("Save", "Saves a project file", "File", 0);
            result.addDefaultKeypress('s', ModifierKeys::commandModifier);
            break;
        case CommandIDs::saveAs:
            result.setInfo("Save As", "Saves a project file to a new location", "File", 0);
            result.addDefaultKeypress(
                's',
                ModifierKeys::commandModifier | ModifierKeys::shiftModifier
            );
            break;
        case CommandIDs::undo:
            result.setInfo("Undo", "Undo one step", "Edit", 0);
            result.addDefaultKeypress('z', ModifierKeys::commandModifier);
            break;
        case CommandIDs::redo:
            result.setInfo("Redo", "Redo one step", "Edit", 0);
            result.addDefaultKeypress(
                'z',
                ModifierKeys::commandModifier | ModifierKeys::shiftModifier
            );
            break;
        default: break;
    }
}

auto MainComponent::perform(juce::ApplicationCommandTarget::InvocationInfo const& info) -> bool
{
    switch (info.commandID) {
        case CommandIDs::open: documentLoad(); break;
        case CommandIDs::save: _document->save(_documentFile); break;
        case CommandIDs::saveAs: documentSaveAs(); break;
        case CommandIDs::undo: _undoManager.undo(); break;
        case CommandIDs::redo: _undoManager.redo(); break;
        default: return false;
    }

    return true;
}

auto MainComponent::documentLoad() -> void
{
    using juce::FileBrowserComponent;
    auto const* msg = "Please select the jml-designer project you want to load...";
    auto const dir  = juce::File::getSpecialLocation(juce::File::currentApplicationFile);
    auto const mode = FileBrowserComponent::openMode | FileBrowserComponent::canSelectFiles;

    _fileChooser = std::make_unique<juce::FileChooser>(msg, dir, "*.jml-designer");
    _fileChooser->launchAsync(mode, [this](auto const& chooser) {
        auto results = chooser.getResults();
        if (results.size() != 1) {
            return;
        }

        auto const file = juce::File{results[0]};
        auto newDoc     = Document::load(file, &_undoManager);
        if (newDoc == nullptr) {
            return;
        }

        _editor.reset(nullptr);
        _document.reset(nullptr);

        _documentFile = file;
        _document     = std::move(newDoc);
        _editor       = std::make_unique<DocumentEditor>(*_document);
        jassert(_editor != nullptr);
        addAndMakeVisible(*_editor);
        resized();
    });
}

auto MainComponent::documentSaveAs() -> void
{
    auto const* msg = "Please select the jml-designer project you want to save...";
    auto const dir  = juce::File::getSpecialLocation(juce::File::currentApplicationFile);
    auto const mode = juce::FileBrowserComponent::saveMode;

    _fileChooser = std::make_unique<juce::FileChooser>(msg, dir, "*.jml-designer");
    _fileChooser->launchAsync(mode, [this](auto const& chooser) {
        auto results = chooser.getResults();
        if (results.size() != 1) {
            return;
        }
        _document->save(juce::File{results[0]});
    });
}

} // namespace jml::designer
