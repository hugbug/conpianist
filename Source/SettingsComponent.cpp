/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.2.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "SettingsComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
SettingsComponent::SettingsComponent (AudioDeviceManager& audioDeviceManager, PianoController& pianoController)
    : audioDeviceManager(audioDeviceManager), pianoController(pianoController)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (audioSelector = new AudioDeviceSelectorComponent (audioDeviceManager, 0, 0, 0, 0, true, true, true, false));
    addAndMakeVisible (remoteIpLabel = new Label ("RemoteIP Label",
                                                  TRANS("Piano IP Address:")));
    remoteIpLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    remoteIpLabel->setJustificationType (Justification::centredRight);
    remoteIpLabel->setEditable (false, false, false);
    remoteIpLabel->setColour (TextEditor::textColourId, Colours::black);
    remoteIpLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    remoteIpLabel->setBounds (104, 16, 112, 24);

    addAndMakeVisible (remoteIpEdit = new TextEditor ("Remote IP Edit"));
    remoteIpEdit->setMultiLine (false);
    remoteIpEdit->setReturnKeyStartsNewLine (false);
    remoteIpEdit->setReadOnly (false);
    remoteIpEdit->setScrollbarsShown (false);
    remoteIpEdit->setCaretVisible (true);
    remoteIpEdit->setPopupMenuEnabled (true);
    remoteIpEdit->setText (TRANS("192.168.1.235"));


    //[UserPreSize]
	remoteIpLabel->attachToComponent(remoteIpEdit, true);
	remoteIpEdit->setText(pianoController.GetRemoteIp());
    //[/UserPreSize]

    setSize (500, 200);


    //[Constructor] You can add your own custom stuff here..
	setSize(500, audioSelector->getBottom());
    //[/Constructor]
}

SettingsComponent::~SettingsComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	pianoController.SetRemoteIp(remoteIpEdit->getText());
	saveState(audioDeviceManager, pianoController);
    //[/Destructor_pre]

    audioSelector = nullptr;
    remoteIpLabel = nullptr;
    remoteIpEdit = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SettingsComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void SettingsComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    audioSelector->setBounds (16, 16 + 24, getWidth() - 30, 192);
    remoteIpEdit->setBounds (proportionOfWidth (0.3601f), 16, 136, 24);
    //[UserResized] Add your own custom resize handling here..
	audioSelector->resized();
	remoteIpEdit->setTopLeftPosition(6 + proportionOfWidth (0.3500f), remoteIpEdit->getY());
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void SettingsComponent::saveState(AudioDeviceManager& audioDeviceManager, PianoController& pianoController)
{
	XmlElement state("ConPianistState");
	XmlElement* audioState = audioDeviceManager.createStateXml();
	if (audioState)
	{
		state.addChildElement(audioState);
	}

	state.createNewChildElement("RemoteIp")->addTextElement(pianoController.GetRemoteIp());

	File stateFile = (File::getSpecialLocation(File::userHomeDirectory)).getFullPathName() + "/.conpianist";
	state.writeToFile(stateFile, "");
}

void SettingsComponent::loadState(AudioDeviceManager& audioDeviceManager, PianoController& pianoController)
{
	File stateFile = (File::getSpecialLocation(File::userHomeDirectory)).getFullPathName() + "/.conpianist";
	if (!stateFile.exists())
	{
		return;
	}

	ScopedPointer<XmlElement> savedState = XmlDocument::parse(stateFile);

	audioDeviceManager.initialise(0, 0, savedState ? savedState->getChildByName("DEVICESETUP") : nullptr, false);

	if (!savedState)
	{
		return;
	}

	XmlElement* el = savedState->getChildByName("RemoteIp");
	if (el)
	{
		pianoController.SetRemoteIp(el->getAllSubText());
	}
}

void SettingsComponent::showDialog(AudioDeviceManager& audioDeviceManager, PianoController& pianoController)
{
	DialogWindow::LaunchOptions dialog;
	dialog.content.setOwned(new SettingsComponent(audioDeviceManager, pianoController));
	dialog.dialogTitle = "Settings";
	dialog.launchAsync();
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SettingsComponent" componentName=""
                 parentClasses="public Component" constructorParams="AudioDeviceManager&amp; audioDeviceManager, PianoController&amp; pianoController"
                 variableInitialisers="audioDeviceManager(audioDeviceManager), pianoController(pianoController)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="500" initialHeight="200">
  <BACKGROUND backgroundColour="ff323e44"/>
  <JUCERCOMP name="Audio Selector" id="ddeb8c497281f468" memberName="audioSelector"
             virtualName="AudioDeviceSelectorComponent" explicitFocusOrder="0"
             pos="16 0R 30M 192" posRelativeY="83358b622e96ec09" sourceFile="../../JUCE/modules/juce_audio_utils/juce_audio_utils.h"
             constructorParams="audioDeviceManager, 0, 0, 0, 0, true, true, true, false"/>
  <LABEL name="RemoteIP Label" id="a2bb47b511220552" memberName="remoteIpLabel"
         virtualName="" explicitFocusOrder="0" pos="104 16 112 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Piano IP Address:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="34"/>
  <TEXTEDITOR name="Remote IP Edit" id="83358b622e96ec09" memberName="remoteIpEdit"
              virtualName="" explicitFocusOrder="0" pos="36.013% 16 136 24"
              initialText="192.168.1.235" multiline="0" retKeyStartsLine="0"
              readonly="0" scrollbars="0" caret="1" popupmenu="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
