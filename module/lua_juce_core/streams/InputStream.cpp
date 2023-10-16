namespace lua_juce {
auto juce_InputStream(sol::table& state) -> void
{
    auto stream                        = state.new_usertype<juce::InputStream>("InputStream", sol::no_constructor);
    stream["getTotalLength"]           = LUA_JUCE_C_CALL(&juce::InputStream::getTotalLength);
    stream["getNumBytesRemaining"]     = LUA_JUCE_C_CALL(&juce::InputStream::getNumBytesRemaining);
    stream["isExhausted"]              = LUA_JUCE_C_CALL(&juce::InputStream::isExhausted);
    stream["readByte"]                 = LUA_JUCE_C_CALL(&juce::InputStream::readByte);
    stream["readBool"]                 = LUA_JUCE_C_CALL(&juce::InputStream::readBool);
    stream["readShort"]                = LUA_JUCE_C_CALL(&juce::InputStream::readShort);
    stream["readShortBigEndian"]       = LUA_JUCE_C_CALL(&juce::InputStream::readShortBigEndian);
    stream["readInt"]                  = LUA_JUCE_C_CALL(&juce::InputStream::readInt);
    stream["readIntBigEndian"]         = LUA_JUCE_C_CALL(&juce::InputStream::readIntBigEndian);
    stream["readInt64"]                = LUA_JUCE_C_CALL(&juce::InputStream::readInt64);
    stream["readInt64BigEndian"]       = LUA_JUCE_C_CALL(&juce::InputStream::readInt64BigEndian);
    stream["readFloat"]                = LUA_JUCE_C_CALL(&juce::InputStream::readFloat);
    stream["readFloatBigEndian"]       = LUA_JUCE_C_CALL(&juce::InputStream::readFloatBigEndian);
    stream["readDouble"]               = LUA_JUCE_C_CALL(&juce::InputStream::readDouble);
    stream["readDoubleBigEndian"]      = LUA_JUCE_C_CALL(&juce::InputStream::readDoubleBigEndian);
    stream["readCompressedInt"]        = LUA_JUCE_C_CALL(&juce::InputStream::readCompressedInt);
    stream["readNextLine"]             = LUA_JUCE_C_CALL(&juce::InputStream::readNextLine);
    stream["readString"]               = LUA_JUCE_C_CALL(&juce::InputStream::readString);
    stream["readEntireStreamAsString"] = LUA_JUCE_C_CALL(&juce::InputStream::readEntireStreamAsString);
    stream["readIntoMemoryBlock"]      = LUA_JUCE_C_CALL(&juce::InputStream::readIntoMemoryBlock);
    stream["getPosition"]              = LUA_JUCE_C_CALL(&juce::InputStream::getPosition);
    stream["setPosition"]              = LUA_JUCE_C_CALL(&juce::InputStream::setPosition);
    stream["skipNextBytes"]            = LUA_JUCE_C_CALL(&juce::InputStream::skipNextBytes);
}
} // namespace lua_juce
