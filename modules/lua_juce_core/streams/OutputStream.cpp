namespace lua_juce {
auto juce_OutputStream(sol::table& state) -> void
{
    auto stream                    = state.new_usertype<juce::OutputStream>("OutputStream", sol::no_constructor);
    stream["flush"]                = LUA_JUCE_C_CALL(&juce::OutputStream::flush);
    stream["setPosition"]          = LUA_JUCE_C_CALL(&juce::OutputStream::setPosition);
    stream["getPosition"]          = LUA_JUCE_C_CALL(&juce::OutputStream::getPosition);
    stream["write"]                = LUA_JUCE_C_CALL(&juce::OutputStream::write);
    stream["writeByte"]            = LUA_JUCE_C_CALL(&juce::OutputStream::writeByte);
    stream["writeBool"]            = LUA_JUCE_C_CALL(&juce::OutputStream::writeBool);
    stream["writeShort"]           = LUA_JUCE_C_CALL(&juce::OutputStream::writeShort);
    stream["writeShortBigEndian"]  = LUA_JUCE_C_CALL(&juce::OutputStream::writeShortBigEndian);
    stream["writeInt"]             = LUA_JUCE_C_CALL(&juce::OutputStream::writeInt);
    stream["writeIntBigEndian"]    = LUA_JUCE_C_CALL(&juce::OutputStream::writeIntBigEndian);
    stream["writeInt64"]           = LUA_JUCE_C_CALL(&juce::OutputStream::writeInt64);
    stream["writeInt64BigEndian"]  = LUA_JUCE_C_CALL(&juce::OutputStream::writeInt64BigEndian);
    stream["writeFloat"]           = LUA_JUCE_C_CALL(&juce::OutputStream::writeFloat);
    stream["writeFloatBigEndian"]  = LUA_JUCE_C_CALL(&juce::OutputStream::writeFloatBigEndian);
    stream["writeDouble"]          = LUA_JUCE_C_CALL(&juce::OutputStream::writeDouble);
    stream["writeDoubleBigEndian"] = LUA_JUCE_C_CALL(&juce::OutputStream::writeDoubleBigEndian);
    stream["writeRepeatedByte"]    = LUA_JUCE_C_CALL(&juce::OutputStream::writeRepeatedByte);
    stream["writeCompressedInt"]   = LUA_JUCE_C_CALL(&juce::OutputStream::writeCompressedInt);
    stream["writeString"]          = LUA_JUCE_C_CALL(&juce::OutputStream::writeString);
    stream["writeText"]            = LUA_JUCE_C_CALL(&juce::OutputStream::writeText);
    stream["writeFromInputStream"] = LUA_JUCE_C_CALL(&juce::OutputStream::writeFromInputStream);
    stream["setNewLineString"]     = LUA_JUCE_C_CALL(&juce::OutputStream::setNewLineString);
    stream["getNewLineString"]     = LUA_JUCE_C_CALL(&juce::OutputStream::getNewLineString);
}
} // namespace lua_juce
