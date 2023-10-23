namespace lua_juce {
auto juce_MouseWheelDetails(sol::table& state) -> void
{
    auto wheel          = state.new_usertype<juce::MouseWheelDetails>("MouseWheelDetails");
    wheel["deltaX"]     = &juce::MouseWheelDetails::deltaX;
    wheel["deltaY"]     = &juce::MouseWheelDetails::deltaY;
    wheel["isReversed"] = &juce::MouseWheelDetails::isReversed;
    wheel["isSmooth"]   = &juce::MouseWheelDetails::isSmooth;
    wheel["isInertial"] = &juce::MouseWheelDetails::isInertial;
}
} // namespace lua_juce
