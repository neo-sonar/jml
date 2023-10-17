json = require("json")

local doxygen = {}

local function parse_member_function(e)
  -- assert e.attrib["kind"] == "function"

  local name_tag = juce.StringRef.new("name")
  local name = e:getChildElementAllSubText(name_tag, juce.String.new(""))

  local brief_tag = juce.StringRef.new("briefdescription")
  local brief = e:getChildElementAllSubText(brief_tag, juce.String.new(""))

  local detail_tag = juce.StringRef.new("detaildescription")
  local detail = e:getChildElementAllSubText(detail_tag, juce.String.new(""))

  local return_t_tag = juce.StringRef.new("type")
  local return_t =
    e:getChildElementAllSubText(return_t_tag, juce.String.new(""))

  local is_static_tag = juce.StringRef.new("static")
  local is_static = e:getBoolAttribute(is_static_tag, true)

  local is_const_tag = juce.StringRef.new("const")
  local is_const = e:getBoolAttribute(is_const_tag, false)

  local is_noexcept_tag = juce.StringRef.new("noexcept")
  local is_noexcept = e:getBoolAttribute(is_noexcept_tag, false)

  local is_virtual_tag = juce.StringRef.new("virt")
  local is_virtual = e:getBoolAttribute(is_virtual_tag, true)

  local mem_fun = {
    name = name:trim(),
    brief = brief:trim(),
    detail = detail:trim(),
    is_static = is_static,
    is_const = is_const,
    is_noexcept = is_noexcept,
    is_virtual = is_virtual,
    return_type = return_t:trim(),
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
  local results = {name = "", members = {}}

  -- For each child
  for i = 0, def:getNumChildElements() - 1 do
    local child = def:getChildElement(i)
    if child:getTagName() == juce.String.new("compoundname") then
      -- Get name
      results["name"] = child:getAllSubText()
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

  -- print(json.encode(results))
  return results

end

return doxygen
