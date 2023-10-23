namespace lua_juce {
auto juce_Path(sol::table& state) -> void
{
    // TODO(tobi)
    // path["defaultToleranceForTesting"]     = std::cref(juce::Path::defaultToleranceForTesting);
    // path["defaultToleranceForMeasurement"] = std::cref(juce::Path::defaultToleranceForMeasurement);
    // lineTo
    // quadraticTo
    // cubicTo
    // addRectangle
    // addRoundedRectangle
    // addTriangle
    // addEllipse
    // addPieSegment
    // addPath
    // getTransformToScaleToFit

    // clang-format off
    auto path = state.new_usertype<juce::Path>("Path",
        sol::constructors<juce::Path()>()
    );
    path["contains"] = sol::overload(
            [] (juce::Path* self, float x, float y) -> bool { return self->contains(x, y); },
            static_cast<bool (juce::Path::*)(float,float,float) const>(&juce::Path::contains),
            static_cast<bool (juce::Path::*)(juce::Point<float>, float) const>(&juce::Path::contains)
    );
    path["intersectsLine"] = sol::overload(
            [] (juce::Path const* self, juce::Line<float> line) -> bool { return self->intersectsLine(line); },
            static_cast<bool (juce::Path::*)(juce::Line<float>, float) const>(&juce::Path::intersectsLine)
    );
    // clang-format on

    path["isEmpty"]                      = LUA_JUCE_C_CALL(&juce::Path::isEmpty);
    path["getBounds"]                    = LUA_JUCE_C_CALL(&juce::Path::getBounds);
    path["getBoundsTransformed"]         = LUA_JUCE_C_CALL(&juce::Path::getBoundsTransformed);
    path["clear"]                        = LUA_JUCE_C_CALL(&juce::Path::clear);
    path["getClippedLine"]               = LUA_JUCE_C_CALL(&juce::Path::getClippedLine);
    path["getLength"]                    = LUA_JUCE_C_CALL(&juce::Path::getLength);
    path["getPointAlongPath"]            = LUA_JUCE_C_CALL(&juce::Path::getPointAlongPath);
    path["getNearestPoint "]             = LUA_JUCE_C_CALL(&juce::Path::getNearestPoint);
    path["closeSubPath"]                 = LUA_JUCE_C_CALL(&juce::Path::closeSubPath);
    path["getCurrentPosition"]           = LUA_JUCE_C_CALL(&juce::Path::getCurrentPosition);
    path["addQuadrilateral"]             = LUA_JUCE_C_CALL(&juce::Path::addQuadrilateral);
    path["addArc"]                       = LUA_JUCE_C_CALL(&juce::Path::addArc);
    path["addCentredArc"]                = LUA_JUCE_C_CALL(&juce::Path::addCentredArc);
    path["addLineSegment"]               = LUA_JUCE_C_CALL(&juce::Path::addLineSegment);
    path["addArrow"]                     = LUA_JUCE_C_CALL(&juce::Path::addArrow);
    path["addPolygon"]                   = LUA_JUCE_C_CALL(&juce::Path::addPolygon);
    path["addStar"]                      = LUA_JUCE_C_CALL(&juce::Path::addStar);
    path["addBubble"]                    = LUA_JUCE_C_CALL(&juce::Path::addBubble);
    path["swapWithPath"]                 = LUA_JUCE_C_CALL(&juce::Path::swapWithPath);
    path["preallocateSpace"]             = LUA_JUCE_C_CALL(&juce::Path::preallocateSpace);
    path["applyTransform"]               = LUA_JUCE_C_CALL(&juce::Path::applyTransform);
    path["scaleToFit"]                   = LUA_JUCE_C_CALL(&juce::Path::scaleToFit);
    path["createPathWithRoundedCorners"] = LUA_JUCE_C_CALL(&juce::Path::createPathWithRoundedCorners);
    path["setUsingNonZeroWinding"]       = LUA_JUCE_C_CALL(&juce::Path::setUsingNonZeroWinding);
    path["isUsingNonZeroWinding"]        = LUA_JUCE_C_CALL(&juce::Path::isUsingNonZeroWinding);
    path["loadPathFromStream"]           = LUA_JUCE_C_CALL(&juce::Path::loadPathFromStream);
    path["loadPathFromData"]             = LUA_JUCE_C_CALL(&juce::Path::loadPathFromData);
    path["writePathToStream"]            = LUA_JUCE_C_CALL(&juce::Path::writePathToStream);
    path["toString"]                     = LUA_JUCE_C_CALL(&juce::Path::toString);
    path["restoreFromString"]            = LUA_JUCE_C_CALL(&juce::Path::restoreFromString);
}
} // namespace lua_juce
