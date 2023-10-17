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
      str = str .. string.format("juce.%s.%s(...)\n", doc.name, member)
    end
  end
  str = str .. string.format("```\n")
  return str
end

local function writeTypesDocsAsMarkdown(file, style, modules)
  modules = sortByKey(modules)

  -- Parse types
  local docs = {}
  local sortedModuleNames = {}

  for moduleName, moduleContent in pairs(modules) do
    local moduleDocs = {}
    local sortedEntityNames = {}
    for _, entity in pairs(moduleContent) do
      local doc = parseType(entity)
      table.insert(moduleDocs, doc)
      table.insert(sortedEntityNames, doc.name)
    end

    table.sort(sortedEntityNames)
    moduleDocs["sortedEntityNames"] = sortedEntityNames

    docs[moduleName] = moduleDocs
    table.insert(sortedModuleNames, moduleName)
  end

  table.sort(sortedModuleNames)

  -- Write header
  file:write("# JML Documentation\n\n")

  -- Write TOC
  for moduleName, moduleDocs in pairs(docs) do
    file:write(string.format("- [%s](#%s)\n", moduleName, moduleName))
    for _, doc in pairs(moduleDocs) do
      local n = doc.name
      if n ~= nil then
        file:write(string.format("\t- [%s](#%s)\n", n, n))
      end
    end
  end
  -- for i = 1, #sortedModuleNames do
  --   local mn = sortedModuleNames[i]
  --   local md = docs[mn]
  --   local sn = md["sortedEntityNames"]
  --   file:write(string.format("- [%s](#%s)\n", mn, mn))
  --   for d = 1, #sn do
  --     local entity = sn[d]
  --     local doc = md[entity]
  --     print(entity, doc)
  --     -- if doc == nil then
  --     -- else
  --     --   file:write(string.format("\t- [%s](#%s)\n", doc.name, doc.name))
  --     -- end
  --   end
  -- end

  -- Wrie Content
  file:write("\n\n")
  for moduleName, moduleDocs in pairs(docs) do
    -- Header
    file:write(string.format("## %s\n\n", moduleName))

    -- Members
    for i = 1, #moduleDocs do
      local doc = moduleDocs[i]
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
  },
  juce_audio_basics = {juce.MidiMessage.new()},
  juce_graphics = {
    juce.AffineTransform.new(),
    juce.Font.new(12.0),
    juce.Colour.new(0, 0, 0, 0),
    juce.ColourGradient.new(),
  },
  juce_gui_basics = {
    juce.ComponentListener.new(),
    juce.ComboBox.new(juce.String.new("")),
    juce.Label.new(juce.String.new(""), juce.String.new("")),
    juce.ImageComponent.new(juce.String.new("")),
    juce.Slider.new(),
    -- juce.ArrowButton.new(juce.String.new("")),
    juce.HyperlinkButton.new(),
    juce.TextButton.new(juce.String.new("")),
    juce.ToggleButton.new(juce.String.new("")),
    juce.TreeView.new(juce.String.new("")),
  },
})
file:close()
