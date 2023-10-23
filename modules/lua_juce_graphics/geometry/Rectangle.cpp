

namespace lua_juce {
template<typename T>
auto juce_RectangleImpl(sol::table& state, char const* name) -> void
{
    using Rect = juce::Rectangle<T>;
    // TODO(tobi)
    // setPosition
    // setCentre
    // withPosition
    // expanded
    // contains
    // intersects
    // intersectRectangle
    // rect["intersectRectangles"]      = &juce::Rectangle<T>::intersectRectangles;

    // clang-format off
    auto rect = state.new_usertype<Rect>(name,
        sol::constructors<
            Rect(),
            Rect(T, T, T, T)
        >()
    );
    rect["reduced"] = sol::overload(
            static_cast<Rect (Rect::*)(T) const noexcept>(&Rect::reduced),
            static_cast<Rect (Rect::*)(T, T) const noexcept>(&Rect::reduced)
    );
    // clang-format on

    rect["isEmpty"]                     = LUA_JUCE_C_CALL(&Rect::isEmpty);
    rect["isFinite"]                    = LUA_JUCE_C_CALL(&Rect::isFinite);
    rect["getX"]                        = LUA_JUCE_C_CALL(&Rect::getX);
    rect["getY"]                        = LUA_JUCE_C_CALL(&Rect::getY);
    rect["getWidth"]                    = LUA_JUCE_C_CALL(&Rect::getWidth);
    rect["getHeight"]                   = LUA_JUCE_C_CALL(&Rect::getHeight);
    rect["getRight"]                    = LUA_JUCE_C_CALL(&Rect::getRight);
    rect["getBottom"]                   = LUA_JUCE_C_CALL(&Rect::getBottom);
    rect["getCentreX"]                  = LUA_JUCE_C_CALL(&Rect::getCentreX);
    rect["getCentreY"]                  = LUA_JUCE_C_CALL(&Rect::getCentreY);
    rect["getCentre"]                   = LUA_JUCE_C_CALL(&Rect::getCentre);
    rect["getAspectRatio"]              = LUA_JUCE_C_CALL(&Rect::getAspectRatio);
    rect["getPosition"]                 = LUA_JUCE_C_CALL(&Rect::getPosition);
    rect["getBottom"]                   = LUA_JUCE_C_CALL(&Rect::getBottom);
    rect["getTopLeft"]                  = LUA_JUCE_C_CALL(&Rect::getTopLeft);
    rect["getTopRight"]                 = LUA_JUCE_C_CALL(&Rect::getTopRight);
    rect["getBottomLeft"]               = LUA_JUCE_C_CALL(&Rect::getBottomLeft);
    rect["getBottomRight"]              = LUA_JUCE_C_CALL(&Rect::getBottomRight);
    rect["getHorizontalRange"]          = LUA_JUCE_C_CALL(&Rect::getHorizontalRange);
    rect["getVerticalRange"]            = LUA_JUCE_C_CALL(&Rect::getVerticalRange);
    rect["setSize"]                     = LUA_JUCE_C_CALL(&Rect::setSize);
    rect["setBounds"]                   = LUA_JUCE_C_CALL(&Rect::setBounds);
    rect["setX"]                        = LUA_JUCE_C_CALL(&Rect::setX);
    rect["setY"]                        = LUA_JUCE_C_CALL(&Rect::setY);
    rect["setWidth"]                    = LUA_JUCE_C_CALL(&Rect::setWidth);
    rect["setHeight"]                   = LUA_JUCE_C_CALL(&Rect::setHeight);
    rect["setHorizontalRange"]          = LUA_JUCE_C_CALL(&Rect::setHorizontalRange);
    rect["setVerticalRange"]            = LUA_JUCE_C_CALL(&Rect::setVerticalRange);
    rect["withX"]                       = LUA_JUCE_C_CALL(&Rect::withX);
    rect["withY"]                       = LUA_JUCE_C_CALL(&Rect::withY);
    rect["withRightX"]                  = LUA_JUCE_C_CALL(&Rect::withRightX);
    rect["withBottomY"]                 = LUA_JUCE_C_CALL(&Rect::withBottomY);
    rect["withZeroOrigin"]              = LUA_JUCE_C_CALL(&Rect::withZeroOrigin);
    rect["withCentre"]                  = LUA_JUCE_C_CALL(&Rect::withCentre);
    rect["withWidth"]                   = LUA_JUCE_C_CALL(&Rect::withWidth);
    rect["withHeight"]                  = LUA_JUCE_C_CALL(&Rect::withHeight);
    rect["withSize"]                    = LUA_JUCE_C_CALL(&Rect::withSize);
    rect["withSizeKeepingCentre"]       = LUA_JUCE_C_CALL(&Rect::withSizeKeepingCentre);
    rect["setLeft"]                     = LUA_JUCE_C_CALL(&Rect::setLeft);
    rect["withLeft"]                    = LUA_JUCE_C_CALL(&Rect::withLeft);
    rect["setTop"]                      = LUA_JUCE_C_CALL(&Rect::setTop);
    rect["withTop"]                     = LUA_JUCE_C_CALL(&Rect::withTop);
    rect["setRight"]                    = LUA_JUCE_C_CALL(&Rect::setRight);
    rect["withRight"]                   = LUA_JUCE_C_CALL(&Rect::withRight);
    rect["setBottom"]                   = LUA_JUCE_C_CALL(&Rect::setBottom);
    rect["withBottom"]                  = LUA_JUCE_C_CALL(&Rect::withBottom);
    rect["withTrimmedLeft"]             = LUA_JUCE_C_CALL(&Rect::withTrimmedLeft);
    rect["withTrimmedRight"]            = LUA_JUCE_C_CALL(&Rect::withTrimmedRight);
    rect["withTrimmedTop"]              = LUA_JUCE_C_CALL(&Rect::withTrimmedTop);
    rect["withTrimmedBottom"]           = LUA_JUCE_C_CALL(&Rect::withTrimmedBottom);
    rect["translate"]                   = LUA_JUCE_C_CALL(&Rect::translate);
    rect["translated"]                  = LUA_JUCE_C_CALL(&Rect::translated);
    rect["expand"]                      = LUA_JUCE_C_CALL(&Rect::expand);
    rect["reduce"]                      = LUA_JUCE_C_CALL(&Rect::reduce);
    rect["removeFromTop"]               = [](Rect* self, double v) { return self->removeFromTop(static_cast<T>(v)); };
    rect["removeFromBottom"]            = [](Rect* self, double v) { return self->removeFromBottom(static_cast<T>(v)); };
    rect["removeFromLeft"]              = [](Rect* self, double v) { return self->removeFromLeft(static_cast<T>(v)); };
    rect["removeFromRight"]             = [](Rect* self, double v) { return self->removeFromRight(static_cast<T>(v)); };
    rect["getConstrainedPoint"]         = LUA_JUCE_C_CALL(&Rect::getConstrainedPoint);
    rect["getRelativePoint"]            = LUA_JUCE_C_CALL(&Rect::template getRelativePoint<double>);
    rect["proportionOfWidth"]           = LUA_JUCE_C_CALL(&Rect::template proportionOfWidth<double>);
    rect["proportionOfHeight"]          = LUA_JUCE_C_CALL(&Rect::template proportionOfHeight<double>);
    rect["getIntersection"]             = LUA_JUCE_C_CALL(&Rect::getIntersection);
    rect["getUnion"]                    = LUA_JUCE_C_CALL(&Rect::getUnion);
    rect["enlargeIfAdjacent"]           = LUA_JUCE_C_CALL(&Rect::enlargeIfAdjacent);
    rect["reduceIfPartlyContainedIn"]   = LUA_JUCE_C_CALL(&Rect::reduceIfPartlyContainedIn);
    rect["constrainedWithin"]           = LUA_JUCE_C_CALL(&Rect::constrainedWithin);
    rect["transformedBy"]               = LUA_JUCE_C_CALL(&Rect::transformedBy);
    rect["getSmallestIntegerContainer"] = LUA_JUCE_C_CALL(&Rect::getSmallestIntegerContainer);
    rect["toNearestInt"]                = LUA_JUCE_C_CALL(&Rect::toNearestInt);
    rect["toNearestIntEdges"]           = LUA_JUCE_C_CALL(&Rect::toNearestIntEdges);
    rect["toFloat"]                     = LUA_JUCE_C_CALL(&Rect::toFloat);
    rect["toDouble"]                    = LUA_JUCE_C_CALL(&Rect::toDouble);
    rect["toString"]                    = LUA_JUCE_C_CALL(&Rect::toString);

    rect["leftTopRightBottom"]       = LUA_JUCE_C_CALL(&Rect::leftTopRightBottom);
    rect["findAreaContainingPoints"] = LUA_JUCE_C_CALL(&Rect::findAreaContainingPoints);
    rect["fromString"]               = LUA_JUCE_C_CALL(&Rect::fromString);
}

auto juce_Rectangle(sol::table& state) -> void
{
    juce_RectangleImpl<int>(state, "Rectangle_int");
    juce_RectangleImpl<float>(state, "Rectangle_float");
    juce_RectangleImpl<double>(state, "Rectangle_double");
}
} // namespace lua_juce
