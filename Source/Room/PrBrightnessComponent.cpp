/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.7

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PrBrightnessComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PrBrightnessComponent::PrBrightnessComponent (Settings& settings, PianoController& pianoController)
    : PrBaseComponent(settings, pianoController)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    slider.reset (new Slider (String()));
    addAndMakeVisible (slider.get());
    slider->setRange (0, 127, 1);
    slider->setSliderStyle (Slider::LinearHorizontal);
    slider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    slider->addListener (this);

    slider->setBounds (272, 38, 344, 24);

    mellowLabel.reset (new Label (String(),
                                  TRANS("Mellow")));
    addAndMakeVisible (mellowLabel.get());
    mellowLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    mellowLabel->setJustificationType (Justification::centredLeft);
    mellowLabel->setEditable (false, false, false);
    mellowLabel->setColour (TextEditor::textColourId, Colours::black);
    mellowLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    mellowLabel->setBounds (272, 12, 88, 24);

    brightLabel.reset (new Label (String(),
                                  TRANS("Bright")));
    addAndMakeVisible (brightLabel.get());
    brightLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    brightLabel->setJustificationType (Justification::centredRight);
    brightLabel->setEditable (false, false, false);
    brightLabel->setColour (TextEditor::textColourId, Colours::black);
    brightLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    brightLabel->setBounds (528, 12, 88, 24);

    titleLabel.reset (new Label (String(),
                                 TRANS("Brightness")));
    addAndMakeVisible (titleLabel.get());
    titleLabel->setFont (Font (16.00f, Font::plain).withTypefaceStyle ("Regular"));
    titleLabel->setJustificationType (Justification::centredLeft);
    titleLabel->setEditable (false, false, false);
    titleLabel->setColour (TextEditor::textColourId, Colours::black);
    titleLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    titleLabel->setBounds (18, 12, 238, 24);


    //[UserPreSize]
	slider->setScrollWheelEnabled(false);
    //[/UserPreSize]

    setSize (640, 74);


    //[Constructor] You can add your own custom stuff here..
    slider->addMouseListener(this, false);
    updatePianoState(PianoController::apActive);
    //[/Constructor]
}

PrBrightnessComponent::~PrBrightnessComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    slider = nullptr;
    mellowLabel = nullptr;
    brightLabel = nullptr;
    titleLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PrBrightnessComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    PrBaseComponent::paint(g);
	drawSliderMark(g, slider.get(), slider->proportionOfWidth((double)0x40/(double)0x7f));
    //[/UserPaint]
}

void PrBrightnessComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void PrBrightnessComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == slider.get())
    {
        //[UserSliderCode_slider] -- add your slider handling code here..
        inSliderChange++;
        pianoController.SetBrightness(slider->getValue());
        //[/UserSliderCode_slider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PrBrightnessComponent::updatePianoState(PianoController::Aspect aspect)
{
	if (aspect == PianoController::apBrightness && inSliderChange && inSliderChange--) return;

	if (aspect == PianoController::apConnection)
	{
		inSliderChange = 0;
	}

	titleLabel->setEnabled(pianoController.IsConnected());
	mellowLabel->setEnabled(pianoController.IsConnected());
	brightLabel->setEnabled(pianoController.IsConnected());
	slider->setEnabled(pianoController.IsConnected());
	slider->setValue(pianoController.GetBrightness(), NotificationType::dontSendNotification);

	repaint(); // for slider mark
}

void PrBrightnessComponent::mouseDoubleClick (const MouseEvent& e)
{
    pianoController.SetBrightness(PianoController::DefaultBrightness);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PrBrightnessComponent" componentName=""
                 parentClasses="public PrBaseComponent" constructorParams="Settings&amp; settings, PianoController&amp; pianoController"
                 variableInitialisers="PrBaseComponent(settings, pianoController)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="640" initialHeight="74">
  <BACKGROUND backgroundColour="ff323e44"/>
  <SLIDER name="" id="98f6a57b48738dcf" memberName="slider" virtualName=""
          explicitFocusOrder="0" pos="272 38 344 24" min="0.0" max="127.0"
          int="1.0" style="LinearHorizontal" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <LABEL name="" id="41de6fa00dd29466" memberName="mellowLabel" virtualName=""
         explicitFocusOrder="0" pos="272 12 88 24" posRelativeY="c7b94b60aa96c6e2"
         edTextCol="ff000000" edBkgCol="0" labelText="Mellow" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="" id="f4c6f8afafd937d5" memberName="brightLabel" virtualName=""
         explicitFocusOrder="0" pos="528 12 88 24" posRelativeY="c7b94b60aa96c6e2"
         edTextCol="ff000000" edBkgCol="0" labelText="Bright" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="34"/>
  <LABEL name="" id="dc20d157ffc118c5" memberName="titleLabel" virtualName=""
         explicitFocusOrder="0" pos="18 12 238 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Brightness" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="16.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

