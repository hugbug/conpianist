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

#include "PrLidPositionComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PrLidPositionComponent::PrLidPositionComponent (Settings& settings, PianoController& pianoController)
    : PrBaseComponent(settings, pianoController)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    closeButton.reset (new TextButton (String()));
    addAndMakeVisible (closeButton.get());
    closeButton->setButtonText (TRANS("Close"));
    closeButton->setConnectedEdges (Button::ConnectedOnRight);
    closeButton->addListener (this);

    closeButton->setBounds (272, 16, 110, 28);

    halfButton.reset (new TextButton (String()));
    addAndMakeVisible (halfButton.get());
    halfButton->setButtonText (TRANS("Half Open"));
    halfButton->setConnectedEdges (Button::ConnectedOnLeft | Button::ConnectedOnRight);
    halfButton->addListener (this);

    halfButton->setBounds (388, 16, 110, 28);

    openButton.reset (new TextButton (String()));
    addAndMakeVisible (openButton.get());
    openButton->setButtonText (TRANS("Open"));
    openButton->setConnectedEdges (Button::ConnectedOnLeft);
    openButton->addListener (this);

    openButton->setBounds (504, 16, 110, 28);

    titleLabel.reset (new Label (String(),
                                 TRANS("Lid Position")));
    addAndMakeVisible (titleLabel.get());
    titleLabel->setFont (Font (16.00f, Font::plain).withTypefaceStyle ("Regular"));
    titleLabel->setJustificationType (Justification::centredLeft);
    titleLabel->setEditable (false, false, false);
    titleLabel->setColour (TextEditor::textColourId, Colours::black);
    titleLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    titleLabel->setBounds (18, 12, 238, 24);


    //[UserPreSize]
    openButton->getProperties().set("toggle", "yes");
    halfButton->getProperties().set("toggle", "yes");
    closeButton->getProperties().set("toggle", "yes");
	openButton->setToggleState(true, NotificationType::dontSendNotification);
    //[/UserPreSize]

    setSize (640, 64);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

PrLidPositionComponent::~PrLidPositionComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    closeButton = nullptr;
    halfButton = nullptr;
    openButton = nullptr;
    titleLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PrLidPositionComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    PrBaseComponent::paint(g);
    //[/UserPaint]
}

void PrLidPositionComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void PrLidPositionComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == closeButton.get())
    {
        //[UserButtonCode_closeButton] -- add your button handler code here..
        //[/UserButtonCode_closeButton]
    }
    else if (buttonThatWasClicked == halfButton.get())
    {
        //[UserButtonCode_halfButton] -- add your button handler code here..
        //[/UserButtonCode_halfButton]
    }
    else if (buttonThatWasClicked == openButton.get())
    {
        //[UserButtonCode_openButton] -- add your button handler code here..
        //[/UserButtonCode_openButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PrLidPositionComponent" componentName=""
                 parentClasses="public PrBaseComponent" constructorParams="Settings&amp; settings, PianoController&amp; pianoController"
                 variableInitialisers="PrBaseComponent(settings, pianoController)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="640" initialHeight="64">
  <BACKGROUND backgroundColour="ff323e44"/>
  <TEXTBUTTON name="" id="3c4e14578c159f0c" memberName="closeButton" virtualName=""
              explicitFocusOrder="0" pos="272 16 110 28" posRelativeX="f4f376ddb622016f"
              posRelativeY="56427593ca278ddd" buttonText="Close" connectedEdges="2"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="8bfde978d6921706" memberName="halfButton" virtualName=""
              explicitFocusOrder="0" pos="388 16 110 28" posRelativeY="56427593ca278ddd"
              buttonText="Half Open" connectedEdges="3" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="ea01e0121c877034" memberName="openButton" virtualName=""
              explicitFocusOrder="0" pos="504 16 110 28" posRelativeY="56427593ca278ddd"
              buttonText="Open" connectedEdges="1" needsCallback="1" radioGroupId="0"/>
  <LABEL name="" id="dc20d157ffc118c5" memberName="titleLabel" virtualName=""
         explicitFocusOrder="0" pos="18 12 238 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Lid Position" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="16.0" kerning="0.0" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

