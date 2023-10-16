namespace lua_juce {
template<typename T>
auto juce_PointImpl(sol::table& state, char const* name) -> void
{
    // TODO(tobi)
    // getPointOnCircumference
    // point["rotatedAboutOrigin"]           = &juce::Point<T>::rotatedAboutOrigin;
    // point["getDotProduct"]                = &juce::Point<T>::getDotProduct;

    auto point = state.new_usertype<juce::Point<T>>(name, sol::constructors<juce::Point<T>(), juce::Point<T>(T, T)>());

    point["isOrigin"]                     = LUA_JUCE_C_CALL(&juce::Point<T>::isOrigin);
    point["isFinite"]                     = LUA_JUCE_C_CALL(&juce::Point<T>::isFinite);
    point["getX"]                         = LUA_JUCE_C_CALL(&juce::Point<T>::getX);
    point["getY"]                         = LUA_JUCE_C_CALL(&juce::Point<T>::getY);
    point["setX"]                         = LUA_JUCE_C_CALL(&juce::Point<T>::setX);
    point["setY"]                         = LUA_JUCE_C_CALL(&juce::Point<T>::setY);
    point["withX"]                        = LUA_JUCE_C_CALL(&juce::Point<T>::withX);
    point["withY"]                        = LUA_JUCE_C_CALL(&juce::Point<T>::withY);
    point["setXY"]                        = LUA_JUCE_C_CALL(&juce::Point<T>::setXY);
    point["addXY"]                        = LUA_JUCE_C_CALL(&juce::Point<T>::addXY);
    point["translated"]                   = LUA_JUCE_C_CALL(&juce::Point<T>::translated);
    point["getDistanceFromOrigin"]        = LUA_JUCE_C_CALL(&juce::Point<T>::getDistanceFromOrigin);
    point["getDistanceFrom"]              = LUA_JUCE_C_CALL(&juce::Point<T>::getDistanceFrom);
    point["getDistanceSquaredFromOrigin"] = LUA_JUCE_C_CALL(&juce::Point<T>::getDistanceSquaredFromOrigin);
    point["getDistanceSquaredFrom"]       = LUA_JUCE_C_CALL(&juce::Point<T>::getDistanceSquaredFrom);
    point["getAngleToPoint"]              = LUA_JUCE_C_CALL(&juce::Point<T>::getAngleToPoint);
    point["applyTransform"]               = LUA_JUCE_C_CALL(&juce::Point<T>::applyTransform);
    point["transformedBy"]                = LUA_JUCE_C_CALL(&juce::Point<T>::transformedBy);
    point["toInt"]                        = LUA_JUCE_C_CALL(&juce::Point<T>::toInt);
    point["toFloat"]                      = LUA_JUCE_C_CALL(&juce::Point<T>::toFloat);
    point["toDouble"]                     = LUA_JUCE_C_CALL(&juce::Point<T>::toDouble);
    point["roundToInt"]                   = LUA_JUCE_C_CALL(&juce::Point<T>::roundToInt);
    point["toString"]                     = LUA_JUCE_C_CALL(&juce::Point<T>::toString);
}

auto juce_Point(sol::table& state) -> void
{
    juce_PointImpl<int>(state, "PointInt");
    juce_PointImpl<float>(state, "PointFloat");
    juce_PointImpl<double>(state, "PointDouble");
}
} // namespace lua_juce
