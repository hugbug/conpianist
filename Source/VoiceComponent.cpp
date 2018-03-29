/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.3.0

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "VoiceComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
VoiceComponent::VoiceComponent (PianoController& pianoController)
    : pianoController(pianoController)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (targetGroup = new GroupComponent ("Target Group",
                                                         TRANS("Target")));
    targetGroup->setTextLabelPosition (Justification::centred);

    addAndMakeVisible (mainTitleLabel = new Label ("Main Title Label",
                                                   TRANS("Main\n")));
    mainTitleLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    mainTitleLabel->setJustificationType (Justification::centred);
    mainTitleLabel->setEditable (false, false, false);
    mainTitleLabel->setColour (TextEditor::textColourId, Colours::black);
    mainTitleLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (leftTitlelabel = new Label ("Left Title Label",
                                                   TRANS("Left")));
    leftTitlelabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    leftTitlelabel->setJustificationType (Justification::centred);
    leftTitlelabel->setEditable (false, false, false);
    leftTitlelabel->setColour (TextEditor::textColourId, Colours::black);
    leftTitlelabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (layerTitleLabel = new Label ("Layer Title Label",
                                                    TRANS("Layer")));
    layerTitleLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    layerTitleLabel->setJustificationType (Justification::centred);
    layerTitleLabel->setEditable (false, false, false);
    layerTitleLabel->setColour (TextEditor::textColourId, Colours::black);
    layerTitleLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (voicesTree = new TreeView ("Voices TreeView"));
    voicesTree->setRootItemVisible (false);

    addAndMakeVisible (leftVoiceButton = new TextButton ("Left Voice Button"));
    leftVoiceButton->setButtonText (TRANS("None"));
    leftVoiceButton->setRadioGroupId (1);
    leftVoiceButton->addListener (this);

    addAndMakeVisible (mainVoiceButton = new TextButton ("Main Voice Button"));
    mainVoiceButton->setButtonText (TRANS("Yamaha CFX Grand"));
    mainVoiceButton->setRadioGroupId (1);
    mainVoiceButton->addListener (this);

    addAndMakeVisible (layerVoiceButton = new TextButton ("Layer Voice Button"));
    layerVoiceButton->setButtonText (TRANS("Strings"));
    layerVoiceButton->setRadioGroupId (1);
    layerVoiceButton->addListener (this);


    //[UserPreSize]
    targetGroup->setColour(GroupComponent::outlineColourId, Colours::transparentBlack);
    targetGroup->setText("");
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    pianoController.addChangeListener(this);

    leftVoiceButton->getProperties().set("toggle", "yes");
    mainVoiceButton->getProperties().set("toggle", "yes");
    layerVoiceButton->getProperties().set("toggle", "yes");

    mainVoiceButton->setToggleState(true, NotificationType::dontSendNotification);
    //[/Constructor]
}

