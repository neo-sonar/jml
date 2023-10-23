namespace lua_juce {
auto juce_ImageCache(sol::table& state) -> void
{
    auto cache                   = state.create_named("ImageCache");
    cache["getFromFile"]         = LUA_JUCE_C_CALL(&juce::ImageCache::getFromFile);
    cache["getFromMemory"]       = LUA_JUCE_C_CALL(&juce::ImageCache::getFromMemory);
    cache["getFromHashCode"]     = LUA_JUCE_C_CALL(&juce::ImageCache::getFromHashCode);
    cache["addImageToCache"]     = LUA_JUCE_C_CALL(&juce::ImageCache::addImageToCache);
    cache["setCacheTimeout"]     = LUA_JUCE_C_CALL(&juce::ImageCache::setCacheTimeout);
    cache["releaseUnusedImages"] = LUA_JUCE_C_CALL(&juce::ImageCache::releaseUnusedImages);
}
} // namespace lua_juce
