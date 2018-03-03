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

#include "SceneComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
SceneComponent::SceneComponent ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (playbackGroup = new GroupComponent ("Playback",
                                                           TRANS("Playback")));
    playbackGroup->setTextLabelPosition (Justification::centred);

    addAndMakeVisible (audioSelector = new AudioDeviceSelectorComponent (audioDeviceManager, 0, 0, 0, 0, true, true, false, false));
    addAndMakeVisible (systemGroup = new GroupComponent ("System Control",
                                                         TRANS("System Control")));
    systemGroup->setTextLabelPosition (Justification::centred);

    addAndMakeVisible (localControlOnButton = new TextButton ("Local-Control On Button"));
    localControlOnButton->setButtonText (TRANS("Tone On"));
    localControlOnButton->addListener (this);

    addAndMakeVisible (localControlOffButton = new TextButton ("Local-Control Off Button"));
    localControlOffButton->setButtonText (TRANS("Tone Off"));
    localControlOffButton->addListener (this);

    addAndMakeVisible (playButton = new TextButton ("Play Button"));
    playButton->setButtonText (TRANS("Play"));
    playButton->addListener (this);

    addAndMakeVisible (rewindButton = new TextButton ("Rewind Button"));
    rewindButton->setButtonText (TRANS("Rewind"));
    rewindButton->addListener (this);

    addAndMakeVisible (forwardButton = new TextButton ("Forward Button"));
    forwardButton->setButtonText (TRANS("Forward"));
    forwardButton->addListener (this);

    addAndMakeVisible (guideOnButton = new TextButton ("Guide On Button"));
    guideOnButton->setButtonText (TRANS("Guide On"));
    guideOnButton->addListener (this);

    addAndMakeVisible (positionSlider = new Slider ("Song Position slider"));
    positionSlider->setTooltip (TRANS("Song Position"));
    positionSlider->setRange (1, 999, 0);
    positionSlider->setSliderStyle (Slider::LinearHorizontal);
    positionSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    positionSlider->addListener (this);

    addAndMakeVisible (positionLabel = new Label ("Song Position Label",
                                                  TRANS("1")));
    positionLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    positionLabel->setJustificationType (Justification::centred);
    positionLabel->setEditable (false, false, false);
    positionLabel->setColour (TextEditor::textColourId, Colours::black);
    positionLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    positionLabel->setBounds ((16 + 131 - (70 / 2)) + -80, ((((-20) + 108 - -48) + 64 - 9) + 72 - 9) + 24, 36, 24);

    addAndMakeVisible (lengthLabel = new Label ("Song Length Label",
                                                TRANS("999")));
    lengthLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lengthLabel->setJustificationType (Justification::centred);
    lengthLabel->setEditable (false, false, false);
    lengthLabel->setColour (TextEditor::textColourId, Colours::black);
    lengthLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (songLabel = new Label ("Song Label",
                                              TRANS("<no song loaded>")));
    songLabel->setFont (Font (37.90f, Font::plain).withTypefaceStyle ("Regular"));
    songLabel->setJustificationType (Justification::centredLeft);
    songLabel->setEditable (false, false, false);
    songLabel->setColour (TextEditor::textColourId, Colours::black);
    songLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (chooseSongButton = new TextButton ("Choose Song Button"));
    chooseSongButton->setButtonText (TRANS("Choose"));
    chooseSongButton->addListener (this);

    addAndMakeVisible (pauseButton = new TextButton ("Pause Button"));
    pauseButton->setButtonText (TRANS("Pause"));
    pauseButton->addListener (this);

    addAndMakeVisible (guideOffButton = new TextButton ("Guide Off Button"));
    guideOffButton->setButtonText (TRANS("Guide Off"));
    guideOffButton->addListener (this);

    addAndMakeVisible (lightsOnButton = new TextButton ("Lights On Button"));
    lightsOnButton->setButtonText (TRANS("Lights On"));
    lightsOnButton->addListener (this);

    addAndMakeVisible (lightsOffButton = new TextButton ("Lights Off Button"));
    lightsOffButton->setButtonText (TRANS("Lights Off"));
    lightsOffButton->addListener (this);

    addAndMakeVisible (remoteIpLabel = new Label ("RemoteIP Label",
                                                  TRANS("Piano IP Address:")));
    remoteIpLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    remoteIpLabel->setJustificationType (Justification::centredRight);
    remoteIpLabel->setEditable (false, false, false);
    remoteIpLabel->setColour (TextEditor::textColourId, Colours::black);
    remoteIpLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    remoteIpLabel->setBounds (176, 104, 112, 24);

    addAndMakeVisible (remoteIpEdit = new TextEditor ("Remote IP Edit"));
    remoteIpEdit->setMultiLine (false);
    remoteIpEdit->setReturnKeyStartsNewLine (false);
    remoteIpEdit->setReadOnly (false);
    remoteIpEdit->setScrollbarsShown (false);
    remoteIpEdit->setCaretVisible (true);
    remoteIpEdit->setPopupMenuEnabled (true);
    remoteIpEdit->setText (TRANS("192.168.1.235"));

    addAndMakeVisible (songGroup = new GroupComponent ("Song",
                                                       TRANS("Song")));
    songGroup->setTextLabelPosition (Justification::centred);


    //[UserPreSize]
    systemGroup->setColour(GroupComponent::outlineColourId, Colours::transparentBlack);
    systemGroup->setText("");
    playbackGroup->setColour(GroupComponent::outlineColourId, Colours::transparentBlack);
    playbackGroup->setText("");
    songGroup->setColour(GroupComponent::outlineColourId, Colours::transparentBlack);
    songGroup->setText("");
    remoteIpLabel->attachToComponent(remoteIpEdit, true);
    //[/UserPreSize]

    setSize (600, 600);


    //[Constructor] You can add your own custom stuff here..
    cspController.Init(&audioDeviceManager, remoteIpEdit->getText());
    remoteIpEdit->addListener(this);
    audioDeviceManager.addMidiInputCallback("", this);
    //[/Constructor]
}

