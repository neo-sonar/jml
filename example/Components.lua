local function MainComponent()
  local mainComponent = juce.Component.new()
  mainComponent:setComponentID(juce.String.new("Main Window"))

  local button = juce.TextButton.new(juce.String.new("Button"))
  local combo = juce.ComboBox.new(juce.String.new("Baz"))
  local slider = juce.Slider.new()
  local rotary = juce.Slider.new(juce.SliderStyle.RotaryHorizontalVerticalDrag, juce.SliderTextEntryBoxPosition.TextBoxBelow)
  local singleLine = juce.TextEditor.new(juce.String.new("Single-Line"), 0x0)
  local password = juce.TextEditor.new(juce.String.new("Password"), 0x2022)

  button:setComponentID(juce.String.new("Button"))
  combo:setComponentID(juce.String.new("Combo-Box"))
  slider:setComponentID(juce.String.new("Slider"))
  rotary:setComponentID(juce.String.new("Rotary"))
  singleLine:setComponentID(juce.String.new("Single-Line"))
  password:setComponentID(juce.String.new("Password"))

  mainComponent:addAndMakeVisible(button)
  mainComponent:addAndMakeVisible(combo)
  mainComponent:addAndMakeVisible(slider)
  mainComponent:addAndMakeVisible(rotary)
  mainComponent:addAndMakeVisible(singleLine)
  mainComponent:addAndMakeVisible(password)

  function mainComponent:paint(g)
    g:fillAll(juce.Colour.new(25, 25, 25, 255))
  end

  function mainComponent:resized()
    local area = mainComponent:getLocalBounds()
    button:setBounds(area:removeFromTop(64):reduced(2))
    combo:setBounds(area:removeFromTop(64):reduced(2))
    slider:setBounds(area:removeFromTop(64):reduced(2))
    rotary:setBounds(area:removeFromTop(64*2):reduced(2))
    singleLine:setBounds(area:removeFromTop(64):reduced(2))
    password:setBounds(area:removeFromTop(64):reduced(2))
  end

  mainComponent:setSize(640, 640)
  return mainComponent
end

return MainComponent()
