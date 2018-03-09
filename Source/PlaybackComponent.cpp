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

#include "PlaybackComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PlaybackComponent::PlaybackComponent (PianoController& pianoController)
    : pianoController(pianoController)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //Desktop::getInstance().setGlobalScaleFactor(1);
    //[/Constructor_pre]

    addAndMakeVisible (songGroup = new GroupComponent ("Song",
                                                       TRANS("Song")));
    songGroup->setTextLabelPosition (Justification::centred);

    addAndMakeVisible (songLabel = new Label ("Song Label",
                                              TRANS("Not connected to piano yet")));
    songLabel->setFont (Font (23.70f, Font::plain).withTypefaceStyle ("Regular"));
    songLabel->setJustificationType (Justification::centredLeft);
    songLabel->setEditable (false, false, false);
    songLabel->setColour (TextEditor::textColourId, Colours::black);
    songLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (playbackGroup = new GroupComponent ("Playback",
                                                           TRANS("Playback")));
    playbackGroup->setTextLabelPosition (Justification::centred);

    addAndMakeVisible (guideButton = new TextButton ("Guide Button"));
    guideButton->setButtonText (TRANS("Guide"));
    guideButton->addListener (this);

    guideButton->setBounds (80, ((-8) + 70 - 8) + 134, 64, 28);

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

    positionLabel->setBounds (16, ((-8) + 70 - 8) + 18, 36, 20);

    addAndMakeVisible (lengthLabel = new Label ("Song Length Label",
                                                TRANS("999")));
    lengthLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lengthLabel->setJustificationType (Justification::centred);
    lengthLabel->setEditable (false, false, false);
    lengthLabel->setColour (TextEditor::textColourId, Colours::black);
    lengthLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (lightsButton = new TextButton ("Lights Button"));
    lightsButton->setButtonText (TRANS("Lights"));
    lightsButton->addListener (this);

    lightsButton->setBounds (0 + 148, ((-8) + 70 - 8) + 134, 64, 28);

    addAndMakeVisible (playButton = new ImageButton ("Play Button"));
    playButton->setButtonText (TRANS("Play"));
    playButton->addListener (this);

    playButton->setImages (false, true, true,
                           ImageCache::getFromMemory (BinaryData::buttonplay_png, BinaryData::buttonplay_pngSize), 1.000f, Colour (0x00000000),
                           Image(), 0.750f, Colour (0x00000000),
                           Image(), 1.000f, Colour (0x00000000));
    addAndMakeVisible (rewindButton = new ImageButton ("Rewind Button"));
    rewindButton->setButtonText (TRANS("Rewind"));
    rewindButton->addListener (this);

    rewindButton->setImages (false, true, true,
                             ImageCache::getFromMemory (BinaryData::buttonrewind_png, BinaryData::buttonrewind_pngSize), 1.000f, Colour (0x00000000),
                             Image(), 0.750f, Colour (0x00000000),
                             Image(), 1.000f, Colour (0x00000000));
    addAndMakeVisible (forwardButton = new ImageButton ("Forward Button"));
    forwardButton->setButtonText (TRANS("Play"));
    forwardButton->addListener (this);

    forwardButton->setImages (false, true, true,
                              ImageCache::getFromMemory (BinaryData::buttonfastforward_png, BinaryData::buttonfastforward_pngSize), 1.000f, Colour (0x00000000),
                              Image(), 0.750f, Colour (0x00000000),
                              Image(), 1.000f, Colour (0x00000000));
    addAndMakeVisible (chooseSongButton = new ImageButton ("Choose Song Button"));
    chooseSongButton->setButtonText (TRANS("Choose"));
    chooseSongButton->addListener (this);

    chooseSongButton->setImages (false, true, true,
                                 ImageCache::getFromMemory (BinaryData::buttonexpand_png, BinaryData::buttonexpand_pngSize), 1.000f, Colour (0x00000000),
                                 Image(), 0.750f, Colour (0x00000000),
                                 Image(), 1.000f, Colour (0x00000000));
    addAndMakeVisible (backingPartButton = new TextButton ("Backing Part Button"));
    backingPartButton->setButtonText (TRANS("Backing"));
    backingPartButton->addListener (this);

    backingPartButton->setBounds (80, ((-8) + 70 - 8) + 182, 64, 28);

    addAndMakeVisible (partLabel = new Label ("Part Label",
                                              TRANS("Part")));
    partLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    partLabel->setJustificationType (Justification::centredLeft);
    partLabel->setEditable (false, false, false);
    partLabel->setColour (TextEditor::textColourId, Colours::black);
    partLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    partLabel->setBounds (16, ((-8) + 70 - 8) + 182, 40, 24);

    addAndMakeVisible (leftPartButton = new TextButton ("Left Part Button"));
    leftPartButton->setButtonText (TRANS("Left"));
    leftPartButton->addListener (this);

    leftPartButton->setBounds (148, ((-8) + 70 - 8) + 182, 64, 28);

    addAndMakeVisible (rightPartButton = new TextButton ("Right Part Button"));
    rightPartButton->setButtonText (TRANS("Right"));
    rightPartButton->addListener (this);

    rightPartButton->setBounds (216, ((-8) + 70 - 8) + 182, 64, 28);

    addAndMakeVisible (lightsFastButton = new TextButton ("Lights Fast Button"));
    lightsFastButton->setButtonText (TRANS("Fast"));
    lightsFastButton->addListener (this);

    lightsFastButton->setBounds (0 + 216, ((-8) + 70 - 8) + 134, 64, 28);

    addAndMakeVisible (partLabel2 = new Label ("Part Label",
                                               TRANS("Practice")));
    partLabel2->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    partLabel2->setJustificationType (Justification::centredLeft);
    partLabel2->setEditable (false, false, false);
    partLabel2->setColour (TextEditor::textColourId, Colours::black);
    partLabel2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    partLabel2->setBounds (16, ((-8) + 70 - 8) + 134, 64, 24);

    addAndMakeVisible (loopButton = new ImageButton ("Loop Button"));
    loopButton->setButtonText (TRANS("Loop"));
    loopButton->addListener (this);

    loopButton->setImages (false, true, true,
                           ImageCache::getFromMemory (BinaryData::buttonabloop_png, BinaryData::buttonabloop_pngSize), 1.000f, Colour (0x00000000),
                           Image(), 0.750f, Colour (0x00000000),
                           Image(), 1.000f, Colour (0x00000000));
    addAndMakeVisible (muteButton = new ImageButton ("Mute Button"));
    muteButton->setButtonText (TRANS("Mute"));
    muteButton->addListener (this);

    muteButton->setImages (false, true, true,
                           ImageCache::getFromMemory (BinaryData::buttonvolume_png, BinaryData::buttonvolume_pngSize), 1.000f, Colour (0x00000000),
                           Image(), 0.750f, Colour (0x00000000),
                           Image(), 1.000f, Colour (0x00000000));

    //[UserPreSize]
    playbackGroup->setColour(GroupComponent::outlineColourId, Colours::transparentBlack);
    playbackGroup->setText("");
    songGroup->setColour(GroupComponent::outlineColourId, Colours::transparentBlack);
    songGroup->setText("");
    //[/UserPreSize]

    setSize (290, 280);


    //[Constructor] You can add your own custom stuff here..
    updateEnabledControls();
    pianoController.addChangeListener(this);
    songLabel->addMouseListener(this, false);
    //[/Constructor]
}

