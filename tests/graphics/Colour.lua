local red = juce.Colours.red

assert(red:getAlpha() == 255)
assert(red:getRed() == 255)
assert(red:getGreen() == 0)
assert(red:getBlue() == 0)

assert(red:getFloatAlpha() == 1.0)
assert(red:getFloatRed() == 1.0)
assert(red:getFloatGreen() == 0)
assert(red:getFloatBlue() == 0)

assert(red:isOpaque())
assert(not red:isTransparent())

local str = red:toString()
local roundtrip = juce.Colour.fromString(juce.StringRef.new(str))
assert(roundtrip == red)
