#include "LuaScriptViewer.hpp"

#include <lua_juce/lua_juce.hpp>

namespace jml::viewer {
namespace {
constexpr auto const* DefaultScriptPath = R"(~/Developer/neo-sonar/jml/examples/Components.lua)";
}

LuaScriptViewer::LuaScriptViewer() : _scriptFile(DefaultScriptPath)
{
    _viewportColour.setValue(toVar(getSchemeWidgetBackgroundColour()));
    _viewportProperties.addProperties(juce::Array<juce::PropertyComponent*>{
        std::make_unique<ColourPropertyComponent>(_viewportColour, "Background").release(),
    });

    _viewportColour.addListener(this);

    addAndMakeVisible(_viewport);
    addAndMakeVisible(_componentTree);
    addAndMakeVisible(_viewportProperties);
    startTimer(2000);
}

auto LuaScriptViewer::setScriptFile(juce::File const& file) -> void
{
    auto componentTreeState = _componentTree.getOpennessState(true);

    _fileListener.reset(nullptr);
    _viewport.setViewedComponent(nullptr);

    if (not file.existsAsFile()) {
        return;
    }
    file.getParentDirectory().setAsCurrentWorkingDirectory();

    reloadLuaState();
    auto script = _lua->state.load_file(file.getFullPathName().toStdString());
    if (not script.valid()) {
        return handleLuaError(script);
    }

    auto factory = script.get<sol::protected_function>();
    auto result  = factory();
    if (not result.valid()) {
        return handleLuaError(result);
    }

    _lua->obj       = result;
    _lua->component = _lua->obj.as<juce::Component*>();
    _lua->component->resized();

    _viewport.setViewedComponent(_lua->component);
    _componentTree.setRootComponent(_lua->component);

    _scriptFile             = file;
    _fileListener           = std::make_unique<FileChangeListener>(_scriptFile);
    _fileListener->onChange = [this] { setScriptFile(_scriptFile); };

    resized();

    if (componentTreeState == nullptr) {
        return;
    }
    _componentTree.restoreOpennessState(*componentTreeState, false);
}

auto LuaScriptViewer::paint(juce::Graphics& g) -> void
{
    g.fillAll(getSchemeWindowBackgroundColour());
}

auto LuaScriptViewer::resized() -> void
{
    auto area     = getLocalBounds();
    auto treeArea = area.removeFromRight(area.proportionOfWidth(0.2));

    _viewportProperties.setBounds(treeArea.removeFromBottom(treeArea.proportionOfHeight(0.15)));
    _componentTree.setBounds(treeArea);
    _viewport.setBounds(area);
}

auto LuaScriptViewer::timerCallback() -> void
{
    if (_lua == nullptr) {
        return;
    }
    _lua->state.collect_garbage();
}

auto LuaScriptViewer::valueChanged(juce::Value& value) -> void
{
    if (value.refersToSameSourceAs(_viewportColour)) {
        _viewport.setBackgroundColour(fromVar<juce::Colour>(_viewportColour));
    }
}

auto LuaScriptViewer::reloadLuaState() -> void
{
    _lua = std::make_unique<LuaState>();
    _lua->state.open_libraries(
        sol::lib::base,
        sol::lib::debug,
        sol::lib::io,
        sol::lib::math,
        sol::lib::os,
        sol::lib::package,
        sol::lib::string,
        sol::lib::table
    );
    lua_juce::allModules(_lua->state);
}

auto LuaScriptViewer::handleLuaError(sol::error const& error) -> void
{
    DBG(error.what());
    juce::ignoreUnused(error);
}

} // namespace jml::viewer
