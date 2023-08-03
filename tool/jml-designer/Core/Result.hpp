#pragma once

#include "Core/String.hpp"

namespace jml::designer {

template<typename... T>
[[nodiscard]] auto fail(::fmt::format_string<T...> fmtStr, T&&... args) -> juce::Result
{
    return juce::Result::fail(fmt::format(fmtStr, std::forward<T>(args)...));
}

} // namespace jml::designer
