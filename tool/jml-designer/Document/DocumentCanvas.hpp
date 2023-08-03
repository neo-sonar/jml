#pragma once

#include "Document/Document.hpp"
#include "Tool/Tool.hpp"
#include "Tool/ToolBar.hpp"

#include <mc_gui_basics/mc_gui_basics.hpp>

namespace jml::designer {
struct DocumentCanvas final : juce::Component
{
    DocumentCanvas(Document& doc, ToolBar& toolBar);
    ~DocumentCanvas() override;

    [[nodiscard]] auto document() -> Document&;
    [[nodiscard]] auto document() const -> Document const&;

    auto paint(juce::Graphics& /*g*/) -> void override;
    auto paintOverChildren(juce::Graphics& /*g*/) -> void override;
    auto resized() -> void override;

private:
    auto updateTool(ToolType type) -> void;

    Document& _document;
    std::unique_ptr<Tool> _tool;
};

} // namespace jml::designer
