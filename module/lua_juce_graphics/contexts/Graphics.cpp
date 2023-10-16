namespace lua_juce {
auto juce_Graphics(sol::table& state) -> void
{
    using juce::Graphics;
    using juce::Justification;
    using juce::Rectangle;
    using juce::String;

    auto g = state.new_usertype<Graphics>("Graphics");

    g["setColour"]                 = LUA_JUCE_C_CALL(&Graphics::setColour);
    g["setOpacity"]                = LUA_JUCE_C_CALL(&Graphics::setOpacity);
    g["setTiledImageFill"]         = LUA_JUCE_C_CALL(&Graphics::setTiledImageFill);
    g["setFillType"]               = LUA_JUCE_C_CALL(&Graphics::setFillType);
    g["getCurrentFont"]            = LUA_JUCE_C_CALL(&Graphics::getCurrentFont);
    g["drawSingleLineText"]        = LUA_JUCE_C_CALL(&Graphics::drawSingleLineText);
    g["drawMultiLineText"]         = LUA_JUCE_C_CALL(&Graphics::drawMultiLineText);
    g["getCurrentFont"]            = LUA_JUCE_C_CALL(&Graphics::getCurrentFont);
    g["fillCheckerBoard"]          = LUA_JUCE_C_CALL(&Graphics::fillCheckerBoard);
    g["drawDashedLine"]            = LUA_JUCE_C_CALL(&Graphics::drawDashedLine);
    g["drawVerticalLine"]          = LUA_JUCE_C_CALL(&Graphics::drawVerticalLine);
    g["drawHorizontalLine"]        = LUA_JUCE_C_CALL(&Graphics::drawHorizontalLine);
    g["strokePath"]                = LUA_JUCE_C_CALL(&Graphics::strokePath);
    g["drawArrow"]                 = LUA_JUCE_C_CALL(&Graphics::drawArrow);
    g["setImageResamplingQuality"] = LUA_JUCE_C_CALL(&Graphics::setImageResamplingQuality);
    g["drawImageAt"]               = LUA_JUCE_C_CALL(&Graphics::drawImageAt);
    g["drawImageTransformed"]      = LUA_JUCE_C_CALL(&Graphics::drawImageTransformed);
    g["drawImageWithin"]           = LUA_JUCE_C_CALL(&Graphics::drawImageWithin);
    g["getClipBounds"]             = LUA_JUCE_C_CALL(&Graphics::getClipBounds);
    g["clipRegionIntersects"]      = LUA_JUCE_C_CALL(&Graphics::clipRegionIntersects);
    g["excludeClipRegion"]         = LUA_JUCE_C_CALL(&Graphics::excludeClipRegion);
    g["isClipEmpty"]               = LUA_JUCE_C_CALL(&Graphics::isClipEmpty);
    g["saveState"]                 = LUA_JUCE_C_CALL(&Graphics::saveState);
    g["restoreState"]              = LUA_JUCE_C_CALL(&Graphics::restoreState);
    g["beginTransparencyLayer"]    = LUA_JUCE_C_CALL(&Graphics::beginTransparencyLayer);
    g["endTransparencyLayer"]      = LUA_JUCE_C_CALL(&Graphics::endTransparencyLayer);
    g["addTransform"]              = LUA_JUCE_C_CALL(&Graphics::addTransform);
    g["resetToDefaultState"]       = LUA_JUCE_C_CALL(&Graphics::resetToDefaultState);
    g["isVectorDevice"]            = LUA_JUCE_C_CALL(&Graphics::isVectorDevice);
    g["getInternalContext"]        = LUA_JUCE_C_CALL(&Graphics::getInternalContext);
    g["setGradientFill"]           = LUA_JUCE_C_CALL(static_cast<void (Graphics::*)(juce::ColourGradient const&)>(&Graphics::setGradientFill));

    g["setFont"] = sol::c_call<                                                               //
        LUA_JUCE_WRAP(static_cast<void (Graphics::*)(float)>(&Graphics::setFont)),            //
        LUA_JUCE_WRAP(static_cast<void (Graphics::*)(juce::Font const&)>(&Graphics::setFont)) //
        >;

    g["drawFittedText"] = sol::c_call<                                                                                                                              //
        LUA_JUCE_WRAP(static_cast<void (Graphics::*)(String const&, int, int, int, int, Justification, int, float) const>(&Graphics::drawFittedText)),              //
        LUA_JUCE_WRAP(+[](Graphics const* ctx, String const& s, int x, int y, int w, int h, Justification j, int m) { ctx->drawFittedText(s, x, y, w, h, j, m); }), //
        LUA_JUCE_WRAP(static_cast<void (Graphics::*)(String const&, Rectangle<int>, Justification, int, float) const>(&Graphics::drawFittedText)),                  //
        LUA_JUCE_WRAP(+[](Graphics const* ctx, String const& s, Rectangle<int> area, Justification j, int m) { ctx->drawFittedText(s, area, j, m); })               //
        >;

    g["drawText"] = sol::c_call<                                                                                                                    //
        LUA_JUCE_WRAP(static_cast<void (Graphics::*)(String const&, int, int, int, int, Justification, bool) const>(&Graphics::drawText)),          //
        LUA_JUCE_WRAP(+[](Graphics const* ctx, String const& s, int x, int y, int w, int h, Justification j) { ctx->drawText(s, x, y, w, h, j); }), //
        LUA_JUCE_WRAP(static_cast<void (Graphics::*)(String const&, Rectangle<int>, Justification, bool) const>(&Graphics::drawText)),              //
        LUA_JUCE_WRAP(+[](Graphics const* ctx, String const& s, Rectangle<int> area, Justification j) { ctx->drawText(s, area, j); }),              //
        LUA_JUCE_WRAP(static_cast<void (Graphics::*)(String const&, Rectangle<float>, Justification, bool) const>(&Graphics::drawText)),            //
        LUA_JUCE_WRAP(+[](Graphics const* ctx, String const& s, Rectangle<float> area, Justification j) { ctx->drawText(s, area, j); })             //
        >;

    g["fillAll"] = sol::c_call<                                                                //
        LUA_JUCE_WRAP(static_cast<void (Graphics::*)() const>(&Graphics::fillAll)),            //
        LUA_JUCE_WRAP(static_cast<void (Graphics::*)(juce::Colour) const>(&Graphics::fillAll)) //
        >;

    g["fillEllipse"] = sol::c_call<                                                                               //
        LUA_JUCE_WRAP(static_cast<void (Graphics::*)(float, float, float, float) const>(&Graphics::fillEllipse)), //
        LUA_JUCE_WRAP(static_cast<void (Graphics::*)(Rectangle<float>) const>(&Graphics::fillEllipse))            //
        >;

    g["fillRect"] = sol::c_call<                                                                              //
        LUA_JUCE_WRAP(static_cast<void (Graphics::*)(Rectangle<int>) const>(&Graphics::fillRect)),            //
        LUA_JUCE_WRAP(static_cast<void (Graphics::*)(Rectangle<float>) const>(&Graphics::fillRect)),          //
        LUA_JUCE_WRAP(static_cast<void (Graphics::*)(int, int, int, int) const>(&Graphics::fillRect)),        //
        LUA_JUCE_WRAP(static_cast<void (Graphics::*)(float, float, float, float) const>(&Graphics::fillRect)) //
        >;

    g["fillRoundedRectangle"] = sol::c_call<                                                                                      //
        LUA_JUCE_WRAP(static_cast<void (Graphics::*)(float, float, float, float, float) const>(&Graphics::fillRoundedRectangle)), //
        LUA_JUCE_WRAP(+[](Graphics* ctx, Rectangle<int> r, double ra) { ctx->fillRoundedRectangle(r.toFloat(), float(ra)); }),    //
        LUA_JUCE_WRAP(+[](Graphics* ctx, Rectangle<float> r, double ra) { ctx->fillRoundedRectangle(r, float(ra)); }),            //
        LUA_JUCE_WRAP(+[](Graphics* ctx, Rectangle<double> r, double ra) { ctx->fillRoundedRectangle(r.toFloat(), float(ra)); })  //
        >;

    g["fillRectList"] = sol::c_call<                                                                                      //
        LUA_JUCE_WRAP(static_cast<void (Graphics::*)(juce::RectangleList<float> const&) const>(&Graphics::fillRectList)), //
        LUA_JUCE_WRAP(static_cast<void (Graphics::*)(juce::RectangleList<int> const&) const>(&Graphics::fillRectList))    //
        >;

    g["drawRect"] = sol::c_call<                                                                                     //
        LUA_JUCE_WRAP(static_cast<void (Graphics::*)(Rectangle<int>, int) const>(&Graphics::drawRect)),              //
        LUA_JUCE_WRAP(static_cast<void (Graphics::*)(Rectangle<float>, float) const>(&Graphics::drawRect)),          //
        LUA_JUCE_WRAP(static_cast<void (Graphics::*)(int, int, int, int, int) const>(&Graphics::drawRect)),          //
        LUA_JUCE_WRAP(static_cast<void (Graphics::*)(float, float, float, float, float) const>(&Graphics::drawRect)) //
        >;

    g["drawLine"] = sol::c_call<                                                                                      //
        LUA_JUCE_WRAP(static_cast<void (Graphics::*)(float, float, float, float) const>(&Graphics::drawLine)),        //
        LUA_JUCE_WRAP(static_cast<void (Graphics::*)(float, float, float, float, float) const>(&Graphics::drawLine)), //
        LUA_JUCE_WRAP(static_cast<void (Graphics::*)(juce::Line<float>) const>(&Graphics::drawLine)),                 //
        LUA_JUCE_WRAP(static_cast<void (Graphics::*)(juce::Line<float>, float) const>(&Graphics::drawLine))           //
        >;

    g["drawRoundedRectangle"] = sol::c_call<                                                                                             //
        LUA_JUCE_WRAP(static_cast<void (Graphics::*)(float, float, float, float, float, float) const>(&Graphics::drawRoundedRectangle)), //
        LUA_JUCE_WRAP(static_cast<void (Graphics::*)(Rectangle<float>, float, float) const>(&Graphics::drawRoundedRectangle))            //
        >;

    g["drawEllipse"] = sol::c_call<                                                                                      //
        LUA_JUCE_WRAP(static_cast<void (Graphics::*)(float, float, float, float, float) const>(&Graphics::drawEllipse)), //
        LUA_JUCE_WRAP(static_cast<void (Graphics::*)(Rectangle<float>, float) const>(&Graphics::drawEllipse))            //
        >;

    // TODO(tobi):
    // fillPath
    // drawImage
    // reduceClipRegion
    // setOrigin
}

} // namespace lua_juce
