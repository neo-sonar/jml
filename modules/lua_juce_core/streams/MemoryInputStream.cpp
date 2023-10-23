namespace lua_juce {

auto juce_MemoryInputStream(sol::table& state) -> void
{
    // clang-format off
    auto stream = state.new_usertype<juce::MemoryInputStream>("MemoryInputStream",
        sol::constructors<
            juce::MemoryInputStream(void const*, size_t, bool),
            juce::MemoryInputStream(juce::MemoryBlock const&, bool)
        >(),
        sol::base_classes, sol::bases<juce::InputStream>()
    );
    // clang-format on

    stream["getData"]     = LUA_JUCE_C_CALL(&juce::MemoryInputStream::getData);
    stream["getDataSize"] = LUA_JUCE_C_CALL(&juce::MemoryInputStream::getDataSize);
}

} // namespace lua_juce
