#pragma once

namespace jml {

struct FilePropertyComponent final : ValuePropertyComponent
{
    struct Options
    {
        juce::String title          = "Open";
        juce::String pattern        = "*.*";
        juce::File defaultDirectory = juce::File::getSpecialLocation(juce::File::userHomeDirectory);
        bool selectDirectory        = false;
        bool showClearButton        = false;
    };

    FilePropertyComponent(juce::Value const& value, juce::String const& name, Options options);
    ~FilePropertyComponent() override = default;

    auto refresh() -> void override;

private:
    struct Container final : juce::Component
    {
        explicit Container(bool showClearButton);
        ~Container() override = default;

        auto resized() -> void override;

        juce::TextEditor filename;
        juce::TextButton browse{"..."};
        juce::TextButton clear{"X"};
    };

    auto launchFileChooser() -> void;

    Options _options;
    Container _container{_options.showClearButton};
    std::unique_ptr<juce::FileChooser> _chooser;
};

} // namespace jml
