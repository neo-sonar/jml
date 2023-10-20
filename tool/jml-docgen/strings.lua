local strings = {}

function strings.starts_with(str, prefix)
  return string.sub(str, 1, string.len(prefix)) == prefix
end

function strings.break_into_lines(str, length, line_prefix)
  if not line_prefix then
    line_prefix = ""
  end
  local lines = {}
  local line = ""

  for word in str:gmatch("%S+") do
    if #line + #word + 1 <= length then
      if #line > 0 then
        line = line .. " "
      end
      line = line .. word
    else
      table.insert(lines, line)
      line = word
    end
  end

  if #line > 0 then
    table.insert(lines, line)
  end

  return line_prefix .. table.concat(lines, "\n" .. line_prefix)
end

local function test()
  -- starts_with
  assert(strings.starts_with("foobar", "foo"))
  assert(not strings.starts_with("foobar", "bar"))

  -- break_into_lines
  local lines = strings.break_into_lines("foo bar baz", 4)
  assert(lines == "foo\nbar\nbaz")

  local docs = strings.break_into_lines("foo bar baz", 4, "-- ")
  assert(docs == "-- foo\n-- bar\n-- baz")

  -- C++ template argument
  local test_cases = {
    {input = "Rectangle<int>", output = "int"},
    {input = "Rectangle< float >", output = " float "},
    {input = "std::unique_ptr< XmlElement >", output = " XmlElement "},
  }

  for _, tc in pairs(test_cases) do
    tc.input:gsub("<([%w%s_]+)>", function(captured)
      assert(captured == tc.output)
    end)
  end

end

test()

return strings
