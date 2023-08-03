local function test(arrayType)
    local array = arrayType.new()
    assert(array:isEmpty())
    assert(array:size() == 0)
    array:resize(42)
    assert(not array:isEmpty())
    assert(array:size() == 42)
    return true
end

assert(test(juce.Array_int))
assert(test(juce.Array_float))
assert(test(juce.Array_double))
assert(test(juce.Array_String))
assert(test(juce.Array_File))
assert(test(juce.Array_var))
assert(test(juce.Array_GridItem))
assert(test(juce.Array_GridTrackInfo))
