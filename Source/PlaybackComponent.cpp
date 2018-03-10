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

    addAndMakeVisible (positionSlider = new Slider ("Song Position slider"));
    positionSlider->setTooltip (TRANS("Song position"));
    positionSlider->setRange (1, 999, 1);
    positionSlider->setSliderStyle (Slider::LinearHorizontal);
    positionSlider->setTextBoxStyle (Slider::NoTextBox, true, 80, 20);
    positionSlider->addListener (this);

    addAndMakeVisible (positionLabel = new Label ("Song Position Label",
                                                  TRANS("001")));
    positionLabel->setTooltip (TRANS("Current measure"));
    positionLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    positionLabel->setJustificationType (Justification::centredLeft);
    positionLabel->setEditable (false, false, false);
    positionLabel->setColour (TextEditor::textColourId, Colours::black);
    positionLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    positionLabel->setBounds (8, ((-8) + 70 - 8) + 24, 36, 20);

    addAndMakeVisible (lengthLabel = new Label ("Song Length Label",
                                                TRANS("999")));
    lengthLabel->setTooltip (TRANS("Number of measures"));
    lengthLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    lengthLabel->setJustificationType (Justification::centredRight);
    lengthLabel->setEditable (false, false, false);
    lengthLabel->setColour (TextEditor::textColourId, Colours::black);
    lengthLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (playButton = new ImageButton ("Play Button"));
    playButton->setTooltip (TRANS("Play/pause"));
    playButton->setButtonText (TRANS("Play"));
    playButton->addListener (this);

    playButton->setImages (false, true, true,
                           ImageCache::getFromMemory (BinaryData::buttonplay_png, BinaryData::buttonplay_pngSize), 1.000f, Colour (0x00000000),
                           Image(), 0.750f, Colour (0x00000000),
                           Image(), 1.000f, Colour (0x00000000));
    playButton->setBounds (59, ((-8) + 70 - 8) + 60, 40, 28);

    addAndMakeVisible (rewindButton = new ImageButton ("Rewind Button"));
    rewindButton->setTooltip (TRANS("Jump to previous measure"));
    rewindButton->setButtonText (TRANS("Rewind"));
    rewindButton->addListener (this);

    rewindButton->setImages (false, true, true,
                             ImageCache::getFromMemory (BinaryData::buttonrewind_png, BinaryData::buttonrewind_pngSize), 1.000f, Colour (0x00000000),
                             Image(), 0.750f, Colour (0x00000000),
                             Image(), 1.000f, Colour (0x00000000));
    rewindButton->setBounds (14, ((-8) + 70 - 8) + 60, 40, 28);

    addAndMakeVisible (forwardButton = new ImageButton ("Forward Button"));
    forwardButton->setTooltip (TRANS("Jump to next measure"));
    forwardButton->setButtonText (TRANS("Play"));
    forwardButton->addListener (this);

    forwardButton->setImages (false, true, true,
                              ImageCache::getFromMemory (BinaryData::buttonfastforward_png, BinaryData::buttonfastforward_pngSize), 1.000f, Colour (0x00000000),
                              Image(), 0.750f, Colour (0x00000000),
                              Image(), 1.000f, Colour (0x00000000));
    forwardButton->setBounds (104, ((-8) + 70 - 8) + 60, 40, 28);

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

    backingPartButton->setBounds (14, ((-8) + 70 - 8) + 142, 86, 28);

    addAndMakeVisible (partLabel = new Label ("Part Label",
                                              TRANS("Part")));
    partLabel->setTooltip (TRANS("Playback part"));
    partLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    partLabel->setJustificationType (Justification::centredLeft);
    partLabel->setEditable (false, false, false);
    partLabel->setColour (TextEditor::textColourId, Colours::black);
    partLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    partLabel->setBounds (8, ((-8) + 70 - 8) + 110, 112, 24);

    addAndMakeVisible (leftPartButton = new TextButton ("Left Part Button"));
    leftPartButton->setButtonText (TRANS("Left"));
    leftPartButton->addListener (this);

    leftPartButton->setBounds (103, ((-8) + 70 - 8) + 142, 86, 28);

    addAndMakeVisible (rightPartButton = new TextButton ("Right Part Button"));
    rightPartButton->setButtonText (TRANS("Right"));
    rightPartButton->addListener (this);

    rightPartButton->setBounds (0 + 192, ((-8) + 70 - 8) + 142, 86, 28);

    addAndMakeVisible (guideButton = new ImageButton ("Guide Button"));
    guideButton->setTooltip (TRANS("Guide mode (wait for note)"));
    guideButton->setButtonText (TRANS("Guide"));
    guideButton->addListener (this);

    guideButton->setImages (false, true, true,
                            ImageCache::getFromMemory (BinaryData::buttonguide_png, BinaryData::buttonguide_pngSize), 1.000f, Colour (0x00000000),
                            Image(), 0.750f, Colour (0x00000000),
                            Image(), 1.000f, Colour (0x00000000));
    guideButton->setBounds (0 + 193, ((-8) + 70 - 8) + 60, 40, 28);

    addAndMakeVisible (loopButton = new ImageButton ("Loop Button"));
    loopButton->setTooltip (TRANS("Repeat selected fragment (click twice to select)"));
    loopButton->setButtonText (TRANS("A->B Loop"));
    loopButton->addListener (this);

    loopButton->setImages (false, true, true,
                           ImageCache::getFromMemory (BinaryData::buttonabloop_png, BinaryData::buttonabloop_pngSize), 1.000f, Colour (0x00000000),
                           Image(), 0.750f, Colour (0x00000000),
                           Image(), 1.000f, Colour (0x00000000));
    loopButton->setBounds (148, ((-8) + 70 - 8) + 60, 40, 28);

    addAndMakeVisible (lightsButton = new ImageButton ("Lights Button"));
    lightsButton->setTooltip (TRANS("Stream lights on/off"));
    lightsButton->setButtonText (TRANS("Lights"));
    lightsButton->addListener (this);

    lightsButton->setImages (false, true, true,
                             ImageCache::getFromMemory (BinaryData::buttonlights_png, BinaryData::buttonlights_pngSize), 1.000f, Colour (0x00000000),
                             Image(), 0.750f, Colour (0x00000000),
                             Image(), 1.000f, Colour (0x00000000));
    lightsButton->setBounds (0 + 238, ((-8) + 70 - 8) + 60, 40, 28);


    //[UserPreSize]
    playbackGroup->setColour(GroupComponent::outlineColourId, Colours::transparentBlack);
    playbackGroup->setText("");
    songGroup->setColour(GroupComponent::outlineColourId, Colours::transparentBlack);
    songGroup->setText("");
    //[/UserPreSize]

    setSize (290, 320);


    //[Constructor] You can add your own custom stuff here..
    updateEnabledControls();
    pianoController.addChangeListener(this);
    songLabel->addMouseListener(this, false);
    backingPartButton->getProperties().set("toggle", "yes");
    leftPartButton->getProperties().set("toggle", "yes");
    rightPartButton->getProperties().set("toggle", "yes");
    guideButton->getProperties().set("toggle", "yes");
    lightsButton->getProperties().set("toggle", "yes");
    loopButton->getProperties().set("toggle", "yes");
    //[/Constructor]
}

