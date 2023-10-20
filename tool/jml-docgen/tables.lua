local tables = {}

function tables.length(T)
  local count = 0
  for _ in pairs(T) do
    count = count + 1
  end
  return count
end

local function test()
  assert(tables.length({}) == 0)
  assert(tables.length({"foo"}) == 1)
  assert(tables.length({"foo", 143}) == 2)
  assert(tables.length({"bar", "baz"}) == 2)
end

test()

return tables
