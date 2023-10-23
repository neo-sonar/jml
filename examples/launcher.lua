local Theme = {
  black = juce.Colour.new(0, 0, 0, 255),
  grey = juce.Colour.new(53, 54, 59, 255),
  lightViolet = juce.Colour.new(93, 152, 255, 255),
  lightBlue = juce.Colour.new(82, 178, 225, 255),
  lightGreen = juce.Colour.new(120, 192, 206, 255),
}

local PluginThumbnail = {}

function PluginThumbnail.new(name)
  local this = {}
  this.component = juce.Component.new()
  this.component:setComponentID(juce.String.new(name))

  this.tag1 = juce.TextButton.new(juce.String.new("tag1"))
  this.tag2 = juce.TextButton.new(juce.String.new("tag2"))
  this.tag3 = juce.TextButton.new(juce.String.new("tag3"))

  this.component:addAndMakeVisible(this.tag1)
  this.component:addAndMakeVisible(this.tag2)
  this.component:addAndMakeVisible(this.tag3)

  this.tag1:setComponentID(juce.String.new("tag1"))
  this.tag2:setComponentID(juce.String.new("tag2"))
  this.tag3:setComponentID(juce.String.new("tag3"))

  local imageArea = juce.Rectangle_int.new(0, 0, 0, 0)

  function this.component:paint(g)
    g:setColour(Theme.black)
    g:fillRoundedRectangle(imageArea, 8.0)
  end

  function this.component:resized()
    local area = self:getLocalBounds()
    local buttonArea = area:removeFromBottom(40)
    imageArea = area:reduced(2)
    local width = buttonArea:getWidth() / 3
    this.tag1:setBounds(buttonArea:removeFromLeft(width):reduced(2))
    this.tag2:setBounds(buttonArea:removeFromLeft(width):reduced(2))
    this.tag3:setBounds(buttonArea:removeFromLeft(width):reduced(2))
  end

  return this
end

local function ContentHeader()
  local component = juce.Component.new()
  component:setComponentID(juce.String.new("Content component"))

  local titleText = juce.String.new("Installed Products")
  local title = juce.Label.new(titleText, titleText)
  title:setComponentID(titleText)
  title:setFont(juce.Font.new(24.0))
  component:addAndMakeVisible(title)

  local searchText = juce.String.new("Search")
  local search = juce.Label.new(searchText, searchText)
  search:setComponentID(searchText)
  search:setJustificationType(juce.Justification.new(
                                juce.JustificationFlags.centred))
  search:setFont(juce.Font.new(24.0))
  component:addAndMakeVisible(search)

  local music = juce.TextButton.new(juce.String.new("Music"))
  music:setComponentID(juce.String.new("Music"))
  component:addAndMakeVisible(music)

  local chat = juce.TextButton.new(juce.String.new("Chat"))
  chat:setComponentID(juce.String.new("Chat"))
  component:addAndMakeVisible(chat)

  local user = juce.TextButton.new(juce.String.new("User"))
  user:setComponentID(juce.String.new("User"))
  component:addAndMakeVisible(user)

  function component:resized()
    local area = self:getLocalBounds():reduced(16)
    title:setBounds(area:removeFromLeft(200))

    user:setBounds(area:removeFromRight(50):reduced(2))
    chat:setBounds(area:removeFromRight(50):reduced(2))
    music:setBounds(area:removeFromRight(50):reduced(2))
    area:removeFromRight(50)

    search:setBounds(area)
  end

  return component
end

local Content = {}

