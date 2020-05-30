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

#include "PrTouchCurveComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PrTouchCurveComponent::PrTouchCurveComponent (Settings& settings, PianoController& pianoController)
    : PrBaseComponent(settings, pianoController)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    soft2Button.reset (new TextButton (String()));
    addAndMakeVisible (soft2Button.get());
    soft2Button->setButtonText (TRANS("Soft 2"));
    soft2Button->setConnectedEdges (Button::ConnectedOnRight);
    soft2Button->addListener (this);

    soft2Button->setBounds (272, 16, 110, 28);

    soft1Button.reset (new TextButton (String()));
    addAndMakeVisible (soft1Button.get());
    soft1Button->setButtonText (TRANS("Soft 1"));
    soft1Button->setConnectedEdges (Button::ConnectedOnLeft);
    soft1Button->addListener (this);

    soft1Button->setBounds (388, 16, 110, 28);

    titleLabel.reset (new Label (String(),
                                 TRANS("Touch Curve")));
    addAndMakeVisible (titleLabel.get());
    titleLabel->setFont (Font (16.00f, Font::plain).withTypefaceStyle ("Regular"));
    titleLabel->setJustificationType (Justification::centredLeft);
    titleLabel->setEditable (false, false, false);
    titleLabel->setColour (TextEditor::textColourId, Colours::black);
    titleLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    titleLabel->setBounds (18, 12, 238, 24);

    mediumButton.reset (new TextButton (String()));
    addAndMakeVisible (mediumButton.get());
    mediumButton->setButtonText (TRANS("Medium"));
    mediumButton->setConnectedEdges (Button::ConnectedOnLeft);
    mediumButton->addListener (this);

    mediumButton->setBounds (504, 16, 110, 28);

    hard1Button.reset (new TextButton (String()));
    addAndMakeVisible (hard1Button.get());
    hard1Button->setButtonText (TRANS("Hard 1"));
    hard1Button->setConnectedEdges (Button::ConnectedOnRight);
    hard1Button->addListener (this);

    hard1Button->setBounds (272, 56, 110, 28);

    hard2Button.reset (new TextButton (String()));
    addAndMakeVisible (hard2Button.get());
    hard2Button->setButtonText (TRANS("Hard 2"));
    hard2Button->setConnectedEdges (Button::ConnectedOnLeft);
    hard2Button->addListener (this);

    hard2Button->setBounds (388, 56, 110, 28);

    fixedButton.reset (new TextButton (String()));
    addAndMakeVisible (fixedButton.get());
    fixedButton->setButtonText (TRANS("Fixed"));
    fixedButton->setConnectedEdges (Button::ConnectedOnLeft);
    fixedButton->addListener (this);

    fixedButton->setBounds (504, 56, 110, 28);

    slider.reset (new Slider (String()));
    addAndMakeVisible (slider.get());
    slider->setRange (-10, 10, 1);
    slider->setSliderStyle (Slider::LinearHorizontal);
    slider->setTextBoxStyle (Slider::TextBoxAbove, false, 80, 20);
    slider->addListener (this);

    slider->setBounds (272, 120, 344, 52);

    velocityLabel.reset (new Label (String(),
                                    TRANS("Velocity")));
    addAndMakeVisible (velocityLabel.get());
    velocityLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    velocityLabel->setJustificationType (Justification::centredLeft);
    velocityLabel->setEditable (false, false, false);
    velocityLabel->setColour (TextEditor::textColourId, Colours::black);
    velocityLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    velocityLabel->setBounds (278, 104, 150, 24);


    //[UserPreSize]
    soft1Button->getProperties().set("toggle", "yes");
    soft2Button->getProperties().set("toggle", "yes");
    mediumButton->getProperties().set("toggle", "yes");
    hard1Button->getProperties().set("toggle", "yes");
    hard2Button->getProperties().set("toggle", "yes");
    fixedButton->getProperties().set("toggle", "yes");
	mediumButton->setToggleState(true, NotificationType::dontSendNotification);
    //[/UserPreSize]

    setSize (640, 180);


    //[Constructor] You can add your own custom stuff here..

	// Fixed curve is not yet implemented
    fixedButton->setEnabled(false);
    velocityLabel->setEnabled(false);
    slider->setEnabled(false);

    updatePianoState(PianoController::apActive);
    //[/Constructor]
}

PrTouchCurveComponent::~PrTouchCurveComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    soft2Button = nullptr;
    soft1Button = nullptr;
    titleLabel = nullptr;
    mediumButton = nullptr;
    hard1Button = nullptr;
    hard2Button = nullptr;
    fixedButton = nullptr;
    slider = nullptr;
    velocityLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PrTouchCurveComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    PrBaseComponent::paint(g);
    //[/UserPaint]
}

void PrTouchCurveComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void PrTouchCurveComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == soft2Button.get())
    {
        //[UserButtonCode_soft2Button] -- add your button handler code here..
		pianoController.SetTouchCurve(PianoController::tcSoft2);
        //[/UserButtonCode_soft2Button]
    }
    else if (buttonThatWasClicked == soft1Button.get())
    {
        //[UserButtonCode_soft1Button] -- add your button handler code here..
		pianoController.SetTouchCurve(PianoController::tcSoft1);
        //[/UserButtonCode_soft1Button]
    }
    else if (buttonThatWasClicked == mediumButton.get())
    {
        //[UserButtonCode_mediumButton] -- add your button handler code here..
		pianoController.SetTouchCurve(PianoController::tcMedium);
        //[/UserButtonCode_mediumButton]
    }
    else if (buttonThatWasClicked == hard1Button.get())
    {
        //[UserButtonCode_hard1Button] -- add your button handler code here..
		pianoController.SetTouchCurve(PianoController::tcHard1);
        //[/UserButtonCode_hard1Button]
    }
    else if (buttonThatWasClicked == hard2Button.get())
    {
        //[UserButtonCode_hard2Button] -- add your button handler code here..
		pianoController.SetTouchCurve(PianoController::tcHard2);
        //[/UserButtonCode_hard2Button]
    }
    else if (buttonThatWasClicked == fixedButton.get())
    {
        //[UserButtonCode_fixedButton] -- add your button handler code here..
        //[/UserButtonCode_fixedButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void PrTouchCurveComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == slider.get())
    {
        //[UserSliderCode_slider] -- add your slider handling code here..
        //[/UserSliderCode_slider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PrTouchCurveComponent::updatePianoState(PianoController::Aspect aspect)
{
	bool enabled = pianoController.IsConnected();

	soft2Button->setEnabled(enabled);
	soft1Button->setEnabled(enabled);
	mediumButton->setEnabled(enabled);
	hard1Button->setEnabled(enabled);
	hard2Button->setEnabled(enabled);

	soft2Button->setToggleState(enabled && pianoController.GetTouchCurve() == PianoController::tcSoft2, NotificationType::dontSendNotification);
	soft1Button->setToggleState(enabled && pianoController.GetTouchCurve() == PianoController::tcSoft1, NotificationType::dontSendNotification);
	mediumButton->setToggleState(enabled && pianoController.GetTouchCurve() == PianoController::tcMedium, NotificationType::dontSendNotification);
	hard1Button->setToggleState(enabled && pianoController.GetTouchCurve() == PianoController::tcHard1, NotificationType::dontSendNotification);
	hard2Button->setToggleState(enabled && pianoController.GetTouchCurve() == PianoController::tcHard2, NotificationType::dontSendNotification);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PrTouchCurveComponent" componentName=""
                 parentClasses="public PrBaseComponent" constructorParams="Settings&amp; settings, PianoController&amp; pianoController"
                 variableInitialisers="PrBaseComponent(settings, pianoController)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="640" initialHeight="180">
  <BACKGROUND backgroundColour="ff323e44"/>
  <TEXTBUTTON name="" id="42d5819d1fa8801e" memberName="soft2Button" virtualName=""
              explicitFocusOrder="0" pos="272 16 110 28" posRelativeX="f4f376ddb622016f"
              posRelativeY="56427593ca278ddd" buttonText="Soft 2" connectedEdges="2"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="76962b892ea540d0" memberName="soft1Button" virtualName=""
              explicitFocusOrder="0" pos="388 16 110 28" posRelativeY="56427593ca278ddd"
              buttonText="Soft 1" connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <LABEL name="" id="dc20d157ffc118c5" memberName="titleLabel" virtualName=""
         explicitFocusOrder="0" pos="18 12 238 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Touch Curve" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="16.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="" id="45945c8dbddf69e7" memberName="mediumButton" virtualName=""
              explicitFocusOrder="0" pos="504 16 110 28" posRelativeY="56427593ca278ddd"
              buttonText="Medium" connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="c3456c628b935d88" memberName="hard1Button" virtualName=""
              explicitFocusOrder="0" pos="272 56 110 28" posRelativeX="f4f376ddb622016f"
              posRelativeY="56427593ca278ddd" buttonText="Hard 1" connectedEdges="2"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="834e45000a187b3b" memberName="hard2Button" virtualName=""
              explicitFocusOrder="0" pos="388 56 110 28" posRelativeY="56427593ca278ddd"
              buttonText="Hard 2" connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="48028fc78c2edd16" memberName="fixedButton" virtualName=""
              explicitFocusOrder="0" pos="504 56 110 28" posRelativeY="56427593ca278ddd"
              buttonText="Fixed" connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <SLIDER name="" id="cb1eec80b99d9306" memberName="slider" virtualName=""
          explicitFocusOrder="0" pos="272 120 344 52" min="-10.0" max="10.0"
          int="1.0" style="LinearHorizontal" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="" id="1cc55609f8698f9d" memberName="velocityLabel" virtualName=""
         explicitFocusOrder="0" pos="278 104 150 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Velocity" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

