namespace lua_juce {
auto juce_MemoryBlock(sol::table& state) -> void
{
    // clang-format off
    auto mb = state.new_usertype<juce::MemoryBlock>("MemoryBlock",
        sol::constructors<
            juce::MemoryBlock(),
            juce::MemoryBlock(size_t, bool),
            juce::MemoryBlock(void const*, size_t)
        >()
    );
    // clang-format on

    mb["matches"]            = LUA_JUCE_C_CALL(&juce::MemoryBlock::matches);
    mb["isEmpty"]            = LUA_JUCE_C_CALL(&juce::MemoryBlock::isEmpty);
    mb["getSize"]            = LUA_JUCE_C_CALL(&juce::MemoryBlock::getSize);
    mb["setSize"]            = LUA_JUCE_C_CALL(&juce::MemoryBlock::setSize);
    mb["ensureSize"]         = LUA_JUCE_C_CALL(&juce::MemoryBlock::ensureSize);
    mb["reset"]              = LUA_JUCE_C_CALL(&juce::MemoryBlock::reset);
    mb["fillWith"]           = LUA_JUCE_C_CALL(&juce::MemoryBlock::fillWith);
    mb["append"]             = LUA_JUCE_C_CALL(&juce::MemoryBlock::append);
    mb["replaceAll"]         = LUA_JUCE_C_CALL(&juce::MemoryBlock::replaceAll);
    mb["insert"]             = LUA_JUCE_C_CALL(&juce::MemoryBlock::insert);
    mb["removeSection"]      = LUA_JUCE_C_CALL(&juce::MemoryBlock::removeSection);
    mb["copyFrom"]           = LUA_JUCE_C_CALL(&juce::MemoryBlock::copyFrom);
    mb["copyTo"]             = LUA_JUCE_C_CALL(&juce::MemoryBlock::copyTo);
    mb["swapWith"]           = LUA_JUCE_C_CALL(&juce::MemoryBlock::swapWith);
    mb["toString"]           = LUA_JUCE_C_CALL(&juce::MemoryBlock::toString);
    mb["loadFromHexString"]  = LUA_JUCE_C_CALL(&juce::MemoryBlock::loadFromHexString);
    mb["setBitRange"]        = LUA_JUCE_C_CALL(&juce::MemoryBlock::setBitRange);
    mb["getBitRange"]        = LUA_JUCE_C_CALL(&juce::MemoryBlock::getBitRange);
    mb["toBase64Encoding"]   = LUA_JUCE_C_CALL(&juce::MemoryBlock::toBase64Encoding);
    mb["fromBase64Encoding"] = LUA_JUCE_C_CALL(&juce::MemoryBlock::fromBase64Encoding);
}
} // namespace lua_juce
