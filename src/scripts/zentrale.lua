local black = juce.Colour.new(0, 0, 0, 255)
local grey = juce.Colour.new(53, 54, 59, 255)

local function PluginThumbnail(name)
  local thumbnail = juce.LuaComponent.new()
  thumbnail:setComponentID(juce.String.new(name))

  local tag1 = juce.TextButton.new(juce.String.new("tag1"))
  local tag2 = juce.TextButton.new(juce.String.new("tag2"))
  local tag3 = juce.TextButton.new(juce.String.new("tag3"))

  thumbnail:addAndMakeVisible(tag1)
  thumbnail:addAndMakeVisible(tag2)
  thumbnail:addAndMakeVisible(tag3)

  function thumbnail:paint(g)
    g:setColour(juce.Colours.black)
    g:fillAll()
  end

  function thumbnail:resized()
    local area = thumbnail:getLocalBounds()
  end

  return thumbnail
end

local function Sidebar()
  local sidebar = juce.LuaComponent.new()

  local plug = juce.TextButton.new(juce.String.new("Plug"))
  local music = juce.TextButton.new(juce.String.new("Music"))
  local rocket = juce.TextButton.new(juce.String.new("Rocket"))
  local star = juce.TextButton.new(juce.String.new("Star"))
  sidebar:setComponentID(juce.String.new("Sidebar"))

  plug:setComponentID(juce.String.new("Plug"))
  music:setComponentID(juce.String.new("Music"))
  rocket:setComponentID(juce.String.new("Rocket"))
  star:setComponentID(juce.String.new("Star"))

  sidebar:addAndMakeVisible(music)
  sidebar:addAndMakeVisible(plug)
  sidebar:addAndMakeVisible(rocket)
  sidebar:addAndMakeVisible(star)

  function sidebar:paint(g)
    g:setColour(black)
    g:fillAll()
  end

  function sidebar:resized()
    local area = sidebar:getLocalBounds()
    star:setBounds(area:removeFromBottom(75):reduced(4))
    rocket:setBounds(area:removeFromBottom(75):reduced(4))
    music:setBounds(area:removeFromBottom(75):reduced(4))
    plug:setBounds(area:removeFromBottom(75):reduced(4))
  end

  return sidebar
end

local function ContentHeader()
  local header = juce.LuaComponent.new()
  header:setComponentID(juce.String.new("Content Header"))

  local titleText = juce.String.new("Installed Products")
  local title = juce.Label.new(titleText, titleText)
  title:setComponentID(titleText)

  local searchText = juce.String.new("Search")
  local search = juce.Label.new(searchText, searchText)
  search:setComponentID(searchText)

  header:addAndMakeVisible(title)
  header:addAndMakeVisible(search)

  function header:resized()
    local area = header:getLocalBounds():reduced(16)
    title:setBounds(area:removeFromLeft(150):toNearestInt())
    search:setBounds(area:removeFromLeft(150):toNearestInt())
  end

  return header
end

local function MainContent()
  local content = juce.LuaComponent.new()
  local header = ContentHeader()
  local dynamic = PluginThumbnail("ASIC Dynamic")
  local filter = PluginThumbnail("ASIC Filter")
  local shape = PluginThumbnail("ASIC Shape")
  local space = PluginThumbnail("ASIC Space")

  content:setComponentID(juce.String.new("Content"))
  content:addAndMakeVisible(header)
  content:addAndMakeVisible(dynamic)
  content:addAndMakeVisible(filter)
  content:addAndMakeVisible(shape)
  content:addAndMakeVisible(space)

  function content:paint(g)
    g:setColour(grey)
    g:fillAll()
  end

  function content:resized()
    local area = content:getLocalBounds():reduced(16)
    local height = area:getHeight() / 3
    local width = area:getWidth() / 3
    header:setBounds(area:removeFromTop(75):reduced(8):toNearestInt())

    thumbnailArea = area:removeFromTop(200):reduced(8)
    dynamic:setBounds(thumbnailArea:removeFromLeft(200):reduced(5))
    filter:setBounds(thumbnailArea:removeFromLeft(200):reduced(5))
    shape:setBounds(thumbnailArea:removeFromLeft(200):reduced(5))
    space:setBounds(thumbnailArea:removeFromLeft(200):reduced(5))
  end

  return content
end

local function MainWindow()
  local mainComponent = juce.LuaComponent.new()
  local sidebar = Sidebar()
  local content = MainContent()

  mainComponent:addAndMakeVisible(sidebar)
  mainComponent:addAndMakeVisible(content)
  mainComponent:setComponentID(juce.String.new("Zentrale"))
  mainComponent:setSize(1152, 648)

  function mainComponent:paint(g)
    g:setColour(black)
    g:fillAll()
  end

  function mainComponent:resized()
    local area = mainComponent:getLocalBounds()
    sidebar:setBounds(area:removeFromLeft(75):toNearestInt())
    content:setBounds(area:reduced(8))
  end

  return mainComponent
end

return MainWindow()
