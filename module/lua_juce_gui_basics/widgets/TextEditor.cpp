namespace lua_juce {

namespace {
auto moveCaretToEnd1(juce::TextEditor* te) -> void { return te->moveCaretToEnd(); }
auto moveCaretToEnd2(juce::TextEditor* te, bool selecting) -> bool { return te->moveCaretToEnd(selecting); }
auto getTextIndexAt1(juce::TextEditor const* te, int x, int y) -> int { return te->getTextIndexAt(x, y); }
auto getTextIndexAt2(juce::TextEditor const* te, juce::Point<int> point) -> int { return te->getTextIndexAt(point); }
} // namespace

auto juce_TextEditor(sol::table& state) -> void
{
    // clang-format off
    auto editor = state.new_usertype<juce::TextEditor>("TextEditor",
        sol::factories(
            [](juce::String const& name) { return std::make_unique<juce::TextEditor>(name); },
            [](juce::String const& name, int flags) { return std::make_unique<juce::TextEditor>(name, static_cast<juce::juce_wchar>(flags)); }
        ),
        sol::base_classes,
        sol::bases<
            juce::TextInputTarget,
            juce::MouseListener,
            juce::Component,
            juce::TooltipClient,
            juce::SettableTooltipClient
        >()
    );
    // clang-format on

    editor["setMultiLine"]                           = LUA_JUCE_C_CALL(&juce::TextEditor::setMultiLine);
    editor["isMultiLine"]                            = LUA_JUCE_C_CALL(&juce::TextEditor::isMultiLine);
    editor["setReturnKeyStartsNewLine"]              = LUA_JUCE_C_CALL(&juce::TextEditor::setReturnKeyStartsNewLine);
    editor["getReturnKeyStartsNewLine"]              = LUA_JUCE_C_CALL(&juce::TextEditor::getReturnKeyStartsNewLine);
    editor["setTabKeyUsedAsCharacter"]               = LUA_JUCE_C_CALL(&juce::TextEditor::setTabKeyUsedAsCharacter);
    editor["isTabKeyUsedAsCharacter"]                = LUA_JUCE_C_CALL(&juce::TextEditor::isTabKeyUsedAsCharacter);
    editor["setEscapeAndReturnKeysConsumed"]         = LUA_JUCE_C_CALL(&juce::TextEditor::setEscapeAndReturnKeysConsumed);
    editor["setReadOnly"]                            = LUA_JUCE_C_CALL(&juce::TextEditor::setReadOnly);
    editor["isReadOnly"]                             = LUA_JUCE_C_CALL(&juce::TextEditor::isReadOnly);
    editor["setCaretVisible"]                        = LUA_JUCE_C_CALL(&juce::TextEditor::setCaretVisible);
    editor["isCaretVisible"]                         = LUA_JUCE_C_CALL(&juce::TextEditor::isCaretVisible);
    editor["setScrollbarsShown"]                     = LUA_JUCE_C_CALL(&juce::TextEditor::setScrollbarsShown);
    editor["areScrollbarsShown"]                     = LUA_JUCE_C_CALL(&juce::TextEditor::areScrollbarsShown);
    editor["setPasswordCharacter"]                   = LUA_JUCE_C_CALL(&juce::TextEditor::setPasswordCharacter);
    editor["getPasswordCharacter"]                   = LUA_JUCE_C_CALL(&juce::TextEditor::getPasswordCharacter);
    editor["setPopupMenuEnabled"]                    = LUA_JUCE_C_CALL(&juce::TextEditor::setPopupMenuEnabled);
    editor["isPopupMenuEnabled"]                     = LUA_JUCE_C_CALL(&juce::TextEditor::isPopupMenuEnabled);
    editor["isPopupMenuCurrentlyActive"]             = LUA_JUCE_C_CALL(&juce::TextEditor::isPopupMenuCurrentlyActive);
    editor["setFont"]                                = LUA_JUCE_C_CALL(&juce::TextEditor::setFont);
    editor["applyFontToAllText"]                     = LUA_JUCE_C_CALL(&juce::TextEditor::applyFontToAllText);
    editor["getFont"]                                = LUA_JUCE_C_CALL(&juce::TextEditor::getFont);
    editor["applyColourToAllText"]                   = LUA_JUCE_C_CALL(&juce::TextEditor::applyColourToAllText);
    editor["setWhitespaceUnderlined"]                = LUA_JUCE_C_CALL(&juce::TextEditor::setWhitespaceUnderlined);
    editor["isWhitespaceUnderlined"]                 = LUA_JUCE_C_CALL(&juce::TextEditor::isWhitespaceUnderlined);
    editor["setSelectAllWhenFocused"]                = LUA_JUCE_C_CALL(&juce::TextEditor::setSelectAllWhenFocused);
    editor["setTextToShowWhenEmpty"]                 = LUA_JUCE_C_CALL(&juce::TextEditor::setTextToShowWhenEmpty);
    editor["getTextToShowWhenEmpty"]                 = LUA_JUCE_C_CALL(&juce::TextEditor::getTextToShowWhenEmpty);
    editor["setScrollBarThickness"]                  = LUA_JUCE_C_CALL(&juce::TextEditor::setScrollBarThickness);
    editor["addListener"]                            = LUA_JUCE_C_CALL(&juce::TextEditor::addListener);
    editor["removeListener"]                         = LUA_JUCE_C_CALL(&juce::TextEditor::removeListener);
    editor["getText"]                                = LUA_JUCE_C_CALL(&juce::TextEditor::getText);
    editor["getTextInRange"]                         = LUA_JUCE_C_CALL(&juce::TextEditor::getTextInRange);
    editor["isEmpty"]                                = LUA_JUCE_C_CALL(&juce::TextEditor::isEmpty);
    editor["setText"]                                = LUA_JUCE_C_CALL(&juce::TextEditor::setText);
    editor["getTextValue"]                           = LUA_JUCE_C_CALL(&juce::TextEditor::getTextValue);
    editor["insertTextAtCaret"]                      = LUA_JUCE_C_CALL(&juce::TextEditor::insertTextAtCaret);
    editor["clear"]                                  = LUA_JUCE_C_CALL(&juce::TextEditor::clear);
    editor["cut"]                                    = LUA_JUCE_C_CALL(&juce::TextEditor::cut);
    editor["copy"]                                   = LUA_JUCE_C_CALL(&juce::TextEditor::copy);
    editor["paste"]                                  = LUA_JUCE_C_CALL(&juce::TextEditor::paste);
    editor["getCaretPosition"]                       = LUA_JUCE_C_CALL(&juce::TextEditor::getCaretPosition);
    editor["setCaretPosition"]                       = LUA_JUCE_C_CALL(&juce::TextEditor::setCaretPosition);
    editor["scrollEditorToPositionCaret"]            = LUA_JUCE_C_CALL(&juce::TextEditor::scrollEditorToPositionCaret);
    editor["getCaretRectangleForCharIndex"]          = LUA_JUCE_C_CALL(&juce::TextEditor::getCaretRectangleForCharIndex);
    editor["setHighlightedRegion"]                   = LUA_JUCE_C_CALL(&juce::TextEditor::setHighlightedRegion);
    editor["getHighlightedRegion"]                   = LUA_JUCE_C_CALL(&juce::TextEditor::getHighlightedRegion);
    editor["getHighlightedText"]                     = LUA_JUCE_C_CALL(&juce::TextEditor::getHighlightedText);
    editor["getCharIndexForPoint"]                   = LUA_JUCE_C_CALL(&juce::TextEditor::getCharIndexForPoint);
    editor["getTotalNumChars"]                       = LUA_JUCE_C_CALL(&juce::TextEditor::getTotalNumChars);
    editor["getTextWidth"]                           = LUA_JUCE_C_CALL(&juce::TextEditor::getTextWidth);
    editor["getTextHeight"]                          = LUA_JUCE_C_CALL(&juce::TextEditor::getTextHeight);
    editor["setIndents"]                             = LUA_JUCE_C_CALL(&juce::TextEditor::setIndents);
    editor["getTopIndent"]                           = LUA_JUCE_C_CALL(&juce::TextEditor::getTopIndent);
    editor["getLeftIndent"]                          = LUA_JUCE_C_CALL(&juce::TextEditor::getLeftIndent);
    editor["setBorder"]                              = LUA_JUCE_C_CALL(&juce::TextEditor::setBorder);
    editor["getBorder"]                              = LUA_JUCE_C_CALL(&juce::TextEditor::getBorder);
    editor["setScrollToShowCursor"]                  = LUA_JUCE_C_CALL(&juce::TextEditor::setScrollToShowCursor);
    editor["setJustification"]                       = LUA_JUCE_C_CALL(&juce::TextEditor::setJustification);
    editor["getJustificationType"]                   = LUA_JUCE_C_CALL(&juce::TextEditor::getJustificationType);
    editor["setLineSpacing"]                         = LUA_JUCE_C_CALL(&juce::TextEditor::setLineSpacing);
    editor["getLineSpacing"]                         = LUA_JUCE_C_CALL(&juce::TextEditor::getLineSpacing);
    editor["getTextBounds"]                          = LUA_JUCE_C_CALL(&juce::TextEditor::getTextBounds);
    editor["moveCaretLeft"]                          = LUA_JUCE_C_CALL(&juce::TextEditor::moveCaretLeft);
    editor["moveCaretRight"]                         = LUA_JUCE_C_CALL(&juce::TextEditor::moveCaretRight);
    editor["moveCaretRight"]                         = LUA_JUCE_C_CALL(&juce::TextEditor::moveCaretRight);
    editor["moveCaretUp"]                            = LUA_JUCE_C_CALL(&juce::TextEditor::moveCaretUp);
    editor["moveCaretDown"]                          = LUA_JUCE_C_CALL(&juce::TextEditor::moveCaretDown);
    editor["pageUp"]                                 = LUA_JUCE_C_CALL(&juce::TextEditor::pageUp);
    editor["pageDown"]                               = LUA_JUCE_C_CALL(&juce::TextEditor::pageDown);
    editor["scrollDown"]                             = LUA_JUCE_C_CALL(&juce::TextEditor::scrollDown);
    editor["scrollUp"]                               = LUA_JUCE_C_CALL(&juce::TextEditor::scrollUp);
    editor["moveCaretToTop"]                         = LUA_JUCE_C_CALL(&juce::TextEditor::moveCaretToTop);
    editor["moveCaretToStartOfLine"]                 = LUA_JUCE_C_CALL(&juce::TextEditor::moveCaretToStartOfLine);
    editor["moveCaretToEndOfLine"]                   = LUA_JUCE_C_CALL(&juce::TextEditor::moveCaretToEndOfLine);
    editor["deleteBackwards"]                        = LUA_JUCE_C_CALL(&juce::TextEditor::deleteBackwards);
    editor["deleteForwards"]                         = LUA_JUCE_C_CALL(&juce::TextEditor::deleteForwards);
    editor["copyToClipboard"]                        = LUA_JUCE_C_CALL(&juce::TextEditor::copyToClipboard);
    editor["cutToClipboard"]                         = LUA_JUCE_C_CALL(&juce::TextEditor::cutToClipboard);
    editor["pasteFromClipboard"]                     = LUA_JUCE_C_CALL(&juce::TextEditor::pasteFromClipboard);
    editor["selectAll"]                              = LUA_JUCE_C_CALL(&juce::TextEditor::selectAll);
    editor["undo"]                                   = LUA_JUCE_C_CALL(&juce::TextEditor::undo);
    editor["redo"]                                   = LUA_JUCE_C_CALL(&juce::TextEditor::redo);
    editor["addPopupMenuItems"]                      = LUA_JUCE_C_CALL(&juce::TextEditor::addPopupMenuItems);
    editor["performPopupMenuAction"]                 = LUA_JUCE_C_CALL(&juce::TextEditor::performPopupMenuAction);
    editor["setInputFilter"]                         = LUA_JUCE_C_CALL(&juce::TextEditor::setInputFilter);
    editor["getInputFilter"]                         = LUA_JUCE_C_CALL(&juce::TextEditor::getInputFilter);
    editor["setInputRestrictions"]                   = LUA_JUCE_C_CALL(&juce::TextEditor::setInputRestrictions);
    editor["setKeyboardType"]                        = LUA_JUCE_C_CALL(&juce::TextEditor::setKeyboardType);
    editor["setClicksOutsideDismissVirtualKeyboard"] = LUA_JUCE_C_CALL(&juce::TextEditor::setClicksOutsideDismissVirtualKeyboard);
    editor["getClicksOutsideDismissVirtualKeyboard"] = LUA_JUCE_C_CALL(&juce::TextEditor::getClicksOutsideDismissVirtualKeyboard);
    editor["moveCaretToEnd"]                         = sol::c_call<LUA_JUCE_WRAP(moveCaretToEnd1), LUA_JUCE_WRAP(moveCaretToEnd2)>;
    editor["getTextIndexAt"]                         = sol::c_call<LUA_JUCE_WRAP(getTextIndexAt1), LUA_JUCE_WRAP(getTextIndexAt2)>;
}

} // namespace lua_juce
