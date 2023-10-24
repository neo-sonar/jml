#include "Settings.hpp"

#include "Application/Application.hpp"

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

    return options;
}

} // namespace

Settings::Settings()
{
    _settings.setStorageParameters(createSettingsOptions());
    _recentFiles.setMaxNumberOfItems(10);
}

auto Settings::getRecentFiles() -> juce::StringArray
{
    auto& settings = *_settings.getUserSettings();
    _recentFiles.restoreFromString(settings.getValue("recent_open_files", ""));
    _recentFiles.removeNonExistentFiles();
    return _recentFiles.getAllFilenames();
}

auto Settings::appendToRecentFiles(juce::File const& file) -> void
{
    _recentFiles.addFile(file);
    saveRecentFiles();
}

auto Settings::clearRecentFiles() -> void
{
    _recentFiles.clear();
    saveRecentFiles();
}

auto Settings::getKeyMapping() -> std::unique_ptr<juce::XmlElement>
{
    auto& settings = *_settings.getUserSettings();
    auto xml       = settings.getXmlValue("key_mapping");
    return xml;
}

auto Settings::setKeyMapping(juce::XmlElement const& xml) -> void
{
    auto& settings = *_settings.getUserSettings();
    settings.setValue("key_mapping", &xml);
}

auto Settings::getThemeFile() -> juce::File
{
    return juce::File{_settings.getUserSettings()->getValue("theme_file")};
}

auto Settings::setThemeFile(juce::File const& file) -> void
{
    _settings.getUserSettings()->setValue("theme_file", file.getFullPathName());
}

auto Settings::saveRecentFiles() -> void
{
    auto& settings = *_settings.getUserSettings();
    settings.setValue("recent_open_files", _recentFiles.toString());
}

SettingsWindow::SettingsWindow(juce::ApplicationCommandManager& commandManager)
    : _commandManager{commandManager}
{
    auto code     = getIcon("data_object_black_48dp_svg");
    auto look     = getIcon("palette_black_48dp_svg");
    auto shortcut = getIcon("keyboard_black_48dp_svg");
    addSettingsPage("Code", code.get(), code.get(), code.get());
    addSettingsPage("Look", look.get(), look.get(), look.get());
    addSettingsPage("Shortcut", shortcut.get(), shortcut.get(), shortcut.get());

    _commandManager.getKeyMappings()->addChangeListener(this);
}

SettingsWindow::~SettingsWindow() { _commandManager.getKeyMappings()->removeChangeListener(this); }

auto SettingsWindow::createComponentForPage(juce::String const& pageName) -> juce::Component*
{
    if (pageName == "Code") {
        auto foo   = _tree.getPropertyAsValue("foo", nullptr);
        auto bar   = _tree.getPropertyAsValue("bar", nullptr);
        auto panel = std::make_unique<juce::PropertyPanel>();
        panel->addProperties(juce::Array<juce::PropertyComponent*>{
            std::make_unique<juce::SliderPropertyComponent>(foo, "Foo", 0.0, 1.0, 0.0).release(),
            std::make_unique<juce::TextPropertyComponent>(bar, "Bar", 32, false).release(),
        });
        return panel.release();
    }

    if (pageName == "Shortcut") {
        auto& mappings = *_commandManager.getKeyMappings();
        return std::make_unique<juce::KeyMappingEditorComponent>(mappings, true).release();
    }

    if (pageName == "Look") {
        auto themeOptions = FilePropertyComponent::Options{.pattern = "*.xml"};
        auto theme        = _tree.getPropertyAsValue("theme_file", nullptr);
        if (auto file = getApplicationSettings().getThemeFile(); file.existsAsFile()) {
            theme.setValue(file.getFullPathName());
        }

        auto panel = std::make_unique<juce::PropertyPanel>();
        panel->addProperties(juce::Array<juce::PropertyComponent*>{
            std::make_unique<FilePropertyComponent>(theme, "Theme", themeOptions).release(),
            std::make_unique<CallbackPropertyComponent>("Reload", [this] { remapColours(); })
                .release(),
        });
        return panel.release();
    }

    jassertfalse;
    return nullptr;
}

auto SettingsWindow::changeListenerCallback(juce::ChangeBroadcaster* source) -> void
{
    if (auto* mapping = _commandManager.getKeyMappings(); mapping == source) {
        auto xml = mapping->createXml(true);
        getApplicationSettings().setKeyMapping(*xml);
    }
}

auto SettingsWindow::remapColours() -> void
{
    auto const file  = fromVar<juce::File>(_tree["theme_file"]);
    auto const theme = loadTheme(file);
    if (not theme) {
        return;
    }

    apply(*theme, getLookAndFeel());
    getTopLevelComponent()->repaint();
    if (onThemeChange) {
        onThemeChange();
    }

    getApplicationSettings().setThemeFile(file);
}

} // namespace jml::viewer
