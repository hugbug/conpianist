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

#include "PrHalfPedalPointComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PrHalfPedalPointComponent::PrHalfPedalPointComponent (Settings& settings, PianoController& pianoController)
    : PrBaseComponent(settings, pianoController)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    valm2Button.reset (new TextButton (String()));
    addAndMakeVisible (valm2Button.get());
    valm2Button->setButtonText (TRANS("-2"));
    valm2Button->addListener (this);

    valm2Button->setBounds (284, 16, 60, 28);

    valm1Button.reset (new TextButton (String()));
    addAndMakeVisible (valm1Button.get());
    valm1Button->setButtonText (TRANS("-1"));
    valm1Button->addListener (this);

    valm1Button->setBounds (348, 16, 60, 28);

    titleLabel.reset (new Label (String(),
                                 TRANS("Half Pedal Point")));
    addAndMakeVisible (titleLabel.get());
    titleLabel->setFont (Font (16.00f, Font::plain).withTypefaceStyle ("Regular"));
    titleLabel->setJustificationType (Justification::centredLeft);
    titleLabel->setEditable (false, false, false);
    titleLabel->setColour (TextEditor::textColourId, Colours::black);
    titleLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    titleLabel->setBounds (18, 12, 238, 24);

    val0Button.reset (new TextButton (String()));
    addAndMakeVisible (val0Button.get());
    val0Button->setButtonText (TRANS("0"));
    val0Button->addListener (this);

    val0Button->setBounds (412, 16, 60, 28);

    valp1Button.reset (new TextButton (String()));
    addAndMakeVisible (valp1Button.get());
    valp1Button->setButtonText (TRANS("+1"));
    valp1Button->addListener (this);

    valp1Button->setBounds (476, 16, 60, 28);

    valp2Button.reset (new TextButton (String()));
    addAndMakeVisible (valp2Button.get());
    valp2Button->setButtonText (TRANS("+2"));
    valp2Button->addListener (this);

    valp2Button->setBounds (540, 16, 60, 28);


    //[UserPreSize]
    valm2Button->getProperties().set("toggle", "yes");
    valm1Button->getProperties().set("toggle", "yes");
    val0Button->getProperties().set("toggle", "yes");
    valp1Button->getProperties().set("toggle", "yes");
    valp2Button->getProperties().set("toggle", "yes");
	val0Button->setToggleState(true, NotificationType::dontSendNotification);
    //[/UserPreSize]

    setSize (640, 64);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

PrHalfPedalPointComponent::~PrHalfPedalPointComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    valm2Button = nullptr;
    valm1Button = nullptr;
    titleLabel = nullptr;
    val0Button = nullptr;
    valp1Button = nullptr;
    valp2Button = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PrHalfPedalPointComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    PrBaseComponent::paint(g);
    //[/UserPaint]
}

void PrHalfPedalPointComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void PrHalfPedalPointComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == valm2Button.get())
    {
        //[UserButtonCode_valm2Button] -- add your button handler code here..
        //[/UserButtonCode_valm2Button]
    }
    else if (buttonThatWasClicked == valm1Button.get())
    {
        //[UserButtonCode_valm1Button] -- add your button handler code here..
        //[/UserButtonCode_valm1Button]
    }
    else if (buttonThatWasClicked == val0Button.get())
    {
        //[UserButtonCode_val0Button] -- add your button handler code here..
        //[/UserButtonCode_val0Button]
    }
    else if (buttonThatWasClicked == valp1Button.get())
    {
        //[UserButtonCode_valp1Button] -- add your button handler code here..
        //[/UserButtonCode_valp1Button]
    }
    else if (buttonThatWasClicked == valp2Button.get())
    {
        //[UserButtonCode_valp2Button] -- add your button handler code here..
        //[/UserButtonCode_valp2Button]
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

<JUCER_COMPONENT documentType="Component" className="PrHalfPedalPointComponent"
                 componentName="" parentClasses="public PrBaseComponent" constructorParams="Settings&amp; settings, PianoController&amp; pianoController"
                 variableInitialisers="PrBaseComponent(settings, pianoController)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="640" initialHeight="64">
  <BACKGROUND backgroundColour="ff323e44"/>
  <TEXTBUTTON name="" id="42d5819d1fa8801e" memberName="valm2Button" virtualName=""
              explicitFocusOrder="0" pos="284 16 60 28" posRelativeX="f4f376ddb622016f"
              posRelativeY="56427593ca278ddd" buttonText="-2" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="76962b892ea540d0" memberName="valm1Button" virtualName=""
              explicitFocusOrder="0" pos="348 16 60 28" posRelativeY="56427593ca278ddd"
              buttonText="-1" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="" id="dc20d157ffc118c5" memberName="titleLabel" virtualName=""
         explicitFocusOrder="0" pos="18 12 238 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Half Pedal Point" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="16.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="" id="298204364598c165" memberName="val0Button" virtualName=""
              explicitFocusOrder="0" pos="412 16 60 28" posRelativeY="56427593ca278ddd"
              buttonText="0" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="230b58ed63a38799" memberName="valp1Button" virtualName=""
              explicitFocusOrder="0" pos="476 16 60 28" posRelativeY="56427593ca278ddd"
              buttonText="+1" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="" id="fa752959194d152c" memberName="valp2Button" virtualName=""
              explicitFocusOrder="0" pos="540 16 60 28" posRelativeY="56427593ca278ddd"
              buttonText="+2" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

