namespace lua_juce {
auto juce_MouseEvent(sol::table& state) -> void
{
    auto event           = state.new_usertype<juce::MouseEvent>("MouseEvent");
    event["x"]           = &juce::MouseEvent::x;
    event["y"]           = &juce::MouseEvent::y;
    event["pressure"]    = &juce::MouseEvent::pressure;
    event["orientation"] = &juce::MouseEvent::orientation;
    event["rotation"]    = &juce::MouseEvent::rotation;
    event["tiltX"]       = &juce::MouseEvent::tiltX;
    event["tiltY"]       = &juce::MouseEvent::tiltY;
}
} // namespace lua_juce
