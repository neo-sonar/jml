#pragma once

namespace jml {

struct LookAndFeel final : juce::LookAndFeel_V4
{
    LookAndFeel();
    ~LookAndFeel() override = default;
};

} // namespace jml
