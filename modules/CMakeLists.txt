cmake_minimum_required(VERSION 3.23)
project(lua-juce VERSION 0.1.0)

juce_add_modules(ALIAS_NAMESPACE lua_juce
    lua_juce_audio_basics
    lua_juce_audio_processors
    lua_juce_core
    lua_juce_data_structures
    lua_juce_events
    lua_juce_graphics
    lua_juce_gui_basics
    lua_juce_gui_extra
    lua_juce
)
