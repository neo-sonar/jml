#include "StackBlurEffect.hpp"

namespace jml::designer {

struct StackBlur
{
    explicit StackBlur(int radius) : blurRadius{radius} {}

    void setNumPixels(int newNumPixels) { numPixels = newNumPixels; }

    void setStride(int newStride) { stride = newStride; }

    void blur(juce::uint8* pixels)
    {
        Queue queue{blurRadius, pixels[0]};

        auto const stackSize = std::pow(blurRadius + 1.0, 2.0);
        auto stack           = static_cast<double>(pixels[0]) * stackSize;

        for (auto sourceIndex = stride; sourceIndex < (numPixels + blurRadius) * stride; sourceIndex += stride) {
            auto const sourcePixel = pixels[juce::jlimit(0, (numPixels - 1) * stride, sourceIndex)];
            queue.add(sourcePixel);

            stack += queue.calculateStackDifference();

            auto const targetIndex = sourceIndex - (blurRadius * stride);

            if (targetIndex >= 0) {
                auto const alpha       = juce::jlimit(0.0, static_cast<double>(std::numeric_limits<juce::uint8>::max()),
                                                      std::round(stack / stackSize));
                auto const targetPixel = static_cast<juce::uint8>(alpha);
                pixels[targetIndex]    = targetPixel;
            }
        }
    }

private:
    struct Queue
    {
        Queue(int radius, juce::uint8 initialValue)
            : size{static_cast<juce::uint64>(radius) * 2 + 1}
            , buffer(size + 1, initialValue)
            , inBuffer{&buffer[static_cast<std::size_t>(radius) + 1], radius + 1}
            , outBuffer{buffer.data(), radius + 1}
        {
        }

        void add(juce::uint8 valueToAdd)
        {
            outBuffer.write(inBuffer.front());
            inBuffer.write(valueToAdd);
        }

        double calculateStackDifference() const { return inBuffer.sum() - outBuffer.sum(); }

        const juce::uint64 size;

    private:
        struct RingBuffer
        {
            RingBuffer(juce::uint8* sourceData, int bufferSize) : data{sourceData}, size{bufferSize} {}

            void write(juce::uint8 value)
            {
                data[writeIndex] = value;

                if (++writeIndex >= size) writeIndex = 0;
            }

            juce::uint8 front() const { return data[writeIndex]; }

            double sum() const { return std::accumulate(data, data + size, 0.0); }

        private:
            int writeIndex{0};
            juce::uint8* data;
            int const size;
        };

        std::vector<juce::uint8> buffer;

        RingBuffer inBuffer;
        RingBuffer outBuffer;
    };

    int const blurRadius;

    int numPixels{0};
    int stride{0};
};

auto StackBlurEffect::setBlurRadius(int radius) -> void
{
    jassert(radius > 0);
    blurRadiusX = radius;
    blurRadiusY = radius;
}

auto StackBlurEffect::setBlurRadius(int radiusX, int radiusY) -> void
{
    jassert(radiusX > 0);
    jassert(radiusY > 0);
    blurRadiusX = radiusX;
    blurRadiusY = radiusY;
}

auto StackBlurEffect::setUseThreadPool(bool shouldUseThreadPool, int jobsPerThread) -> void
{
    threadPoolEnabled = shouldUseThreadPool;
    numJobsPerThread  = jobsPerThread;
}

auto StackBlurEffect::isUsingThreadPool() const -> bool { return threadPoolEnabled; }

static auto getNumColourChannels(juce::Image const& image) -> int
{
    switch (image.getFormat()) {
        case juce::Image::PixelFormat::RGB: return 3;
        case juce::Image::PixelFormat::ARGB: return 4;
        case juce::Image::PixelFormat::SingleChannel: return 1;
        case juce::Image::UnknownFormat:
        default: return 0;
    }
}

auto StackBlurEffect::applyEffect(juce::Image& source, juce::Graphics& g, float scale, float alpha) -> void
{
    // Create a copy of the image
    auto blurredImage = source.createCopy();

    // Blur each channel in the image
    for (auto channel = 0; channel < getNumColourChannels(blurredImage); channel++) {
        blurHorizontally(blurredImage, channel, scale);
        blurVertically(blurredImage, channel, scale);
    }

    // Draw the blurred image to the provided context
    blurredImage.multiplyAllAlphas(alpha);
    g.drawImageAt(blurredImage, 0, 0);
}

auto StackBlurEffect::blurHorizontally(juce::Image& image, int channel, float scale) -> void
{
    juce::Image::BitmapData bitmapData{image, juce::Image::BitmapData::readWrite};

    auto const numRows = image.getHeight();

    StackBlur blur{juce::roundToInt(static_cast<float>(blurRadiusX) * scale)};
    blur.setNumPixels(bitmapData.width);
    blur.setStride(bitmapData.pixelStride);

    for (auto i = 0; i < numRows; i += numJobsPerThread) {
        auto blurRow = [this, &bitmapData, i, channel, numRows, &blur]() {
            for (auto row = i; row < i + numJobsPerThread && row < numRows; row++) {
                auto* const pixels = bitmapData.getPixelPointer(0, row) + channel;
                blur.blur(pixels);
            }
        };

        if (threadPoolEnabled)
            threadPool.addJob(blurRow);
        else
            blurRow();
    }

    waitForAllThreadPoolJobsToFinish();
}

auto StackBlurEffect::blurVertically(juce::Image& image, int channel, float scale) -> void
{
    juce::Image::BitmapData bitmapData{image, juce::Image::BitmapData::readWrite};

    auto const numColumns = image.getWidth();

    StackBlur blur{juce::roundToInt(static_cast<float>(blurRadiusY) * scale)};
    blur.setNumPixels(bitmapData.height);
    blur.setStride(bitmapData.lineStride);

    for (auto i = 0; i < numColumns; i += numJobsPerThread) {
        auto blurColumn = [this, &bitmapData, i, channel, numColumns, &blur]() {
            for (auto column = i; column < i + numJobsPerThread && column < numColumns; column++) {
                auto* const pixels = bitmapData.getPixelPointer(column, 0) + channel;
                blur.blur(pixels);
            }
        };

        if (threadPoolEnabled)
            threadPool.addJob(blurColumn);
        else
            blurColumn();
    }

    waitForAllThreadPoolJobsToFinish();
}

auto StackBlurEffect::waitForAllThreadPoolJobsToFinish() const -> void
{
    while (threadPool.getNumJobs() > 0) {}
}

} // namespace jml::designer
