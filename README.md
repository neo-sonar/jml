# JUCE Meets LUA

[![Build](https://github.com/neo-sonar/jml/actions/workflows/build.yml/badge.svg)](https://github.com/neo-sonar/jml/actions/workflows/build.yml)

- [Usage](#usage)
  - [Bindings](#bindings)
- [Tools](#tools)
  - [jml-viewer](#jml-viewer)
  - [jml-designer](#jml-designer)

> **WORK IN PROGRESS**: For license information please refer to [juce.com/get-juce](https://juce.com/get-juce)

## Usage

### Bindings

In your `CMakeLists.txt`:

```cmake
find_package(sol2 REQUIRED)
add_subdirectory(path/to/jml/module)

target_link_libraries(YourApplication
    PRIVATE
        # This includes all JUCE modules for which bindings have been created
        lua_juce::lua_juce

        # You could also only link to individual modules
        # lua_juce::lua_juce_core
        # lua_juce::lua_juce_events
        # ...
    PUBLIC
        # Required for bindings
        sol2::sol2
)
```

In your source code:

```cpp
#include <lua_juce/lua_juce.hpp>

auto state = sol::state{};
state.open_libraries(sol::lib::base, sol::lib::package, sol::lib::string);
lua_juce::allModules(state);
```

## Tools

### jml-viewer

#### Command-Line

- Run unit tests. See [Test.hpp](./tool/jml-viewer/Command/Test.hpp)
- Create component snapshot images. See [Snapshot.hpp](./tool/jml-viewer/Command/Snapshot.hpp)

### jml-designer

- ToDo
