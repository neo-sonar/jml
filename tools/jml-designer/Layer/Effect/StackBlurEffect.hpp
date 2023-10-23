#pragma once

#include <juce_graphics/juce_graphics.h>

namespace jml::designer {

struct StackBlurEffect final : juce::ImageEffectFilter
{
    StackBlurEffect()           = default;
    ~StackBlurEffect() override = default;

    /** Sets the blur radius for this effect.

        The radius must be greater than 0.
    */
    auto setBlurRadius(int radius) -> void;
    auto setBlurRadius(int radiusX, int radiusY) -> void;

    /** Specified whether or not to use a thread pool for the rendering.

        If enabled, each row and column of the image will be blurred in a
        separate job. You can control the number of jobs run on each thread in
        the pool using the jobsPerThread parameter.
        Enabled by default, using 5 jobs per thread.
    */
    auto setUseThreadPool(bool shouldUseThreadPool, int jobsPerThread = 5) -> void;

    /** Returns true if this effect will use a thread pool for its rendering.

        True by default.
    */
    [[nodiscard]] auto isUsingThreadPool() const -> bool;

    /** Blurs the source image and draws the result to the destination context.
        The original image will be left un-blurred, so you probably want to make
        sure the destination context isn't going to draw to that image.
    */
    auto applyEffect(juce::Image& source, juce::Graphics& g, float scaleFactor, float alpha)
        -> void override;

private:
    auto blurHorizontally(juce::Image& image, int channel, float scale) -> void;
    auto blurVertically(juce::Image& image, int channel, float scale) -> void;
    auto waitForAllThreadPoolJobsToFinish() const -> void;

    int _blurRadiusX{0};
    int _blurRadiusY{0};
    bool _threadPoolEnabled{true};
    int _numJobsPerThread{5};
    juce::ThreadPool _threadPool;

    JUCE_LEAK_DETECTOR(StackBlurEffect)
};

} // namespace jml::designer
