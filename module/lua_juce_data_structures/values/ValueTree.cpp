namespace lua_juce {

auto juce_ValueTree(sol::table& state) -> void
{
    // clang-format off
    auto vt = state.new_usertype<juce::ValueTree>("ValueTree",
        sol::constructors<
            juce::ValueTree(),
            juce::ValueTree(juce::Identifier const&)
        >()
    );

    vt["getProperty"] = sol::overload(
        [](juce::ValueTree* self, juce::Identifier const& name) { return self->getProperty(name); },
        [](juce::ValueTree* self, juce::Identifier const& name, juce::var const& val) { return self->getProperty(name, val); }
    );

    vt["removeChild"] = sol::overload(
        [](juce::ValueTree* self, juce::ValueTree const& child, juce::UndoManager* um) { self->removeChild(child, um); },
        [](juce::ValueTree* self, int index, juce::UndoManager* um) { self->removeChild(index, um); }
    );

    vt["fromXml"] = sol::overload(
        [](juce::String const& xml) { return juce::ValueTree::fromXml(xml); },
        [](juce::XmlElement const& xml) { return juce::ValueTree::fromXml(xml); }
    );

    // clang-format on

    vt["isEquivalentTo"]                = LUA_JUCE_C_CALL(&juce::ValueTree::isEquivalentTo);
    vt["isValid"]                       = LUA_JUCE_C_CALL(&juce::ValueTree::isValid);
    vt["createCopy"]                    = LUA_JUCE_C_CALL(&juce::ValueTree::createCopy);
    vt["copyPropertiesFrom"]            = LUA_JUCE_C_CALL(&juce::ValueTree::copyPropertiesFrom);
    vt["copyPropertiesAndChildrenFrom"] = LUA_JUCE_C_CALL(&juce::ValueTree::copyPropertiesAndChildrenFrom);
    vt["getType"]                       = LUA_JUCE_C_CALL(&juce::ValueTree::getType);
    vt["hasType"]                       = LUA_JUCE_C_CALL(&juce::ValueTree::hasType);
    vt["getPropertyPointer"]            = LUA_JUCE_C_CALL(&juce::ValueTree::getPropertyPointer);
    vt["setProperty"]                   = LUA_JUCE_C_CALL(&juce::ValueTree::setProperty);
    vt["hasProperty"]                   = LUA_JUCE_C_CALL(&juce::ValueTree::hasProperty);
    vt["removeProperty"]                = LUA_JUCE_C_CALL(&juce::ValueTree::removeProperty);
    vt["removeAllProperties"]           = LUA_JUCE_C_CALL(&juce::ValueTree::removeAllProperties);
    vt["getNumProperties"]              = LUA_JUCE_C_CALL(&juce::ValueTree::getNumProperties);
    vt["getPropertyName"]               = LUA_JUCE_C_CALL(&juce::ValueTree::getPropertyName);
    vt["getPropertyAsValue"]            = LUA_JUCE_C_CALL(&juce::ValueTree::getPropertyAsValue);
    vt["getNumChildren"]                = LUA_JUCE_C_CALL(&juce::ValueTree::getNumChildren);
    vt["getChild"]                      = LUA_JUCE_C_CALL(&juce::ValueTree::getChild);
    vt["getChildWithName"]              = LUA_JUCE_C_CALL(&juce::ValueTree::getChildWithName);
    vt["getOrCreateChildWithName"]      = LUA_JUCE_C_CALL(&juce::ValueTree::getOrCreateChildWithName);
    vt["getChildWithProperty"]          = LUA_JUCE_C_CALL(&juce::ValueTree::getChildWithProperty);
    vt["addChild"]                      = LUA_JUCE_C_CALL(&juce::ValueTree::addChild);
    vt["appendChild"]                   = LUA_JUCE_C_CALL(&juce::ValueTree::appendChild);
    vt["removeAllChildren"]             = LUA_JUCE_C_CALL(&juce::ValueTree::removeAllChildren);
    vt["moveChild"]                     = LUA_JUCE_C_CALL(&juce::ValueTree::moveChild);
    vt["isAChildOf"]                    = LUA_JUCE_C_CALL(&juce::ValueTree::isAChildOf);
    vt["indexOf"]                       = LUA_JUCE_C_CALL(&juce::ValueTree::indexOf);
    vt["getParent"]                     = LUA_JUCE_C_CALL(&juce::ValueTree::getParent);
    vt["getRoot"]                       = LUA_JUCE_C_CALL(&juce::ValueTree::getRoot);
    vt["getSibling"]                    = LUA_JUCE_C_CALL(&juce::ValueTree::getSibling);
    vt["createXml"]                     = LUA_JUCE_C_CALL(&juce::ValueTree::createXml);
    vt["toXmlString"]                   = LUA_JUCE_C_CALL(&juce::ValueTree::toXmlString);
    vt["writeToStream"]                 = LUA_JUCE_C_CALL(&juce::ValueTree::writeToStream);
    vt["addListener"]                   = LUA_JUCE_C_CALL(&juce::ValueTree::addListener);
    vt["removeListener"]                = LUA_JUCE_C_CALL(&juce::ValueTree::removeListener);
    vt["setPropertyExcludingListener"]  = LUA_JUCE_C_CALL(&juce::ValueTree::setPropertyExcludingListener);
    vt["sendPropertyChangeMessage"]     = LUA_JUCE_C_CALL(&juce::ValueTree::sendPropertyChangeMessage);
    vt["getReferenceCount"]             = LUA_JUCE_C_CALL(&juce::ValueTree::getReferenceCount);

    vt["readFromStream"]   = LUA_JUCE_C_CALL(&juce::ValueTree::readFromStream);
    vt["readFromData"]     = LUA_JUCE_C_CALL(&juce::ValueTree::readFromData);
    vt["readFromGZIPData"] = LUA_JUCE_C_CALL(&juce::ValueTree::readFromGZIPData);
}

} // namespace lua_juce