VoiceComponent::~VoiceComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    targetGroup = nullptr;
    mainTitleLabel = nullptr;
    leftTitlelabel = nullptr;
    layerTitleLabel = nullptr;
    voicesTree = nullptr;
    leftVoiceButton = nullptr;
    mainVoiceButton = nullptr;
    layerVoiceButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void VoiceComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void VoiceComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    targetGroup->setBounds (0, -8, getWidth() - 0, 88);
    mainTitleLabel->setBounds (0 + (getWidth() - 0) / 2 - (proportionOfWidth (0.3030f) / 2), (-8) + 16, proportionOfWidth (0.3030f), 24);
    leftTitlelabel->setBounds (0 + 16, (-8) + 16, proportionOfWidth (0.3030f), 24);
    layerTitleLabel->setBounds (0 + (getWidth() - 0) - 17 - proportionOfWidth (0.3030f), (-8) + 16, proportionOfWidth (0.3030f), 24);
    voicesTree->setBounds (8, (-8) + 88, getWidth() - 16, getHeight() - 88);
    leftVoiceButton->setBounds (0 + 16, (-8) + 48, proportionOfWidth (0.3030f), 28);
    mainVoiceButton->setBounds (0 + (getWidth() - 0) / 2 - (proportionOfWidth (0.3030f) / 2), (-8) + 48, proportionOfWidth (0.3030f), 28);
    layerVoiceButton->setBounds (0 + (getWidth() - 0) - 17 - proportionOfWidth (0.3030f), (-8) + 48, proportionOfWidth (0.3030f), 28);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void VoiceComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == leftVoiceButton)
    {
        //[UserButtonCode_leftVoiceButton] -- add your button handler code here..
        pianoController.SetVoice(PianoController::vsLeft, "PRESET:/VOICE/Guitar & Bass/Nylon Acoustic/Nylon Guitar.T242.SAR");
        //[/UserButtonCode_leftVoiceButton]
    }
    else if (buttonThatWasClicked == mainVoiceButton)
    {
        //[UserButtonCode_mainVoiceButton] -- add your button handler code here..
        pianoController.SetVoice(PianoController::vsMain, "PRESET:/VOICE/Piano/Grand Piano/Rock Piano1.T228.VRM");
        //[/UserButtonCode_mainVoiceButton]
    }
    else if (buttonThatWasClicked == layerVoiceButton)
    {
        //[UserButtonCode_layerVoiceButton] -- add your button handler code here..
        pianoController.SetVoice(PianoController::vsLayer, "PRESET:/VOICE/Brass & Woodwind/Sax Ensemble/Sax Section.T259.SAR");
        //[/UserButtonCode_layerVoiceButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void VoiceComponent::changeListenerCallback(ChangeBroadcaster* source)
{
	if (source == &pianoController)
	{
		updateVoiceState();
	}
}

void VoiceComponent::updateVoiceState()
{
	mainVoiceButton->setButtonText(voiceName(pianoController.GetVoice(PianoController::vsMain)));
	layerVoiceButton->setButtonText(voiceName(pianoController.GetVoice(PianoController::vsLayer)));
	leftVoiceButton->setButtonText(voiceName(pianoController.GetVoice(PianoController::vsLeft)));
}

String VoiceComponent::voiceName(String preset)
{
	int begin = strlen("PRESET:/VOICE/");
	int end = preset.indexOf(".");
	if (begin > -1 && end > -1)
	{
		return preset.substring(begin, end);
	}
	else
	{
		return preset;
	}
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="VoiceComponent" componentName=""
                 parentClasses="public Component, public ChangeListener" constructorParams="PianoController&amp; pianoController"
                 variableInitialisers="pianoController(pianoController)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="0"
                 initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff323e44"/>
  <GROUPCOMPONENT name="Target Group" id="56427593ca278ddd" memberName="targetGroup"
                  virtualName="" explicitFocusOrder="0" pos="0 -8 0M 88" title="Target"
                  textpos="36"/>
  <LABEL name="Main Title Label" id="9fa4d9ce58b1b951" memberName="mainTitleLabel"
         virtualName="" explicitFocusOrder="0" pos="0Cc 16 30.295% 24"
         posRelativeX="56427593ca278ddd" posRelativeY="56427593ca278ddd"
         edTextCol="ff000000" edBkgCol="0" labelText="Main&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="36"/>
  <LABEL name="Left Title Label" id="3c4e14578c159f0c" memberName="leftTitlelabel"
         virtualName="" explicitFocusOrder="0" pos="16 16 30.295% 24"
         posRelativeX="56427593ca278ddd" posRelativeY="56427593ca278ddd"
         edTextCol="ff000000" edBkgCol="0" labelText="Left" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="36"/>
  <LABEL name="Layer Title Label" id="1146e54ffb4cf467" memberName="layerTitleLabel"
         virtualName="" explicitFocusOrder="0" pos="17Rr 16 30.295% 24"
         posRelativeX="56427593ca278ddd" posRelativeY="56427593ca278ddd"
         edTextCol="ff000000" edBkgCol="0" labelText="Layer" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="36"/>
  <TREEVIEW name="Voices TreeView" id="5c337882807de41a" memberName="voicesTree"
            virtualName="" explicitFocusOrder="0" pos="8 0R 16M 88M" posRelativeY="56427593ca278ddd"
            rootVisible="0" openByDefault="0"/>
  <TEXTBUTTON name="Left Voice Button" id="f4f376ddb622016f" memberName="leftVoiceButton"
              virtualName="" explicitFocusOrder="0" pos="16 48 30.295% 28"
              posRelativeX="56427593ca278ddd" posRelativeY="56427593ca278ddd"
              buttonText="None" connectedEdges="0" needsCallback="1" radioGroupId="1"/>
  <TEXTBUTTON name="Main Voice Button" id="a44dda5da363325" memberName="mainVoiceButton"
              virtualName="" explicitFocusOrder="0" pos="0Cc 48 30.295% 28"
              posRelativeX="56427593ca278ddd" posRelativeY="56427593ca278ddd"
              buttonText="Yamaha CFX Grand" connectedEdges="0" needsCallback="1"
              radioGroupId="1"/>
  <TEXTBUTTON name="Layer Voice Button" id="e72441cfef2070c4" memberName="layerVoiceButton"
              virtualName="" explicitFocusOrder="0" pos="17Rr 48 30.295% 28"
              posRelativeX="56427593ca278ddd" posRelativeY="56427593ca278ddd"
              buttonText="Strings" connectedEdges="0" needsCallback="1" radioGroupId="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
