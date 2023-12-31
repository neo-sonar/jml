#include <lua_juce/lua_juce.hpp>

namespace lua_juce {

auto allModules(sol::state& lua) -> void
{
    auto table = lua["juce"].get_or_create<sol::table>();

    // juce_core
    juce_Array(table);
    juce_BigInteger(table);
    juce_File(table);
    juce_IPAddress(table);
    juce_InputStream(table);
    juce_Int(table);
    juce_MathConstants(table);
    juce_MemoryBlock(table);
    juce_MemoryInputStream(table);
    juce_MemoryOutputStream(table);
    juce_NormalisableRange(table);
    juce_OutputStream(table);
    juce_Random(table);
    juce_Range(table);
    juce_Result(table);
    juce_StatisticsAccumulator(table);
    juce_String(table);
    juce_StringRef(table);
    juce_StringArray(table);
    juce_Uuid(table);
    juce_PerformanceCounter(table);
    juce_RelativeTime(table);
    juce_Time(table);
    juce_XmlDocument(table);
    juce_XmlElement(table);

    // juce_audio_basics
    juce_AudioPlayHead(table);
    juce_MidiFile(table);
    juce_MidiMessage(table);
    juce_MidiMessageSequence(table);
    juce_MidiRPNDetector(table);
    juce_MidiRPNMessage(table);

    // juce_data_structures
    juce_UndoableAction(table);
    juce_UndoManager(table);
    juce_ValueTree(table);

    // juce_events
    juce_Timer(table);

    // juce_graphics
    juce_AffineTransform(table);
    juce_Colour(table);
    juce_ColourGradient(table);
    juce_Colours(table);
    juce_DropShadow(table);
    juce_FillType(table);
    juce_Font(table);
    juce_Graphics(table);
    juce_Image(table);
    juce_ImageCache(table);
    juce_Justification(table);
    juce_Line(table);
    juce_Path(table);
    juce_PixelARGB(table);
    juce_Point(table);
    juce_Rectangle(table);

    // juce_gui_basics
    juce_ArrowButton(table);
    juce_Button(table);
    juce_ComboBox(table);
    juce_ImageComponent(table);
    juce_Component(table);
    juce_ComponentListener(table);
    juce_Grid(table);
    juce_HyperlinkButton(table);
    juce_ImageButton(table);
    juce_Label(table);
    juce_ListBox(table);
    juce_ListBoxModel(table);
    juce_LookAndFeel(table);
    juce_LookAndFeel_V4(table);
    juce_MouseEvent(table);
    juce_ShapeButton(table);
    juce_Slider(table);
    juce_TextButton(table);
    juce_TextEditor(table);
    juce_ToggleButton(table);
    juce_TreeView(table);

    // juce_gui_extra
    juce_CodeDocument(table);
    // juce_CodeTokeniser(table);
    // juce_CPlusPlusCodeTokeniser(table);
    // juce_LuaTokeniser(table);
    // juce_XmlTokeniser(table);

    // juce_audio_processors
    juce_AudioProcessor(table);

    // xtensions
    juce_LuaComponent(table);
    juce_LuaLookAndFeel_V4(table);
    juce_LuaTimer(table);
}

} // namespace lua_juce
