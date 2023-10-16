namespace lua_juce {
auto juce_Graphics(sol::table& state) -> void
{
    // TODO(tobi):
    // fillPath
    // drawImage
    // reduceClipRegion
    // setOrigin

    auto g = state.new_usertype<juce::Graphics>("Graphics");

    g["setColour"]                 = LUA_JUCE_C_CALL(&juce::Graphics::setColour);
    g["setOpacity"]                = LUA_JUCE_C_CALL(&juce::Graphics::setOpacity);
    g["setTiledImageFill"]         = LUA_JUCE_C_CALL(&juce::Graphics::setTiledImageFill);
    g["setFillType"]               = LUA_JUCE_C_CALL(&juce::Graphics::setFillType);
    g["getCurrentFont"]            = LUA_JUCE_C_CALL(&juce::Graphics::getCurrentFont);
    g["drawSingleLineText"]        = LUA_JUCE_C_CALL(&juce::Graphics::drawSingleLineText);
    g["drawMultiLineText"]         = LUA_JUCE_C_CALL(&juce::Graphics::drawMultiLineText);
    g["getCurrentFont"]            = LUA_JUCE_C_CALL(&juce::Graphics::getCurrentFont);
    g["fillCheckerBoard"]          = LUA_JUCE_C_CALL(&juce::Graphics::fillCheckerBoard);
    g["drawDashedLine"]            = LUA_JUCE_C_CALL(&juce::Graphics::drawDashedLine);
    g["drawVerticalLine"]          = LUA_JUCE_C_CALL(&juce::Graphics::drawVerticalLine);
    g["drawHorizontalLine"]        = LUA_JUCE_C_CALL(&juce::Graphics::drawHorizontalLine);
    g["strokePath"]                = LUA_JUCE_C_CALL(&juce::Graphics::strokePath);
    g["drawArrow"]                 = LUA_JUCE_C_CALL(&juce::Graphics::drawArrow);
    g["setImageResamplingQuality"] = LUA_JUCE_C_CALL(&juce::Graphics::setImageResamplingQuality);
    g["drawImageAt"]               = LUA_JUCE_C_CALL(&juce::Graphics::drawImageAt);
    g["drawImageTransformed"]      = LUA_JUCE_C_CALL(&juce::Graphics::drawImageTransformed);
    g["drawImageWithin"]           = LUA_JUCE_C_CALL(&juce::Graphics::drawImageWithin);
    g["getClipBounds"]             = LUA_JUCE_C_CALL(&juce::Graphics::getClipBounds);
    g["clipRegionIntersects"]      = LUA_JUCE_C_CALL(&juce::Graphics::clipRegionIntersects);
    g["excludeClipRegion"]         = LUA_JUCE_C_CALL(&juce::Graphics::excludeClipRegion);
    g["isClipEmpty"]               = LUA_JUCE_C_CALL(&juce::Graphics::isClipEmpty);
    g["saveState"]                 = LUA_JUCE_C_CALL(&juce::Graphics::saveState);
    g["restoreState"]              = LUA_JUCE_C_CALL(&juce::Graphics::restoreState);
    g["beginTransparencyLayer"]    = LUA_JUCE_C_CALL(&juce::Graphics::beginTransparencyLayer);
    g["endTransparencyLayer"]      = LUA_JUCE_C_CALL(&juce::Graphics::endTransparencyLayer);
    g["addTransform"]              = LUA_JUCE_C_CALL(&juce::Graphics::addTransform);
    g["resetToDefaultState"]       = LUA_JUCE_C_CALL(&juce::Graphics::resetToDefaultState);
    g["isVectorDevice"]            = LUA_JUCE_C_CALL(&juce::Graphics::isVectorDevice);
    g["getInternalContext"]        = LUA_JUCE_C_CALL(&juce::Graphics::getInternalContext);
    g["setFont"]                   = sol::overload(                                                          //
        static_cast<void (juce::Graphics::*)(float)>(&juce::Graphics::setFont),            //
        static_cast<void (juce::Graphics::*)(juce::Font const&)>(&juce::Graphics::setFont) //
    );

    // clang-format off
    g.set_function("drawText", sol::overload(
            static_cast<void (juce::Graphics::*)(juce::String const&, int, int, int, int, juce::Justification, bool) const>(&juce::Graphics::drawText),
            [](juce::Graphics const* ctx, juce::String const& s, int x, int y, int w, int h, juce::Justification j) { ctx->drawText(s, x, y, w, h, j); },

            static_cast<void (juce::Graphics::*)(juce::String const&, juce::Rectangle<int>, juce::Justification, bool) const>(&juce::Graphics::drawText),
            [](juce::Graphics const* ctx, juce::String const& s, juce::Rectangle<int> area, juce::Justification j) { ctx->drawText(s, area, j); },

            static_cast<void (juce::Graphics::*)(juce::String const&, juce::Rectangle<float>, juce::Justification, bool) const>(&juce::Graphics::drawText),
            [](juce::Graphics const* ctx, juce::String const& s, juce::Rectangle<float> area, juce::Justification j) { ctx->drawText(s, area, j); }
        )
    );
    g.set_function("drawFittedText", sol::overload(
            static_cast<void (juce::Graphics::*)(juce::String const&, int, int, int, int, juce::Justification, int, float) const>(&juce::Graphics::drawFittedText),
            [](juce::Graphics const* ctx, juce::String const& s, int x, int y, int w, int h, juce::Justification j, int m) { ctx->drawFittedText(s, x, y, w, h, j, m); },

            static_cast<void (juce::Graphics::*)(juce::String const&, juce::Rectangle<int>, juce::Justification, int, float) const>(&juce::Graphics::drawFittedText),
            [](juce::Graphics const* ctx, juce::String const& s, juce::Rectangle<int> area, juce::Justification j, int m) { ctx->drawFittedText(s, area, j, m); }
        )
    );
    g.set_function("setGradientFill", sol::overload(
            static_cast<void (juce::Graphics::*)(juce::ColourGradient const&)>(&juce::Graphics::setGradientFill)
        )
    );
    g.set_function("fillAll", sol::overload(
            static_cast<void (juce::Graphics::*)() const>(&juce::Graphics::fillAll),
            static_cast<void (juce::Graphics::*)(juce::Colour) const>(&juce::Graphics::fillAll)
        )
    );
    g.set_function("fillEllipse", sol::overload(
            static_cast<void (juce::Graphics::*)(float, float, float, float) const>(&juce::Graphics::fillEllipse),
            static_cast<void (juce::Graphics::*)(juce::Rectangle<float>) const>(&juce::Graphics::fillEllipse)
        )
    );
    g.set_function("fillRect", sol::overload(
            static_cast<void (juce::Graphics::*)(juce::Rectangle<int>) const>(&juce::Graphics::fillRect),
            static_cast<void (juce::Graphics::*)(juce::Rectangle<float>) const>(&juce::Graphics::fillRect),
            static_cast<void (juce::Graphics::*)(int, int, int, int) const>(&juce::Graphics::fillRect),
            static_cast<void (juce::Graphics::*)(float, float, float, float) const>(&juce::Graphics::fillRect)
        )
    );
    g.set_function("fillRectList", sol::overload(
            static_cast<void (juce::Graphics::*)(juce::RectangleList<float> const&) const>(&juce::Graphics::fillRectList),
            static_cast<void (juce::Graphics::*)(juce::RectangleList<int> const&) const>(&juce::Graphics::fillRectList)
        )
    );
    g.set_function("fillRoundedRectangle", sol::overload(
            static_cast<void (juce::Graphics::*)(float, float, float, float, float) const>(&juce::Graphics::fillRoundedRectangle),
            [](juce::Graphics* ctx, juce::Rectangle<int> rect, double radius){ ctx->fillRoundedRectangle(rect.toFloat(), static_cast<float>(radius)); },
            [](juce::Graphics* ctx, juce::Rectangle<float> rect, double radius){ ctx->fillRoundedRectangle(rect, static_cast<float>(radius)); },
            [](juce::Graphics* ctx, juce::Rectangle<double> rect, double radius){ ctx->fillRoundedRectangle(rect.toFloat(), static_cast<float>(radius)); }
        )
    );
    g.set_function("drawRect", sol::overload(
            static_cast<void (juce::Graphics::*)(juce::Rectangle<int>, int) const>(&juce::Graphics::drawRect),
            static_cast<void (juce::Graphics::*)(juce::Rectangle<float>, float) const>(&juce::Graphics::drawRect),
            static_cast<void (juce::Graphics::*)(int, int, int, int, int) const>(&juce::Graphics::drawRect),
            static_cast<void (juce::Graphics::*)(float, float, float, float, float) const>(&juce::Graphics::drawRect)
        )
    );
    g.set_function("drawLine", sol::overload(
            static_cast<void (juce::Graphics::*)(float, float, float, float) const>(&juce::Graphics::drawLine),
            static_cast<void (juce::Graphics::*)(float, float, float, float, float) const>(&juce::Graphics::drawLine),
            static_cast<void (juce::Graphics::*)(juce::Line<float>) const>(&juce::Graphics::drawLine),
            static_cast<void (juce::Graphics::*)(juce::Line<float>, float) const>(&juce::Graphics::drawLine)
        )
    );
    g.set_function("drawRoundedRectangle", sol::overload(
            static_cast<void (juce::Graphics::*)(float, float, float, float, float, float) const>(&juce::Graphics::drawRoundedRectangle),
            static_cast<void (juce::Graphics::*)(juce::Rectangle<float>, float, float) const>(&juce::Graphics::drawRoundedRectangle)
        )
    );
    g.set_function("drawEllipse", sol::overload(
            static_cast<void (juce::Graphics::*)(float, float, float, float, float) const>(&juce::Graphics::drawEllipse),
            static_cast<void (juce::Graphics::*)(juce::Rectangle<float>, float) const>(&juce::Graphics::drawEllipse)
        )
    );
    // clang-format on
}
} // namespace lua_juce
