namespace lua_juce {

auto juce_UndoableAction(sol::table& state) -> void
{
    auto action                     = state.new_usertype<juce::UndoableAction>("InternalUndoableAction", sol::no_constructor);
    action["perform"]               = LUA_JUCE_C_CALL(&juce::UndoableAction::perform);
    action["undo"]                  = LUA_JUCE_C_CALL(&juce::UndoableAction::undo);
    action["getSizeInUnits"]        = LUA_JUCE_C_CALL(&juce::UndoableAction::getSizeInUnits);
    action["createCoalescedAction"] = LUA_JUCE_C_CALL(&juce::UndoableAction::createCoalescedAction);
}

} // namespace lua_juce
