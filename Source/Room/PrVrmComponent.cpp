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

#include "PrVrmComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PrVrmComponent::PrVrmComponent (Settings& settings, PianoController& pianoController)
    : PrBaseComponent(settings, pianoController)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    offButton.reset (new TextButton (String()));
    addAndMakeVisible (offButton.get());
    offButton->setButtonText (TRANS("Off"));
    offButton->setConnectedEdges (Button::ConnectedOnRight);
    offButton->addListener (this);

    offButton->setBounds (328, 16, 110, 28);

    onButton.reset (new TextButton (String()));
    addAndMakeVisible (onButton.get());
    onButton->setButtonText (TRANS("On"));
    onButton->setConnectedEdges (Button::ConnectedOnLeft);
    onButton->addListener (this);

    onButton->setBounds (444, 16, 110, 28);

    titleLabel.reset (new Label (String(),
                                 TRANS("Virtual Resonance Modelling")));
    addAndMakeVisible (titleLabel.get());
    titleLabel->setFont (Font (16.00f, Font::plain).withTypefaceStyle ("Regular"));
    titleLabel->setJustificationType (Justification::centredLeft);
    titleLabel->setEditable (false, false, false);
    titleLabel->setColour (TextEditor::textColourId, Colours::black);
    titleLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    titleLabel->setBounds (18, 12, 238, 24);


    //[UserPreSize]
    offButton->getProperties().set("toggle", "yes");
    onButton->getProperties().set("toggle", "yes");
	onButton->setToggleState(true, NotificationType::dontSendNotification);
    //[/UserPreSize]

    setSize (640, 64);


    //[Constructor] You can add your own custom stuff here..
    updatePianoState(PianoController::apActive);
    //[/Constructor]
}

PrVrmComponent::~PrVrmComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    offButton = nullptr;
    onButton = nullptr;
    titleLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PrVrmComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    PrBaseComponent::paint(g);
    //[/UserPaint]
}

void PrVrmComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void PrVrmComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == offButton.get())
    {
        //[UserButtonCode_offButton] -- add your button handler code here..
        pianoController.SetVrm(false);
        //[/UserButtonCode_offButton]
    }
    else if (buttonThatWasClicked == onButton.get())
    {
        //[UserButtonCode_onButton] -- add your button handler code here..
        pianoController.SetVrm(true);
        //[/UserButtonCode_onButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PrVrmComponent::updatePianoState(PianoController::Aspect aspect)
{
	bool enabled = pianoController.IsConnected();

	offButton->setEnabled(enabled);
	onButton->setEnabled(enabled);

	offButton->setToggleState(enabled && !pianoController.GetVrm(), NotificationType::dontSendNotification);
	onButton->setToggleState(enabled && pianoController.GetVrm(), NotificationType::dontSendNotification);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PrVrmComponent" componentName=""
                 parentClasses="public PrBaseComponent" constructorParams="Settings&amp; settings, PianoController&amp; pianoController"
                 variableInitialisers="PrBaseComponent(settings, pianoController)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="640" initialHeight="64">
  <BACKGROUND backgroundColour="ff323e44"/>
  <TEXTBUTTON name="" id="42d5819d1fa8801e" memberName="offButton" virtualName=""
              explicitFocusOrder="0" pos="328 16 110 28" posRelativeX="f4f376ddb622016f"
              posRelativeY="56427593ca278ddd" buttonText="Off" connectedEdges="2"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="76962b892ea540d0" memberName="onButton" virtualName=""
              explicitFocusOrder="0" pos="444 16 110 28" posRelativeY="56427593ca278ddd"
              buttonText="On" connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <LABEL name="" id="dc20d157ffc118c5" memberName="titleLabel" virtualName=""
         explicitFocusOrder="0" pos="18 12 238 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Virtual Resonance Modelling" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="16.0" kerning="0.0" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

