namespace jml {

namespace {

using ColourScheme = juce::LookAndFeel_V4::ColourScheme;

struct SchemeColorIdMapping
{
    char const* name;
    ColourScheme::UIColour value;
};

constexpr auto schemeColorIdMapping = std::array{
    SchemeColorIdMapping{"windowBackground", ColourScheme::UIColour::windowBackground},
    SchemeColorIdMapping{"widgetBackground", ColourScheme::UIColour::widgetBackground},
    SchemeColorIdMapping{"menuBackground",   ColourScheme::UIColour::menuBackground  },
    SchemeColorIdMapping{"outline",          ColourScheme::UIColour::outline         },
    SchemeColorIdMapping{"defaultText",      ColourScheme::UIColour::defaultText     },
    SchemeColorIdMapping{"defaultFill",      ColourScheme::UIColour::defaultFill     },
    SchemeColorIdMapping{"highlightedText",  ColourScheme::UIColour::highlightedText },
    SchemeColorIdMapping{"highlightedFill",  ColourScheme::UIColour::highlightedFill },
    SchemeColorIdMapping{"menuText",         ColourScheme::UIColour::menuText        },
};

struct ComponentColorIdMapping
{
    char const* name;
    int value;
};

constexpr auto componentColorIdMapping = std::array{
    ComponentColorIdMapping{"DrawableButton::textColourId",                               0x1004010},
    ComponentColorIdMapping{"DrawableButton::textColourOnId",                             0x1004013},
    ComponentColorIdMapping{"DrawableButton::backgroundColourId",                         0x1004011},
    ComponentColorIdMapping{"DrawableButton::backgroundOnColourId",                       0x1004012},
    ComponentColorIdMapping{"HyperlinkButton::textColourId",                              0x1001f00},
    ComponentColorIdMapping{"TextButton::buttonColourId",                                 0x1000100},
    ComponentColorIdMapping{"TextButton::buttonOnColourId",                               0x1000101},
    ComponentColorIdMapping{"TextButton::textColourOffId",                                0x1000102},
    ComponentColorIdMapping{"TextButton::textColourOnId",                                 0x1000103},
    ComponentColorIdMapping{"ToggleButton::textColourId",                                 0x1006501},
    ComponentColorIdMapping{"ToggleButton::tickColourId",                                 0x1006502},
    ComponentColorIdMapping{"ToggleButton::tickDisabledColourId",                         0x1006503},
    ComponentColorIdMapping{"DirectoryContentsDisplayComponent::highlightColourId",       0x1000540},
    ComponentColorIdMapping{"DirectoryContentsDisplayComponent::textColourId",            0x1000541},
    ComponentColorIdMapping{"DirectoryContentsDisplayComponent::highlightedTextColourId", 0x1000542},
    ComponentColorIdMapping{"FileBrowserComponent::currentPathBoxBackgroundColourId",     0x1000640},
    ComponentColorIdMapping{"FileBrowserComponent::currentPathBoxTextColourId",           0x1000641},
    ComponentColorIdMapping{"FileBrowserComponent::currentPathBoxArrowColourId",          0x1000642},
    ComponentColorIdMapping{"FileBrowserComponent::filenameBoxBackgroundColourId",        0x1000643},
    ComponentColorIdMapping{"FileBrowserComponent::filenameBoxTextColourId",              0x1000644},
    ComponentColorIdMapping{"FileChooserDialogBox::titleTextColourId",                    0x1000850},
    ComponentColorIdMapping{"FileSearchPathListComponent::backgroundColourId",            0x1004100},
    ComponentColorIdMapping{"CaretComponent::caretColourId",                              0x1000204},
    ComponentColorIdMapping{"GroupComponent::outlineColourId",                            0x1005400},
    ComponentColorIdMapping{"GroupComponent::textColourId",                               0x1005410},
    ComponentColorIdMapping{"ScrollBar::backgroundColourId",                              0x1000300},
    ComponentColorIdMapping{"ScrollBar::thumbColourId",                                   0x1000400},
    ComponentColorIdMapping{"ScrollBar::trackColourId",                                   0x1000401},
    ComponentColorIdMapping{"SidePanel::backgroundColour",                                0x100f001},
    ComponentColorIdMapping{"SidePanel::titleTextColour",                                 0x100f002},
    ComponentColorIdMapping{"SidePanel::shadowBaseColour",                                0x100f003},
    ComponentColorIdMapping{"SidePanel::dismissButtonNormalColour",                       0x100f004},
    ComponentColorIdMapping{"SidePanel::dismissButtonOverColour",                         0x100f005},
    ComponentColorIdMapping{"SidePanel::dismissButtonDownColour",                         0x100f006},
    ComponentColorIdMapping{"TabbedButtonBar::tabOutlineColourId",                        0x1005812},
    ComponentColorIdMapping{"TabbedButtonBar::tabTextColourId",                           0x1005813},
    ComponentColorIdMapping{"TabbedButtonBar::frontOutlineColourId",                      0x1005814},
    ComponentColorIdMapping{"TabbedButtonBar::frontTextColourId",                         0x1005815},
    ComponentColorIdMapping{"TabbedComponent::backgroundColourId",                        0x1005800},
    ComponentColorIdMapping{"TabbedComponent::outlineColourId",                           0x1005801},
    ComponentColorIdMapping{"PopupMenu::backgroundColourId",                              0x1000700},
    ComponentColorIdMapping{"PopupMenu::textColourId",                                    0x1000600},
    ComponentColorIdMapping{"PopupMenu::headerTextColourId",                              0x1000601},
    ComponentColorIdMapping{"PopupMenu::highlightedBackgroundColourId",                   0x1000900},
    ComponentColorIdMapping{"PopupMenu::highlightedTextColourId",                         0x1000800},
    ComponentColorIdMapping{"BubbleComponent::backgroundColourId",                        0x1000af0},
    ComponentColorIdMapping{"BubbleComponent::outlineColourId",                           0x1000af1},
    ComponentColorIdMapping{"LassoComponent::lassoFillColourId",                          0x1000440},
    ComponentColorIdMapping{"LassoComponent::lassoOutlineColourId",                       0x1000441},
    ComponentColorIdMapping{"BooleanPropertyComponent::backgroundColourId",               0x100e801},
    ComponentColorIdMapping{"BooleanPropertyComponent::outlineColourId",                  0x100e803},
    ComponentColorIdMapping{"PropertyComponent::backgroundColourId",                      0x1008300},
    ComponentColorIdMapping{"PropertyComponent::labelTextColourId",                       0x1008301},
    ComponentColorIdMapping{"TextPropertyComponent::backgroundColourId",                  0x100e401},
    ComponentColorIdMapping{"TextPropertyComponent::textColourId",                        0x100e402},
    ComponentColorIdMapping{"TextPropertyComponent::outlineColourId",                     0x100e403},
    ComponentColorIdMapping{"ComboBox::backgroundColourId",                               0x1000b00},
    ComponentColorIdMapping{"ComboBox::textColourId",                                     0x1000a00},
    ComponentColorIdMapping{"ComboBox::outlineColourId",                                  0x1000c00},
    ComponentColorIdMapping{"ComboBox::buttonColourId",                                   0x1000d00},
    ComponentColorIdMapping{"ComboBox::arrowColourId",                                    0x1000e00},
    ComponentColorIdMapping{"ComboBox::focusedOutlineColourId",                           0x1000f00},
    ComponentColorIdMapping{"Label::backgroundColourId",                                  0x1000280},
    ComponentColorIdMapping{"Label::textColourId",                                        0x1000281},
    ComponentColorIdMapping{"Label::outlineColourId",                                     0x1000282},
    ComponentColorIdMapping{"Label::backgroundWhenEditingColourId",                       0x1000283},
    ComponentColorIdMapping{"Label::textWhenEditingColourId",                             0x1000284},
    ComponentColorIdMapping{"Label::outlineWhenEditingColourId",                          0x1000285},
    ComponentColorIdMapping{"ListBox::backgroundColourId",                                0x1002800},
    ComponentColorIdMapping{"ListBox::outlineColourId",                                   0x1002810},
    ComponentColorIdMapping{"ListBox::textColourId",                                      0x1002820},
    ComponentColorIdMapping{"ProgressBar::backgroundColourId",                            0x1001900},
    ComponentColorIdMapping{"ProgressBar::foregroundColourId",                            0x1001a00},
    ComponentColorIdMapping{"Slider::backgroundColourId",                                 0x1001200},
    ComponentColorIdMapping{"Slider::thumbColourId",                                      0x1001300},
    ComponentColorIdMapping{"Slider::trackColourId",                                      0x1001310},
    ComponentColorIdMapping{"Slider::rotarySliderFillColourId",                           0x1001311},
    ComponentColorIdMapping{"Slider::rotarySliderOutlineColourId",                        0x1001312},
    ComponentColorIdMapping{"Slider::textBoxTextColourId",                                0x1001400},
    ComponentColorIdMapping{"Slider::textBoxBackgroundColourId",                          0x1001500},
    ComponentColorIdMapping{"Slider::textBoxHighlightColourId",                           0x1001600},
    ComponentColorIdMapping{"Slider::textBoxOutlineColourId",                             0x1001700},
    ComponentColorIdMapping{"TableHeaderComponent::textColourId",                         0x1003800},
    ComponentColorIdMapping{"TableHeaderComponent::backgroundColourId",                   0x1003810},
    ComponentColorIdMapping{"TableHeaderComponent::outlineColourId",                      0x1003820},
    ComponentColorIdMapping{"TableHeaderComponent::highlightColourId",                    0x1003830},
    ComponentColorIdMapping{"TextEditor::backgroundColourId",                             0x1000200},
    ComponentColorIdMapping{"TextEditor::textColourId",                                   0x1000201},
    ComponentColorIdMapping{"TextEditor::highlightColourId",                              0x1000202},
    ComponentColorIdMapping{"TextEditor::highlightedTextColourId",                        0x1000203},
    ComponentColorIdMapping{"TextEditor::outlineColourId",                                0x1000205},
    ComponentColorIdMapping{"TextEditor::focusedOutlineColourId",                         0x1000206},
    ComponentColorIdMapping{"TextEditor::shadowColourId",                                 0x1000207},
    ComponentColorIdMapping{"Toolbar::backgroundColourId",                                0x1003200},
    ComponentColorIdMapping{"Toolbar::separatorColourId",                                 0x1003210},
    ComponentColorIdMapping{"Toolbar::buttonMouseOverBackgroundColourId",                 0x1003220},
    ComponentColorIdMapping{"Toolbar::buttonMouseDownBackgroundColourId",                 0x1003230},
    ComponentColorIdMapping{"Toolbar::labelTextColourId",                                 0x1003240},
    ComponentColorIdMapping{"Toolbar::editingModeOutlineColourId",                        0x1003250},
    ComponentColorIdMapping{"TreeView::backgroundColourId",                               0x1000500},
    ComponentColorIdMapping{"TreeView::linesColourId",                                    0x1000501},
    ComponentColorIdMapping{"TreeView::dragAndDropIndicatorColourId",                     0x1000502},
    ComponentColorIdMapping{"TreeView::selectedItemBackgroundColourId",                   0x1000503},
    ComponentColorIdMapping{"TreeView::oddItemsColourId",                                 0x1000504},
    ComponentColorIdMapping{"TreeView::evenItemsColourId",                                0x1000505},
    ComponentColorIdMapping{"AlertWindow::backgroundColourId",                            0x1001800},
    ComponentColorIdMapping{"AlertWindow::textColourId",                                  0x1001810},
    ComponentColorIdMapping{"AlertWindow::outlineColourId",                               0x1001820},
    ComponentColorIdMapping{"DocumentWindow::textColourId",                               0x1005701},
    ComponentColorIdMapping{"ResizableWindow::backgroundColourId",                        0x1005700},
    ComponentColorIdMapping{"TooltipWindow::backgroundColourId",                          0x1001b00},
    ComponentColorIdMapping{"TooltipWindow::textColourId",                                0x1001c00},
    ComponentColorIdMapping{"TooltipWindow::outlineColourId",                             0x1001c10},
};

[[nodiscard]] auto componentColorIdToString(int id) -> juce::String
{
    auto const* found
        = std::ranges::find(componentColorIdMapping, id, &ComponentColorIdMapping::value);
    if (found == std::ranges::end(componentColorIdMapping)) {
        jassertfalse;
        return "???";
    }

    return found->name;
}

[[nodiscard]] auto componentColorIdFromString(juce::String const& str) -> int
{
    auto* found
        = std::ranges::find_if(componentColorIdMapping, [&str](ComponentColorIdMapping const& cm) {
        return juce::StringRef{cm.name} == str;
    });
    if (found == std::ranges::end(componentColorIdMapping)) {
        jassertfalse;
        return 0;
    }

    return found->value;
}

[[nodiscard]] auto schemeColorIdToString(juce::LookAndFeel_V4::ColourScheme::UIColour id)
    -> juce::String
{
    auto const* found = std::ranges::find(schemeColorIdMapping, id, &SchemeColorIdMapping::value);
    if (found == std::ranges::end(schemeColorIdMapping)) {
        jassertfalse;
        return "???";
    }

    return found->name;
}

[[nodiscard]] auto schemeColorIdFromString(juce::String const& str)
    -> juce::LookAndFeel_V4::ColourScheme::UIColour
{
    auto* found = std::ranges::find_if(schemeColorIdMapping, [&str](SchemeColorIdMapping const& cm) {
        return juce::StringRef{cm.name} == str;
    });
    if (found == std::ranges::end(schemeColorIdMapping)) {
        jassertfalse;
        return {};
    }

    return found->value;
}

} // namespace

auto getCurrentTheme(juce::LookAndFeel& lookAndFeel) -> Theme
{
    auto theme = Theme{};

    auto copyComponentId = [&theme, &lookAndFeel](int id) {
        if (lookAndFeel.isColourSpecified(id)) {
            theme.componentColors.push_back(Theme::ComponentColor{
                id,
                lookAndFeel.findColour(id),
            });
        }
    };
    std::ranges::for_each(componentColorIdMapping, copyComponentId, &ComponentColorIdMapping::value);

    if (auto* v4 = dynamic_cast<juce::LookAndFeel_V4*>(&lookAndFeel); v4 != nullptr) {
        using Id    = juce::LookAndFeel_V4::ColourScheme::UIColour;
        auto scheme = v4->getCurrentColourScheme();
        for (auto i{0}; i < Id::numColours; ++i) {
            auto const id = static_cast<Id>(i);
            theme.schemeColors.push_back(Theme::SchemeColor{
                id,
                scheme.getUIColour(id),
            });
        }
        v4->setColourScheme(scheme);
    }

    return theme;
}

auto makeTheme(juce::ValueTree const& tree) -> std::optional<Theme>
{
    if (tree.getType() != juce::StringRef{"Theme"}) {
        return std::nullopt;
    }

    auto theme = Theme{};
    for (auto const& child : tree) {
        if (child.getType() == juce::StringRef{"SchemeColor"}) {
            auto const id    = schemeColorIdFromString(child["id"].toString());
            auto const color = juce::Colour::fromString(child["color"].toString());
            theme.schemeColors.push_back(Theme::SchemeColor{id, color});
        } else if (child.getType() == juce::StringRef{"ComponentColor"}) {
            auto const id    = static_cast<int>(componentColorIdFromString(child["id"].toString()));
            auto const color = juce::Colour::fromString(child["color"].toString());
            theme.componentColors.push_back(Theme::ComponentColor{id, color});
        } else {
            return std::nullopt;
        }
    }

    return theme;
}

auto loadTheme(juce::File const& file) -> std::optional<Theme>
{
    if (not file.existsAsFile()) {
        return std::nullopt;
    }

    auto tree = loadValueTree(file, true);
    if (not tree.isValid()) {
        return std::nullopt;
    }

    return makeTheme(tree);
}

auto toValueTree(Theme const& theme) -> juce::ValueTree
{
    auto tree = juce::ValueTree{"Theme"};

    for (auto const& sc : theme.schemeColors) {
        auto child = juce::ValueTree{"SchemeColor"};
        child.setProperty("id", schemeColorIdToString(sc.id), nullptr);
        child.setProperty("color", sc.color.toString(), nullptr);
        tree.appendChild(child, nullptr);
    }

    for (auto const& cc : theme.componentColors) {
        auto child = juce::ValueTree{"ComponentColor"};
        child.setProperty("id", componentColorIdToString(cc.id), nullptr);
        child.setProperty("color", cc.color.toString(), nullptr);
        tree.appendChild(child, nullptr);
    }

    return tree;
}

auto apply(Theme const& theme, juce::LookAndFeel& lookAndFeel) -> void
{
    if (auto* v4 = dynamic_cast<juce::LookAndFeel_V4*>(&lookAndFeel); v4 != nullptr) {
        auto scheme = v4->getCurrentColourScheme();
        for (auto const& sc : theme.schemeColors) {
            scheme.setUIColour(sc.id, sc.color);
        }
        v4->setColourScheme(scheme);
    }

    for (auto const& cc : theme.componentColors) {
        lookAndFeel.setColour(cc.id, cc.color);
    }
}

} // namespace jml
