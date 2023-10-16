namespace lua_juce {
auto juce_ColourGradient(sol::table& state) -> void
{
    // TODO(tobi):
    // createLookupTable

    // clang-format off
    auto gradient = state.new_usertype<juce::ColourGradient>("ColourGradient",
        sol::constructors<
            juce::ColourGradient(),
            juce::ColourGradient(juce::Colour, float, float, juce::Colour, float, float, bool),
            juce::ColourGradient(juce::Colour, juce::Point<float>, juce::Colour, juce::Point<float>, bool)
        >()
    );
    gradient.set_function("vertical", sol::overload(
            static_cast<juce::ColourGradient (*)(juce::Colour, float, juce::Colour, float)>(&juce::ColourGradient::vertical),
            static_cast<juce::ColourGradient (*)(juce::Colour, juce::Colour, juce::Rectangle<int>)>(&juce::ColourGradient::template vertical<int>),
            static_cast<juce::ColourGradient (*)(juce::Colour, juce::Colour, juce::Rectangle<float>)>(&juce::ColourGradient::template vertical<float>),
            static_cast<juce::ColourGradient (*)(juce::Colour, juce::Colour, juce::Rectangle<double>)>(&juce::ColourGradient::template vertical<double>)
        )
    );
    gradient.set_function("horizontal", sol::overload(
            static_cast<juce::ColourGradient (*)(juce::Colour, float, juce::Colour, float)>(&juce::ColourGradient::horizontal),
            static_cast<juce::ColourGradient (*)(juce::Colour, juce::Colour, juce::Rectangle<int>)>(&juce::ColourGradient::template horizontal<int>),
            static_cast<juce::ColourGradient (*)(juce::Colour, juce::Colour, juce::Rectangle<float>)>(&juce::ColourGradient::template horizontal<float>),
            static_cast<juce::ColourGradient (*)(juce::Colour, juce::Colour, juce::Rectangle<double>)>(&juce::ColourGradient::template horizontal<double>)
        )
    );
    // clang-format on

    gradient["clearColours"]        = LUA_JUCE_C_CALL(&juce::ColourGradient::clearColours);
    gradient["addColour"]           = LUA_JUCE_C_CALL(&juce::ColourGradient::addColour);
    gradient["removeColour"]        = LUA_JUCE_C_CALL(&juce::ColourGradient::removeColour);
    gradient["multiplyOpacity"]     = LUA_JUCE_C_CALL(&juce::ColourGradient::multiplyOpacity);
    gradient["getNumColours"]       = LUA_JUCE_C_CALL(&juce::ColourGradient::getNumColours);
    gradient["getColourPosition"]   = LUA_JUCE_C_CALL(&juce::ColourGradient::getColourPosition);
    gradient["getColour"]           = LUA_JUCE_C_CALL(&juce::ColourGradient::getColour);
    gradient["setColour"]           = LUA_JUCE_C_CALL(&juce::ColourGradient::setColour);
    gradient["getColourAtPosition"] = LUA_JUCE_C_CALL(&juce::ColourGradient::getColourAtPosition);
    gradient["isOpaque"]            = LUA_JUCE_C_CALL(&juce::ColourGradient::isOpaque);
    gradient["isInvisible"]         = LUA_JUCE_C_CALL(&juce::ColourGradient::isInvisible);

    gradient["point1"]   = &juce::ColourGradient::point1;
    gradient["point2"]   = &juce::ColourGradient::point2;
    gradient["isRadial"] = &juce::ColourGradient::isRadial;
}
} // namespace lua_juce
