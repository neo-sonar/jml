local sol2 = {}

local function sort_by_key(t)
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

local function parse_usertype(obj)
  local meta = getmetatable(obj)
  local name = meta.__name
  local doc = {name = nil, members = {}}

  i, j = string.find(name, "lua_juce")
  if i == nil or j == nil then
    doc.name = string.sub(meta.__name, 11) -- Remove "sol.juce::"
  else
    doc.name = string.sub(meta.__name, 18) -- Remove "sol.lua_juce::Lua"
  end

  doc.name = doc.name:gsub("*", "")
  doc.name = doc.name:gsub("&", "")
  assert(doc.name ~= nil)

  for key, value in pairs(meta) do
    if type(value) == "function" then
      table.insert(doc.members, key)
    end
  end

  table.sort(doc.members)
  return doc
end

function sol2.parse_juce_types(modules)
  modules = sort_by_key(modules)

  local docs = {}
  local sorted_names = {}

  for name, entities in pairs(modules) do
    local module_docs = {}
    local sorted_entity_names = {}
    for _, entity in pairs(entities) do
      local doc = parse_usertype(entity)
      module_docs[doc.name] = doc
      table.insert(sorted_entity_names, doc.name)
    end

    table.insert(sorted_names, name)
    table.sort(sorted_entity_names)
    docs[name] = {sorted_entity_names, module_docs}
  end

  table.sort(sorted_names)
  return docs, sorted_names
end

local function test()
  assert(parse_usertype(juce.String.new()).name == "String")
  assert(parse_usertype(juce.abstract.Button).name == "Button")
  assert(parse_usertype(juce.abstract.LookAndFeel).name == "LookAndFeel")

  local types = io.open("out/types.txt", "w")
  for k, v in pairs(juce) do
    types:write(string.format("%s\n", k))
  end
  types:close()

end

test()
return sol2