PlaybackComponent::~PlaybackComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    songGroup = nullptr;
    songLabel = nullptr;
    playbackGroup = nullptr;
    positionSlider = nullptr;
    positionLabel = nullptr;
    lengthLabel = nullptr;
    playButton = nullptr;
    rewindButton = nullptr;
    forwardButton = nullptr;
    chooseSongButton = nullptr;
    backingPartButton = nullptr;
    partLabel = nullptr;
    leftPartButton = nullptr;
    rightPartButton = nullptr;
    guideButton = nullptr;
    loopButton = nullptr;
    lightsButton = nullptr;


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
        int x = -4, y = 156, width = getWidth() - -8, height = 2;
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
    playbackGroup->setBounds (0, (-8) + 70 - 8, getWidth() - 0, 186);
    positionSlider->setBounds (0 + 48, ((-8) + 70 - 8) + 22, (getWidth() - 0) - 96, 24);
    lengthLabel->setBounds (0 + (getWidth() - 0) - 8 - 36, ((-8) + 70 - 8) + 24, 36, 20);
    chooseSongButton->setBounds (0 + (getWidth() - 0) - 20 - (20 / 2), (-8) + 25, 20, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
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

void PlaybackComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == playButton)
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
    else if (buttonThatWasClicked == guideButton)
    {
        //[UserButtonCode_guideButton] -- add your button handler code here..
        pianoController.SetGuide(!pianoController.GetGuide());
        //[/UserButtonCode_guideButton]
    }
    else if (buttonThatWasClicked == loopButton)
    {
        //[UserButtonCode_loopButton] -- add your button handler code here..
        loopButtonClicked();
        //[/UserButtonCode_loopButton]
    }
    else if (buttonThatWasClicked == lightsButton)
    {
        //[UserButtonCode_lightsButton] -- add your button handler code here..
        pianoController.SetStreamLights(!pianoController.GetStreamLights());
        //[/UserButtonCode_lightsButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
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
			guideButton->setToggleState(pianoController.GetGuide() && pianoController.GetConnected(), NotificationType::dontSendNotification);
			lightsButton->setToggleState(pianoController.GetStreamLights() && pianoController.GetConnected(), NotificationType::dontSendNotification);
			//lightsFastButton->setToggleState(pianoController.GetStreamLightsFast() && pianoController.GetConnected(), NotificationType::dontSendNotification);

			backingPartButton->setToggleState(pianoController.GetBackingPart() && pianoController.GetConnected(), NotificationType::dontSendNotification);
			leftPartButton->setToggleState(pianoController.GetLeftPart() && pianoController.GetConnected(), NotificationType::dontSendNotification);
			rightPartButton->setToggleState(pianoController.GetRightPart() && pianoController.GetConnected(), NotificationType::dontSendNotification);

			updateEnabledControls();
			if (pianoController.GetConnected() && songLabel->getText() == "Not connected to piano yet")
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

void PlaybackComponent::loopButtonClicked()
{
	AlertWindow::showNativeDialogBox("Information",
		"This function is not yet implemented.", false);
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
                 initialWidth="290" initialHeight="320">
  <BACKGROUND backgroundColour="ff323e44">
    <RECT pos="0 0 0M 58" fill="solid: ff4e5b62" hasStroke="0"/>
    <RECT pos="-4 156 -8M 2" fill="solid: ff4e5b62" hasStroke="0"/>
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
                  virtualName="" explicitFocusOrder="0" pos="0 8R 0M 186" posRelativeY="4e6df4a0ae6e851b"
                  title="Playback" textpos="36"/>
  <SLIDER name="Song Position slider" id="3f9d3a942dcf1d69" memberName="positionSlider"
          virtualName="" explicitFocusOrder="0" pos="48 22 96M 24" posRelativeX="c7b94b60aa96c6e2"
          posRelativeY="c7b94b60aa96c6e2" posRelativeW="c7b94b60aa96c6e2"
          tooltip="Song position" min="1.00000000000000000000" max="999.00000000000000000000"
          int="1.00000000000000000000" style="LinearHorizontal" textBoxPos="NoTextBox"
          textBoxEditable="0" textBoxWidth="80" textBoxHeight="20" skewFactor="1.00000000000000000000"
          needsCallback="1"/>
  <LABEL name="Song Position Label" id="17ac2967e993dc43" memberName="positionLabel"
         virtualName="" explicitFocusOrder="0" pos="8 24 36 20" posRelativeY="c7b94b60aa96c6e2"
         tooltip="Current measure" edTextCol="ff000000" edBkgCol="0" labelText="001"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="33"/>
  <LABEL name="Song Length Label" id="537604aa6486f948" memberName="lengthLabel"
         virtualName="" explicitFocusOrder="0" pos="8Rr 24 36 20" posRelativeX="c7b94b60aa96c6e2"
         posRelativeY="c7b94b60aa96c6e2" tooltip="Number of measures"
         edTextCol="ff000000" edBkgCol="0" labelText="999" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="34"/>
  <IMAGEBUTTON name="Play Button" id="e85b378cc3166e44" memberName="playButton"
               virtualName="" explicitFocusOrder="0" pos="59 60 40 28" posRelativeY="c7b94b60aa96c6e2"
               tooltip="Play/pause" buttonText="Play" connectedEdges="0" needsCallback="1"
               radioGroupId="0" keepProportions="1" resourceNormal="BinaryData::buttonplay_png"
               opacityNormal="1.00000000000000000000" colourNormal="0" resourceOver=""
               opacityOver="0.75000000000000000000" colourOver="0" resourceDown=""
               opacityDown="1.00000000000000000000" colourDown="0"/>
  <IMAGEBUTTON name="Rewind Button" id="e7074d9d71bdc0e6" memberName="rewindButton"
               virtualName="" explicitFocusOrder="0" pos="14 60 40 28" posRelativeY="c7b94b60aa96c6e2"
               tooltip="Jump to previous measure" buttonText="Rewind" connectedEdges="0"
               needsCallback="1" radioGroupId="0" keepProportions="1" resourceNormal="BinaryData::buttonrewind_png"
               opacityNormal="1.00000000000000000000" colourNormal="0" resourceOver=""
               opacityOver="0.75000000000000000000" colourOver="0" resourceDown=""
               opacityDown="1.00000000000000000000" colourDown="0"/>
  <IMAGEBUTTON name="Forward Button" id="80a800a526f191f0" memberName="forwardButton"
               virtualName="" explicitFocusOrder="0" pos="104 60 40 28" posRelativeY="c7b94b60aa96c6e2"
               tooltip="Jump to next measure" buttonText="Play" connectedEdges="0"
               needsCallback="1" radioGroupId="0" keepProportions="1" resourceNormal="BinaryData::buttonfastforward_png"
               opacityNormal="1.00000000000000000000" colourNormal="0" resourceOver=""
               opacityOver="0.75000000000000000000" colourOver="0" resourceDown=""
               opacityDown="1.00000000000000000000" colourDown="0"/>
  <IMAGEBUTTON name="Choose Song Button" id="290d61a1138635c0" memberName="chooseSongButton"
               virtualName="" explicitFocusOrder="0" pos="20Rc 25 20 24" posRelativeX="4e6df4a0ae6e851b"
               posRelativeY="4e6df4a0ae6e851b" buttonText="Choose" connectedEdges="0"
               needsCallback="1" radioGroupId="0" keepProportions="1" resourceNormal="BinaryData::buttonexpand_png"
               opacityNormal="1.00000000000000000000" colourNormal="0" resourceOver=""
               opacityOver="0.75000000000000000000" colourOver="0" resourceDown=""
               opacityDown="1.00000000000000000000" colourDown="0"/>
  <TEXTBUTTON name="Backing Part Button" id="c44e73ef2ac29304" memberName="backingPartButton"
              virtualName="" explicitFocusOrder="0" pos="14 142 86 28" posRelativeY="c7b94b60aa96c6e2"
              buttonText="Backing" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="Part Label" id="35efabd1f34f8989" memberName="partLabel"
         virtualName="" explicitFocusOrder="0" pos="8 110 112 24" posRelativeY="c7b94b60aa96c6e2"
         tooltip="Playback part" edTextCol="ff000000" edBkgCol="0" labelText="Part"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="Left Part Button" id="e9e1457f74b6fe2f" memberName="leftPartButton"
              virtualName="" explicitFocusOrder="0" pos="103 142 86 28" posRelativeY="c7b94b60aa96c6e2"
              buttonText="Left" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Right Part Button" id="7413d6f9d0d8d631" memberName="rightPartButton"
              virtualName="" explicitFocusOrder="0" pos="192 142 86 28" posRelativeX="c7b94b60aa96c6e2"
              posRelativeY="c7b94b60aa96c6e2" buttonText="Right" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <IMAGEBUTTON name="Guide Button" id="21ab7b81d08c0a5a" memberName="guideButton"
               virtualName="" explicitFocusOrder="0" pos="193 60 40 28" posRelativeX="c7b94b60aa96c6e2"
               posRelativeY="c7b94b60aa96c6e2" tooltip="Guide mode (wait for note)"
               buttonText="Guide" connectedEdges="0" needsCallback="1" radioGroupId="0"
               keepProportions="1" resourceNormal="BinaryData::buttonguide_png"
               opacityNormal="1.00000000000000000000" colourNormal="0" resourceOver=""
               opacityOver="0.75000000000000000000" colourOver="0" resourceDown=""
               opacityDown="1.00000000000000000000" colourDown="0"/>
  <IMAGEBUTTON name="Loop Button" id="f6f613d6939aee17" memberName="loopButton"
               virtualName="" explicitFocusOrder="0" pos="148 60 40 28" posRelativeY="c7b94b60aa96c6e2"
               tooltip="Repeat selected fragment (click twice to select)" buttonText="A-&gt;B Loop"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="BinaryData::buttonabloop_png" opacityNormal="1.00000000000000000000"
               colourNormal="0" resourceOver="" opacityOver="0.75000000000000000000"
               colourOver="0" resourceDown="" opacityDown="1.00000000000000000000"
               colourDown="0"/>
  <IMAGEBUTTON name="Lights Button" id="ca510a4be11fdde2" memberName="lightsButton"
               virtualName="" explicitFocusOrder="0" pos="238 60 40 28" posRelativeX="c7b94b60aa96c6e2"
               posRelativeY="c7b94b60aa96c6e2" tooltip="Stream lights on/off"
               buttonText="Lights" connectedEdges="0" needsCallback="1" radioGroupId="0"
               keepProportions="1" resourceNormal="BinaryData::buttonlights_png"
               opacityNormal="1.00000000000000000000" colourNormal="0" resourceOver=""
               opacityOver="0.75000000000000000000" colourOver="0" resourceDown=""
               opacityDown="1.00000000000000000000" colourDown="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