function Content.new()
  local component = juce.Component.new()
  local header = ContentHeader()
  local dynamic = PluginThumbnail.new("ASIC Dynamic")
  local filter = PluginThumbnail.new("ASIC Filter")
  local shape = PluginThumbnail.new("ASIC Shape")
  local space = PluginThumbnail.new("ASIC Space")

  local listModel = juce.ListBoxModel.new()
  function listModel:getNumRows()
    return 24
  end

  function listModel:paintListBoxItem(rowNumber, g, width, height, rowIsSelected)
    g:setColour(juce.Colours.black)
    g:fillRect(juce.Rectangle_int.new(0, 0, width, height):reduced(2))
  end

  local list = juce.ListBox.new()
  list:setModel(listModel)

  dynamic.tag1.onClick = function()
    print("Dynamic: 1")
  end

  component:setComponentID(juce.String.new("Content"))
  component:addAndMakeVisible(header)
  component:addAndMakeVisible(dynamic.component)
  component:addAndMakeVisible(filter.component)
  component:addAndMakeVisible(shape.component)
  component:addAndMakeVisible(space.component)
  component:addAndMakeVisible(list)

  function component:paint(g)
    g:setColour(Theme.grey)
    g:fillRoundedRectangle(component:getLocalBounds(), 8.0)
  end

  function component:resized()
    local area = self:getLocalBounds():reduced(16)
    header:setBounds(area:removeFromTop(75):reduced(8))

    local height = area:getHeight() / 2.5
    local width = area:getWidth() / 4
    local thumbnailArea = area:removeFromTop(height):reduced(8)
    dynamic.component:setBounds(thumbnailArea:removeFromLeft(width):reduced(8))
    filter.component:setBounds(thumbnailArea:removeFromLeft(width):reduced(8))
    shape.component:setBounds(thumbnailArea:removeFromLeft(width):reduced(8))
    space.component:setBounds(thumbnailArea:removeFromLeft(width):reduced(8))
    list:setBounds(area)
  end

  return component
end

local Sidebar = {}

function Sidebar.new()
  local component = juce.Component.new()

  local plug = juce.TextButton.new(juce.String.new("Plug"))
  local music = juce.TextButton.new(juce.String.new("Music"))
  local rocket = juce.TextButton.new(juce.String.new("Rocket"))
  local star = juce.TextButton.new(juce.String.new("Star"))
  component:setComponentID(juce.String.new("Sidebar"))

  plug:setComponentID(juce.String.new("Plug"))
  music:setComponentID(juce.String.new("Music"))
  rocket:setComponentID(juce.String.new("Rocket"))
  star:setComponentID(juce.String.new("Star"))

  component:addAndMakeVisible(music)
  component:addAndMakeVisible(plug)
  component:addAndMakeVisible(rocket)
  component:addAndMakeVisible(star)

  function component:paint(g)
    g:setColour(Theme.black)
    g:fillAll()
  end

  function component:resized()
    local area = self:getLocalBounds():reduced(4)
    star:setBounds(area:removeFromBottom(60):reduced(4))
    rocket:setBounds(area:removeFromBottom(60):reduced(4))
    music:setBounds(area:removeFromBottom(60):reduced(4))
    plug:setBounds(area:removeFromBottom(60):reduced(4))
  end

  return component
end

local function MainWindow()
  local lnf = juce.LookAndFeel_V4.new()
  function lnf:drawButtonBackground(g, btn, c, isHighlighted, isDown)
    g:setColour(isHighlighted and Theme.lightGreen or Theme.lightBlue)
    g:fillRoundedRectangle(btn:getLocalBounds(), 8.0)

  end

  local component = juce.Component.new()
  component:setComponentID(juce.String.new("Launcher"))

  local sidebar = Sidebar.new()
  component:addAndMakeVisible(sidebar)

  local content = Content.new()
  component:addAndMakeVisible(content)

  component:setLookAndFeel(lnf)
  component:setSize(1152, 648)

  function component:paint(g)
    g:setColour(Theme.black)
    g:fillAll()
  end

  function component:resized()
    local area = self:getLocalBounds()
    sidebar:setBounds(area:removeFromLeft(75))
    content:setBounds(area:reduced(8))
  end

  return component
end

return MainWindow()
