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
#include "SettingsComponent.h"
//[/Headers]

#include "SceneComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
SceneComponent::SceneComponent ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (songGroup = new GroupComponent ("Song",
                                                       TRANS("Song")));
    songGroup->setTextLabelPosition (Justification::centred);

    addAndMakeVisible (playbackGroup = new GroupComponent ("Playback",
                                                           TRANS("Playback")));
    playbackGroup->setTextLabelPosition (Justification::centred);

    addAndMakeVisible (systemGroup = new GroupComponent ("System Control",
                                                         TRANS("System Control")));
    systemGroup->setTextLabelPosition (Justification::centred);

    addAndMakeVisible (localControlButton = new TextButton ("Local-Control Button"));
    localControlButton->setButtonText (TRANS("Tone"));
    localControlButton->addListener (this);

    addAndMakeVisible (playButton = new TextButton ("Play Button"));
    playButton->setButtonText (TRANS("Play"));
    playButton->addListener (this);

    addAndMakeVisible (rewindButton = new TextButton ("Rewind Button"));
    rewindButton->setButtonText (TRANS("<<"));
    rewindButton->addListener (this);

    addAndMakeVisible (forwardButton = new TextButton ("Forward Button"));
    forwardButton->setButtonText (TRANS(">>"));
    forwardButton->addListener (this);

    addAndMakeVisible (guideButton = new TextButton ("Guide Button"));
    guideButton->setButtonText (TRANS("Guide"));
    guideButton->addListener (this);

    addAndMakeVisible (positionSlider = new Slider ("Song Position slider"));
    positionSlider->setTooltip (TRANS("Song Position"));
    positionSlider->setRange (1, 999, 1);
    positionSlider->setSliderStyle (Slider::LinearHorizontal);
    positionSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    positionSlider->addListener (this);

    addAndMakeVisible (positionLabel = new Label ("Song Position Label",
                                                  TRANS("001")));
    positionLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    positionLabel->setJustificationType (Justification::centred);
    positionLabel->setEditable (false, false, false);
    positionLabel->setColour (TextEditor::textColourId, Colours::black);
    positionLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    positionLabel->setBounds ((16 + 131 - (70 / 2)) + -80, ((0 + 64 - 8) + 70 - 7) + 16, 36, 24);

    addAndMakeVisible (lengthLabel = new Label ("Song Length Label",
                                                TRANS("999")));
    lengthLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lengthLabel->setJustificationType (Justification::centred);
    lengthLabel->setEditable (false, false, false);
    lengthLabel->setColour (TextEditor::textColourId, Colours::black);
    lengthLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (songLabel = new Label ("Song Label",
                                              TRANS("No song loaded")));
    songLabel->setFont (Font (37.90f, Font::plain).withTypefaceStyle ("Regular"));
    songLabel->setJustificationType (Justification::centredLeft);
    songLabel->setEditable (false, false, false);
    songLabel->setColour (TextEditor::textColourId, Colours::black);
    songLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (chooseSongButton = new TextButton ("Choose Song Button"));
    chooseSongButton->setButtonText (TRANS("Choose..."));
    chooseSongButton->addListener (this);

    addAndMakeVisible (lightsButton = new TextButton ("Lights Button"));
    lightsButton->setButtonText (TRANS("Lights"));
    lightsButton->addListener (this);

    addAndMakeVisible (connectButton = new TextButton ("Connect Button"));
    connectButton->setButtonText (TRANS("Connect"));
    connectButton->addListener (this);

    addAndMakeVisible (settingsButton = new TextButton ("Settings Button"));
    settingsButton->setButtonText (TRANS("Settings..."));
    settingsButton->addListener (this);


    //[UserPreSize]
    systemGroup->setColour(GroupComponent::outlineColourId, Colours::transparentBlack);
    systemGroup->setText("");
    playbackGroup->setColour(GroupComponent::outlineColourId, Colours::transparentBlack);
    playbackGroup->setText("");
    songGroup->setColour(GroupComponent::outlineColourId, Colours::transparentBlack);
    songGroup->setText("");
    //[/UserPreSize]

    setSize (600, 230);


    //[Constructor] You can add your own custom stuff here..
	SettingsComponent::loadState(audioDeviceManager, pianoController);
	pianoController.SetAudioDeviceManager(&audioDeviceManager);
    pianoController.SetListener(this);
    updateEnabledControls();
    //[/Constructor]
}

