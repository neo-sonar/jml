#pragma once

#include <fmt/format.h>
#include <fmt/os.h>
#include <fmt/ostream.h>

#include <juce_core/juce_core.h>

namespace jml::designer {

template<typename... T>
[[nodiscard]] auto fail(::fmt::format_string<T...> fmtStr, T&&... args) -> juce::Result
{
    return juce::Result::fail(fmt::format(fmtStr, std::forward<T>(args)...));
}

} // namespace jml::designer
