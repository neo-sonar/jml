doxygen = require("doxygen")
sol2 = require("sol2")
strings = require("strings")
tables = require("tables")

local function format_usertype_docs_as_lua_stubs(doc)
  local ignored_functions = {
    ["__gc"] = true,
    ["__pairs"] = true,
    ["__newindex"] = true,
    ["__index"] = true,
  }

  local str = string.format("## %s\n\n", doc.name)
  str = str .. string.format("```lua\n")
  for i = 1, #doc.members do
    func = doc.members[i]
    if ignored_functions[func] == nil then
      str = str .. string.format("juce.%s.%s(...)\n", doc.name, func)
    end
  end
  str = str .. string.format("```\n\n")
  return str
end

local function write_usertype_as_lua_stubs(dir, modules)
  local docs, _ = sol2.parse_juce_types(modules)

  for module_name, juce_module in pairs(docs) do
    for class_name, class in pairs(juce_module[2]) do
      local doxygen_spec = doxygen.parse_xml(class_name)
      if doxygen_spec == nil then
        doxygen_spec = {brief = class_name, members = {}, variables = {}}
      end

      -- Create lua file
      local path = string.format("%s/%s.lua", dir, class_name)
      local file = io.open(path, "w")
      if file == nil then
        print("error:", class_name)
      end

      -- Write ldoc headers
      local namespace = "juce"
      file:write(string.format("--- %s\n", doxygen_spec.brief))
      file:write(string.format("-- @classmod %s.%s\n\n", namespace, class_name))
      file:write(string.format("local %s = {}\n\n", class_name))

      -- For each variable in class
      local members_variables = {}
      for _, variable in pairs(doxygen_spec.variables) do
        for _, member_name in pairs(class.members) do
          if member_name == variable.name then
            members_variables[member_name] = true
          end
        end
      end

      if tables.length(members_variables) > 0 then
        file:write("--- Public variables of the class\n")
        file:write("-- @table Variables\n")
        for name, var in pairs(members_variables) do
          file:write(string.format("-- @field %s\n", name))
        end
        file:write("\n\n")
      end

      -- For each member in class
      for _, member in pairs(class.members) do
        -- Skip function body for variables
        local skip = false
        if members_variables[member] then
          skip = true
        end

        -- Skip special functions
        if not skip then
          local member_dox = nil
          -- Match doxygen to sol names
          for _, spec in pairs(doxygen_spec.members) do
            if spec.name == member then
              member_dox = spec
            end
          end

          -- Fallback if doxygen not available
          if member_dox == nil then
            member_dox = {
              brief = member,
              detail = "",
              is_static = true,
              parameter = {},
              return_type = nil,
            }
          end

          -- Brief
          local brief = strings.break_into_lines(member_dox.brief, 70, "-- ")
          file:write(string.format("-%s\n", brief))

          -- Detail
          if member_dox.detail ~= "" then
            local detail =
              strings.break_into_lines(member_dox.detail, 70, "-- ")
            file:write(string.format("--\n%s\n--\n", detail))
          end

          -- Static or member function
          local seperator = nil
          if member_dox.is_static then
            seperator = "."
            file:write(string.format("-- @static\n"))
          else
            seperator = ":"
          end

          -- Function parameter
          for i = 1, #member_dox.parameter do
            local param = member_dox.parameter[i]
            if param.name ~= "" then
              file:write(string.format("-- @param %s\n", param.name))
            end
          end

          -- Function return type
          if member_dox.return_type then
            local name_only = member_dox.return_type:gsub("<[ %w_]+>", "")
            file:write(string.format("-- @treturn %s\n", name_only))
          end

          -- Function definition
          if #member_dox.parameter == 0 then
            local fmt = "function %s%s%s() end\n\n"
            file:write(string.format(fmt, class_name, seperator, member))
          else
            local fmt = "function %s%s%s(...) end\n\n"
            file:write(string.format(fmt, class_name, seperator, member))
          end
        end
      end

      -- Return module/class
      file:write(string.format("return %s\n", class_name))
      file:close()
    end
  end

  -- --- Represents a colour, also including a transparency value.
  -- -- @module juce

  -- --- Constant colors
  -- -- @table Colours
  -- -- @field black HTML black
  -- Colours = {
  --   black = ""
  -- }

  local colours = io.open(string.format("%s/Colours.lua", dir), "w")
  colours:write([[--- JUCE framework
-- @module juce

--- Contains a set of predefined named colours
-- @table Colours
]])

  for name, colour in pairs(juce.Colours) do
    colours:write(string.format("-- @field %s 0x%s\n", name, colour))
  end
  colours:write("Colours = {\n")
  for name, colour in pairs(juce.Colours) do
    colours:write(string.format("\t%-20s = 0x%s\n", name, colour))
  end
  colours:write("}\n\n")

end

local function write_usertype_as_markdown(file, modules)
  local docs, sorted_modules_names = sol2.parse_juce_types(modules)

  -- Write header
  file:write("# JML Documentation\n\n")

  -- Write TOC
  for i = 1, #sorted_modules_names do
    local module_name = sorted_modules_names[i]
    local module_docs = docs[module_name]
    file:write(string.format("- [%s](#%s)\n", module_name, module_name))
    for d = 1, #module_docs[1] do
      local name = module_docs[1][d]
      local entity = module_docs[2][name]
      local name = entity.name
      if name ~= nil then
        file:write(string.format("  - [%s](#%s)\n", name, name))
      end
    end
  end

  -- Wrie Content
  file:write("\n\n")
  for i = 1, #sorted_modules_names do
    local module_name = sorted_modules_names[i]
    local module_docs = docs[module_name]

    -- Header
    file:write(string.format("## %s\n\n", module_name))

    -- Members
    for d = 1, #module_docs[1] do
      local name = module_docs[1][d]
      local doc = module_docs[2][name]
      file:write(format_usertype_docs_as_lua_stubs(doc))
    end
  end
end

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
  juce_gui_extra = {
    juce.CodeDocument.new(),
    juce.abstract.CodeTokeniser,
    juce.CPlusPlusCodeTokeniser.new(),
    juce.LuaTokeniser.new(),
    juce.XmlTokeniser.new(),
  },
  juce_audio_processors = {juce.abstract.AudioProcessor},

}

local readme = io.open("README.md", "w")
write_usertype_as_markdown(readme, classes)
readme:close()

write_usertype_as_lua_stubs("out/lua", classes)
