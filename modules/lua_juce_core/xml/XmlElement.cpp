namespace lua_juce {

namespace {
auto getStringAttribute_1(juce::XmlElement* xml, juce::StringRef str) -> juce::String const& { return xml->getStringAttribute(str); }
auto getStringAttribute_2(juce::XmlElement* xml, juce::StringRef str, juce::String const& defaultValue) -> juce::String { return xml->getStringAttribute(str, defaultValue); }
} // namespace

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
    xml["getAttributeValue"]           = LUA_JUCE_C_CALL(&juce::XmlElement::getAttributeValue);
    xml["hasAttribute"]                = LUA_JUCE_C_CALL(&juce::XmlElement::hasAttribute);
    xml["getStringAttribute"]          = sol::c_call<LUA_JUCE_WRAP(getStringAttribute_1), LUA_JUCE_WRAP(getStringAttribute_2)>;
    xml["compareAttribute"]            = LUA_JUCE_C_CALL(&juce::XmlElement::compareAttribute);
    xml["getIntAttribute"]             = LUA_JUCE_C_CALL(&juce::XmlElement::getIntAttribute);
    xml["getDoubleAttribute"]          = LUA_JUCE_C_CALL(&juce::XmlElement::getDoubleAttribute);
    xml["getBoolAttribute"]            = LUA_JUCE_C_CALL(&juce::XmlElement::getBoolAttribute);
    xml["removeAttribute"]             = LUA_JUCE_C_CALL(&juce::XmlElement::removeAttribute);
    xml["removeAllAttributes"]         = LUA_JUCE_C_CALL(&juce::XmlElement::removeAllAttributes);
    xml["getFirstChildElement"]        = LUA_JUCE_C_CALL(&juce::XmlElement::getFirstChildElement);
    xml["getNextElement"]              = LUA_JUCE_C_CALL(&juce::XmlElement::getNextElement);
    xml["getNextElementWithTagName"]   = LUA_JUCE_C_CALL(&juce::XmlElement::getNextElementWithTagName);
    xml["getNumChildElements"]         = LUA_JUCE_C_CALL(&juce::XmlElement::getNumChildElements);
    xml["getChildElement"]             = LUA_JUCE_C_CALL(&juce::XmlElement::getChildElement);
    xml["getChildByName"]              = LUA_JUCE_C_CALL(&juce::XmlElement::getChildByName);
    xml["getChildByAttribute"]         = LUA_JUCE_C_CALL(&juce::XmlElement::getChildByAttribute);
    xml["getAllSubText"]               = LUA_JUCE_C_CALL(&juce::XmlElement::getAllSubText);
    xml["getChildElementAllSubText"]   = LUA_JUCE_C_CALL(&juce::XmlElement::getChildElementAllSubText);
    xml["getText"]                     = LUA_JUCE_C_CALL(&juce::XmlElement::getText);
    xml["setText"]                     = LUA_JUCE_C_CALL(&juce::XmlElement::setText);
}

} // namespace lua_juce
