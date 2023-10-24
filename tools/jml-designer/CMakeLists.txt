project(jml-designer VERSION 0.1.0)

juce_add_binary_data(JMLDesigner_BinaryData
    HEADER_NAME
        "BinaryData.hpp"
    NAMESPACE
        BinaryData
    SOURCES
        "Resources/svg/tool_circle.svg"
        "Resources/svg/tool_rectangle.svg"
        "Resources/svg/tool_select.svg"

        "Resources/svg/outline/content_copy.svg"
        "Resources/svg/outline/content_cut.svg"
        "Resources/svg/outline/content_paste.svg"
        "Resources/svg/outline/file_open.svg"
        "Resources/svg/outline/open_in_new.svg"
        "Resources/svg/outline/redo.svg"
        "Resources/svg/outline/save_as.svg"
        "Resources/svg/outline/save.svg"
        "Resources/svg/outline/undo.svg"
)

juce_add_gui_app(jml-designer
    PRODUCT_NAME
        "jml-designer"
)

set_target_properties(jml-designer
    PROPERTIES
        UNITY_BUILD_MODE GROUP
)

set(sources
    "Application/Application.cpp"
    "Application/Application.hpp"
    "Application/Main.cpp"
    "Application/MainComponent.cpp"
    "Application/MainComponent.hpp"

    "Component/Button.hpp"
    "Component/PropertyPanel.hpp"
    "Component/TreeView.hpp"

    "Core/Justification.cpp"
    "Core/Justification.hpp"
    "Core/ValueTreeObject.hpp"
    "Core/ValueTreeObjectList.hpp"

    "Document/Document.cpp"
    "Document/Document.hpp"
    "Document/DocumentCanvas.cpp"
    "Document/DocumentCanvas.hpp"
    "Document/DocumentEditor.cpp"
    "Document/DocumentEditor.hpp"

    "Layer/Layer.cpp"
    "Layer/Layer.hpp"
    "Layer/LayerCanvas.cpp"
    "Layer/LayerCanvas.hpp"
    "Layer/LayerList.cpp"
    "Layer/LayerList.hpp"
    "Layer/LayerListener.cpp"
    "Layer/LayerListener.hpp"
    "Layer/LayerPropertyPanel.cpp"
    "Layer/LayerPropertyPanel.hpp"
    "Layer/LayerSelection.cpp"
    "Layer/LayerSelection.hpp"
    "Layer/LayerTree.cpp"
    "Layer/LayerTree.hpp"
    "Layer/LayerTreeItem.cpp"
    "Layer/LayerTreeItem.hpp"

    "Layer/Effect/DropShadow.cpp"
    "Layer/Effect/DropShadow.hpp"
    "Layer/Effect/GlowEffect.cpp"
    "Layer/Effect/GlowEffect.hpp"
    "Layer/Effect/LayerEffect.cpp"
    "Layer/Effect/LayerEffect.hpp"
    "Layer/Effect/LayerEffectList.cpp"
    "Layer/Effect/LayerEffectList.hpp"
    "Layer/Effect/StackBlurEffect.cpp"
    "Layer/Effect/StackBlurEffect.hpp"

    "Layer/Export/Exporter.hpp"
    "Layer/Export/ExportPanel.cpp"
    "Layer/Export/ExportPanel.hpp"
    "Layer/Export/ImageExporter.cpp"
    "Layer/Export/ImageExporter.hpp"

    "Layers/GroupLayer.cpp"
    "Layers/GroupLayer.hpp"
    "Layers/ShapeLayer.cpp"
    "Layers/ShapeLayer.hpp"
    "Layers/TextLayer.cpp"
    "Layers/TextLayer.hpp"

    "Menu/CommandIDs.hpp"
    "Menu/MenuBar.cpp"
    "Menu/MenuBar.hpp"

    "Tool/SelectionTool.cpp"
    "Tool/SelectionTool.hpp"
    "Tool/ShapeTool.cpp"
    "Tool/ShapeTool.hpp"
    "Tool/Tool.cpp"
    "Tool/Tool.hpp"
    "Tool/ToolBar.cpp"
    "Tool/ToolBar.hpp"
)

target_sources(jml-designer PRIVATE ${sources})
set_source_files_properties(jml-designer ${sources} PROPERTIES UNITY_GROUP "src")

target_compile_definitions(jml-designer
    PRIVATE
        JUCE_WEB_BROWSER=0
        JUCE_USE_CURL=0
        JUCE_DISABLE_JUCE_VERSION_PRINTING=1
        JUCE_APPLICATION_NAME_STRING="$<TARGET_PROPERTY:jml-designer,JUCE_PRODUCT_NAME>"
        JUCE_APPLICATION_VERSION_STRING="$<TARGET_PROPERTY:jml-designer,JUCE_VERSION>"
        JUCE_SILENCE_XCODE_15_LINKER_WARNING=1
)

target_include_directories(jml-designer
    PUBLIC
        ${PROJECT_SOURCE_DIR}
)

target_link_libraries(jml-designer
    PRIVATE
        juce::juce_gui_extra
        jml::jml_tools

    PUBLIC
        lua::lua
        sol2::sol2

        JMLDesigner_BinaryData
        juce::juce_recommended_warning_flags
)

if (${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    if(${CMAKE_CXX_COMPILER_VERSION} VERSION_GREATER 15)
        target_link_options(jml-designer
            PRIVATE
                -Wl,-weak_reference_mismatches,weak
        )
    endif()
endif()