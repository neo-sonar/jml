namespace lua_juce {

namespace {

auto getDocumentElement_1(juce::XmlDocument* xml) -> std::unique_ptr<juce::XmlElement> { return xml->getDocumentElement(); }
auto getDocumentElement_2(juce::XmlDocument* xml, bool b) -> std::unique_ptr<juce::XmlElement> { return xml->getDocumentElement(b); }

auto parse_1(juce::String const& str) -> std::unique_ptr<juce::XmlElement> { return juce::XmlDocument::parse(str); }
auto parse_2(juce::File const& file) -> std::unique_ptr<juce::XmlElement> { return juce::XmlDocument::parse(file); }

} // namespace

auto juce_XmlDocument(sol::table& state) -> void
{
    using juce::XmlDocument;
    auto xml = state.new_usertype<XmlDocument>("XmlDocument", sol::constructors<XmlDocument(juce::String const&), XmlDocument(juce::File const&)>());

    xml["getDocumentElement"]             = sol::c_call<LUA_JUCE_WRAP(getDocumentElement_1), LUA_JUCE_WRAP(getDocumentElement_2)>;
    xml["getDocumentElementIfTagMatches"] = LUA_JUCE_C_CALL(&XmlDocument::getDocumentElementIfTagMatches);
    xml["getLastParseError"]              = LUA_JUCE_C_CALL(&XmlDocument::getLastParseError);
    xml["setEmptyTextElementsIgnored"]    = LUA_JUCE_C_CALL(&XmlDocument::setEmptyTextElementsIgnored);
    xml["parse"]                          = sol::c_call<LUA_JUCE_WRAP(parse_1), LUA_JUCE_WRAP(parse_2)>;
}

} // namespace lua_juce
