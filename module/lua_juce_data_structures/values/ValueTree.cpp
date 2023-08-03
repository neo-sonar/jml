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

    vt["isEquivalentTo"]                = &juce::ValueTree::isEquivalentTo;
    vt["isValid"]                       = &juce::ValueTree::isValid;
    vt["createCopy"]                    = &juce::ValueTree::createCopy;
    vt["copyPropertiesFrom"]            = &juce::ValueTree::copyPropertiesFrom;
    vt["copyPropertiesAndChildrenFrom"] = &juce::ValueTree::copyPropertiesAndChildrenFrom;
    vt["getType"]                       = &juce::ValueTree::getType;
    vt["hasType"]                       = &juce::ValueTree::hasType;
    vt["getPropertyPointer"]            = &juce::ValueTree::getPropertyPointer;
    vt["setProperty"]                   = &juce::ValueTree::setProperty;
    vt["hasProperty"]                   = &juce::ValueTree::hasProperty;
    vt["removeProperty"]                = &juce::ValueTree::removeProperty;
    vt["removeAllProperties"]           = &juce::ValueTree::removeAllProperties;
    vt["getNumProperties"]              = &juce::ValueTree::getNumProperties;
    vt["getPropertyName"]               = &juce::ValueTree::getPropertyName;
    vt["getPropertyAsValue"]            = &juce::ValueTree::getPropertyAsValue;
    vt["getNumChildren"]                = &juce::ValueTree::getNumChildren;
    vt["getChild"]                      = &juce::ValueTree::getChild;
    vt["getChildWithName"]              = &juce::ValueTree::getChildWithName;
    vt["getOrCreateChildWithName"]      = &juce::ValueTree::getOrCreateChildWithName;
    vt["getChildWithProperty"]          = &juce::ValueTree::getChildWithProperty;
    vt["addChild"]                      = &juce::ValueTree::addChild;
    vt["appendChild"]                   = &juce::ValueTree::appendChild;
    vt["removeAllChildren"]             = &juce::ValueTree::removeAllChildren;
    vt["moveChild"]                     = &juce::ValueTree::moveChild;
    vt["isAChildOf"]                    = &juce::ValueTree::isAChildOf;
    vt["indexOf"]                       = &juce::ValueTree::indexOf;
    vt["getParent"]                     = &juce::ValueTree::getParent;
    vt["getRoot"]                       = &juce::ValueTree::getRoot;
    vt["getSibling"]                    = &juce::ValueTree::getSibling;
    vt["createXml"]                     = &juce::ValueTree::createXml;
    vt["toXmlString"]                   = &juce::ValueTree::toXmlString;
    vt["writeToStream"]                 = &juce::ValueTree::writeToStream;
    vt["addListener"]                   = &juce::ValueTree::addListener;
    vt["removeListener"]                = &juce::ValueTree::removeListener;
    vt["setPropertyExcludingListener"]  = &juce::ValueTree::setPropertyExcludingListener;
    vt["sendPropertyChangeMessage"]     = &juce::ValueTree::sendPropertyChangeMessage;
    vt["getReferenceCount"]             = &juce::ValueTree::getReferenceCount;

    vt["readFromStream"]   = &juce::ValueTree::readFromStream;
    vt["readFromData"]     = &juce::ValueTree::readFromData;
    vt["readFromGZIPData"] = &juce::ValueTree::readFromGZIPData;
}

} // namespace lua_juce
