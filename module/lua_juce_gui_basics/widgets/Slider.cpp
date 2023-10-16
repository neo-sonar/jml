namespace lua_juce {
auto juce_Slider(sol::table& state) -> void
{

    auto params                 = state.new_usertype<juce::Slider::RotaryParameters>("SliderRotaryParameters");
    params["startAngleRadians"] = &juce::Slider::RotaryParameters::startAngleRadians;
    params["endAngleRadians"]   = &juce::Slider::RotaryParameters::endAngleRadians;
    params["stopAtEnd"]         = &juce::Slider::RotaryParameters::stopAtEnd;

    // clang-format off
    state.new_enum("SliderColourIds",
        "backgroundColourId",           juce::Slider::ColourIds::backgroundColourId,
        "thumbColourId",                juce::Slider::ColourIds::thumbColourId,
        "trackColourId",                juce::Slider::ColourIds::trackColourId,
        "rotarySliderFillColourId",     juce::Slider::ColourIds::rotarySliderFillColourId,
        "rotarySliderOutlineColourId",  juce::Slider::ColourIds::rotarySliderOutlineColourId,
        "textBoxBackgroundColourId",    juce::Slider::ColourIds::textBoxBackgroundColourId,
        "textBoxHighlightColourId",     juce::Slider::ColourIds::textBoxHighlightColourId,
        "textBoxOutlineColourId",       juce::Slider::ColourIds::textBoxOutlineColourId,
        "textBoxTextColourId",          juce::Slider::ColourIds::textBoxTextColourId
    );

    state.new_enum("SliderStyle",
        "LinearHorizontal",             juce::Slider::SliderStyle::LinearHorizontal,
        "LinearVertical",               juce::Slider::SliderStyle::LinearVertical,
        "LinearBar",                    juce::Slider::SliderStyle::LinearBar,
        "LinearBarVertical",            juce::Slider::SliderStyle::LinearBarVertical,
        "Rotary",                       juce::Slider::SliderStyle::Rotary,
        "RotaryHorizontalDrag",         juce::Slider::SliderStyle::RotaryHorizontalDrag,
        "RotaryVerticalDrag",           juce::Slider::SliderStyle::RotaryVerticalDrag,
        "RotaryHorizontalVerticalDrag", juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag,
        "IncDecButtons",                juce::Slider::SliderStyle::IncDecButtons,
        "TwoValueHorizontal",           juce::Slider::SliderStyle::TwoValueHorizontal,
        "TwoValueVertical",             juce::Slider::SliderStyle::TwoValueVertical,
        "ThreeValueHorizontal",         juce::Slider::SliderStyle::ThreeValueHorizontal,
        "ThreeValueVertical",           juce::Slider::SliderStyle::ThreeValueVertical
    );

    state.new_enum("SliderTextEntryBoxPosition",
        "NoTextBox",    juce::Slider::TextEntryBoxPosition::NoTextBox,
        "TextBoxLeft",  juce::Slider::TextEntryBoxPosition::TextBoxLeft,
        "TextBoxRight", juce::Slider::TextEntryBoxPosition::TextBoxRight,
        "TextBoxAbove", juce::Slider::TextEntryBoxPosition::TextBoxAbove,
        "TextBoxBelow", juce::Slider::TextEntryBoxPosition::TextBoxBelow
    );

    state.new_enum("SliderDragMode",
        "notDragging",  juce::Slider::DragMode::notDragging,
        "absoluteDrag", juce::Slider::DragMode::absoluteDrag,
        "velocityDrag", juce::Slider::DragMode::velocityDrag
    );

    auto slider = state.new_usertype<juce::Slider>("Slider",
        sol::constructors<
            juce::Slider(),
            juce::Slider(juce::String const&),
            juce::Slider(juce::Slider::SliderStyle, juce::Slider::TextEntryBoxPosition)
        >(),
        sol::base_classes,
        sol::bases<
            juce::MouseListener,
            juce::Component,
            juce::TooltipClient,
            juce::SettableTooltipClient
        >()
    );
    slider["setRange"] =  sol::overload(
            static_cast<void (juce::Slider::*)(juce::Range<double>, double)>(&juce::Slider::setRange),
            static_cast<void (juce::Slider::*)(double, double, double)>(&juce::Slider::setRange),
            [] (juce::Slider* self, double minValue, double maxValue) { self->setRange(minValue, maxValue); }
    );
    slider["setRotaryParameters"] =  sol::overload(
            static_cast<void (juce::Slider::*)(juce::Slider::RotaryParameters)>(&juce::Slider::setRotaryParameters),
            static_cast<void (juce::Slider::*)(float, float, bool)>(&juce::Slider::setRotaryParameters)
    );
    // clang-format on

    slider["setSliderStyle"]                     = LUA_JUCE_C_CALL(&juce::Slider::setSliderStyle);
    slider["getSliderStyle"]                     = LUA_JUCE_C_CALL(&juce::Slider::getSliderStyle);
    slider["getRotaryParameters"]                = LUA_JUCE_C_CALL(&juce::Slider::getRotaryParameters);
    slider["setMouseDragSensitivity"]            = LUA_JUCE_C_CALL(&juce::Slider::setMouseDragSensitivity);
    slider["getMouseDragSensitivity"]            = LUA_JUCE_C_CALL(&juce::Slider::getMouseDragSensitivity);
    slider["setVelocityBasedMode"]               = LUA_JUCE_C_CALL(&juce::Slider::setVelocityBasedMode);
    slider["getVelocityBasedMode"]               = LUA_JUCE_C_CALL(&juce::Slider::getVelocityBasedMode);
    slider["setVelocityModeParameters"]          = LUA_JUCE_C_CALL(&juce::Slider::setVelocityModeParameters);
    slider["getVelocitySensitivity"]             = LUA_JUCE_C_CALL(&juce::Slider::getVelocitySensitivity);
    slider["getVelocityThreshold"]               = LUA_JUCE_C_CALL(&juce::Slider::getVelocityThreshold);
    slider["getVelocityOffset"]                  = LUA_JUCE_C_CALL(&juce::Slider::getVelocityOffset);
    slider["getVelocityModeIsSwappable"]         = LUA_JUCE_C_CALL(&juce::Slider::getVelocityModeIsSwappable);
    slider["setSkewFactor"]                      = LUA_JUCE_C_CALL(&juce::Slider::setSkewFactor);
    slider["setSkewFactorFromMidPoint"]          = LUA_JUCE_C_CALL(&juce::Slider::setSkewFactorFromMidPoint);
    slider["getSkewFactor"]                      = LUA_JUCE_C_CALL(&juce::Slider::getSkewFactor);
    slider["isSymmetricSkew"]                    = LUA_JUCE_C_CALL(&juce::Slider::isSymmetricSkew);
    slider["setIncDecButtonsMode"]               = LUA_JUCE_C_CALL(&juce::Slider::setIncDecButtonsMode);
    slider["setTextBoxStyle"]                    = LUA_JUCE_C_CALL(&juce::Slider::setTextBoxStyle);
    slider["getTextBoxPosition"]                 = LUA_JUCE_C_CALL(&juce::Slider::getTextBoxPosition);
    slider["getTextBoxWidth"]                    = LUA_JUCE_C_CALL(&juce::Slider::getTextBoxWidth);
    slider["getTextBoxHeight"]                   = LUA_JUCE_C_CALL(&juce::Slider::getTextBoxHeight);
    slider["setTextBoxIsEditable"]               = LUA_JUCE_C_CALL(&juce::Slider::setTextBoxIsEditable);
    slider["isTextBoxEditable"]                  = LUA_JUCE_C_CALL(&juce::Slider::isTextBoxEditable);
    slider["showTextBox"]                        = LUA_JUCE_C_CALL(&juce::Slider::showTextBox);
    slider["hideTextBox"]                        = LUA_JUCE_C_CALL(&juce::Slider::hideTextBox);
    slider["getValue"]                           = LUA_JUCE_C_CALL(&juce::Slider::getValue);
    slider["getValueObject"]                     = LUA_JUCE_C_CALL(&juce::Slider::getValueObject);
    slider["setNormalisableRange"]               = LUA_JUCE_C_CALL(&juce::Slider::setNormalisableRange);
    slider["getRange"]                           = LUA_JUCE_C_CALL(&juce::Slider::getRange);
    slider["getMaximum"]                         = LUA_JUCE_C_CALL(&juce::Slider::getMaximum);
    slider["getMinimum"]                         = LUA_JUCE_C_CALL(&juce::Slider::getMinimum);
    slider["getInterval"]                        = LUA_JUCE_C_CALL(&juce::Slider::getInterval);
    slider["getMinValue"]                        = LUA_JUCE_C_CALL(&juce::Slider::getMinValue);
    slider["getMinValueObject"]                  = LUA_JUCE_C_CALL(&juce::Slider::getMinValueObject);
    slider["getMaxValue"]                        = LUA_JUCE_C_CALL(&juce::Slider::getMaxValue);
    slider["getMaxValueObject"]                  = LUA_JUCE_C_CALL(&juce::Slider::getMaxValueObject);
    slider["addListener"]                        = LUA_JUCE_C_CALL(&juce::Slider::addListener);
    slider["removeListener"]                     = LUA_JUCE_C_CALL(&juce::Slider::removeListener);
    slider["setDoubleClickReturnValue"]          = LUA_JUCE_C_CALL(&juce::Slider::setDoubleClickReturnValue);
    slider["getDoubleClickReturnValue"]          = LUA_JUCE_C_CALL(&juce::Slider::getDoubleClickReturnValue);
    slider["isDoubleClickReturnEnabled"]         = LUA_JUCE_C_CALL(&juce::Slider::isDoubleClickReturnEnabled);
    slider["setChangeNotificationOnlyOnRelease"] = LUA_JUCE_C_CALL(&juce::Slider::setChangeNotificationOnlyOnRelease);
    slider["setSliderSnapsToMousePosition"]      = LUA_JUCE_C_CALL(&juce::Slider::setSliderSnapsToMousePosition);
    slider["getSliderSnapsToMousePosition"]      = LUA_JUCE_C_CALL(&juce::Slider::getSliderSnapsToMousePosition);
    slider["setPopupDisplayEnabled"]             = LUA_JUCE_C_CALL(&juce::Slider::setPopupDisplayEnabled);
    slider["getCurrentPopupDisplay"]             = LUA_JUCE_C_CALL(&juce::Slider::getCurrentPopupDisplay);
    slider["setPopupMenuEnabled"]                = LUA_JUCE_C_CALL(&juce::Slider::setPopupMenuEnabled);
    slider["setScrollWheelEnabled"]              = LUA_JUCE_C_CALL(&juce::Slider::setScrollWheelEnabled);
    slider["isScrollWheelEnabled"]               = LUA_JUCE_C_CALL(&juce::Slider::isScrollWheelEnabled);
    slider["getThumbBeingDragged"]               = LUA_JUCE_C_CALL(&juce::Slider::getThumbBeingDragged);
    slider["startedDragging"]                    = LUA_JUCE_C_CALL(&juce::Slider::startedDragging);
    slider["stoppedDragging"]                    = LUA_JUCE_C_CALL(&juce::Slider::stoppedDragging);
    slider["valueChanged"]                       = LUA_JUCE_C_CALL(&juce::Slider::valueChanged);
    slider["getValueFromText"]                   = LUA_JUCE_C_CALL(&juce::Slider::getValueFromText);
    slider["getTextFromValue"]                   = LUA_JUCE_C_CALL(&juce::Slider::getTextFromValue);
    slider["setTextValueSuffix"]                 = LUA_JUCE_C_CALL(&juce::Slider::setTextValueSuffix);
    slider["getTextValueSuffix"]                 = LUA_JUCE_C_CALL(&juce::Slider::getTextValueSuffix);
    slider["getNumDecimalPlacesToDisplay"]       = LUA_JUCE_C_CALL(&juce::Slider::getNumDecimalPlacesToDisplay);
    slider["setNumDecimalPlacesToDisplay"]       = LUA_JUCE_C_CALL(&juce::Slider::setNumDecimalPlacesToDisplay);
    slider["proportionOfLengthToValue"]          = LUA_JUCE_C_CALL(&juce::Slider::proportionOfLengthToValue);
    slider["valueToProportionOfLength"]          = LUA_JUCE_C_CALL(&juce::Slider::valueToProportionOfLength);
    slider["getPositionOfValue"]                 = LUA_JUCE_C_CALL(&juce::Slider::getPositionOfValue);
    slider["snapValue"]                          = LUA_JUCE_C_CALL(&juce::Slider::snapValue);
    slider["updateText"]                         = LUA_JUCE_C_CALL(&juce::Slider::updateText);
    slider["isHorizontal"]                       = LUA_JUCE_C_CALL(&juce::Slider::isHorizontal);
    slider["isVertical"]                         = LUA_JUCE_C_CALL(&juce::Slider::isVertical);
    slider["isRotary"]                           = LUA_JUCE_C_CALL(&juce::Slider::isRotary);
    slider["isBar"]                              = LUA_JUCE_C_CALL(&juce::Slider::isBar);
    slider["isTwoValue"]                         = LUA_JUCE_C_CALL(&juce::Slider::isTwoValue);

    // slider["setValue"]                           = &juce::Slider::setValue;
    // slider["setMinValue"]                        = &juce::Slider::setMinValue;
    // slider["setMaxValue"]                        = &juce::Slider::setMaxValue;
    // slider["setMinAndMaxValues"]                 = &juce::Slider::setMinAndMaxValues;

    slider["onValueChange"] = &juce::Slider::onValueChange;
    // slider["onDragStart"]           = &juce::Slider::onDragStart;
    // slider["onDragEnd"]             = &juce::Slider::onDragEnd;
    // slider["valueFromTextFunction"] = &juce::Slider::valueFromTextFunction;
    // slider["textFromValueFunction"] = &juce::Slider::textFromValueFunction;
}
} // namespace lua_juce
