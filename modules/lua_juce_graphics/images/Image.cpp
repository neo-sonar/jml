namespace lua_juce {
auto juce_Image(sol::table& state) -> void
{
    // clang-format off
    state.new_enum("ImagePixelFormat",
        "UnknownFormat",    juce::Image::PixelFormat::UnknownFormat,
        "RGB",              juce::Image::PixelFormat::RGB,
        "ARGB",             juce::Image::PixelFormat::ARGB,
        "SingleChannel",    juce::Image::PixelFormat::SingleChannel
    );

    auto img = state.new_usertype<juce::Image>("Image",
        sol::constructors<
            juce::Image(),
            juce::Image(juce::Image::PixelFormat, int, int, bool),
            juce::Image(juce::Image::PixelFormat, int, int, bool, juce::ImageType const&),
            juce::Image(juce::ReferenceCountedObjectPtr<juce::ImagePixelData>)
        >()
    );
    // clang-format on

    img["isValid"]               = LUA_JUCE_C_CALL(&juce::Image::isValid);
    img["isNull"]                = LUA_JUCE_C_CALL(&juce::Image::isNull);
    img["getWidth"]              = LUA_JUCE_C_CALL(&juce::Image::getWidth);
    img["getHeight"]             = LUA_JUCE_C_CALL(&juce::Image::getHeight);
    img["getBounds"]             = LUA_JUCE_C_CALL(&juce::Image::getBounds);
    img["getFormat"]             = LUA_JUCE_C_CALL(&juce::Image::getFormat);
    img["isARGB"]                = LUA_JUCE_C_CALL(&juce::Image::isARGB);
    img["isRGB"]                 = LUA_JUCE_C_CALL(&juce::Image::isRGB);
    img["isSingleChannel"]       = LUA_JUCE_C_CALL(&juce::Image::isSingleChannel);
    img["hasAlphaChannel"]       = LUA_JUCE_C_CALL(&juce::Image::hasAlphaChannel);
    img["clear"]                 = LUA_JUCE_C_CALL(&juce::Image::clear);
    img["rescaled"]              = LUA_JUCE_C_CALL(&juce::Image::rescaled);
    img["createCopy"]            = LUA_JUCE_C_CALL(&juce::Image::createCopy);
    img["convertedToFormat"]     = LUA_JUCE_C_CALL(&juce::Image::convertedToFormat);
    img["duplicateIfShared"]     = LUA_JUCE_C_CALL(&juce::Image::duplicateIfShared);
    img["getClippedImage"]       = LUA_JUCE_C_CALL(&juce::Image::getClippedImage);
    img["getPixelAt"]            = LUA_JUCE_C_CALL(&juce::Image::getPixelAt);
    img["setPixelAt"]            = LUA_JUCE_C_CALL(&juce::Image::setPixelAt);
    img["multiplyAlphaAt"]       = LUA_JUCE_C_CALL(&juce::Image::multiplyAlphaAt);
    img["multiplyAllAlphas"]     = LUA_JUCE_C_CALL(&juce::Image::multiplyAllAlphas);
    img["desaturate"]            = LUA_JUCE_C_CALL(&juce::Image::desaturate);
    img["moveImageSection"]      = LUA_JUCE_C_CALL(&juce::Image::moveImageSection);
    img["createSolidAreaMask"]   = LUA_JUCE_C_CALL(&juce::Image::createSolidAreaMask);
    img["getProperties"]         = LUA_JUCE_C_CALL(&juce::Image::getProperties);
    img["createLowLevelContext"] = LUA_JUCE_C_CALL(&juce::Image::createLowLevelContext);
    img["getReferenceCount"]     = LUA_JUCE_C_CALL(&juce::Image::getReferenceCount);
    img["getPixelData"]          = LUA_JUCE_C_CALL(&juce::Image::getPixelData);
}
} // namespace lua_juce
