json = require("json")

local doxygen = {}

local function parse_function_parameter(func)
  local empty = juce.String.new("")
  local name_tag = juce.StringRef.new("declname")
  local type_tag = juce.StringRef.new("type")

  local parameter = {}
  for j = 0, func:getNumChildElements() - 1 do
    local param = func:getChildElement(j)
    if param:getTagName() == juce.String.new("param") then
      table.insert(parameter, {
        name = param:getChildElementAllSubText(name_tag, empty):trim(),
        type = param:getChildElementAllSubText(type_tag, empty):trim(),
      })
    end
  end
  return parameter
end

local function parse_member_function(e)
  -- assert e.attrib["kind"] == "function"
  local empty = juce.String.new("")

  local name_tag = juce.StringRef.new("name")
  local name = e:getChildElementAllSubText(name_tag, empty)

  local brief_tag = juce.StringRef.new("briefdescription")
  local brief = e:getChildElementAllSubText(brief_tag, empty)

  local detail_tag = juce.StringRef.new("detaileddescription")
  local detail = e:getChildElementAllSubText(detail_tag, empty)

  local return_t_tag = juce.StringRef.new("type")
  local return_t = e:getChildElementAllSubText(return_t_tag, empty)

  local is_static_tag = juce.StringRef.new("static")
  local is_static = e:getBoolAttribute(is_static_tag, true)

  local is_const_tag = juce.StringRef.new("const")
  local is_const = e:getBoolAttribute(is_const_tag, false)

  local is_noexcept_tag = juce.StringRef.new("noexcept")
  local is_noexcept = e:getBoolAttribute(is_noexcept_tag, false)

  local is_virtual_tag = juce.StringRef.new("virt")
  local is_virtual = e:getBoolAttribute(is_virtual_tag, true)

  local space = juce.StringRef.new(" ")
  local new_line = juce.StringRef.new("\n")

  local mem_fun = {
    name = name:trim():replace(new_line, space, false),
    brief = brief:trim():replace(new_line, space, false),
    detail = detail:trim():replace(new_line, space, false),
    is_static = is_static,
    is_const = is_const,
    is_noexcept = is_noexcept,
    is_virtual = is_virtual,
    return_type = return_t:trim(),
    parameter = parse_function_parameter(e),
  }

  return mem_fun
end

function doxygen.parse_xml(entity_name)
  -- Paths
  local juce_path = "~/Developer/tobiashienzsch/JUCE"
  local class_path = string.format("%s/docs/doxygen/xml/class%s.xml", juce_path,
                                   entity_name)
  local struct_path = string.format("%s/docs/doxygen/xml/struct%s.xml",
                                    juce_path, entity_name)

  local xml_path = nil
  if juce.File.new(juce.String.new(class_path)):existsAsFile() then
    xml_path = class_path
  else
    xml_path = struct_path
  end

  -- Xml file
  local xml_file = juce.File.new(juce.String.new(xml_path))
  local xml_doc = juce.XmlDocument.parse(xml_file)
  if xml_doc == nil then
    print("error loading xml from " .. xml_path)
  end

  -- Root element
  local def = xml_doc:getFirstChildElement()
  assert(def:getTagName() == juce.String.new("compounddef"))

  local kindAttribute = juce.String.new("kind")

  -- Results
  local results = {name = "", brief = "", members = {}}

  -- For each child
  for i = 0, def:getNumChildElements() - 1 do
    local child = def:getChildElement(i)
    if child:getTagName() == juce.String.new("compoundname") then
      -- Get name
      results["name"] = child:getAllSubText()
    elseif child:getTagName() == juce.String.new("briefdescription") then
      results["brief"] = child:getAllSubText()
    elseif child:getTagName() == juce.String.new("sectiondef") then
      local pub = child:getStringAttribute(juce.StringRef.new(kindAttribute))
      if pub == juce.String.new("public-func") then
        for j = 0, child:getNumChildElements() - 1 do
          local members = child:getChildElement(j)
          if members:getTagName() == juce.String.new("memberdef") then
            local func = parse_member_function(members)
            table.insert(results.members, func)
            -- print(results.name, func.name, func.brief)

          end
        end
      end
      -- Get public section
      -- print(child:getAllSubText())
    end

  end

  local f = io.open("out/docs.json", "w")
  f:write(json.encode(results))
  f:close()

  return results

end

return doxygen
