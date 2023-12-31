#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

namespace jml::designer {

struct DocumentCanvas;

enum struct ToolType
{
    invalid,
    select,
    rectangle,
    ellipse,
};

struct Tool
{
    explicit Tool(DocumentCanvas& canvas);
    virtual ~Tool() = default;

    virtual auto paintTool(juce::Graphics& g) -> void = 0;

    [[nodiscard]] auto getDocumentCanvas() -> DocumentCanvas&;
    [[nodiscard]] auto getDocumentCanvas() const -> DocumentCanvas const&;

private:
    DocumentCanvas* _canvas;
};

} // namespace jml::designer
