#include "StackBlurEffect.hpp"

#include <span>

namespace jml::designer {

struct StackBlur
{
    explicit StackBlur(int radius) : _blurRadius{radius} {}

    void setNumPixels(int newNumPixels) { _numPixels = newNumPixels; }

    void setStride(int newStride) { _stride = newStride; }

    void blur(juce::uint8* pixels) const
    {
        Queue queue{_blurRadius, pixels[0]};

        auto const stackSize = std::pow(_blurRadius + 1.0, 2.0);
        auto stack           = static_cast<double>(pixels[0]) * stackSize;

        for (auto sourceIndex = _stride; sourceIndex < (_numPixels + _blurRadius) * _stride; sourceIndex += _stride) {
            auto const sourcePixel = pixels[juce::jlimit(0, (_numPixels - 1) * _stride, sourceIndex)];
            queue.add(sourcePixel);

            stack += queue.calculateStackDifference();

            auto const targetIndex = sourceIndex - (_blurRadius * _stride);

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
            , _buffer(size + 1, initialValue)
            , _inBuffer{&_buffer[static_cast<std::size_t>(radius) + 1], radius + 1}
            , _outBuffer{_buffer.data(), radius + 1}
        {
        }

        void add(juce::uint8 valueToAdd)
        {
            _outBuffer.write(_inBuffer.front());
            _inBuffer.write(valueToAdd);
        }

        [[nodiscard]] auto calculateStackDifference() const -> double { return _inBuffer.sum() - _outBuffer.sum(); }

        juce::uint64 const size;

    private:
        struct RingBuffer
        {
            RingBuffer(juce::uint8* sourceData, int bufferSize)
                : _data{sourceData, static_cast<std::size_t>(bufferSize)}
            {
            }

            void write(juce::uint8 value)
            {
                _data[_writeIndex] = value;

                if (++_writeIndex >= _data.size()) { _writeIndex = 0; }
            }

            [[nodiscard]] auto front() const -> juce::uint8 { return _data[_writeIndex]; }

            [[nodiscard]] auto sum() const -> double { return std::accumulate(_data.begin(), _data.end(), 0.0); }

        private:
            std::span<juce::uint8> _data;
            std::size_t _writeIndex{0};
        };

        std::vector<juce::uint8> _buffer;

        RingBuffer _inBuffer;
        RingBuffer _outBuffer;
    };

    int const _blurRadius;

    int _numPixels{0};
    int _stride{0};
};

auto StackBlurEffect::setBlurRadius(int radius) -> void
{
    jassert(radius > 0);
    _blurRadiusX = radius;
    _blurRadiusY = radius;
}

auto StackBlurEffect::setBlurRadius(int radiusX, int radiusY) -> void
{
    jassert(radiusX > 0);
    jassert(radiusY > 0);
    _blurRadiusX = radiusX;
    _blurRadiusY = radiusY;
}

auto StackBlurEffect::setUseThreadPool(bool shouldUseThreadPool, int jobsPerThread) -> void
{
    _threadPoolEnabled = shouldUseThreadPool;
    _numJobsPerThread  = jobsPerThread;
}

auto StackBlurEffect::isUsingThreadPool() const -> bool { return _threadPoolEnabled; }

namespace {
auto getNumColourChannels(juce::Image const& image) -> int
{
    switch (image.getFormat()) {
        case juce::Image::PixelFormat::RGB: return 3;
        case juce::Image::PixelFormat::ARGB: return 4;
        case juce::Image::PixelFormat::SingleChannel: return 1;
        case juce::Image::UnknownFormat:
        default: return 0;
    }
}
} // namespace

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

    StackBlur blur{juce::roundToInt(static_cast<float>(_blurRadiusX) * scale)};
    blur.setNumPixels(bitmapData.width);
    blur.setStride(bitmapData.pixelStride);

    for (auto i = 0; i < numRows; i += _numJobsPerThread) {
        auto blurRow = [this, &bitmapData, i, channel, numRows, &blur]() {
            for (auto row = i; row < i + _numJobsPerThread && row < numRows; row++) {
                auto* const pixels = std::next(bitmapData.getPixelPointer(0, row), channel);
                blur.blur(pixels);
            }
        };

        if (_threadPoolEnabled) {
            _threadPool.addJob(blurRow);
        } else {
            blurRow();
        }
    }

    waitForAllThreadPoolJobsToFinish();
}

auto StackBlurEffect::blurVertically(juce::Image& image, int channel, float scale) -> void
{
    juce::Image::BitmapData bitmapData{image, juce::Image::BitmapData::readWrite};

    auto const numColumns = image.getWidth();

    StackBlur blur{juce::roundToInt(static_cast<float>(_blurRadiusY) * scale)};
    blur.setNumPixels(bitmapData.height);
    blur.setStride(bitmapData.lineStride);

    for (auto i = 0; i < numColumns; i += _numJobsPerThread) {
        auto blurColumn = [this, &bitmapData, i, channel, numColumns, &blur]() {
            for (auto column = i; column < i + _numJobsPerThread && column < numColumns; column++) {
                auto* const pixels = std::next(bitmapData.getPixelPointer(column, 0), channel);
                blur.blur(pixels);
            }
        };

        if (_threadPoolEnabled) {
            _threadPool.addJob(blurColumn);
        } else {
            blurColumn();
        }
    }

    waitForAllThreadPoolJobsToFinish();
}

auto StackBlurEffect::waitForAllThreadPoolJobsToFinish() const -> void
{
    while (_threadPool.getNumJobs() > 0) {}
}

} // namespace jml::designer
