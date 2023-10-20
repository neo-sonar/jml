json = require("json")
strings = require("strings")
testing = require("testing")

local juce_root = "~/Developer/tobiashienzsch/JUCE"

local doxygen = {}

local function assert_file_exists(file)
  if not file:existsAsFile() then
    print(file:getFullPathName())
    assert(false)
  end
end

local function has_kind(e, expected_kind)
  local tag = juce.String.new("kind")
  local kind = e:getStringAttribute(juce.StringRef.new(tag))
  return tostring(kind) == expected_kind
end

local function select_xml_file(entity)
  entity = entity:gsub('_', '__')
  entity = entity:gsub('%.', '_1_1')
  entity = entity:gsub('<int>', '')
  entity = entity:gsub('<float>', '')
  entity = entity:gsub('<double>', '')
  local xml = string.format("%s/docs/doxygen/xml", juce_root)

  local class = string.format("%s/class%s.xml", xml, entity)
  local file = juce.File.new(juce.String.new(class))
  if file:existsAsFile() then
    return file
  end

  local struct = string.format("%s/struct%s.xml", xml, entity)
  return juce.File.new(juce.String.new(struct))
end

local function get_all_text(element, tag)
  local tag_ref = juce.StringRef.new(tag)
  local txt = element:getChildElementAllSubText(tag_ref, juce.String.new(""))
  local space = juce.StringRef.new(" ")
  local new_line = juce.StringRef.new("\n")
  return tostring(txt:trim():replace(new_line, space, false))
end

local function get_bool(element, tag)
  local tag_ref = juce.StringRef.new(tag)
  return element:getBoolAttribute(tag_ref, false)
end

local function parse_function_parameter(func)
  local parameter = {}
  for i = 0, func:getNumChildElements() - 1 do
    local p = func:getChildElement(i)
    if tostring(p:getTagName()) == "param" then
      table.insert(parameter, {
        name = get_all_text(p, "declname"),
        type = get_all_text(p, "type"),
      })
    end
  end
  return parameter
end

local function parse_return_type(e)
  local ret_type = strings.trim(get_all_text(e, "type"))

  for _, template in pairs({"std::unique_ptr", "std::optional"}) do
    if string.find(ret_type, template) then
      template_arg = nil
      ret_type:gsub("<([%w%s_]+)>", function(captured)
        template_arg = captured
      end)

      assert(template_arg)
      return strings.trim(template_arg)
    end
  end

  return ret_type
end

local function parse_member_function(e)
  assert(has_kind(e, "function"))

  return {
    name = get_all_text(e, "name"),
    brief = get_all_text(e, "briefdescription"),
    detail = get_all_text(e, "detaileddescription"),
    is_static = get_bool(e, "static"),
    is_const = get_bool(e, "const"),
    is_noexcept = get_bool(e, "noexcept"),
    is_virtual = get_bool(e, "virt"),
    return_type = parse_return_type(e),
    parameter = parse_function_parameter(e),
  }
end

local function parse_member_variable(e)
  assert(has_kind(e, "variable"))

  return {
    name = get_all_text(e, "name"),
    type = get_all_text(e, "type"),
    brief = get_all_text(e, "briefdescription"),
    detail = get_all_text(e, "detaileddescription"),
    is_static = get_bool(e, "static"),
  }
end

function doxygen.parse_xml(type_name)
  -- Results
  local results = {name = "", brief = "", members = {}, variables = {}}

  local add_function = function(e)
    table.insert(results.members, parse_member_function(e))
  end
  local add_variable = function(e)
    table.insert(results.variables, parse_member_variable(e))
  end
  local section_parsers = {
    ["public-func"] = add_function,
    ["public-static-func"] = add_function,
    ["public-attrib"] = add_variable,
    ["public-static-attrib"] = add_variable,
  }

  -- Xml file
  local xml_file = select_xml_file(type_name)
  assert_file_exists(xml_file)

  local xml_doc = juce.XmlDocument.parse(xml_file)
  if xml_doc == nil then
    print("error loading xml from " .. tostring(xml_file:getFullPathName()))
  end

  -- Root element
  local def = xml_doc:getFirstChildElement()
  assert(tostring(def:getTagName()) == "compounddef")

  local kind_tag = juce.String.new("kind")

  -- For each child
  for i = 0, def:getNumChildElements() - 1 do
    local child = def:getChildElement(i)
    local tag = tostring(child:getTagName())
    if tag == "compoundname" then
      -- Get name
      results["name"] = tostring(child:getAllSubText():trim()):gsub("\n", " ")
    elseif tag == "briefdescription" then
      -- Get brief
      results["brief"] = tostring(child:getAllSubText():trim()):gsub("\n", " ")
    elseif tag == "sectiondef" then
      -- Sections
      local section = child:getStringAttribute(juce.StringRef.new(kind_tag))
      local parser = section_parsers[tostring(section)]
      if parser then
        for j = 0, child:getNumChildElements() - 1 do
          local members = child:getChildElement(j)
          if tostring(members:getTagName()) == "memberdef" then
            parser(members)
          end
        end
      end
    end
  end

  local f = io.open(string.format("../out/json/%s.json", type_name), "w")
  f:write(json.encode(results))
  f:close()

  return results

end

local function test()
  local file = doxygen.parse_xml("File")
  testing.eq(file.name, "File")
  testing.eq(file.brief, "Represents a local file or directory.")

  local create = nil
  for _, v in pairs(file.members) do
    if v["name"] == "createInputStream" then
      create = v
    end
  end

  assert(create)
  testing.eq(create.is_static, false)
  testing.eq(create.is_const, true)
  testing.eq(create.is_noexcept, false)
  testing.eq(create.is_virtual, false)
  testing.eq(#create.parameter, 0)
  testing.eq(create.return_type, "FileInputStream")
  testing.eq(create.brief, "Creates a stream to read from this file.")
end

test()
return doxygen
