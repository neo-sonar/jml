namespace lua_juce {

auto juce_CodeDocument(sol::table& state) -> void
{
    auto table = state["CodeDocument"].get_or_create<sol::table>();

    auto doc                        = table.new_usertype<juce::CodeDocument>("CodeDocument", sol::constructors<juce::CodeDocument()>());
    doc["getAllContent"]            = LUA_JUCE_C_CALL(&juce::CodeDocument::getAllContent);
    doc["getTextBetween"]           = LUA_JUCE_C_CALL(&juce::CodeDocument::getTextBetween);
    doc["getLine"]                  = LUA_JUCE_C_CALL(&juce::CodeDocument::getLine);
    doc["getNumCharacters"]         = LUA_JUCE_C_CALL(&juce::CodeDocument::getNumCharacters);
    doc["getNumLines"]              = LUA_JUCE_C_CALL(&juce::CodeDocument::getNumLines);
    doc["getMaximumLineLength"]     = LUA_JUCE_C_CALL(&juce::CodeDocument::getMaximumLineLength);
    doc["replaceSection"]           = LUA_JUCE_C_CALL(&juce::CodeDocument::replaceSection);
    doc["replaceAllContent"]        = LUA_JUCE_C_CALL(&juce::CodeDocument::replaceAllContent);
    doc["applyChanges"]             = LUA_JUCE_C_CALL(&juce::CodeDocument::applyChanges);
    doc["loadFromStream"]           = LUA_JUCE_C_CALL(&juce::CodeDocument::loadFromStream);
    doc["writeToStream"]            = LUA_JUCE_C_CALL(&juce::CodeDocument::writeToStream);
    doc["getNewLineCharacters"]     = LUA_JUCE_C_CALL(&juce::CodeDocument::getNewLineCharacters);
    doc["setNewLineCharacters"]     = LUA_JUCE_C_CALL(&juce::CodeDocument::setNewLineCharacters);
    doc["newTransaction"]           = LUA_JUCE_C_CALL(&juce::CodeDocument::newTransaction);
    doc["undo"]                     = LUA_JUCE_C_CALL(&juce::CodeDocument::undo);
    doc["redo"]                     = LUA_JUCE_C_CALL(&juce::CodeDocument::redo);
    doc["clearUndoHistory"]         = LUA_JUCE_C_CALL(&juce::CodeDocument::clearUndoHistory);
    doc["getUndoManager"]           = LUA_JUCE_C_CALL(&juce::CodeDocument::getUndoManager);
    doc["setSavePoint"]             = LUA_JUCE_C_CALL(&juce::CodeDocument::setSavePoint);
    doc["hasChangedSinceSavePoint"] = LUA_JUCE_C_CALL(&juce::CodeDocument::hasChangedSinceSavePoint);
    doc["findWordBreakBefore"]      = LUA_JUCE_C_CALL(&juce::CodeDocument::findWordBreakBefore);
    doc["findTokenContaining"]      = LUA_JUCE_C_CALL(&juce::CodeDocument::findTokenContaining);
    doc["findLineContaining"]       = LUA_JUCE_C_CALL(&juce::CodeDocument::findLineContaining);
    doc["addListener"]              = LUA_JUCE_C_CALL(&juce::CodeDocument::addListener);
    doc["removeListener"]           = LUA_JUCE_C_CALL(&juce::CodeDocument::removeListener);
    // doc["deleteSection"]            = &juce::CodeDocument::deleteSection;
    // doc["deleteSection"]            = &juce::CodeDocument::deleteSection;
    // doc["insertText"]               = &juce::CodeDocument::insertText;
    // doc["insertText"]               = &juce::CodeDocument::insertText;

    table["new"] = [] { return std::unique_ptr<juce::CodeDocument>(); };
}

} // namespace lua_juce
