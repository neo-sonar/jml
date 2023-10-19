namespace lua_juce {
template<typename T>
auto juce_RangeImpl(sol::table& state, char const* name) -> void
{
    // clang-format off
    auto range = state.new_usertype<juce::Range<T>>(name,
        sol::constructors<juce::Range<T>(), juce::Range<T>(T, T)>(),
        "start",
        sol::property(&juce::Range<T>::getStart, &juce::Range<T>::setStart),
        "end",
        sol::property(&juce::Range<T>::getEnd, &juce::Range<T>::setEnd)
    );
    // clang-format on
}

auto juce_Range(sol::table& state) -> void
{
    juce_RangeImpl<int>(state, "Range_int");
    juce_RangeImpl<juce::int64>(state, "Range_int64");

    juce_RangeImpl<float>(state, "Range_float");
    juce_RangeImpl<double>(state, "Range_double");
}
} // namespace lua_juce
