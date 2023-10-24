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

Settings::Settings() { _settings.setStorageParameters(createSettingsOptions()); }

auto Settings::getRecentOpenFiles() -> juce::StringArray
{
    auto& settings      = *_settings.getUserSettings();
    auto const property = settings.getValue("recent_open_files", "");
    return juce::StringArray::fromTokens(property, ";", "");
}

auto Settings::appendToRecentOpenFiles(juce::File const& file) -> void
{
    auto fileList = getRecentOpenFiles();
    fileList.addIfNotAlreadyThere(file.getFullPathName());

    auto& settings = *_settings.getUserSettings();
    settings.setValue("recent_open_files", fileList.joinIntoString(";"));
}

auto Settings::clearRecentOpenFiles() -> void
{
    auto& settings = *_settings.getUserSettings();
    settings.setValue("recent_open_files", "");
}

} // namespace jml::viewer
