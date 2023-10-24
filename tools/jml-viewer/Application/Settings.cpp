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

    DBG(options.getDefaultFile().getFullPathName());
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

auto Settings::appendToRecentOpenFiles(juce::File const& file) -> void
{
    _recentFiles.addFile(file);
    saveRecentFiles();
}

auto Settings::clearRecentOpenFiles() -> void
{
    _recentFiles.clear();
    saveRecentFiles();
}

auto Settings::saveRecentFiles() -> void
{
    auto& settings = *_settings.getUserSettings();
    settings.setValue("recent_open_files", _recentFiles.toString());
}

} // namespace jml::viewer
