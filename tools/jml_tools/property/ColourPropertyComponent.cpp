namespace jml {

ColourPropertyComponent::ColourPropertyComponent(
    juce::Value const& valueToControl,
    juce::String const& propertyName,
    bool showAlpha
)
    : ValuePropertyComponent(valueToControl, propertyName)
    , _container(getValue(), showAlpha)
{
    addAndMakeVisible(_container);
}

auto ColourPropertyComponent::refresh() -> void { repaint(); }

auto ColourPropertyComponent::paint(juce::Graphics& g) -> void
{
    PropertyComponent::paint(g);

    g.setColour(findColour(juce::BooleanPropertyComponent::backgroundColourId));
    g.fillRect(_container.getBounds());

    g.setColour(findColour(juce::BooleanPropertyComponent::outlineColourId));
    g.drawRect(_container.getBounds());
}

ColourPropertyComponent::Container::Container(juce::Value& v, bool a) : value(v), alpha(a) {}

auto ColourPropertyComponent::Container::paint(juce::Graphics& g) -> void
{
    auto const color = fromVar<juce::Colour>(value);

    g.setColour(color);
    g.fillRect(getLocalBounds().reduced(1));

    g.setColour(color.contrasting());
    g.drawText(color.toDisplayString(alpha), getLocalBounds(), juce::Justification::centred);
}

auto ColourPropertyComponent::Container::mouseUp(juce::MouseEvent const& event) -> void
{
    if (not event.mouseWasClicked()) {
        return;
    }

    auto cs = std::make_unique<juce::ColourSelector>();
    cs->setSize(300, 280);
    cs->setCurrentColour(fromVar<juce::Colour>(value), juce::dontSendNotification);
    cs->addChangeListener(this);

    juce::CallOutBox::launchAsynchronously(std::move(cs), getScreenBounds(), nullptr);
}

auto ColourPropertyComponent::Container::changeListenerCallback(juce::ChangeBroadcaster* source)
    -> void
{
    auto* const cs = dynamic_cast<juce::ColourSelector*>(source);
    jassert(cs != nullptr);
    if (cs == nullptr) {
        return;
    }
    value = toVar(cs->getCurrentColour());
}

} // namespace jml
