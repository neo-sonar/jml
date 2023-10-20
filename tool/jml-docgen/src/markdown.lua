local markdown = {}

local function format_usertype_as_code_block(doc)
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

  return str .. string.format("```\n")
end

function markdown.write_usertype(file, modules)
  local docs, sorted_modules_names = sol2.parse_juce_types(modules)

  -- Write header
  file:write("# JML Documentation\n\n")

  -- Write TOC
  for i = 1, #sorted_modules_names do
    -- Module name
    local module_name = sorted_modules_names[i]
    local module_docs = docs[module_name]
    file:write(string.format("- [%s](#%s)\n", module_name, module_name))

    -- Module class
    for d = 1, #module_docs[1] do
      local name = module_docs[1][d]
      local class = module_docs[2][name]
      local name = class.name
      if name ~= nil then
        file:write(string.format("  - [%s](#%s)\n", name, name))
      end
    end
  end

  -- Wrie Content
  for i = 1, #sorted_modules_names do
    local module_name = sorted_modules_names[i]
    local module_docs = docs[module_name]

    -- Header
    file:write(string.format("\n## %s\n", module_name))

    -- Members
    for j = 1, #module_docs[1] do
      local name = module_docs[1][j]
      local doc = module_docs[2][name]
      file:write("\n")
      file:write(format_usertype_as_code_block(doc))
    end
  end
end

return markdown
