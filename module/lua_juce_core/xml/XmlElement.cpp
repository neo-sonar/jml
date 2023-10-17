namespace lua_juce {

auto juce_XmlElement(sol::table& state) -> void
{
    auto xml = state.new_usertype<juce::XmlElement>("XmlElement", sol::constructors<juce::XmlElement(juce::String const&), juce::XmlElement(char const*)>());

    xml["isEquivalentTo "]             = LUA_JUCE_C_CALL(&juce::XmlElement::isEquivalentTo);
    xml["getTagName"]                  = LUA_JUCE_C_CALL(&juce::XmlElement::getTagName);
    xml["getNamespace"]                = LUA_JUCE_C_CALL(&juce::XmlElement::getNamespace);
    xml["getTagNameWithoutNamespace"]  = LUA_JUCE_C_CALL(&juce::XmlElement::getTagNameWithoutNamespace);
    xml["hasTagName"]                  = LUA_JUCE_C_CALL(&juce::XmlElement::hasTagName);
    xml["hasTagNameIgnoringNamespace"] = LUA_JUCE_C_CALL(&juce::XmlElement::hasTagNameIgnoringNamespace);
    xml["setTagName"]                  = LUA_JUCE_C_CALL(&juce::XmlElement::setTagName);
    xml["getNumAttributes"]            = LUA_JUCE_C_CALL(&juce::XmlElement::getNumAttributes);
    xml["getAttributeName"]            = LUA_JUCE_C_CALL(&juce::XmlElement::getAttributeName);
}

} // namespace lua_juce