SceneComponent::~SceneComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    songGroup = nullptr;
    playbackGroup = nullptr;
    systemGroup = nullptr;
    localControlButton = nullptr;
    playButton = nullptr;
    rewindButton = nullptr;
    forwardButton = nullptr;
    guideButton = nullptr;
    positionSlider = nullptr;
    positionLabel = nullptr;
    lengthLabel = nullptr;
    songLabel = nullptr;
    chooseSongButton = nullptr;
    lightsButton = nullptr;
    connectButton = nullptr;
    settingsButton = nullptr;


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

    songGroup->setBounds (16, 0 + 64 - 8, getWidth() - 32, 70);
    playbackGroup->setBounds (16, (0 + 64 - 8) + 70 - 7, getWidth() - 32, 95);
    systemGroup->setBounds (16, 0, getWidth() - 32, 64);
    localControlButton->setBounds (16 + (getWidth() - 32) - 86, 0 + 24, 70, 24);
    playButton->setBounds (16 + 131 - (70 / 2), ((0 + 64 - 8) + 70 - 7) + 56, 70, 24);
    rewindButton->setBounds (16 + 51 - (70 / 2), ((0 + 64 - 8) + 70 - 7) + 56, 70, 24);
    forwardButton->setBounds (16 + 211 - (70 / 2), ((0 + 64 - 8) + 70 - 7) + 56, 70, 24);
    guideButton->setBounds (16 + (getWidth() - 32) - 129 - (70 / 2), ((0 + 64 - 8) + 70 - 7) + 56, 70, 24);
    positionSlider->setBounds (16 + 64, ((0 + 64 - 8) + 70 - 7) + 16, getWidth() - 155, 24);
    lengthLabel->setBounds (16 + (getWidth() - 32) - 51, ((0 + 64 - 8) + 70 - 7) + 16, 36, 24);
    songLabel->setBounds (16 + 8, (0 + 64 - 8) + 15, (getWidth() - 32) - 102, 70 - 24);
    chooseSongButton->setBounds (16 + (getWidth() - 32) - 86, (0 + 64 - 8) + 28, 70, 24);
    lightsButton->setBounds (16 + (getWidth() - 32) - 86, ((0 + 64 - 8) + 70 - 7) + 56, 70, 24);
    connectButton->setBounds (16 + 124 - (216 / 2), 0 + 24, 216, 24);
    settingsButton->setBounds (16 + 284 - (88 / 2), 0 + 24, 88, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void SceneComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == localControlButton)
    {
        //[UserButtonCode_localControlButton] -- add your button handler code here..
        pianoController.LocalControl(!pianoController.GetLocalControl());
        //[/UserButtonCode_localControlButton]
    }
    else if (buttonThatWasClicked == playButton)
    {
        //[UserButtonCode_playButton] -- add your button handler code here..
        pianoController.GetPlaying() ? pianoController.Pause() : pianoController.Play();
        //[/UserButtonCode_playButton]
    }
    else if (buttonThatWasClicked == rewindButton)
    {
        //[UserButtonCode_rewindButton] -- add your button handler code here..
        pianoController.SetSongPosition(pianoController.GetSongPosition() - 1);
        //[/UserButtonCode_rewindButton]
    }
    else if (buttonThatWasClicked == forwardButton)
    {
        //[UserButtonCode_forwardButton] -- add your button handler code here..
        pianoController.SetSongPosition(pianoController.GetSongPosition() + 1);
        //[/UserButtonCode_forwardButton]
    }
    else if (buttonThatWasClicked == guideButton)
    {
        //[UserButtonCode_guideButton] -- add your button handler code here..
        pianoController.Guide(!pianoController.GetGuide());
        //[/UserButtonCode_guideButton]
    }
    else if (buttonThatWasClicked == chooseSongButton)
    {
        //[UserButtonCode_chooseSongButton] -- add your button handler code here..
        chooseSong();
        //[/UserButtonCode_chooseSongButton]
    }
    else if (buttonThatWasClicked == lightsButton)
    {
        //[UserButtonCode_lightsButton] -- add your button handler code here..
        pianoController.StreamLights(!pianoController.GetStreamLights());
        //[/UserButtonCode_lightsButton]
    }
    else if (buttonThatWasClicked == connectButton)
    {
        //[UserButtonCode_connectButton] -- add your button handler code here..
        pianoController.Connect();
        //[/UserButtonCode_connectButton]
    }
    else if (buttonThatWasClicked == settingsButton)
    {
        //[UserButtonCode_settingsButton] -- add your button handler code here..
		showSettingsDialog();
        //[/UserButtonCode_settingsButton]
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
        pianoController.SetSongPosition(positionSlider->getValue());
        //[/UserSliderCode_positionSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...

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

	if (!pianoController.UploadSong(file))
	{
		songLabel->setText(TRANS("Error loading midi"), NotificationType::dontSendNotification);
		return;
	}

	songLabel->setText(file.getFileNameWithoutExtension(), NotificationType::dontSendNotification);
	positionLabel->setText("001", NotificationType::dontSendNotification);
	lengthLabel->setText("999", NotificationType::dontSendNotification);
}

