namespace lua_juce {
auto juce_StringArray(sol::table& state) -> void
{
    auto array = state.new_usertype<juce::StringArray>("StringArray", sol::constructors<juce::StringArray()>());

    array["size"]                      = LUA_JUCE_C_CALL(&juce::StringArray::size);
    array["isEmpty"]                   = LUA_JUCE_C_CALL(&juce::StringArray::isEmpty);
    array["swapWith"]                  = LUA_JUCE_C_CALL(&juce::StringArray::swapWith);
    array["contains"]                  = LUA_JUCE_C_CALL(&juce::StringArray::contains);
    array["indexOf"]                   = LUA_JUCE_C_CALL(&juce::StringArray::indexOf);
    array["add"]                       = LUA_JUCE_C_CALL(&juce::StringArray::add);
    array["mergeArray"]                = LUA_JUCE_C_CALL(&juce::StringArray::mergeArray);
    array["addLines"]                  = LUA_JUCE_C_CALL(&juce::StringArray::addLines);
    array["clear"]                     = LUA_JUCE_C_CALL(&juce::StringArray::clear);
    array["clearQuick"]                = LUA_JUCE_C_CALL(&juce::StringArray::clearQuick);
    array["remove"]                    = LUA_JUCE_C_CALL(&juce::StringArray::remove);
    array["removeString"]              = LUA_JUCE_C_CALL(&juce::StringArray::removeString);
    array["removeRange"]               = LUA_JUCE_C_CALL(&juce::StringArray::removeRange);
    array["removeDuplicates"]          = LUA_JUCE_C_CALL(&juce::StringArray::removeDuplicates);
    array["removeEmptyStrings"]        = LUA_JUCE_C_CALL(&juce::StringArray::removeEmptyStrings);
    array["move"]                      = LUA_JUCE_C_CALL(&juce::StringArray::move);
    array["trim"]                      = LUA_JUCE_C_CALL(&juce::StringArray::trim);
    array["appendNumbersToDuplicates"] = LUA_JUCE_C_CALL(&juce::StringArray::appendNumbersToDuplicates);
    array["joinIntoString"]            = LUA_JUCE_C_CALL(&juce::StringArray::joinIntoString);
    // array["sort"]                      = &juce::StringArray::sort;
    // array["sortNatural"]               = &juce::StringArray::sortNatural;
    array["minimiseStorageOverheads"] = LUA_JUCE_C_CALL(&juce::StringArray::minimiseStorageOverheads);
    array["ensureStorageAllocated"]   = LUA_JUCE_C_CALL(&juce::StringArray::ensureStorageAllocated);
    // array["fromLines"]                 = &juce::StringArray::fromLines;
    // array["strings"]                   = &juce::StringArray::strings;

    // TODO(tobi)
    // getReference
    // begin
    // end
    // addTokens
    // fromTokens
}
} // namespace lua_juce
