local color = {}

function color.randomWithAlpha(alpha)
  local r = juce.Random.getSystemRandom():nextInt(255)
  local g = juce.Random.getSystemRandom():nextInt(255)
  local b = juce.Random.getSystemRandom():nextInt(255)
  return juce.Colour.new(r, g, b, alpha)
end

function color.random()
  return color.randomWithAlpha(255)
end

local function makeMainComponent()
  local lnf = juce.LookAndFeel_V4.new()
  function lnf:drawButtonBackground(g, btn, colour, highlighted, down)
    g:setColour(highlighted and colour or juce.Colours.blue)
    g:fillAll()
  end

  local mainComponent = juce.Component.new()
  local btn_1 = juce.TextButton.new(juce.String.new("Foo"))
  local btn_2 = juce.TextButton.new(juce.String.new("Baz"))
  local slider_1 = juce.Slider.new()
  local topColor = juce.Colours.red
  local bottomColor = juce.Colours.black

  mainComponent:setLookAndFeel(lnf)

  mainComponent:setComponentID(juce.String.new("Main Window"))
  btn_1:setComponentID(juce.String.new("Foo"))
  btn_2:setComponentID(juce.String.new("Baz"))
  slider_1:setComponentID(juce.String.new("Slider Linear"))

  mainComponent:addAndMakeVisible(btn_1)
  mainComponent:addAndMakeVisible(btn_2)
  mainComponent:addAndMakeVisible(slider_1)

  slider_1.onValueChange = function()
    slider_1:setColour(juce.Slider.ColourIds.thumbColourId, color.random())
  end

  btn_1.onClick = function()
  end
  btn_2.onClick = function()
    mainComponent:repaint()
  end

  function mainComponent:paint(g)
    local gradient = juce.ColourGradient.vertical(topColor, bottomColor,
                                                  mainComponent:getLocalBounds())
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

  local timer = juce.Timer.new()
  function timer:timerCallback()
    topColor = juce.Colours.pink
    bottomColor = color.random()
    mainComponent:repaint()
  end
  timer:startTimer(2000)

  mainComponent:setSize(1024, 576)
  return mainComponent
end

return makeMainComponent()
