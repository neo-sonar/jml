
namespace jml {

FilePropertyComponent::FilePropertyComponent(
    juce::Value const& value,
    juce::String const& name,
    Options options
)
    : ValuePropertyComponent{value, name}
    , _options{std::move(options)}
{
    if (not _options.defaultDirectory.isDirectory()) {
        _options.defaultDirectory = juce::File::getSpecialLocation(juce::File::userHomeDirectory);
    }

    _container.browse.onClick = [this] { launchFileChooser(); };
    _container.clear.onClick  = [this] { getValue().setValue(""); };
    addAndMakeVisible(_container);
}

void FilePropertyComponent::refresh() { _container.filename.setText(getValue().toString()); }

auto FilePropertyComponent::launchFileChooser() -> void
{
    using juce::FileBrowserComponent;

    auto options = _options.selectDirectory ? FileBrowserComponent::canSelectDirectories
                                            : FileBrowserComponent::openMode;

    auto dir = juce::File{getValue().toString()};
    if (not dir.isDirectory()) {
        dir = _options.defaultDirectory;
    }

    _chooser = std::make_unique<juce::FileChooser>(_options.title, dir, _options.pattern);
    _chooser->launchAsync(options, [this](juce::FileChooser const&) {
        getValue().setValue(_chooser->getResult().getFullPathName());
    });
}

FilePropertyComponent::Container::Container(bool showClearButton)
{
    addAndMakeVisible(filename);
    addAndMakeVisible(browse);
    if (showClearButton) {
        addAndMakeVisible(clear);
    }

    filename.setReadOnly(true);
}

void FilePropertyComponent::Container::resized()
{
    auto rc = getLocalBounds();
    if (clear.isVisible()) {
        clear.setBounds(rc.removeFromRight(rc.getHeight()));
    }
    browse.setBounds(rc.removeFromRight(rc.getHeight()));
    rc.removeFromRight(3);
    filename.setBounds(rc);
}

} // namespace jml
