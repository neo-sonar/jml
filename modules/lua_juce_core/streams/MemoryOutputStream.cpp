namespace lua_juce {

auto juce_MemoryOutputStream(sol::table& state) -> void
{
    // clang-format off
    auto stream = state.new_usertype<juce::MemoryOutputStream>("MemoryOutputStream",
        sol::constructors<
            juce::MemoryOutputStream(size_t),
            juce::MemoryOutputStream(juce::MemoryBlock&, bool),
            juce::MemoryOutputStream(void*, size_t)
        >(),
        sol::base_classes, sol::bases<juce::OutputStream>()
    );
    // clang-format on

    stream["getData"]        = LUA_JUCE_C_CALL(&juce::MemoryOutputStream::getData);
    stream["getDataSize"]    = LUA_JUCE_C_CALL(&juce::MemoryOutputStream::getDataSize);
    stream["reset"]          = LUA_JUCE_C_CALL(&juce::MemoryOutputStream::reset);
    stream["preallocate"]    = LUA_JUCE_C_CALL(&juce::MemoryOutputStream::preallocate);
    stream["appendUTF8Char"] = LUA_JUCE_C_CALL(&juce::MemoryOutputStream::appendUTF8Char);
    stream["toUTF8"]         = LUA_JUCE_C_CALL(&juce::MemoryOutputStream::toUTF8);
    stream["toString"]       = LUA_JUCE_C_CALL(&juce::MemoryOutputStream::toString);
    stream["getMemoryBlock"] = LUA_JUCE_C_CALL(&juce::MemoryOutputStream::getMemoryBlock);
}

} // namespace lua_juce
