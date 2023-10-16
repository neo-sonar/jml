project(test)

function(lua_juce_add_test _name)
    add_test(
        NAME
            "lua: ${_name}"
        COMMAND
            $<TARGET_FILE:jml-viewer> test -s "${_name}.lua"
        WORKING_DIRECTORY
            ${PROJECT_SOURCE_DIR}
    )
endfunction()

lua_juce_add_test("core/Array")
lua_juce_add_test("core/BigInteger")
lua_juce_add_test("core/File")
lua_juce_add_test("core/String")