void SceneComponent::updateSongState()
{
	MessageManager::callAsync([=] ()
		{
			int songLength = pianoController.GetSongLength() > 0 ? pianoController.GetSongLength() : 999;
			lengthLabel->setText(String::formatted("%03d", songLength), NotificationType::dontSendNotification);
			positionSlider->setRange(1, songLength, 1);
			positionLabel->setText(String::formatted("%03d", pianoController.GetSongPosition()),
				NotificationType::dontSendNotification);
			positionSlider->setValue(pianoController.GetSongPosition(), NotificationType::dontSendNotification);
			playButton->setButtonText(pianoController.GetPlaying() ? "Pause" : "Play");
		});
}

void SceneComponent::updateSettingsState()
{
	MessageManager::callAsync([=] ()
		{
			localControlButton->setToggleState(pianoController.GetLocalControl() && pianoController.GetConnected(), NotificationType::dontSendNotification);
			lightsButton->setToggleState(pianoController.GetStreamLights() && pianoController.GetConnected(), NotificationType::dontSendNotification);
			guideButton->setToggleState(pianoController.GetGuide() && pianoController.GetConnected(), NotificationType::dontSendNotification);
			connectButton->setToggleState(pianoController.GetConnected(), NotificationType::dontSendNotification);
			connectButton->setButtonText(!pianoController.GetConnected() ? "Connect" :
				String("Connected to ") + pianoController.GetModel() + " (" + pianoController.GetVersion() + ")");
			updateEnabledControls();
		});
}

void SceneComponent::updateEnabledControls()
{
	for (Component* co : getChildren())
	{
		bool alwaysEnabled = co == connectButton || co == settingsButton;
		co->setEnabled(pianoController.GetConnected() || alwaysEnabled);
	}
}

