namespace lua_juce {

auto juce_UndoManager(sol::table& state) -> void
{
    // clang-format off
    auto um = state.new_usertype<juce::UndoManager>("UndoManager",
        sol::constructors<juce::UndoManager(int, int)>(),
        sol::base_classes, sol::bases<juce::ChangeBroadcaster>()
    );
    um["perform"] = sol::overload(
        [](juce::UndoManager* self, juce::UndoableAction* action) { return self->perform(action); },
        [](juce::UndoManager* self, juce::UndoableAction* action, juce::String const& name) { return self->perform(action, name); }
    );
    um["beginNewTransaction"] = sol::overload(
        [](juce::UndoManager* self) { return self->beginNewTransaction(); },
        [](juce::UndoManager* self, juce::String const& name) { return self->beginNewTransaction(name); }
    );
    // clang-format on

    um["clearUndoHistory"]                        = LUA_JUCE_C_CALL(&juce::UndoManager::clearUndoHistory);
    um["getNumberOfUnitsTakenUpByStoredCommands"] = LUA_JUCE_C_CALL(&juce::UndoManager::getNumberOfUnitsTakenUpByStoredCommands);
    um["setMaxNumberOfStoredUnits"]               = LUA_JUCE_C_CALL(&juce::UndoManager::setMaxNumberOfStoredUnits);
    um["setCurrentTransactionName"]               = LUA_JUCE_C_CALL(&juce::UndoManager::setCurrentTransactionName);
    um["getCurrentTransactionName"]               = LUA_JUCE_C_CALL(&juce::UndoManager::getCurrentTransactionName);
    um["canUndo"]                                 = LUA_JUCE_C_CALL(&juce::UndoManager::canUndo);
    um["undo"]                                    = LUA_JUCE_C_CALL(&juce::UndoManager::undo);
    um["undoCurrentTransactionOnly"]              = LUA_JUCE_C_CALL(&juce::UndoManager::undoCurrentTransactionOnly);
    um["getUndoDescription"]                      = LUA_JUCE_C_CALL(&juce::UndoManager::getUndoDescription);
    um["getUndoDescriptions"]                     = LUA_JUCE_C_CALL(&juce::UndoManager::getUndoDescriptions);
    um["getTimeOfUndoTransaction"]                = LUA_JUCE_C_CALL(&juce::UndoManager::getTimeOfUndoTransaction);
    um["getActionsInCurrentTransaction"]          = LUA_JUCE_C_CALL(&juce::UndoManager::getActionsInCurrentTransaction);
    um["getNumActionsInCurrentTransaction"]       = LUA_JUCE_C_CALL(&juce::UndoManager::getNumActionsInCurrentTransaction);
    um["canRedo"]                                 = LUA_JUCE_C_CALL(&juce::UndoManager::canRedo);
    um["redo"]                                    = LUA_JUCE_C_CALL(&juce::UndoManager::redo);
    um["getRedoDescription"]                      = LUA_JUCE_C_CALL(&juce::UndoManager::getRedoDescription);
    um["getRedoDescriptions"]                     = LUA_JUCE_C_CALL(&juce::UndoManager::getRedoDescriptions);
    um["getTimeOfRedoTransaction"]                = LUA_JUCE_C_CALL(&juce::UndoManager::getTimeOfRedoTransaction);
    um["isPerformingUndoRedo"]                    = LUA_JUCE_C_CALL(&juce::UndoManager::isPerformingUndoRedo);
}

} // namespace lua_juce
