namespace lua_juce {
auto juce_Justification(sol::table& state) -> void
{
    // clang-format off
    state.new_enum("JustificationFlags",
        "left",                     juce::Justification::left,
        "right",                    juce::Justification::right,
        "horizontallyCentred",      juce::Justification::horizontallyCentred,
        "top",                      juce::Justification::top,
        "bottom",                   juce::Justification::bottom,
        "verticallyCentred",        juce::Justification::verticallyCentred,
        "horizontallyJustified",    juce::Justification::horizontallyJustified,
        "centred",                  juce::Justification::centred,
        "centredLeft",              juce::Justification::centredLeft,
        "centredRight",             juce::Justification::centredRight,
        "centredTop",               juce::Justification::centredTop,
        "centredBottom",            juce::Justification::centredBottom,
        "topLeft",                  juce::Justification::topLeft,
        "topRight",                 juce::Justification::topRight,
        "bottomLeft",               juce::Justification::bottomLeft,
        "bottomRight",              juce::Justification::bottomRight
    );

    auto justification = state.new_usertype<juce::Justification>("Justification",
        sol::constructors<juce::Justification(int)>()
    );
    // clang-format on
}
} // namespace lua_juce