PlaybackComponent::~PlaybackComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    songGroup = nullptr;
    songLabel = nullptr;
    playbackGroup = nullptr;
    guideButton = nullptr;
    positionSlider = nullptr;
    positionLabel = nullptr;
    lengthLabel = nullptr;
    lightsButton = nullptr;
    playButton = nullptr;
    rewindButton = nullptr;
    forwardButton = nullptr;
    chooseSongButton = nullptr;
    backingPartButton = nullptr;
    partLabel = nullptr;
    leftPartButton = nullptr;
    rightPartButton = nullptr;
    lightsFastButton = nullptr;
    partLabel2 = nullptr;
    loopButton = nullptr;
    muteButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PlaybackComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    {
        int x = 0, y = 0, width = getWidth() - 0, height = 58;
        Colour fillColour = Colour (0xff4e5b62);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
    }

    {
        int x = -4, y = 172, width = getWidth() - -8, height = 2;
        Colour fillColour = Colour (0xff4e5b62);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PlaybackComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    songGroup->setBounds (0, -8, getWidth() - 0, 70);
    songLabel->setBounds (0 + 12, (-8) + 16, (getWidth() - 0) - 59, 70 - 29);
    playbackGroup->setBounds (0, (-8) + 70 - 8, getWidth() - 0, 226);
    positionSlider->setBounds (0 + 12, ((-8) + 70 - 8) + 42, (getWidth() - 0) - 24, 24);
    lengthLabel->setBounds (getWidth() - 15 - 36, ((-8) + 70 - 8) + 18, 36, 20);
    playButton->setBounds (0 + 82 - (40 / 2), ((-8) + 70 - 8) + 77, 40, 28);
    rewindButton->setBounds (0 + 32 - (40 / 2), ((-8) + 70 - 8) + 77, 40, 28);
    forwardButton->setBounds (0 + 132 - (40 / 2), ((-8) + 70 - 8) + 77, 40, 28);
    chooseSongButton->setBounds (0 + (getWidth() - 0) - 20 - (20 / 2), (-8) + 29, 20, 24);
    loopButton->setBounds (0 + 194 - (40 / 2), ((-8) + 70 - 8) + 77, 40, 28);
    muteButton->setBounds (0 + 257 - (40 / 2), ((-8) + 70 - 8) + 77, 40, 28);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void PlaybackComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == guideButton)
    {
        //[UserButtonCode_guideButton] -- add your button handler code here..
        pianoController.SetGuide(!pianoController.GetGuide());
        //[/UserButtonCode_guideButton]
    }
    else if (buttonThatWasClicked == lightsButton)
    {
        //[UserButtonCode_lightsButton] -- add your button handler code here..
        pianoController.SetStreamLights(!pianoController.GetStreamLights());
        //[/UserButtonCode_lightsButton]
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
    else if (buttonThatWasClicked == chooseSongButton)
    {
        //[UserButtonCode_chooseSongButton] -- add your button handler code here..
        chooseSong();
        //[/UserButtonCode_chooseSongButton]
    }
    else if (buttonThatWasClicked == backingPartButton)
    {
        //[UserButtonCode_backingPartButton] -- add your button handler code here..
        pianoController.SetBackingPart(!pianoController.GetBackingPart());
        //[/UserButtonCode_backingPartButton]
    }
    else if (buttonThatWasClicked == leftPartButton)
    {
        //[UserButtonCode_leftPartButton] -- add your button handler code here..
        pianoController.SetLeftPart(!pianoController.GetLeftPart());
        //[/UserButtonCode_leftPartButton]
    }
    else if (buttonThatWasClicked == rightPartButton)
    {
        //[UserButtonCode_rightPartButton] -- add your button handler code here..
        pianoController.SetRightPart(!pianoController.GetRightPart());
        //[/UserButtonCode_rightPartButton]
    }
    else if (buttonThatWasClicked == lightsFastButton)
    {
        //[UserButtonCode_lightsFastButton] -- add your button handler code here..
        pianoController.SetStreamLightsFast(!pianoController.GetStreamLightsFast());
        //[/UserButtonCode_lightsFastButton]
    }
    else if (buttonThatWasClicked == loopButton)
    {
        //[UserButtonCode_loopButton] -- add your button handler code here..
        //[/UserButtonCode_loopButton]
    }
    else if (buttonThatWasClicked == muteButton)
    {
        //[UserButtonCode_muteButton] -- add your button handler code here..
        pianoController.SetLocalControl(!pianoController.GetLocalControl());
        //[/UserButtonCode_muteButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void PlaybackComponent::sliderValueChanged (Slider* sliderThatWasMoved)
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
void PlaybackComponent::chooseSong()
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

void PlaybackComponent::loadSong(const File& file)
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

void PlaybackComponent::changeListenerCallback(ChangeBroadcaster* source)
{
	if (source == &pianoController)
	{
		updateSongState();
		updateSettingsState();
	}
}

void PlaybackComponent::updateSongState()
{
	MessageManager::callAsync([=] ()
		{
			int songLength = pianoController.GetSongLength() > 0 ? pianoController.GetSongLength() : 999;
			lengthLabel->setText(String::formatted("%03d", songLength), NotificationType::dontSendNotification);
			positionSlider->setRange(1, songLength, 1);
			positionLabel->setText(String::formatted("%03d", pianoController.GetSongPosition()),
				NotificationType::dontSendNotification);
			positionSlider->setValue(pianoController.GetSongPosition(), NotificationType::dontSendNotification);

			playButton->setImages(false, true, true, ImageCache::getFromMemory(
					pianoController.GetPlaying() ? BinaryData::buttonpause_png : BinaryData::buttonplay_png,
					pianoController.GetPlaying() ? BinaryData::buttonpause_pngSize : BinaryData::buttonplay_pngSize),
					1.000f, Colour (0x00000000), Image(), 0.750f, Colour (0x00000000), Image(), 1.000f, Colour (0x00000000));
			playButton->setTooltip(pianoController.GetPlaying() ? "Pause" : "Play");
		});
}

void PlaybackComponent::updateSettingsState()
{
	MessageManager::callAsync([=] ()
		{
			bool mute = !pianoController.GetLocalControl() && pianoController.GetConnected();
			muteButton->setImages(false, true, true, ImageCache::getFromMemory(
					mute ? BinaryData::buttonmute_png : BinaryData::buttonvolume_png,
					mute ? BinaryData::buttonmute_pngSize : BinaryData::buttonvolume_pngSize),
					1.000f, Colour (0x00000000), Image(), 0.750f, Colour (0x00000000), Image(), 1.000f, Colour (0x00000000));

			guideButton->setToggleState(pianoController.GetGuide() && pianoController.GetConnected(), NotificationType::dontSendNotification);
			lightsButton->setToggleState(pianoController.GetStreamLights() && pianoController.GetConnected(), NotificationType::dontSendNotification);
			lightsFastButton->setToggleState(pianoController.GetStreamLightsFast() && pianoController.GetConnected(), NotificationType::dontSendNotification);

			backingPartButton->setToggleState(pianoController.GetBackingPart() && pianoController.GetConnected(), NotificationType::dontSendNotification);
			leftPartButton->setToggleState(pianoController.GetLeftPart() && pianoController.GetConnected(), NotificationType::dontSendNotification);
			rightPartButton->setToggleState(pianoController.GetRightPart() && pianoController.GetConnected(), NotificationType::dontSendNotification);

			updateEnabledControls();
			if (pianoController.GetConnected() && pianoController.GetSongLength() == 0)
			{
				songLabel->setText("Click here and select a Song", NotificationType::dontSendNotification);
			}
		});
}

void PlaybackComponent::updateEnabledControls()
{
	for (Component* co : getChildren())
	{
		co->setEnabled(pianoController.GetConnected());
	}
}

void PlaybackComponent::mouseUp(const MouseEvent& event)
{
	if (event.eventComponent == songLabel)
	{
		chooseSong();
	}
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PlaybackComponent" componentName=""
                 parentClasses="public Component, public ChangeListener" constructorParams="PianoController&amp; pianoController"
                 variableInitialisers="pianoController(pianoController)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="0"
                 initialWidth="290" initialHeight="280">
  <BACKGROUND backgroundColour="ff323e44">
    <RECT pos="0 0 0M 58" fill="solid: ff4e5b62" hasStroke="0"/>
    <RECT pos="-4 172 -8M 2" fill="solid: ff4e5b62" hasStroke="0"/>
  </BACKGROUND>
  <GROUPCOMPONENT name="Song" id="4e6df4a0ae6e851b" memberName="songGroup" virtualName=""
                  explicitFocusOrder="0" pos="0 -8 0M 70" title="Song" textpos="36"/>
  <LABEL name="Song Label" id="8682794e760bce8" memberName="songLabel"
         virtualName="" explicitFocusOrder="0" pos="12 16 59M 29M" posRelativeX="4e6df4a0ae6e851b"
         posRelativeY="4e6df4a0ae6e851b" posRelativeW="4e6df4a0ae6e851b"
         posRelativeH="4e6df4a0ae6e851b" edTextCol="ff000000" edBkgCol="0"
         labelText="Not connected to piano yet" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="23.69999999999999928946" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="33"/>
  <GROUPCOMPONENT name="Playback" id="c7b94b60aa96c6e2" memberName="playbackGroup"
                  virtualName="" explicitFocusOrder="0" pos="0 8R 0M 226" posRelativeY="4e6df4a0ae6e851b"
                  title="Playback" textpos="36"/>
  <TEXTBUTTON name="Guide Button" id="c850d2e92ae26093" memberName="guideButton"
              virtualName="" explicitFocusOrder="0" pos="80 134 64 28" posRelativeY="c7b94b60aa96c6e2"
              buttonText="Guide" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <SLIDER name="Song Position slider" id="3f9d3a942dcf1d69" memberName="positionSlider"
          virtualName="" explicitFocusOrder="0" pos="12 42 24M 24" posRelativeX="c7b94b60aa96c6e2"
          posRelativeY="c7b94b60aa96c6e2" posRelativeW="c7b94b60aa96c6e2"
          tooltip="Song Position" min="1.00000000000000000000" max="999.00000000000000000000"
          int="1.00000000000000000000" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1.00000000000000000000"
          needsCallback="1"/>
  <LABEL name="Song Position Label" id="17ac2967e993dc43" memberName="positionLabel"
         virtualName="" explicitFocusOrder="0" pos="16 18 36 20" posRelativeX="be38d66c26f6bda6"
         posRelativeY="c7b94b60aa96c6e2" edTextCol="ff000000" edBkgCol="0"
         labelText="001" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.00000000000000000000"
         kerning="0.00000000000000000000" bold="0" italic="0" justification="36"/>
  <LABEL name="Song Length Label" id="537604aa6486f948" memberName="lengthLabel"
         virtualName="" explicitFocusOrder="0" pos="15Rr 18 36 20" posRelativeX="be38d66c26f6bda6"
         posRelativeY="c7b94b60aa96c6e2" edTextCol="ff000000" edBkgCol="0"
         labelText="999" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.00000000000000000000"
         kerning="0.00000000000000000000" bold="0" italic="0" justification="36"/>
  <TEXTBUTTON name="Lights Button" id="5e04ec6b8d091999" memberName="lightsButton"
              virtualName="" explicitFocusOrder="0" pos="148 134 64 28" posRelativeX="c7b94b60aa96c6e2"
              posRelativeY="c7b94b60aa96c6e2" buttonText="Lights" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <IMAGEBUTTON name="Play Button" id="e85b378cc3166e44" memberName="playButton"
               virtualName="" explicitFocusOrder="0" pos="82c 77 40 28" posRelativeX="c7b94b60aa96c6e2"
               posRelativeY="c7b94b60aa96c6e2" buttonText="Play" connectedEdges="0"
               needsCallback="1" radioGroupId="0" keepProportions="1" resourceNormal="BinaryData::buttonplay_png"
               opacityNormal="1.00000000000000000000" colourNormal="0" resourceOver=""
               opacityOver="0.75000000000000000000" colourOver="0" resourceDown=""
               opacityDown="1.00000000000000000000" colourDown="0"/>
  <IMAGEBUTTON name="Rewind Button" id="e7074d9d71bdc0e6" memberName="rewindButton"
               virtualName="" explicitFocusOrder="0" pos="32c 77 40 28" posRelativeX="c7b94b60aa96c6e2"
               posRelativeY="c7b94b60aa96c6e2" buttonText="Rewind" connectedEdges="0"
               needsCallback="1" radioGroupId="0" keepProportions="1" resourceNormal="BinaryData::buttonrewind_png"
               opacityNormal="1.00000000000000000000" colourNormal="0" resourceOver=""
               opacityOver="0.75000000000000000000" colourOver="0" resourceDown=""
               opacityDown="1.00000000000000000000" colourDown="0"/>
  <IMAGEBUTTON name="Forward Button" id="80a800a526f191f0" memberName="forwardButton"
               virtualName="" explicitFocusOrder="0" pos="132c 77 40 28" posRelativeX="c7b94b60aa96c6e2"
               posRelativeY="c7b94b60aa96c6e2" buttonText="Play" connectedEdges="0"
               needsCallback="1" radioGroupId="0" keepProportions="1" resourceNormal="BinaryData::buttonfastforward_png"
               opacityNormal="1.00000000000000000000" colourNormal="0" resourceOver=""
               opacityOver="0.75000000000000000000" colourOver="0" resourceDown=""
               opacityDown="1.00000000000000000000" colourDown="0"/>
  <IMAGEBUTTON name="Choose Song Button" id="290d61a1138635c0" memberName="chooseSongButton"
               virtualName="" explicitFocusOrder="0" pos="20Rc 29 20 24" posRelativeX="4e6df4a0ae6e851b"
               posRelativeY="4e6df4a0ae6e851b" buttonText="Choose" connectedEdges="0"
               needsCallback="1" radioGroupId="0" keepProportions="1" resourceNormal="BinaryData::buttonexpand_png"
               opacityNormal="1.00000000000000000000" colourNormal="0" resourceOver=""
               opacityOver="0.75000000000000000000" colourOver="0" resourceDown=""
               opacityDown="1.00000000000000000000" colourDown="0"/>
  <TEXTBUTTON name="Backing Part Button" id="c44e73ef2ac29304" memberName="backingPartButton"
              virtualName="" explicitFocusOrder="0" pos="80 182 64 28" posRelativeY="c7b94b60aa96c6e2"
              buttonText="Backing" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="Part Label" id="35efabd1f34f8989" memberName="partLabel"
         virtualName="" explicitFocusOrder="0" pos="16 182 40 24" posRelativeY="c7b94b60aa96c6e2"
         edTextCol="ff000000" edBkgCol="0" labelText="Part" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="Left Part Button" id="e9e1457f74b6fe2f" memberName="leftPartButton"
              virtualName="" explicitFocusOrder="0" pos="148 182 64 28" posRelativeY="c7b94b60aa96c6e2"
              buttonText="Left" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Right Part Button" id="7413d6f9d0d8d631" memberName="rightPartButton"
              virtualName="" explicitFocusOrder="0" pos="216 182 64 28" posRelativeY="c7b94b60aa96c6e2"
              buttonText="Right" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Lights Fast Button" id="88cbd655c4b5df0e" memberName="lightsFastButton"
              virtualName="" explicitFocusOrder="0" pos="216 134 64 28" posRelativeX="c7b94b60aa96c6e2"
              posRelativeY="c7b94b60aa96c6e2" buttonText="Fast" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <LABEL name="Part Label" id="bfc2692dcec51aeb" memberName="partLabel2"
         virtualName="" explicitFocusOrder="0" pos="16 134 64 24" posRelativeY="c7b94b60aa96c6e2"
         edTextCol="ff000000" edBkgCol="0" labelText="Practice" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="33"/>
  <IMAGEBUTTON name="Loop Button" id="bb69a3594c9c2d4a" memberName="loopButton"
               virtualName="" explicitFocusOrder="0" pos="194c 77 40 28" posRelativeX="c7b94b60aa96c6e2"
               posRelativeY="c7b94b60aa96c6e2" buttonText="Loop" connectedEdges="0"
               needsCallback="1" radioGroupId="0" keepProportions="1" resourceNormal="BinaryData::buttonabloop_png"
               opacityNormal="1.00000000000000000000" colourNormal="0" resourceOver=""
               opacityOver="0.75000000000000000000" colourOver="0" resourceDown=""
               opacityDown="1.00000000000000000000" colourDown="0"/>
  <IMAGEBUTTON name="Mute Button" id="5fb10e62b96082d3" memberName="muteButton"
               virtualName="" explicitFocusOrder="0" pos="257c 77 40 28" posRelativeX="c7b94b60aa96c6e2"
               posRelativeY="c7b94b60aa96c6e2" buttonText="Mute" connectedEdges="0"
               needsCallback="1" radioGroupId="0" keepProportions="1" resourceNormal="BinaryData::buttonvolume_png"
               opacityNormal="1.00000000000000000000" colourNormal="0" resourceOver=""
               opacityOver="0.75000000000000000000" colourOver="0" resourceDown=""
               opacityDown="1.00000000000000000000" colourDown="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
