namespace lua_juce {

auto juce_ImageComponent(sol::table& state) -> void
{
    // clang-format off
    auto imgComponent = state.new_usertype<juce::ImageComponent>("ImageComponent",
        sol::constructors<juce::ImageComponent(juce::String const&)>(),
        sol::base_classes,
        sol::bases<
            juce::MouseListener,
            juce::Component,
            juce::TooltipClient,
            juce::SettableTooltipClient
        >()
    );
    // clang-format on

    imgComponent["getImage"]          = LUA_JUCE_C_CALL(&juce::ImageComponent::getImage);
    imgComponent["setImagePlacement"] = LUA_JUCE_C_CALL(&juce::ImageComponent::setImagePlacement);
    imgComponent["getImagePlacement"] = LUA_JUCE_C_CALL(&juce::ImageComponent::getImagePlacement);
    imgComponent["setImage"]          = sol::overload(                                                                          //
        [](juce::ImageComponent* comp, juce::Image const& img) { comp->setImage(img); },                               //
        [](juce::ImageComponent* comp, juce::Image const& img, juce::RectanglePlacement p) { comp->setImage(img, p); } //
    );
}

} // namespace lua_juce