SceneComponent::~SceneComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    playbackGroup = nullptr;
    audioSelector = nullptr;
    systemGroup = nullptr;
    localControlOnButton = nullptr;
    localControlOffButton = nullptr;
    playButton = nullptr;
    rewindButton = nullptr;
    forwardButton = nullptr;
    guideOnButton = nullptr;
    positionSlider = nullptr;
    positionLabel = nullptr;
    lengthLabel = nullptr;
    songLabel = nullptr;
    chooseSongButton = nullptr;
    pauseButton = nullptr;
    guideOffButton = nullptr;
    lightsOnButton = nullptr;
    lightsOffButton = nullptr;
    remoteIpLabel = nullptr;
    remoteIpEdit = nullptr;
    songGroup = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SceneComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void SceneComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    playbackGroup->setBounds (16, (((-20) + 108 - -48) + 64 - 9) + 72 - 9, getWidth() - 32, 144);
    audioSelector->setBounds (16, -20, getWidth() - 30, 108);
    systemGroup->setBounds (16, (-20) + 108 - -48, getWidth() - 32, 64);
    localControlOnButton->setBounds (16 + 50 - (70 / 2), ((-20) + 108 - -48) + 24, 70, 24);
    localControlOffButton->setBounds (16 + 131 - (70 / 2), ((-20) + 108 - -48) + 24, 70, 24);
    playButton->setBounds (16 + 131 - (70 / 2), ((((-20) + 108 - -48) + 64 - 9) + 72 - 9) + 64, 70, 24);
    rewindButton->setBounds (16 + 51 - (70 / 2), ((((-20) + 108 - -48) + 64 - 9) + 72 - 9) + 64, 70, 24);
    forwardButton->setBounds (16 + 291 - (70 / 2), ((((-20) + 108 - -48) + 64 - 9) + 72 - 9) + 64, 70, 24);
    guideOnButton->setBounds (16 + (getWidth() - 32) - 136 - (70 / 2), ((((-20) + 108 - -48) + 64 - 9) + 72 - 9) + 64, 70, 24);
    positionSlider->setBounds (16 + 64, ((((-20) + 108 - -48) + 64 - 9) + 72 - 9) + 24, getWidth() - 155, 24);
    lengthLabel->setBounds (16 + (getWidth() - 32) - 51, ((((-20) + 108 - -48) + 64 - 9) + 72 - 9) + 24, 36, 24);
    songLabel->setBounds (16 + 10, (((-20) + 108 - -48) + 64 - 9) + 17, (getWidth() - 32) - 101, 72 - 27);
    chooseSongButton->setBounds (16 + (getWidth() - 32) - 83, (((-20) + 108 - -48) + 64 - 9) + 28, 70, 24);
    pauseButton->setBounds (16 + 211 - (70 / 2), ((((-20) + 108 - -48) + 64 - 9) + 72 - 9) + 64, 70, 24);
    guideOffButton->setBounds (16 + (getWidth() - 32) - 56 - (70 / 2), ((((-20) + 108 - -48) + 64 - 9) + 72 - 9) + 64, 70, 24);
    lightsOnButton->setBounds (16 + (getWidth() - 32) - 136 - (70 / 2), ((((-20) + 108 - -48) + 64 - 9) + 72 - 9) + 104, 70, 24);
    lightsOffButton->setBounds (16 + (getWidth() - 32) - 56 - (70 / 2), ((((-20) + 108 - -48) + 64 - 9) + 72 - 9) + 104, 70, 24);
    remoteIpEdit->setBounds (proportionOfWidth (0.3498f), (-20) + 124, 136, 24);
    songGroup->setBounds (16, ((-20) + 108 - -48) + 64 - 9, getWidth() - 32, 72);
    //[UserResized] Add your own custom resize handling here..
    remoteIpEdit->setBounds (6 + proportionOfWidth (0.3500f), (-20) + 124, 136, 24);
    //[/UserResized]
}

void SceneComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == localControlOnButton)
    {
        //[UserButtonCode_localControlOnButton] -- add your button handler code here..
        cspController.SwitchLocalControl(true);
        //[/UserButtonCode_localControlOnButton]
    }
    else if (buttonThatWasClicked == localControlOffButton)
    {
        //[UserButtonCode_localControlOffButton] -- add your button handler code here..
        cspController.SwitchLocalControl(false);
        //[/UserButtonCode_localControlOffButton]
    }
    else if (buttonThatWasClicked == playButton)
    {
        //[UserButtonCode_playButton] -- add your button handler code here..
        cspController.Play();
        //[/UserButtonCode_playButton]
    }
    else if (buttonThatWasClicked == rewindButton)
    {
        //[UserButtonCode_rewindButton] -- add your button handler code here..
        //[/UserButtonCode_rewindButton]
    }
    else if (buttonThatWasClicked == forwardButton)
    {
        //[UserButtonCode_forwardButton] -- add your button handler code here..
        //[/UserButtonCode_forwardButton]
    }
    else if (buttonThatWasClicked == guideOnButton)
    {
        //[UserButtonCode_guideOnButton] -- add your button handler code here..
        cspController.Guide(true);
        //[/UserButtonCode_guideOnButton]
    }
    else if (buttonThatWasClicked == chooseSongButton)
    {
        //[UserButtonCode_chooseSongButton] -- add your button handler code here..
        chooseSong();
        //[/UserButtonCode_chooseSongButton]
    }
    else if (buttonThatWasClicked == pauseButton)
    {
        //[UserButtonCode_pauseButton] -- add your button handler code here..
        cspController.Pause();
        //[/UserButtonCode_pauseButton]
    }
    else if (buttonThatWasClicked == guideOffButton)
    {
        //[UserButtonCode_guideOffButton] -- add your button handler code here..
        cspController.Guide(false);
        //[/UserButtonCode_guideOffButton]
    }
    else if (buttonThatWasClicked == lightsOnButton)
    {
        //[UserButtonCode_lightsOnButton] -- add your button handler code here..
        cspController.StreamLights(true);
        //[/UserButtonCode_lightsOnButton]
    }
    else if (buttonThatWasClicked == lightsOffButton)
    {
        //[UserButtonCode_lightsOffButton] -- add your button handler code here..
        cspController.StreamLights(false);
        //[/UserButtonCode_lightsOffButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void SceneComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == positionSlider)
    {
        //[UserSliderCode_positionSlider] -- add your slider handling code here..
        //[/UserSliderCode_positionSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

void SceneComponent::textEditorReturnKeyPressed(TextEditor & editor)
{
	if (&editor == remoteIpEdit.get())
	{
    	cspController.Init(&audioDeviceManager, remoteIpEdit->getText());
	}
}

void SceneComponent::chooseSong()
{
	File initialLocation = File::getSpecialLocation(File::userHomeDirectory);
	initialLocation = initialLocation.getFullPathName() + "/Midi";
	FileChooser chooser ("Please select the song you want to load...", initialLocation, "*.mid");
    if (chooser.browseForFileToOpen())
    {
        File file(chooser.getResult());
		songLabel->setText(TRANS("Loading..."), NotificationType::dontSendNotification);
		MessageManager::callAsync([=] () { loadSong(file); });
    }
}

void SceneComponent::loadSong(const File& file)
{
	MidiFile midiFile;
	FileInputStream inp(file);
	if (!midiFile.readFrom(inp))
	{
		songLabel->setText(TRANS("Error reading file"), NotificationType::dontSendNotification);
		return;
	}

	if (!cspController.UploadSong(file))
	{
		songLabel->setText(TRANS("Error loading midi"), NotificationType::dontSendNotification);
		return;
	}

	songLabel->setText(file.getFileNameWithoutExtension(), NotificationType::dontSendNotification);
	positionLabel->setText("1", NotificationType::dontSendNotification);
	lengthLabel->setText("999", NotificationType::dontSendNotification);
}

void SceneComponent::handleIncomingMidiMessage(MidiInput *source, const MidiMessage &message)
{
	if (message.isSysEx())
	{
		MemoryBlock sysex(message.getSysExData(), message.getSysExDataSize());
		MemoryBlock sig;

		sig.loadFromHexString("43 73 01 52 25 26 00 00 04 00 0a 01 00 01 00 00 04");
		if (sysex.getSize() == sig.getSize() + 4 &&
			memcmp(sysex.getData(), sig.getData(), sig.getSize()) == 0)
		{
			int measure = (sysex[sig.getSize()] << 7) + sysex[sig.getSize() + 1];
			MessageManager::callAsync([=] ()
				{
					positionLabel->setText(String(measure), NotificationType::dontSendNotification);
					positionSlider->setValue(measure);
				});
		}

		sig.loadFromHexString("43 73 01 52 25 26 00 00 04 00 1b 01 00 01 00 00 04");
		if (sysex.getSize() == sig.getSize() + 4 &&
			memcmp(sysex.getData(), sig.getData(), sig.getSize()) == 0)
		{
			int length = (sysex[sig.getSize()] << 7) + sysex[sig.getSize() + 1];
			MessageManager::callAsync([=] ()
				{
					lengthLabel->setText(String(length), NotificationType::dontSendNotification);
    				positionSlider->setRange(1, length, 0);
				});
		}
	}
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SceneComponent" componentName=""
                 parentClasses="public Component, public TextEditor::Listener, public MidiInputCallback"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="600">
  <BACKGROUND backgroundColour="ff323e44"/>
  <GROUPCOMPONENT name="Playback" id="c7b94b60aa96c6e2" memberName="playbackGroup"
                  virtualName="" explicitFocusOrder="0" pos="16 9R 32M 144" posRelativeY="4e6df4a0ae6e851b"
                  title="Playback" textpos="36"/>
  <JUCERCOMP name="Audio Selector" id="ddeb8c497281f468" memberName="audioSelector"
             virtualName="AudioDeviceSelectorComponent" explicitFocusOrder="0"
             pos="16 -20 30M 108" sourceFile="../../JUCE/modules/juce_audio_utils/juce_audio_utils.h"
             constructorParams="audioDeviceManager, 0, 0, 0, 0, true, true, false, false"/>
  <GROUPCOMPONENT name="System Control" id="69305d91c2150486" memberName="systemGroup"
                  virtualName="" explicitFocusOrder="0" pos="16 -48R 32M 64" posRelativeY="ddeb8c497281f468"
                  title="System Control" textpos="36"/>
  <TEXTBUTTON name="Local-Control On Button" id="99f311ed53591c70" memberName="localControlOnButton"
              virtualName="" explicitFocusOrder="0" pos="50c 24 70 24" posRelativeX="69305d91c2150486"
              posRelativeY="69305d91c2150486" buttonText="Tone On" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Local-Control Off Button" id="55c13d8af41edb4e" memberName="localControlOffButton"
              virtualName="" explicitFocusOrder="0" pos="131c 24 70 24" posRelativeX="69305d91c2150486"
              posRelativeY="69305d91c2150486" buttonText="Tone Off" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Play Button" id="be38d66c26f6bda6" memberName="playButton"
              virtualName="" explicitFocusOrder="0" pos="131c 64 70 24" posRelativeX="c7b94b60aa96c6e2"
              posRelativeY="c7b94b60aa96c6e2" buttonText="Play" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Rewind Button" id="c1113d02cbf7d143" memberName="rewindButton"
              virtualName="" explicitFocusOrder="0" pos="51c 64 70 24" posRelativeX="c7b94b60aa96c6e2"
              posRelativeY="c7b94b60aa96c6e2" buttonText="Rewind" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Forward Button" id="82d7c8c8e52fdffb" memberName="forwardButton"
              virtualName="" explicitFocusOrder="0" pos="291c 64 70 24" posRelativeX="c7b94b60aa96c6e2"
              posRelativeY="c7b94b60aa96c6e2" buttonText="Forward" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Guide On Button" id="c850d2e92ae26093" memberName="guideOnButton"
              virtualName="" explicitFocusOrder="0" pos="136Rc 64 70 24" posRelativeX="c7b94b60aa96c6e2"
              posRelativeY="c7b94b60aa96c6e2" buttonText="Guide On" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <SLIDER name="Song Position slider" id="3f9d3a942dcf1d69" memberName="positionSlider"
          virtualName="" explicitFocusOrder="0" pos="64 24 155M 24" posRelativeX="c7b94b60aa96c6e2"
          posRelativeY="c7b94b60aa96c6e2" tooltip="Song Position" min="1.00000000000000000000"
          max="999.00000000000000000000" int="0.00000000000000000000" style="LinearHorizontal"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.00000000000000000000" needsCallback="1"/>
  <LABEL name="Song Position Label" id="17ac2967e993dc43" memberName="positionLabel"
         virtualName="" explicitFocusOrder="0" pos="-80 24 36 24" posRelativeX="be38d66c26f6bda6"
         posRelativeY="c7b94b60aa96c6e2" edTextCol="ff000000" edBkgCol="0"
         labelText="1" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.00000000000000000000"
         kerning="0.00000000000000000000" bold="0" italic="0" justification="36"/>
  <LABEL name="Song Length Label" id="537604aa6486f948" memberName="lengthLabel"
         virtualName="" explicitFocusOrder="0" pos="51R 24 36 24" posRelativeX="c7b94b60aa96c6e2"
         posRelativeY="c7b94b60aa96c6e2" edTextCol="ff000000" edBkgCol="0"
         labelText="999" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.00000000000000000000"
         kerning="0.00000000000000000000" bold="0" italic="0" justification="36"/>
  <LABEL name="Song Label" id="8682794e760bce8" memberName="songLabel"
         virtualName="" explicitFocusOrder="0" pos="10 17 101M 27M" posRelativeX="4e6df4a0ae6e851b"
         posRelativeY="4e6df4a0ae6e851b" posRelativeW="4e6df4a0ae6e851b"
         posRelativeH="4e6df4a0ae6e851b" edTextCol="ff000000" edBkgCol="0"
         labelText="&lt;no song loaded&gt;" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="37.89999999999999857891"
         kerning="0.00000000000000000000" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="Choose Song Button" id="73e64e146d2a4fc2" memberName="chooseSongButton"
              virtualName="" explicitFocusOrder="0" pos="83R 28 70 24" posRelativeX="4e6df4a0ae6e851b"
              posRelativeY="4e6df4a0ae6e851b" buttonText="Choose" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Pause Button" id="28873e78ae76dcd9" memberName="pauseButton"
              virtualName="" explicitFocusOrder="0" pos="211c 64 70 24" posRelativeX="c7b94b60aa96c6e2"
              posRelativeY="c7b94b60aa96c6e2" buttonText="Pause" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Guide Off Button" id="9fb8edac050b156b" memberName="guideOffButton"
              virtualName="" explicitFocusOrder="0" pos="56Rc 64 70 24" posRelativeX="c7b94b60aa96c6e2"
              posRelativeY="c7b94b60aa96c6e2" buttonText="Guide Off" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Lights On Button" id="5e04ec6b8d091999" memberName="lightsOnButton"
              virtualName="" explicitFocusOrder="0" pos="136Rc 104 70 24" posRelativeX="c7b94b60aa96c6e2"
              posRelativeY="c7b94b60aa96c6e2" buttonText="Lights On" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Lights Off Button" id="a2890553270a5b82" memberName="lightsOffButton"
              virtualName="" explicitFocusOrder="0" pos="56Rc 104 70 24" posRelativeX="c7b94b60aa96c6e2"
              posRelativeY="c7b94b60aa96c6e2" buttonText="Lights Off" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <LABEL name="RemoteIP Label" id="a2bb47b511220552" memberName="remoteIpLabel"
         virtualName="" explicitFocusOrder="0" pos="176 104 112 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Piano IP Address:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="34"/>
  <TEXTEDITOR name="Remote IP Edit" id="83358b622e96ec09" memberName="remoteIpEdit"
              virtualName="" explicitFocusOrder="0" pos="34.977% 124 136 24"
              posRelativeY="ddeb8c497281f468" initialText="192.168.1.235" multiline="0"
              retKeyStartsLine="0" readonly="0" scrollbars="0" caret="1" popupmenu="1"/>
  <GROUPCOMPONENT name="Song" id="4e6df4a0ae6e851b" memberName="songGroup" virtualName=""
                  explicitFocusOrder="0" pos="16 9R 32M 72" posRelativeY="69305d91c2150486"
                  title="Song" textpos="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
