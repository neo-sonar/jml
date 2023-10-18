doxygen = require("doxygen")

local function sortByKey(t)
  -- Collect the keys into an array
  local keys = {}
  for key in pairs(t) do
    table.insert(keys, key)
  end

  -- Sort the keys
  table.sort(keys)

  -- Create a new table with sorted keys
  local sorted = {}
  for _, key in ipairs(keys) do
    sorted[key] = t[key]
  end

  return sorted
end

local function startsWith(str, prefix)
  return string.sub(str, 1, string.len(prefix)) == prefix
end

local function parseType(obj)
  local meta = getmetatable(obj)
  local name = meta.__name
  local doc = {}

  i, j = string.find(name, "lua_juce")
  if i == nil or j == nil then
    doc["name"] = string.sub(meta.__name, 11) -- Remove "sol.juce::"
  else
    doc["name"] = string.sub(meta.__name, 18) -- Remove "sol.lua_juce::Lua"
  end
  assert(name ~= nil)

  doc["members"] = {}

  for key, value in pairs(meta) do
    if type(value) == "function" then
      table.insert(doc.members, key)
      -- for k, v in pairs(debug.getinfo(value)) do
      -- end
    end

  end

  table.sort(doc.members)
  return doc
end

local function formatTypeDocsAsMarkdownTable(doc)
  local str = string.format("## %s\n\n", doc.name)
  str = str .. string.format("| Name | Type | Description |\n")
  str = str .. string.format("| :--: | :--: | :---------: |\n")
  for i = 1, #doc.members do
    member = doc.members[i]
    local fmt = "| `%s` | %s | %s |\n"
    str = str .. string.format(fmt, member, "Function", "help")
  end
  return str
end

local function formatTypeDocsAsLuaSnippet(doc)
  local str = string.format("## %s\n\n", doc.name)
  str = str .. string.format("```lua\n")
  for i = 1, #doc.members do
    member = doc.members[i]
    if startsWith(member, "__") == false then
      str = str .. string.format("juce.%s.%s(...)\n", doc.name, member)
    end
  end
  str = str .. string.format("```\n\n")
  return str
end

local function parseTypeDocs(modules)
  modules = sortByKey(modules)

  local docs = {}
  local sortedModuleNames = {}

  for moduleName, moduleContent in pairs(modules) do
    local moduleDocs = {}
    local sortedEntityNames = {}
    for _, entity in pairs(moduleContent) do
      local doc = parseType(entity)
      moduleDocs[doc.name] = doc
      table.insert(sortedEntityNames, doc.name)
    end

    table.insert(sortedModuleNames, moduleName)
    table.sort(sortedEntityNames)
    docs[moduleName] = {sortedEntityNames, moduleDocs}
  end

  table.sort(sortedModuleNames)
  return docs, sortedModuleNames
end

local function writeTypesDocsAsLuaStubs(dir, modules)
  local docs, _ = parseTypeDocs(modules)
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
        if startsWith(member, "__") == false then
          local doxygen_member = nil
          for _, spec in pairs(doxygen_spec.members) do
            if spec.name:toStdString() == member then
              doxygen_member = spec
            end
          end

          if doxygen_member == nil then
            doxygen_member = {
              brief = member,
              detail = juce.String.new(""),
              is_static = true,
              parameter = {},
              return_type = nil,
            }
          end

          file:write(string.format("--- %s\n", doxygen_member.brief))
          if doxygen_member.detail ~= juce.String.new("") then
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
            if param.name ~= juce.String.new("") then
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

local function writeTypesDocsAsMarkdown(file, style, modules)
  local docs, sortedModuleNames = parseTypeDocs(modules)

  -- Write header
  file:write("# JML Documentation\n\n")

  -- Write TOC
  for i = 1, #sortedModuleNames do
    local moduleName = sortedModuleNames[i]
    local moduleDocs = docs[moduleName]
    file:write(string.format("- [%s](#%s)\n", moduleName, moduleName))
    for d = 1, #moduleDocs[1] do
      local name = moduleDocs[1][d]
      local entity = moduleDocs[2][name]
      local name = entity.name
      if name ~= nil then
        file:write(string.format("  - [%s](#%s)\n", name, name))
      end
    end
  end

  -- Wrie Content
  file:write("\n\n")
  for i = 1, #sortedModuleNames do
    local moduleName = sortedModuleNames[i]
    local moduleDocs = docs[moduleName]
    -- Header
    file:write(string.format("## %s\n\n", moduleName))

    -- Members
    for d = 1, #moduleDocs[1] do
      local name = moduleDocs[1][d]
      local doc = moduleDocs[2][name]
      if style == "table" then
        file:write(formatTypeDocsAsMarkdownTable(doc))
      else
        assert(style == "snippets")
        file:write(formatTypeDocsAsLuaSnippet(doc))
      end
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

local file = io.open("README.md", "w")
writeTypesDocsAsMarkdown(file, "snippets", classes)
file:close()

writeTypesDocsAsLuaStubs("out/src", classes)
