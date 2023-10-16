namespace lua_juce {
auto juce_AffineTransform(sol::table& state) -> void
{
    using Transform = juce::AffineTransform;

    // clang-format off
    auto transform = state.new_usertype<Transform>("AffineTransform",
        sol::constructors<
            Transform(),
            Transform(float, float, float, float, float, float)
        >()
    );
    transform.set_function("rotated", sol::overload(
            static_cast<Transform (Transform::*)(float) const noexcept>(&Transform::rotated),
            static_cast<Transform (Transform::*)(float, float, float) const noexcept>(&Transform::rotated)
        )
    );
    transform.set_function("scaled", sol::overload(
            static_cast<Transform (Transform::*)(float) const noexcept>(&Transform::scaled),
            static_cast<Transform (Transform::*)(float, float) const noexcept>(&Transform::scaled),
            static_cast<Transform (Transform::*)(float, float, float, float) const noexcept>(&Transform::scaled)
        )
    );
    transform.set_function("rotation", sol::overload(
            static_cast<Transform (*)(float) noexcept>(&Transform::rotation),
            static_cast<Transform (*)(float, float, float) noexcept>(&Transform::rotation)
        )
    );
    // clang-format on
    transform["withAbsoluteTranslation"] = LUA_JUCE_C_CALL(&Transform::withAbsoluteTranslation);
    transform["sheared"]                 = LUA_JUCE_C_CALL(&Transform::sheared);
    transform["shear"]                   = LUA_JUCE_C_CALL(&Transform::shear);
    transform["verticalFlip"]            = LUA_JUCE_C_CALL(&Transform::verticalFlip);
    transform["inverted"]                = LUA_JUCE_C_CALL(&Transform::inverted);
    transform["followedBy"]              = LUA_JUCE_C_CALL(&Transform::followedBy);
    transform["isIdentity"]              = LUA_JUCE_C_CALL(&Transform::isIdentity);
    transform["isSingularity"]           = LUA_JUCE_C_CALL(&Transform::isSingularity);
    transform["isOnlyTranslation"]       = LUA_JUCE_C_CALL(&Transform::isOnlyTranslation);
    transform["getTranslationX"]         = LUA_JUCE_C_CALL(&Transform::getTranslationX);
    transform["getTranslationY"]         = LUA_JUCE_C_CALL(&Transform::getTranslationY);
    transform["getDeterminant"]          = LUA_JUCE_C_CALL(&Transform::getDeterminant);

    transform["mat00"] = &Transform::mat00;
    transform["mat01"] = &Transform::mat01;
    transform["mat02"] = &Transform::mat02;
    transform["mat10"] = &Transform::mat10;
    transform["mat11"] = &Transform::mat11;
    transform["mat12"] = &Transform::mat12;
}
} // namespace lua_juce
