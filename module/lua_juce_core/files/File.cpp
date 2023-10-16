namespace lua_juce {

auto juce_File(sol::table& state) -> void
{
    // clang-format off
    state.new_enum("FileTypesOfFileToFind",
        "findDirectories",          juce::File::TypesOfFileToFind::findDirectories,
        "findFiles",                juce::File::TypesOfFileToFind::findFiles,
        "findFilesAndDirectories",  juce::File::TypesOfFileToFind::findFilesAndDirectories,
        "ignoreHiddenFiles",        juce::File::TypesOfFileToFind::ignoreHiddenFiles
    );

    state.new_enum("FileSpecialLocationType",
        "userHomeDirectory",                juce::File::userHomeDirectory,
        "userDocumentsDirectory",           juce::File::userDocumentsDirectory,
        "userDesktopDirectory",             juce::File::userDesktopDirectory,
        "userMusicDirectory",               juce::File::userMusicDirectory,
        "userMoviesDirectory",              juce::File::userMoviesDirectory,
        "userPicturesDirectory",            juce::File::userPicturesDirectory,
        "userApplicationDataDirectory",     juce::File::userApplicationDataDirectory,
        "commonApplicationDataDirectory",   juce::File::commonApplicationDataDirectory,
        "commonDocumentsDirectory",         juce::File::commonDocumentsDirectory,
        "tempDirectory",                    juce::File::tempDirectory,
        "currentExecutableFile",            juce::File::currentExecutableFile,
        "currentApplicationFile",           juce::File::currentApplicationFile,
        "invokedExecutableFile",            juce::File::invokedExecutableFile,
        "hostApplicationPath",              juce::File::hostApplicationPath,
    #if JUCE_WINDOWS
        "windowsSystemDirectory",           juce::File::windowsSystemDirectory,
    #endif
        "globalApplicationsDirectory",      juce::File::globalApplicationsDirectory
    #if JUCE_WINDOWS
        ,"globalApplicationsDirectoryX86",  juce::File::globalApplicationsDirectoryX86
    #endif
    );

    auto cmp = state.new_usertype<juce::File::NaturalFileComparator>("FileNaturalFileComparator",
        sol::constructors<juce::File::NaturalFileComparator(bool)>()
    );
    cmp["compareElements"] = &juce::File::NaturalFileComparator::compareElements;
    cmp["foldersFirst"] = &juce::File::NaturalFileComparator::foldersFirst;

    auto file = state.new_usertype<juce::File>("File",
        sol::constructors<juce::File(), juce::File(juce::String const&)>()
    );
    file.set_function("findChildFiles", sol::overload(
            // Array<File> findChildFiles(int whatToLookFor, bool searchRecursively, const String &wildCardPattern="*") const
            [](juce::File const* self, int what, bool recursive) { return self->findChildFiles(what, recursive); },
            static_cast<juce::Array<juce::File> (juce::File::*)(int, bool, juce::String const&, juce::File::FollowSymlinks) const>(&juce::File::findChildFiles),

            // int findChildFiles(Array<File> &results, int whatToLookFor, bool searchRecursively, const String &wildCardPattern="*") const
            [](juce::File const* self, juce::Array<juce::File>& results, int what, bool recursive) { return self->findChildFiles(results, what, recursive); },
            static_cast<int (juce::File::*)(juce::Array<juce::File>&, int, bool, juce::String const&, juce::File::FollowSymlinks) const>(&juce::File::findChildFiles)
        )
    );
    // clang-format on
    file["exists"]                        = LUA_JUCE_C_CALL(&juce::File::exists);
    file["existsAsFile"]                  = LUA_JUCE_C_CALL(&juce::File::existsAsFile);
    file["isDirectory"]                   = LUA_JUCE_C_CALL(&juce::File::isDirectory);
    file["isRoot"]                        = LUA_JUCE_C_CALL(&juce::File::isRoot);
    file["getSize"]                       = LUA_JUCE_C_CALL(&juce::File::getSize);
    file["descriptionOfSizeInBytes"]      = LUA_JUCE_C_CALL(&juce::File::descriptionOfSizeInBytes);
    file["getFullPathName"]               = LUA_JUCE_C_CALL(&juce::File::getFullPathName);
    file["getFileName"]                   = LUA_JUCE_C_CALL(&juce::File::getFileName);
    file["getRelativePathFrom"]           = LUA_JUCE_C_CALL(&juce::File::getRelativePathFrom);
    file["getFileExtension"]              = LUA_JUCE_C_CALL(&juce::File::getFileExtension);
    file["hasFileExtension"]              = LUA_JUCE_C_CALL(&juce::File::hasFileExtension);
    file["withFileExtension"]             = LUA_JUCE_C_CALL(&juce::File::withFileExtension);
    file["getFileNameWithoutExtension"]   = LUA_JUCE_C_CALL(&juce::File::getFileNameWithoutExtension);
    file["hashCode"]                      = LUA_JUCE_C_CALL(&juce::File::hashCode);
    file["hashCode64"]                    = LUA_JUCE_C_CALL(&juce::File::hashCode64);
    file["getSiblingFile"]                = LUA_JUCE_C_CALL(&juce::File::getSiblingFile);
    file["getParentDirectory"]            = LUA_JUCE_C_CALL(&juce::File::getParentDirectory);
    file["isAChildOf"]                    = LUA_JUCE_C_CALL(&juce::File::isAChildOf);
    file["getNonexistentChildFile"]       = LUA_JUCE_C_CALL(&juce::File::getNonexistentChildFile);
    file["getNonexistentSibling"]         = LUA_JUCE_C_CALL(&juce::File::getNonexistentSibling);
    file["hasWriteAccess"]                = LUA_JUCE_C_CALL(&juce::File::hasWriteAccess);
    file["setReadOnly"]                   = LUA_JUCE_C_CALL(&juce::File::setReadOnly);
    file["setExecutePermission"]          = LUA_JUCE_C_CALL(&juce::File::setExecutePermission);
    file["isHidden"]                      = LUA_JUCE_C_CALL(&juce::File::isHidden);
    file["getFileIdentifier"]             = LUA_JUCE_C_CALL(&juce::File::getFileIdentifier);
    file["getLastModificationTime"]       = LUA_JUCE_C_CALL(&juce::File::getLastModificationTime);
    file["getLastAccessTime"]             = LUA_JUCE_C_CALL(&juce::File::getLastAccessTime);
    file["getCreationTime"]               = LUA_JUCE_C_CALL(&juce::File::getCreationTime);
    file["setLastModificationTime"]       = LUA_JUCE_C_CALL(&juce::File::setLastModificationTime);
    file["setLastAccessTime"]             = LUA_JUCE_C_CALL(&juce::File::setLastAccessTime);
    file["setCreationTime"]               = LUA_JUCE_C_CALL(&juce::File::setCreationTime);
    file["getVersion"]                    = LUA_JUCE_C_CALL(&juce::File::getVersion);
    file["create"]                        = LUA_JUCE_C_CALL(&juce::File::create);
    file["createDirectory"]               = LUA_JUCE_C_CALL(&juce::File::createDirectory);
    file["deleteFile"]                    = LUA_JUCE_C_CALL(&juce::File::deleteFile);
    file["deleteRecursively"]             = LUA_JUCE_C_CALL(&juce::File::deleteRecursively);
    file["moveToTrash"]                   = LUA_JUCE_C_CALL(&juce::File::moveToTrash);
    file["moveFileTo"]                    = LUA_JUCE_C_CALL(&juce::File::moveFileTo);
    file["copyFileTo"]                    = LUA_JUCE_C_CALL(&juce::File::copyFileTo);
    file["replaceFileIn"]                 = LUA_JUCE_C_CALL(&juce::File::replaceFileIn);
    file["copyDirectoryTo"]               = LUA_JUCE_C_CALL(&juce::File::copyDirectoryTo);
    file["getNumberOfChildFiles"]         = LUA_JUCE_C_CALL(&juce::File::getNumberOfChildFiles);
    file["containsSubDirectories"]        = LUA_JUCE_C_CALL(&juce::File::containsSubDirectories);
    file["createInputStream"]             = LUA_JUCE_C_CALL(&juce::File::createInputStream);
    file["createOutputStream"]            = LUA_JUCE_C_CALL(&juce::File::createOutputStream);
    file["loadFileAsData"]                = LUA_JUCE_C_CALL(&juce::File::loadFileAsData);
    file["loadFileAsString"]              = LUA_JUCE_C_CALL(&juce::File::loadFileAsString);
    file["readLines"]                     = LUA_JUCE_C_CALL(&juce::File::readLines);
    file["appendData"]                    = LUA_JUCE_C_CALL(&juce::File::appendData);
    file["replaceWithData"]               = LUA_JUCE_C_CALL(&juce::File::replaceWithData);
    file["appendText"]                    = LUA_JUCE_C_CALL(&juce::File::appendText);
    file["replaceWithText"]               = LUA_JUCE_C_CALL(&juce::File::replaceWithText);
    file["hasIdenticalContentTo"]         = LUA_JUCE_C_CALL(&juce::File::hasIdenticalContentTo);
    file["findFileSystemRoots"]           = LUA_JUCE_C_CALL(&juce::File::findFileSystemRoots);
    file["getVolumeLabel"]                = LUA_JUCE_C_CALL(&juce::File::getVolumeLabel);
    file["getVolumeSerialNumber"]         = LUA_JUCE_C_CALL(&juce::File::getVolumeSerialNumber);
    file["getBytesFreeOnVolume"]          = LUA_JUCE_C_CALL(&juce::File::getBytesFreeOnVolume);
    file["getVolumeTotalSize"]            = LUA_JUCE_C_CALL(&juce::File::getVolumeTotalSize);
    file["isOnCDRomDrive"]                = LUA_JUCE_C_CALL(&juce::File::isOnCDRomDrive);
    file["isOnHardDisk"]                  = LUA_JUCE_C_CALL(&juce::File::isOnHardDisk);
    file["isOnRemovableDrive"]            = LUA_JUCE_C_CALL(&juce::File::isOnRemovableDrive);
    file["startAsProcess"]                = LUA_JUCE_C_CALL(&juce::File::startAsProcess);
    file["revealToUser"]                  = LUA_JUCE_C_CALL(&juce::File::revealToUser);
    file["getSpecialLocation"]            = LUA_JUCE_C_CALL(&juce::File::getSpecialLocation);
    file["createTempFile"]                = LUA_JUCE_C_CALL(&juce::File::createTempFile);
    file["getCurrentWorkingDirectory"]    = LUA_JUCE_C_CALL(&juce::File::getCurrentWorkingDirectory);
    file["setAsCurrentWorkingDirectory"]  = LUA_JUCE_C_CALL(&juce::File::setAsCurrentWorkingDirectory);
    file["getSeparatorChar"]              = LUA_JUCE_C_CALL(&juce::File::getSeparatorChar);
    file["getSeparatorString"]            = LUA_JUCE_C_CALL(&juce::File::getSeparatorString);
    file["createLegalFileName"]           = LUA_JUCE_C_CALL(&juce::File::createLegalFileName);
    file["createLegalPathName"]           = LUA_JUCE_C_CALL(&juce::File::createLegalPathName);
    file["areFileNamesCaseSensitive"]     = LUA_JUCE_C_CALL(&juce::File::areFileNamesCaseSensitive);
    file["isAbsolutePath"]                = LUA_JUCE_C_CALL(&juce::File::isAbsolutePath);
    file["createFileWithoutCheckingPath"] = LUA_JUCE_C_CALL(&juce::File::createFileWithoutCheckingPath);
    file["addTrailingSeparator"]          = LUA_JUCE_C_CALL(&juce::File::addTrailingSeparator);
    file["isSymbolicLink"]                = LUA_JUCE_C_CALL(&juce::File::isSymbolicLink);
    file["getLinkedTarget"]               = LUA_JUCE_C_CALL(&juce::File::getLinkedTarget);
    file["getNativeLinkedTarget"]         = LUA_JUCE_C_CALL(&juce::File::getNativeLinkedTarget);
    file["getChildFile"]                  = sol::overload(                                                 //
        [](juce::File* self, char const* child) { return self->getChildFile(child); },    //
        [](juce::File* self, juce::StringRef child) { return self->getChildFile(child); } //
    );                                                                                    //

#if JUCE_WINDOWS
    file["createShortcut"] = &juce::File::createShortcut;
    file["isShortcut"]     = &juce::File::isShortcut;
#endif

#if JUCE_MAC
    file["getMacOSType"] = &juce::File::getMacOSType;
    file["isBundle"]     = &juce::File::isBundle;
    file["addToDock"]    = &juce::File::addToDock;
#endif

    // TODO(tobi): createSymbolicLink
}
} // namespace lua_juce
