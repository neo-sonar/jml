namespace lua_juce {

template<typename T>
auto juce_RangeImpl(sol::table& state, char const* name) -> void
{
    auto range = state.new_usertype<juce::Range<T>>(name, sol::constructors<juce::Range<T>(), juce::Range<T>(T, T)>());

    range["getStart"] = LUA_JUCE_C_CALL(&juce::Range<T>::getStart);
    range["getEnd"]   = LUA_JUCE_C_CALL(&juce::Range<T>::getEnd);
}

auto juce_Range(sol::table& state) -> void
{
    juce_RangeImpl<int>(state, "Range_int");
    juce_RangeImpl<juce::int64>(state, "Range_int64");

    juce_RangeImpl<float>(state, "Range_float");
    juce_RangeImpl<double>(state, "Range_double");
}
} // namespace lua_juce
