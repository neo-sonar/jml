project(jml-viewer VERSION 0.1.0)

find_package(CLI11 REQUIRED)

juce_add_binary_data(jml-viewer_BinaryData
    HEADER_NAME
        "BinaryData.hpp"
    NAMESPACE
        BinaryData
    SOURCES
        "Asset/Icon/autorenew_black_48dp.svg"
        "Asset/Icon/close_black_48dp.svg"
        "Asset/Icon/content_copy_black_48dp.svg"
        "Asset/Icon/content_cut_black_48dp.svg"
        "Asset/Icon/content_paste_black_48dp.svg"
        "Asset/Icon/data_object_black_48dp.svg"
        "Asset/Icon/delete_black_48dp.svg"
        "Asset/Icon/deselect_black_48dp.svg"
        "Asset/Icon/help_outline_black_48dp.svg"
        "Asset/Icon/info_black_48dp.svg"
        "Asset/Icon/keyboard_black_48dp.svg"
        "Asset/Icon/launch_black_48dp.svg"
        "Asset/Icon/palette_black_48dp.svg"
        "Asset/Icon/redo_black_48dp.svg"
        "Asset/Icon/save_as_black_48dp.svg"
        "Asset/Icon/save_black_48dp.svg"
        "Asset/Icon/select_all_black_48dp.svg"
        "Asset/Icon/settings_black_48dp.svg"
        "Asset/Icon/undo_black_48dp.svg"
)

juce_add_gui_app(jml-viewer
    # VERSION ...                       # Set this if the app version is different to the project version
    # ICON_BIG ...                      # ICON_* arguments specify a path to an image file to use as an icon
    # ICON_SMALL ...
    # DOCUMENT_EXTENSIONS ...           # Specify file extensions that should be associated with this app
    # COMPANY_NAME ...                  # Specify the name of the app's author
    PRODUCT_NAME "jml-viewer"           # The name of the final executable, which can differ from the target name
)

set(sources
    "Application/CommandIDs.hpp"
    "Application/CommandLine.hpp"
    "Application/CommandLine.cpp"
    "Application/Main.cpp"
    "Application/MainComponent.hpp"
    "Application/MainComponent.cpp"
    "Application/MenuBar.hpp"
    "Application/MenuBar.cpp"

    "CodeEditor/CodeEditor.cpp"
    "CodeEditor/CodeEditor.hpp"

    "Command/Snapshot.hpp"
    "Command/Test.hpp"

    "Core/Graphics.cpp"
    "Core/Graphics.hpp"

    "LookAndFeel/Colours.hpp"
    "LookAndFeel/LookAndFeel.cpp"
    "LookAndFeel/LookAndFeel.hpp"

    "Viewer/ComponentTree.cpp"
    "Viewer/ComponentTree.hpp"
    "Viewer/FileChangeListener.cpp"
    "Viewer/FileChangeListener.hpp"
    "Viewer/LuaScriptViewer.cpp"
    "Viewer/LuaScriptViewer.hpp"
    "Viewer/ScriptPanel.cpp"
    "Viewer/ScriptPanel.hpp"
    "Viewer/ScriptViewport.cpp"
    "Viewer/ScriptViewport.hpp"
)

target_sources(jml-viewer PRIVATE ${sources})
set_source_files_properties(jml-viewer ${sources} PROPERTIES UNITY_GROUP "src")
set_target_properties(jml-viewer PROPERTIES UNITY_BUILD_MODE GROUP)

target_include_directories(jml-viewer
    PUBLIC
        ${PROJECT_SOURCE_DIR}
)

target_compile_definitions(jml-viewer
    PRIVATE
        SOL_ALL_SAFETIES_ON=1
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_DISABLE_JUCE_VERSION_PRINTING=1
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:jml-viewer,JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:jml-viewer,JUCE_VERSION>"
)

target_link_libraries(jml-viewer
    PRIVATE
        lua_juce::lua_juce

    PUBLIC
        jml-viewer_BinaryData

        lua::lua
        sol2::sol2
        CLI11::CLI11

        juce::juce_recommended_warning_flags
)
