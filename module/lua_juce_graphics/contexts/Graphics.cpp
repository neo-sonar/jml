namespace lua_juce {

namespace {

auto drawFittedText2(juce::Graphics const* g, juce::String const& s, int x, int y, int w, int h, juce::Justification j, int m) -> void { g->drawFittedText(s, x, y, w, h, j, m); }
auto drawFittedText4(juce::Graphics const* g, juce::String const& s, juce::Rectangle<int> area, juce::Justification j, int m) -> void { g->drawFittedText(s, area, j, m); }

auto drawText1(juce::Graphics const* g, juce::String const& s, int x, int y, int w, int h, juce::Justification j) -> void { g->drawText(s, x, y, w, h, j); }
auto drawText3(juce::Graphics const* g, juce::String const& s, juce::Rectangle<int> area, juce::Justification j) -> void { g->drawText(s, area, j); }
auto drawText5(juce::Graphics const* g, juce::String const& s, juce::Rectangle<float> area, juce::Justification j) -> void { g->drawText(s, area, j); }

auto fillRoundedRectangle1(juce::Graphics* g, juce::Rectangle<int> r, double ra) -> void { g->fillRoundedRectangle(r.toFloat(), static_cast<float>(ra)); }
auto fillRoundedRectangle2(juce::Graphics* g, juce::Rectangle<float> r, double ra) -> void { g->fillRoundedRectangle(r, static_cast<float>(ra)); }
auto fillRoundedRectangle3(juce::Graphics* g, juce::Rectangle<double> r, double ra) -> void { g->fillRoundedRectangle(r.toFloat(), static_cast<float>(ra)); }

} // namespace
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

    g["drawFittedText"] = sol::c_call<                                                                                                                 //
        LUA_JUCE_WRAP(static_cast<void (Graphics::*)(String const&, int, int, int, int, Justification, int, float) const>(&Graphics::drawFittedText)), //
        LUA_JUCE_WRAP(drawFittedText2),                                                                                                                //
        LUA_JUCE_WRAP(static_cast<void (Graphics::*)(String const&, Rectangle<int>, Justification, int, float) const>(&Graphics::drawFittedText)),     //
        LUA_JUCE_WRAP(drawFittedText4)                                                                                                                 //
        >;

    g["drawText"] = sol::c_call<                                                                                                           //
        LUA_JUCE_WRAP(static_cast<void (Graphics::*)(String const&, int, int, int, int, Justification, bool) const>(&Graphics::drawText)), //
        LUA_JUCE_WRAP(drawText1),                                                                                                          //
        LUA_JUCE_WRAP(static_cast<void (Graphics::*)(String const&, Rectangle<int>, Justification, bool) const>(&Graphics::drawText)),     //
        LUA_JUCE_WRAP(drawText3),                                                                                                          //
        LUA_JUCE_WRAP(static_cast<void (Graphics::*)(String const&, Rectangle<float>, Justification, bool) const>(&Graphics::drawText)),   //
        LUA_JUCE_WRAP(drawText5)                                                                                                           //
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
        LUA_JUCE_WRAP(fillRoundedRectangle1),                                                                                     //
        LUA_JUCE_WRAP(fillRoundedRectangle2),                                                                                     //
        LUA_JUCE_WRAP(fillRoundedRectangle3)                                                                                      //
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
