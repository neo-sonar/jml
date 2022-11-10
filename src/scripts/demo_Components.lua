color = require("color")

local function makeMainComponent()
  local mainComponent = juce.LuaComponent.new()
  local btn_1 = juce.TextButton.new(juce.String.new("Foo"))
  local btn_2 = juce.TextButton.new(juce.String.new("Baz"))
  local slider_1 = juce.Slider.new()
  local topColor = juce.Colours.cadetblue
  local bottomColor = juce.Colours.black

  mainComponent:addAndMakeVisible(btn_1)
  mainComponent:addAndMakeVisible(btn_2)
  mainComponent:addAndMakeVisible(slider_1)

  slider_1.onValueChange = function()
    slider_1:setColour(juce.SliderColourIds.thumbColourId, color.random())
  end

  btn_1.onClick = function()
  end
  btn_2.onClick = function()
    mainComponent:repaint()
  end

  function mainComponent:paint(g)
    local gradient = juce.ColourGradient.vertical(topColor, bottomColor, mainComponent:getLocalBounds())
    g:setGradientFill(gradient)
    g:fillAll()
  end

  function mainComponent:resized()
    local area = mainComponent:getLocalBounds()
    local btn1Area = area:removeFromTop(50):reduced(5)
    btn_1:setBounds(btn1Area)
    btn_2:setBounds(400, 200, 250, 150)
    slider_1:setBounds(10, 200, 250, 150)
  end

  function mainComponent:mouseDown()
    topColor = juce.Colours.pink
    bottomColor = color.random()
    mainComponent:repaint()
  end

  local lnf = juce.LuaLookAndFeel.new()
  function lnf:drawButtonBackground(g, btn, color, highlighted, down)
    local b = btn:getBounds()
    local bf = juce.RectangleInt.new(b:getX(), b:getY(), b:getWidth(), b:getHeight())
    local c = highlighted and juce.Colours.red or juce.Colours.blue
    g:setColour(c)
    g:fillAll()
  end
  mainComponent:setLookAndFeel(lnf)

  local timer = juce.LuaTimer.new()
  function timer:timerCallback()
    topColor = juce.Colours.pink
    bottomColor = color.random()
    mainComponent:repaint()
  end
  timer:startTimer(2000)

  return mainComponent
end

return makeMainComponent()
