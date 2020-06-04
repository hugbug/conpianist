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

#include "PrDamperResonanceComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PrDamperResonanceComponent::PrDamperResonanceComponent (Settings& settings, PianoController& pianoController)
    : PrBaseComponent(settings, pianoController)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    slider.reset (new Slider (String()));
    addAndMakeVisible (slider.get());
    slider->setRange (0, 10, 1);
    slider->setSliderStyle (Slider::LinearHorizontal);
    slider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    slider->addListener (this);

    slider->setBounds (272, 38, 344, 24);

    depthLabel.reset (new Label (String(),
                                 TRANS("Depth")));
    addAndMakeVisible (depthLabel.get());
    depthLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    depthLabel->setJustificationType (Justification::centred);
    depthLabel->setEditable (false, false, false);
    depthLabel->setColour (TextEditor::textColourId, Colours::black);
    depthLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    depthLabel->setBounds (400, 12, 88, 24);

    titleLabel.reset (new Label (String(),
                                 TRANS("Damper Resonance")));
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

PrDamperResonanceComponent::~PrDamperResonanceComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    slider = nullptr;
    depthLabel = nullptr;
    titleLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PrDamperResonanceComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    PrBaseComponent::paint(g);
	drawSliderMark(g, slider.get());
    //[/UserPaint]
}

void PrDamperResonanceComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void PrDamperResonanceComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == slider.get())
    {
        //[UserSliderCode_slider] -- add your slider handling code here..
        inSliderChange++;
        pianoController.SetDamperResonance(slider->getValue());
        //[/UserSliderCode_slider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PrDamperResonanceComponent::updatePianoState(PianoController::Aspect aspect)
{
	if (aspect == PianoController::apDamperResonance && inSliderChange && inSliderChange--) return;

	if (aspect == PianoController::apConnection)
	{
		inSliderChange = 0;
	}

	slider->setEnabled(pianoController.IsConnected() && pianoController.GetVrm());
	slider->setValue(pianoController.GetDamperResonance(), NotificationType::dontSendNotification);
	titleLabel->setEnabled(pianoController.IsConnected() && pianoController.GetVrm());
	depthLabel->setEnabled(pianoController.IsConnected() && pianoController.GetVrm());

	repaint(); // for slider mark
}

void PrDamperResonanceComponent::mouseDoubleClick (const MouseEvent& e)
{
    pianoController.SetDamperResonance(PianoController::DefaultResonance);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PrDamperResonanceComponent"
                 componentName="" parentClasses="public PrBaseComponent" constructorParams="Settings&amp; settings, PianoController&amp; pianoController"
                 variableInitialisers="PrBaseComponent(settings, pianoController)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="640" initialHeight="74">
  <BACKGROUND backgroundColour="ff323e44"/>
  <SLIDER name="" id="ddd023939bd49970" memberName="slider" virtualName=""
          explicitFocusOrder="0" pos="272 38 344 24" min="0.0" max="10.0"
          int="1.0" style="LinearHorizontal" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <LABEL name="" id="7b567f4e1ba148c9" memberName="depthLabel" virtualName=""
         explicitFocusOrder="0" pos="400 12 88 24" posRelativeY="c7b94b60aa96c6e2"
         edTextCol="ff000000" edBkgCol="0" labelText="Depth" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="dc20d157ffc118c5" memberName="titleLabel" virtualName=""
         explicitFocusOrder="0" pos="18 12 238 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Damper Resonance" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="16.0" kerning="0.0" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

