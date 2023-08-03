# JUCE Meets LUA

> **WORK IN PROGRESS**: For license information please refer to [juce.com/get-juce](https://juce.com/get-juce)

## Projects

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

### Tools

#### jml-cli

- Run unit tests. See [Test.hpp](./tool/jml-cli/Command/Test.hpp)
- Create component snapshot images. See [Snapshot.hpp](./tool/jml-cli/Command/Snapshot.hpp)

#### jml-viewer

- ToDo

#### jml-designer

- ToDo
