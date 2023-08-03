namespace lua_juce {
auto juce_Justification(sol::table& state) -> void
{
    using Type = juce::Justification;

    // clang-format off
    state.new_enum("JustificationFlags",
        "left", Type::left,
        "right", Type::right,
        "horizontallyCentred", Type::horizontallyCentred,
        "top", Type::top,
        "bottom", Type::bottom,
        "verticallyCentred", Type::verticallyCentred,
        "horizontallyJustified", Type::horizontallyJustified,
        "centred", Type::centred,
        "centredLeft", Type::centredLeft,
        "centredRight", Type::centredRight,
        "centredTop", Type::centredTop,
        "centredBottom", Type::centredBottom,
        "topLeft", Type::topLeft,
        "topRight", Type::topRight,
        "bottomLeft", Type::bottomLeft,
        "bottomRight", Type::bottomRight
    );

    auto justification = state.new_usertype<Type>("Justification",
        sol::constructors<Type(int)>()
    );
    // clang-format on
}
} // namespace lua_juce
