#pragma once

#include <juce_core/juce_core.h>

#include <fmt/format.h>
#include <fmt/os.h>
#include <fmt/ostream.h>

template<>
struct fmt::formatter<juce::String> : formatter<string_view>
{
    template<typename FormatContext>
    auto format(juce::String const& str, FormatContext& ctx) const
    {
        return fmt::format_to(ctx.out(), "{}", str.getCharPointer());
    }
};
