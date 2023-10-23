namespace lua_juce {

auto juce_FillType(sol::table& state) -> void
{
    auto fill = state.new_usertype<juce::FillType>(                          //
        "FillType",                                                          //
        sol::constructors<                                                   //
            juce::FillType(),                                                //
            juce::FillType(juce::Colour),                                    //
            juce::FillType(juce::ColourGradient const&),                     //
            juce::FillType(juce::Image const&, juce::AffineTransform const&) //
            >()                                                              //
    );

    // member functions
    fill["isColour"]      = LUA_JUCE_C_CALL(&juce::FillType::isColour);
    fill["isGradient"]    = LUA_JUCE_C_CALL(&juce::FillType::isGradient);
    fill["isTiledImage"]  = LUA_JUCE_C_CALL(&juce::FillType::isTiledImage);
    fill["setColour"]     = LUA_JUCE_C_CALL(&juce::FillType::setColour);
    fill["setGradient"]   = LUA_JUCE_C_CALL(&juce::FillType::setGradient);
    fill["setTiledImage"] = LUA_JUCE_C_CALL(&juce::FillType::setTiledImage);
    fill["setOpacity"]    = LUA_JUCE_C_CALL(&juce::FillType::setOpacity);
    fill["getOpacity"]    = LUA_JUCE_C_CALL(&juce::FillType::getOpacity);
    fill["isInvisible"]   = LUA_JUCE_C_CALL(&juce::FillType::isInvisible);
    fill["transformed"]   = LUA_JUCE_C_CALL(&juce::FillType::transformed);

    // member vars
    fill["colour"]    = &juce::FillType::colour;
    fill["image"]     = &juce::FillType::image;
    fill["transform"] = &juce::FillType::transform;

    // TODO(tobi): unique_ptr crashes on gcc 13.2. Other platforms not tested
    // fill["gradient"]  = &juce::FillType::gradient;
}

} // namespace lua_juce
