local function startsWith(str, prefix)
  return string.sub(str, 1, string.len(prefix)) == prefix
end

local function parseType(obj)
  local meta = getmetatable(obj)

  local doc = {}
  doc["name"] = string.sub(meta.__name, 11) -- Remove "sol.juce::"
  doc["members"] = {}

  for key, value in pairs(meta) do
    if type(value) == "function" then
      table.insert(doc.members, key)
      -- for k, v in pairs(debug.getinfo(value)) do
      --   print(k, v)
      -- end
    end

  end

  return doc
end

local function formatTypeDocsAsMarkdownTable(doc)
  local str = string.format("## %s\n\n", doc.name)
  str = str .. string.format("| Name | Type | Description |\n")
  str = str .. string.format("| :--: | :--: | :---------: |\n")
  for _, value in pairs(doc.members) do
    local fmt = "| `%s` | %s | %s |\n"
    str = str .. string.format(fmt, value, "Function", "help")
  end
  return str
end

local function formatTypeDocsAsLuaSnippet(doc)
  local str = string.format("## %s\n\n", doc.name)
  str = str .. string.format("```lua\n")
  for _, member in pairs(doc.members) do
    if startsWith(member, "__") == false then
      str = str .. string.format("juce.%s.%s()\n", doc.name, member)
    end
  end
  str = str .. string.format("```\n")
  return str
end

local function writeTypesDocsAsMarkdown(file, style, modules)
  -- Parse types
  local docs = {}
  for modName, mod in pairs(modules) do
    local modDocs = {}
    for _, value in pairs(mod) do
      local doc = parseType(value)
      modDocs[doc.name] = doc
    end
    docs[modName] = modDocs
  end

  table.sort(docs)

  -- Write header
  file:write("# JML Documentation\n\n")

  -- Write TOC
  for modName, modDocs in pairs(docs) do
    file:write(string.format("- [%s](#%s)\n", modName, modName))
    for _, doc in pairs(modDocs) do
      file:write(string.format("\t- [%s](#%s)\n", doc.name, doc.name))
    end
  end

  -- Wrie Content
  file:write("\n\n")
  for modName, modDocs in pairs(docs) do
    -- Header
    file:write(string.format("## %s\n\n", modName))

    -- Members
    for _, doc in pairs(modDocs) do
      if style == "table" then
        file:write(formatTypeDocsAsMarkdownTable(doc))
      else
        assert(style == "snippets")
        file:write(formatTypeDocsAsLuaSnippet(doc))
      end
    end
  end
end

local file = io.open("doc.md", "w")
writeTypesDocsAsMarkdown(file, "snippets", {
  ["juce_core"] = {
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
  },
  ["juce_audio_basics"] = {juce.MidiMessage.new()},
  ["juce_graphics"] = {
    juce.AffineTransform.new(),
    juce.Font.new(12.0),
    juce.Colour.new(0, 0, 0, 0),
    juce.ColourGradient.new(),
  },
  ["juce_gui_basics"] = {
    juce.ComboBox.new(juce.String.new("")),
    juce.Slider.new(),
    juce.TextButton.new(juce.String.new("")),
  },
})
file:close()

-- for key, value in pairs(juce) do
--   print(key)
-- end