void SceneComponent::showSettingsDialog()
{
	SettingsComponent::showDialog(audioDeviceManager, pianoController);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SceneComponent" componentName=""
                 parentClasses="public Component, public PianoControllerListener"
                 constructorParams="" variableInitialisers="" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="600"
                 initialHeight="230">
  <BACKGROUND backgroundColour="ff323e44"/>
  <GROUPCOMPONENT name="Song" id="4e6df4a0ae6e851b" memberName="songGroup" virtualName=""
                  explicitFocusOrder="0" pos="16 8R 32M 70" posRelativeY="69305d91c2150486"
                  title="Song" textpos="36"/>
  <GROUPCOMPONENT name="Playback" id="c7b94b60aa96c6e2" memberName="playbackGroup"
                  virtualName="" explicitFocusOrder="0" pos="16 7R 32M 95" posRelativeY="4e6df4a0ae6e851b"
                  title="Playback" textpos="36"/>
  <GROUPCOMPONENT name="System Control" id="69305d91c2150486" memberName="systemGroup"
                  virtualName="" explicitFocusOrder="0" pos="16 0 32M 64" title="System Control"
                  textpos="36"/>
  <TEXTBUTTON name="Local-Control Button" id="99f311ed53591c70" memberName="localControlButton"
              virtualName="" explicitFocusOrder="0" pos="86R 24 70 24" posRelativeX="69305d91c2150486"
              posRelativeY="69305d91c2150486" buttonText="Tone" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Play Button" id="be38d66c26f6bda6" memberName="playButton"
              virtualName="" explicitFocusOrder="0" pos="131c 56 70 24" posRelativeX="c7b94b60aa96c6e2"
              posRelativeY="c7b94b60aa96c6e2" buttonText="Play" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Rewind Button" id="c1113d02cbf7d143" memberName="rewindButton"
              virtualName="" explicitFocusOrder="0" pos="51c 56 70 24" posRelativeX="c7b94b60aa96c6e2"
              posRelativeY="c7b94b60aa96c6e2" buttonText="&lt;&lt;" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Forward Button" id="82d7c8c8e52fdffb" memberName="forwardButton"
              virtualName="" explicitFocusOrder="0" pos="211c 56 70 24" posRelativeX="c7b94b60aa96c6e2"
              posRelativeY="c7b94b60aa96c6e2" buttonText="&gt;&gt;" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Guide Button" id="c850d2e92ae26093" memberName="guideButton"
              virtualName="" explicitFocusOrder="0" pos="129Rc 56 70 24" posRelativeX="c7b94b60aa96c6e2"
              posRelativeY="c7b94b60aa96c6e2" buttonText="Guide" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <SLIDER name="Song Position slider" id="3f9d3a942dcf1d69" memberName="positionSlider"
          virtualName="" explicitFocusOrder="0" pos="64 16 155M 24" posRelativeX="c7b94b60aa96c6e2"
          posRelativeY="c7b94b60aa96c6e2" tooltip="Song Position" min="1.00000000000000000000"
          max="999.00000000000000000000" int="1.00000000000000000000" style="LinearHorizontal"
          textBoxPos="NoTextBox" textBoxEditable="0" textBoxWidth="80"
          textBoxHeight="20" skewFactor="1.00000000000000000000" needsCallback="1"/>
  <LABEL name="Song Position Label" id="17ac2967e993dc43" memberName="positionLabel"
         virtualName="" explicitFocusOrder="0" pos="-80 16 36 24" posRelativeX="be38d66c26f6bda6"
         posRelativeY="c7b94b60aa96c6e2" edTextCol="ff000000" edBkgCol="0"
         labelText="001" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.00000000000000000000"
         kerning="0.00000000000000000000" bold="0" italic="0" justification="36"/>
  <LABEL name="Song Length Label" id="537604aa6486f948" memberName="lengthLabel"
         virtualName="" explicitFocusOrder="0" pos="51R 16 36 24" posRelativeX="c7b94b60aa96c6e2"
         posRelativeY="c7b94b60aa96c6e2" edTextCol="ff000000" edBkgCol="0"
         labelText="999" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.00000000000000000000"
         kerning="0.00000000000000000000" bold="0" italic="0" justification="36"/>
  <LABEL name="Song Label" id="8682794e760bce8" memberName="songLabel"
         virtualName="" explicitFocusOrder="0" pos="8 15 102M 24M" posRelativeX="4e6df4a0ae6e851b"
         posRelativeY="4e6df4a0ae6e851b" posRelativeW="4e6df4a0ae6e851b"
         posRelativeH="4e6df4a0ae6e851b" edTextCol="ff000000" edBkgCol="0"
         labelText="No song loaded" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="37.89999999999999857891"
         kerning="0.00000000000000000000" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="Choose Song Button" id="73e64e146d2a4fc2" memberName="chooseSongButton"
              virtualName="" explicitFocusOrder="0" pos="86R 28 70 24" posRelativeX="4e6df4a0ae6e851b"
              posRelativeY="4e6df4a0ae6e851b" buttonText="Choose..." connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Lights Button" id="5e04ec6b8d091999" memberName="lightsButton"
              virtualName="" explicitFocusOrder="0" pos="86R 56 70 24" posRelativeX="c7b94b60aa96c6e2"
              posRelativeY="c7b94b60aa96c6e2" buttonText="Lights" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Connect Button" id="a82c92b5d1470311" memberName="connectButton"
              virtualName="" explicitFocusOrder="0" pos="124c 24 216 24" posRelativeX="69305d91c2150486"
              posRelativeY="69305d91c2150486" buttonText="Connect" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Settings Button" id="bf47ed7d30088c39" memberName="settingsButton"
              virtualName="" explicitFocusOrder="0" pos="284c 24 88 24" posRelativeX="69305d91c2150486"
              posRelativeY="69305d91c2150486" buttonText="Settings..." connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
