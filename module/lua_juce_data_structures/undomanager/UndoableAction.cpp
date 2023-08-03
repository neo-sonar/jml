namespace lua_juce {

auto juce_UndoableAction(sol::table& state) -> void
{
    auto action                     = state.new_usertype<juce::UndoableAction>("InternalUndoableAction", sol::no_constructor);
    action["perform"]               = &juce::UndoableAction::perform;
    action["undo"]                  = &juce::UndoableAction::undo;
    action["getSizeInUnits"]        = &juce::UndoableAction::getSizeInUnits;
    action["createCoalescedAction"] = &juce::UndoableAction::createCoalescedAction;
}

} // namespace lua_juce
