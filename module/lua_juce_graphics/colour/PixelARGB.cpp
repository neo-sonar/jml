namespace lua_juce {

auto juce_PixelARGB(sol::table& state) -> void
{
    using juce::PixelARGB;
    using juce::uint8;

    auto px = state.new_usertype<PixelARGB>("PixelARGB", sol::constructors<PixelARGB(), PixelARGB(uint8, uint8, uint8, uint8)>());

    px["getNativeARGB"]        = LUA_JUCE_C_CALL(&PixelARGB::getNativeARGB);
    px["getInARGBMaskOrder"]   = LUA_JUCE_C_CALL(&PixelARGB::getInARGBMaskOrder);
    px["getInARGBMemoryOrder"] = LUA_JUCE_C_CALL(&PixelARGB::getInARGBMemoryOrder);
    px["getEvenBytes"]         = LUA_JUCE_C_CALL(&PixelARGB::getEvenBytes);
    px["getOddBytes"]          = LUA_JUCE_C_CALL(&PixelARGB::getOddBytes);
    px["getAlpha"]             = LUA_JUCE_C_CALL(&PixelARGB::getAlpha);
    px["getRed"]               = LUA_JUCE_C_CALL(&PixelARGB::getRed);
    px["getGreen"]             = LUA_JUCE_C_CALL(&PixelARGB::getGreen);
    px["getBlue"]              = LUA_JUCE_C_CALL(&PixelARGB::getBlue);
    px["setARGB"]              = LUA_JUCE_C_CALL(&PixelARGB::setARGB);
    px["setAlpha"]             = LUA_JUCE_C_CALL(&PixelARGB::setAlpha);
    px["premultiply"]          = LUA_JUCE_C_CALL(&PixelARGB::premultiply);
    px["unpremultiply"]        = LUA_JUCE_C_CALL(&PixelARGB::unpremultiply);
    px["desaturate"]           = LUA_JUCE_C_CALL(&PixelARGB::desaturate);

    // px["multiplyAlpha"] = LUA_JUCE_C_CALL(&PixelARGB::multiplyAlpha);
    // px["multiplyAlpha"] = LUA_JUCE_C_CALL(&PixelARGB::multiplyAlpha);
    // px["set"]           = LUA_JUCE_C_CALL(&PixelARGB::set);
    // px["blend"]         = LUA_JUCE_C_CALL(&PixelARGB::blend);
    // px["tween"]         = LUA_JUCE_C_CALL(&PixelARGB::tween);
}

} // namespace lua_juce
