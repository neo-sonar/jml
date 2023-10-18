doxygen = require("doxygen")
sol2 = require("sol2")

local function starts_with(str, prefix)
  return string.sub(str, 1, string.len(prefix)) == prefix
end

local function format_usertype_docs_as_lua_stubs(doc)
  local str = string.format("## %s\n\n", doc.name)
  str = str .. string.format("```lua\n")
  for i = 1, #doc.members do
    member = doc.members[i]
    if starts_with(member, "__") == false then
      str = str .. string.format("juce.%s.%s(...)\n", doc.name, member)
    end
  end
  str = str .. string.format("```\n\n")
  return str
end

local function write_usertype_docs_as_lua_stubs(dir, modules)
  local docs, _ = sol2.parse_juce_types(modules)
  for module_name, juce_module in pairs(docs) do
    for entity_name, entity in pairs(juce_module[2]) do
      local doxygen_spec = doxygen.parse_xml(entity_name)

      -- Create lua file
      local file = io.open(dir .. "/" .. entity_name .. ".lua", "w")
      if file == nil then
        print("error:", entity_name)
      end

      -- Write ldoc headers
      local ns = "juce"

      file:write(string.format("--- %s\n", doxygen_spec.brief))
      file:write(string.format("-- @classmod %s.%s\n\n", ns, entity_name))
      file:write(string.format("local %s = {}\n\n", entity_name))

      -- For each member in entity
      for _, member in pairs(entity.members) do
        -- Skip special functions
        if starts_with(member, "__") == false then
          local doxygen_member = nil
          for _, spec in pairs(doxygen_spec.members) do
            if spec.name == member then
              doxygen_member = spec
            end
          end

          if doxygen_member == nil then
            doxygen_member = {
              brief = member,
              detail = "",
              is_static = true,
              parameter = {},
              return_type = nil,
            }
          end

          file:write(string.format("--- %s\n", doxygen_member.brief))
          if doxygen_member.detail ~= "" then
            file:write(string.format("-- %s\n", doxygen_member.detail))
          end

          local seperator = nil
          if doxygen_member.is_static then
            seperator = "."
            file:write(string.format("-- @static\n"))
          else
            seperator = ":"
          end

          for i = 1, #doxygen_member.parameter do
            local param = doxygen_member.parameter[i]
            if param.name ~= "" then
              file:write(string.format("-- @param %s\n", param.name))
            end
          end

          if doxygen_member.return_type then
            file:write(string.format("-- @treturn %s\n",
                                     doxygen_member.return_type))
          end

          if #doxygen_member.parameter == 0 then
            local fmt = "function %s%s%s() end\n\n"
            file:write(string.format(fmt, entity_name, seperator, member))
          else
            local fmt = "function %s%s%s(...) end\n\n"
            file:write(string.format(fmt, entity_name, seperator, member))
          end
        end
      end

      file:write(string.format("return %s\n", entity_name))
      file:close()
    end
  end
end

local function write_usertype_docs_as_markdown(file, modules)
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
    juce.BigInteger.new(),
    juce.File.new(),
    juce.IPAddress.new(),
    juce.MemoryBlock.new(),
    -- juce.NormalisableRangeDouble.new(),
    juce.Random.new(),
    -- juce.RangeDouble.new(0.0, 1.0),
    juce.Result.ok(),
    -- juce.StatisticsAccumulatorDouble.new(),
    juce.String.new(),
    juce.StringArray.new(),
    juce.Uuid.new(),
    juce.RelativeTime.seconds(1.0),
    juce.Time.new(),
    juce.XmlElement.new("TAG"),
  },
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
    juce.Path.new(),
  },
  juce_gui_basics = {
    juce.ComponentListener.new(),
    juce.ComboBox.new(juce.String.new("")),
    juce.Label.new(juce.String.new(""), juce.String.new("")),
    -- juce.LookAndFeel_V4.new(),
    juce.ImageComponent.new(juce.String.new("")),
    juce.Slider.new(),
    juce.ArrowButton.new(juce.String.new(""), 1.0, juce.Colours.black),
    juce.HyperlinkButton.new(),
    juce.TextButton.new(juce.String.new("")),
    juce.ToggleButton.new(juce.String.new("")),
    juce.TreeView.new(juce.String.new("")),
  },
  juce_gui_extra = {juce.CodeDocument.new()},
}

local readme = io.open("README.md", "w")
write_usertype_docs_as_markdown(readme, classes)
readme:close()

write_usertype_docs_as_lua_stubs("out/src", classes)
