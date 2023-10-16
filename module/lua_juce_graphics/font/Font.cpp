namespace lua_juce {
auto juce_Font(sol::table& state) -> void
{

    // clang-format off

    state.new_enum("FontStyleFlags",
        "plain",        juce::Font::plain,
        "bold",         juce::Font::bold,
        "italic",       juce::Font::italic,
        "underlined",   juce::Font::underlined
    );

    auto font = state.new_usertype<juce::Font>("Font");
    font["new"] = sol::factories(
        [](float height) { return juce::Font { height }; },
        [](float height, int flags) { return juce::Font { height, flags }; }
    );

    // clang-format on

    font["setTypefaceName"]    = LUA_JUCE_C_CALL(&juce::Font::setTypefaceName);
    font["getTypefaceName"]    = LUA_JUCE_C_CALL(&juce::Font::getTypefaceName);
    font["getTypefaceStyle"]   = LUA_JUCE_C_CALL(&juce::Font::getTypefaceStyle);
    font["setTypefaceStyle"]   = LUA_JUCE_C_CALL(&juce::Font::setTypefaceStyle);
    font["withTypefaceStyle"]  = LUA_JUCE_C_CALL(&juce::Font::withTypefaceStyle);
    font["getAvailableStyles"] = LUA_JUCE_C_CALL(&juce::Font::getAvailableStyles);
}
} // namespace lua_juce
