local doxygen = require("doxygen")
local sol2 = require("sol2")
local strings = require("strings")
local tables = require("tables")

local ldoc = {}

function ldoc.write_usertype_stubs(dir, modules)
  local docs, _ = sol2.parse_juce_types(modules)

  for _, juce_module in pairs(docs) do
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
        for name, _ in pairs(members_variables) do
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
          local seperator = ":"
          if member_dox.is_static then
            seperator = "."
            file:write(string.format("-- @static\n"))
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

return ldoc
