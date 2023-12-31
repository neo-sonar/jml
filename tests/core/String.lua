local empty = juce.String.new()
assert(empty:isEmpty())
assert(not empty:isNotEmpty())
assert(empty:length() == 0)

local foo = juce.String.new("foo")
assert(not foo:isEmpty())
assert(foo:isNotEmpty())
assert(foo:length() == 3)

local long = juce.String.new("this variable tests a string that is long!")
assert(not long:isEmpty())
assert(long:isNotEmpty())
assert(long:length() == 42)
assert(long:hash() ~= 0)
assert(long:hashCode() ~= 0)
assert(long:hashCode64() ~= 0)

long:clear()
assert(long:isEmpty())
assert(not long:isNotEmpty())
assert(long:length() == 0)
