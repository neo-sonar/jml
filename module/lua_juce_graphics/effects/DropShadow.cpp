namespace lua_juce {

auto juce_DropShadow(sol::table& state) -> void
{
    auto fill = state.new_usertype<juce::DropShadow>(             //
        "DropShadow",                                             //
        sol::constructors<                                        //
            juce::DropShadow(),                                   //
            juce::DropShadow(juce::Colour, int, juce::Point<int>) //
            >()                                                   //
    );

    // member functions
    fill["drawForImage"]     = LUA_JUCE_C_CALL(&juce::DropShadow::drawForImage);
    fill["drawForPath"]      = LUA_JUCE_C_CALL(&juce::DropShadow::drawForPath);
    fill["drawForRectangle"] = LUA_JUCE_C_CALL(&juce::DropShadow::drawForRectangle);

    // member vars
    fill["colour"] = &juce::DropShadow::colour;
    fill["radius"] = &juce::DropShadow::radius;
    fill["offset"] = &juce::DropShadow::offset;
}

} // namespace lua_juce
