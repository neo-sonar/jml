ldoc = require("ldoc")
markdown = require("markdown")

local classes = {
  juce_core = {
    -- juce.Array_double.new(),
    juce.BigInteger.new(),
    juce.File.new(),
    juce.abstract.InputStream,
    juce.abstract.MemoryInputStream,
    juce.IPAddress.new(),
    juce.MemoryBlock.new(),
    juce.NormalisableRange_double.new(),
    juce.Random.new(),
    juce.Range_double.new(0.0, 1.0),
    juce.Result.ok(),
    juce.StatisticsAccumulator.new(),
    juce.abstract.OutputStream,
    juce.abstract.MemoryOutputStream,
    juce.String.new(),
    juce.StringArray.new(),
    juce.Uuid.new(),
    juce.RelativeTime.seconds(1.0),
    juce.Time.new(),
    juce.XmlElement.new("TAG"),
  },
  juce_events = {juce.Timer.new()},
  juce_audio_basics = {
    juce.MidiFile.new(),
    juce.MidiMessage.new(),
    juce.MidiMessageSequence.new(),
    juce.MidiRPNDetector.new(),
    juce.MidiRPNMessage.new(),
  },
  juce_data_structures = {juce.UndoManager.new(0, 0), juce.ValueTree.new()},
  juce_graphics = {
    juce.AffineTransform.new(),
    juce.Colour.new(0, 0, 0, 0),
    juce.ColourGradient.new(),
    juce.DropShadow.new(),
    juce.FillType.new(),
    juce.Font.new(12.0),
    juce.Image.new(),
    juce.Graphics.new(juce.Image.new()),
    juce.Line_double.new(),
    juce.Path.new(),
    juce.PixelARGB.new(),
    juce.Point_double.new(),
    juce.Rectangle_double.new(),
  },
  juce_gui_basics = {
    juce.abstract.Button,
    juce.Component.new(),
    juce.ComponentListener.new(),
    juce.ComboBox.new(juce.String.new("")),
    juce.Grid.new(),
    juce.Grid.Fr.new(1),
    juce.Grid.Px.new(1),
    juce.Grid.TrackInfo.new(),
    juce.GridItem.new(juce.Component.new()),
    juce.GridItem.Margin.new(),
    juce.GridItem.Property.new(),
    juce.GridItem.Span.new(1),
    juce.Label.new(juce.String.new(""), juce.String.new("")),
    juce.abstract.LookAndFeel,
    juce.LookAndFeel_V4.new(),
    juce.ImageComponent.new(juce.String.new("")),
    juce.Slider.new(),
    juce.ArrowButton.new(juce.String.new(""), 1.0, juce.Colours.black),
    juce.HyperlinkButton.new(),
    juce.TextButton.new(juce.String.new("")),
    juce.ToggleButton.new(juce.String.new("")),
    juce.TreeView.new(juce.String.new("")),
  },
  juce_gui_extra = {juce.CodeDocument.new()},
  juce_audio_processors = {juce.abstract.AudioProcessor},

}

local readme = io.open("../README.md", "w")
markdown.write_usertype(readme, classes)
readme:close()

ldoc.write_usertype_stubs("../out/lua", classes)
