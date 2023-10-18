namespace lua_juce {
auto juce_String(sol::table& state) -> void
{
    auto str = state.new_usertype<juce::String>("String", sol::constructors<juce::String(), juce::String(char const*)>());

    str["hashCode"]                     = LUA_JUCE_C_CALL(&juce::String::hashCode);
    str["hashCode64"]                   = LUA_JUCE_C_CALL(&juce::String::hashCode64);
    str["hash"]                         = LUA_JUCE_C_CALL(&juce::String::hash);
    str["length"]                       = LUA_JUCE_C_CALL(&juce::String::length);
    str["append"]                       = LUA_JUCE_C_CALL(&juce::String::append);
    str["isEmpty"]                      = LUA_JUCE_C_CALL(&juce::String::isEmpty);
    str["isNotEmpty"]                   = LUA_JUCE_C_CALL(&juce::String::isNotEmpty);
    str["clear"]                        = LUA_JUCE_C_CALL(&juce::String::clear);
    str["compareIgnoreCase"]            = LUA_JUCE_C_CALL(&juce::String::compareIgnoreCase);
    str["compareNatural"]               = LUA_JUCE_C_CALL(&juce::String::compareNatural);
    str["startsWith"]                   = LUA_JUCE_C_CALL(&juce::String::startsWith);
    str["startsWithChar"]               = LUA_JUCE_C_CALL(&juce::String::startsWithChar);
    str["startsWithIgnoreCase"]         = LUA_JUCE_C_CALL(&juce::String::startsWithIgnoreCase);
    str["endsWith"]                     = LUA_JUCE_C_CALL(&juce::String::endsWith);
    str["endsWithChar"]                 = LUA_JUCE_C_CALL(&juce::String::endsWithChar);
    str["endsWithIgnoreCase"]           = LUA_JUCE_C_CALL(&juce::String::endsWithIgnoreCase);
    str["contains"]                     = LUA_JUCE_C_CALL(&juce::String::contains);
    str["containsChar"]                 = LUA_JUCE_C_CALL(&juce::String::containsChar);
    str["containsIgnoreCase"]           = LUA_JUCE_C_CALL(&juce::String::containsIgnoreCase);
    str["containsWholeWord"]            = LUA_JUCE_C_CALL(&juce::String::containsWholeWord);
    str["containsWholeWordIgnoreCase"]  = LUA_JUCE_C_CALL(&juce::String::containsWholeWordIgnoreCase);
    str["indexOfWholeWord"]             = LUA_JUCE_C_CALL(&juce::String::indexOfWholeWord);
    str["indexOfWholeWordIgnoreCase"]   = LUA_JUCE_C_CALL(&juce::String::indexOfWholeWordIgnoreCase);
    str["containsAnyOf"]                = LUA_JUCE_C_CALL(&juce::String::containsAnyOf);
    str["containsOnly"]                 = LUA_JUCE_C_CALL(&juce::String::containsOnly);
    str["containsNonWhitespaceChars"]   = LUA_JUCE_C_CALL(&juce::String::containsNonWhitespaceChars);
    str["matchesWildcard"]              = LUA_JUCE_C_CALL(&juce::String::matchesWildcard);
    str["indexOfAnyOf"]                 = LUA_JUCE_C_CALL(&juce::String::indexOfAnyOf);
    str["lastIndexOfChar"]              = LUA_JUCE_C_CALL(&juce::String::lastIndexOfChar);
    str["lastIndexOf"]                  = LUA_JUCE_C_CALL(&juce::String::lastIndexOf);
    str["lastIndexOfIgnoreCase"]        = LUA_JUCE_C_CALL(&juce::String::lastIndexOfIgnoreCase);
    str["lastIndexOfAnyOf"]             = LUA_JUCE_C_CALL(&juce::String::lastIndexOfAnyOf);
    str["getLastCharacter"]             = LUA_JUCE_C_CALL(&juce::String::getLastCharacter);
    str["dropLastCharacters"]           = LUA_JUCE_C_CALL(&juce::String::dropLastCharacters);
    str["getLastCharacters"]            = LUA_JUCE_C_CALL(&juce::String::getLastCharacters);
    str["fromFirstOccurrenceOf"]        = LUA_JUCE_C_CALL(&juce::String::fromFirstOccurrenceOf);
    str["fromLastOccurrenceOf"]         = LUA_JUCE_C_CALL(&juce::String::fromLastOccurrenceOf);
    str["upToFirstOccurrenceOf"]        = LUA_JUCE_C_CALL(&juce::String::upToFirstOccurrenceOf);
    str["upToLastOccurrenceOf"]         = LUA_JUCE_C_CALL(&juce::String::upToLastOccurrenceOf);
    str["trim"]                         = LUA_JUCE_C_CALL(&juce::String::trim);
    str["trimStart"]                    = LUA_JUCE_C_CALL(&juce::String::trimStart);
    str["trimEnd"]                      = LUA_JUCE_C_CALL(&juce::String::trimEnd);
    str["trimCharactersAtStart"]        = LUA_JUCE_C_CALL(&juce::String::trimCharactersAtStart);
    str["trimCharactersAtEnd"]          = LUA_JUCE_C_CALL(&juce::String::trimCharactersAtEnd);
    str["toUpperCase"]                  = LUA_JUCE_C_CALL(&juce::String::toUpperCase);
    str["toLowerCase"]                  = LUA_JUCE_C_CALL(&juce::String::toLowerCase);
    str["replaceSection"]               = LUA_JUCE_C_CALL(&juce::String::replaceSection);
    str["replace"]                      = LUA_JUCE_C_CALL(&juce::String::replace);
    str["replaceFirstOccurrenceOf"]     = LUA_JUCE_C_CALL(&juce::String::replaceFirstOccurrenceOf);
    str["replaceCharacter"]             = LUA_JUCE_C_CALL(&juce::String::replaceCharacter);
    str["replaceCharacters"]            = LUA_JUCE_C_CALL(&juce::String::replaceCharacters);
    str["retainCharacters"]             = LUA_JUCE_C_CALL(&juce::String::retainCharacters);
    str["removeCharacters"]             = LUA_JUCE_C_CALL(&juce::String::removeCharacters);
    str["initialSectionContainingOnly"] = LUA_JUCE_C_CALL(&juce::String::initialSectionContainingOnly);
    str["initialSectionNotContaining"]  = LUA_JUCE_C_CALL(&juce::String::initialSectionNotContaining);
    str["isQuotedString"]               = LUA_JUCE_C_CALL(&juce::String::isQuotedString);
    str["unquoted"]                     = LUA_JUCE_C_CALL(&juce::String::unquoted);
    str["quoted"]                       = LUA_JUCE_C_CALL(&juce::String::quoted);
    str["toStdString"]                  = LUA_JUCE_C_CALL(&juce::String::toStdString);

    // str["compare"] = LUA_JUCE_C_CALL(&juce::String::compare);
}
} // namespace lua_juce
