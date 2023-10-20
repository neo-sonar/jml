namespace lua_juce {
auto juce_Colour(sol::table& state) -> void
{
    using juce::Colour;
    using juce::uint8;

    auto colour = state.new_usertype<Colour>("Colour", sol::constructors<Colour(), Colour(uint8, uint8, uint8, uint8)>());

    // static
    colour["fromRGB"]       = LUA_JUCE_C_CALL(&Colour::fromRGB);
    colour["fromRGBA"]      = LUA_JUCE_C_CALL(&Colour::fromRGBA);
    colour["fromFloatRGBA"] = LUA_JUCE_C_CALL(&Colour::fromFloatRGBA);
    colour["fromHSV"]       = LUA_JUCE_C_CALL(&Colour::fromHSV);
    colour["fromHSL"]       = LUA_JUCE_C_CALL(&Colour::fromHSL);
    colour["greyLevel"]     = LUA_JUCE_C_CALL(&Colour::greyLevel);
    colour["fromString"]    = LUA_JUCE_C_CALL(&Colour::fromString);

    // member
    colour["getRed"]                       = LUA_JUCE_C_CALL(&Colour::getRed);
    colour["getGreen"]                     = LUA_JUCE_C_CALL(&Colour::getGreen);
    colour["getBlue"]                      = LUA_JUCE_C_CALL(&Colour::getBlue);
    colour["getFloatRed"]                  = LUA_JUCE_C_CALL(&Colour::getFloatRed);
    colour["getFloatGreen"]                = LUA_JUCE_C_CALL(&Colour::getFloatGreen);
    colour["getFloatBlue"]                 = LUA_JUCE_C_CALL(&Colour::getFloatBlue);
    colour["getPixelARGB"]                 = LUA_JUCE_C_CALL(&Colour::getPixelARGB);
    colour["getNonPremultipliedPixelARGB"] = LUA_JUCE_C_CALL(&Colour::getNonPremultipliedPixelARGB);
    colour["getARGB"]                      = LUA_JUCE_C_CALL(&Colour::getARGB);
    colour["getAlpha"]                     = LUA_JUCE_C_CALL(&Colour::getAlpha);
    colour["getFloatAlpha"]                = LUA_JUCE_C_CALL(&Colour::getFloatAlpha);
    colour["isOpaque"]                     = LUA_JUCE_C_CALL(&Colour::isOpaque);
    colour["isTransparent"]                = LUA_JUCE_C_CALL(&Colour::isTransparent);
    colour["withMultipliedAlpha"]          = LUA_JUCE_C_CALL(&Colour::withMultipliedAlpha);
    colour["overlaidWith"]                 = LUA_JUCE_C_CALL(&Colour::overlaidWith);
    colour["interpolatedWith"]             = LUA_JUCE_C_CALL(&Colour::interpolatedWith);
    colour["getHue"]                       = LUA_JUCE_C_CALL(&Colour::getHue);
    colour["getSaturation"]                = LUA_JUCE_C_CALL(&Colour::getSaturation);
    colour["getSaturationHSL"]             = LUA_JUCE_C_CALL(&Colour::getSaturationHSL);
    colour["getBrightness"]                = LUA_JUCE_C_CALL(&Colour::getBrightness);
    colour["getLightness"]                 = LUA_JUCE_C_CALL(&Colour::getLightness);
    colour["getPerceivedBrightness"]       = LUA_JUCE_C_CALL(&Colour::getPerceivedBrightness);
    colour["withHue"]                      = LUA_JUCE_C_CALL(&Colour::withHue);
    colour["withSaturation"]               = LUA_JUCE_C_CALL(&Colour::withSaturation);
    colour["withSaturationHSL"]            = LUA_JUCE_C_CALL(&Colour::withSaturationHSL);
    colour["withBrightness"]               = LUA_JUCE_C_CALL(&Colour::withBrightness);
    colour["withLightness"]                = LUA_JUCE_C_CALL(&Colour::withLightness);
    colour["withRotatedHue"]               = LUA_JUCE_C_CALL(&Colour::withRotatedHue);
    colour["withMultipliedSaturation"]     = LUA_JUCE_C_CALL(&Colour::withMultipliedSaturation);
    colour["withMultipliedSaturationHSL"]  = LUA_JUCE_C_CALL(&Colour::withMultipliedSaturationHSL);
    colour["withMultipliedBrightness"]     = LUA_JUCE_C_CALL(&Colour::withMultipliedBrightness);
    colour["withMultipliedLightness"]      = LUA_JUCE_C_CALL(&Colour::withMultipliedLightness);
    colour["brighter"]                     = LUA_JUCE_C_CALL(&Colour::brighter);
    colour["darker"]                       = LUA_JUCE_C_CALL(&Colour::darker);
    colour["toString"]                     = LUA_JUCE_C_CALL(&Colour::toString);
    colour["toDisplayString"]              = LUA_JUCE_C_CALL(&Colour::toDisplayString);

    // colour["withAlpha"]   = LUA_JUCE_C_CALL(&Colour::withAlpha);
    // colour["withAlpha"]   = LUA_JUCE_C_CALL(&Colour::withAlpha);
    // colour["contrasting"] = LUA_JUCE_C_CALL(&Colour::contrasting); // static
    // colour["contrasting"] = LUA_JUCE_C_CALL(&Colour::contrasting); // member
    // colour["contrasting"] = LUA_JUCE_C_CALL(&Colour::contrasting); // member
    // colour["getHSB"]      = LUA_JUCE_C_CALL(&Colour::getHSB);
    // colour["getHSL"]      = LUA_JUCE_C_CALL(&Colour::getHSL);
}

} // namespace lua_juce
