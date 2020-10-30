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
#include "Presets.h"
#include "GuiHelper.h"
//[/Headers]

#include "ChannelComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ChannelComponent::ChannelComponent (Settings& settings, PianoController& pianoController, PianoController::Channel channel, String title, bool showLabels, bool showMenu, bool shrinkMenu, bool scrollable)
    : settings(settings), pianoController(pianoController), channel(channel), title(title), showMenuRow(showMenu), shrinkMenu(shrinkMenu)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    keyboardButton.reset (new ImageButton ("Keyboard Button"));
    addAndMakeVisible (keyboardButton.get());
    keyboardButton->setTooltip (TRANS("Target for Virtual Keyboard"));
    keyboardButton->setButtonText (TRANS("Menu"));
    keyboardButton->addListener (this);

    keyboardButton->setImages (false, true, true,
                               ImageCache::getFromMemory (BinaryData::buttonkeyboardwide_png, BinaryData::buttonkeyboardwide_pngSize), 1.000f, Colour (0x00000000),
                               Image(), 0.750f, Colour (0x00000000),
                               Image(), 1.000f, Colour (0x00000000));
    keyboardButton->setBounds (11, 96, 48, 16);

    menuButton.reset (new ImageButton ("Menu Button"));
    addAndMakeVisible (menuButton.get());
    menuButton->setTooltip (TRANS("Context Menu"));
    menuButton->setButtonText (TRANS("Menu"));
    menuButton->addListener (this);

    menuButton->setImages (false, true, true,
                           ImageCache::getFromMemory (BinaryData::buttoncontextmenu_png, BinaryData::buttoncontextmenu_pngSize), 1.000f, Colour (0x00000000),
                           Image(), 0.750f, Colour (0x00000000),
                           Image(), 1.000f, Colour (0x00000000));
    menuButton->setBounds (4, 66, 28, 28);

    partLabel.reset (new Label ("Part Label",
                                TRANS("R")));
    addAndMakeVisible (partLabel.get());
    partLabel->setFont (Font (18.00f, Font::plain).withTypefaceStyle ("Regular"));
    partLabel->setJustificationType (Justification::centred);
    partLabel->setEditable (false, false, false);
    partLabel->setColour (Label::backgroundColourId, Colour (0xff42a2c8));
    partLabel->setColour (Label::textColourId, Colours::azure);
    partLabel->setColour (TextEditor::textColourId, Colours::black);
    partLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    partLabel->setBounds (37, 69, 22, 21);

    panLabel.reset (new Label ("Pan Label",
                               TRANS("Pan")));
    addAndMakeVisible (panLabel.get());
    panLabel->setFont (Font (15.40f, Font::plain).withTypefaceStyle ("Regular"));
    panLabel->setJustificationType (Justification::centredLeft);
    panLabel->setEditable (false, false, false);
    panLabel->setColour (TextEditor::textColourId, Colours::black);
    panLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    panLabel->setBounds (0, 90, 40, 24);

    menuButton2.reset (new ImageButton ("Menu Button"));
    addAndMakeVisible (menuButton2.get());
    menuButton2->setTooltip (TRANS("Context Menu"));
    menuButton2->setButtonText (TRANS("Menu"));
    menuButton2->addListener (this);

    menuButton2->setImages (false, true, true,
                            Image(), 1.000f, Colour (0x00000000),
                            Image(), 0.750f, Colour (0x00000000),
                            Image(), 1.000f, Colour (0x00000000));
    menuButton2->setBounds (33, 66, 28, 28);

    volumeSlider.reset (new Slider ("Volume Slider"));
    addAndMakeVisible (volumeSlider.get());
    volumeSlider->setRange (0, 127, 1);
    volumeSlider->setSliderStyle (Slider::LinearVertical);
    volumeSlider->setTextBoxStyle (Slider::TextBoxAbove, false, 50, 20);
    volumeSlider->setColour (Slider::textBoxOutlineColourId, Colour (0x80939d9f));
    volumeSlider->addListener (this);

    panSlider.reset (new Slider ("Pan Slider"));
    addAndMakeVisible (panSlider.get());
    panSlider->setRange (-64, 63, 1);
    panSlider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    panSlider->setTextBoxStyle (Slider::TextBoxAbove, false, 50, 20);
    panSlider->setColour (Slider::textBoxHighlightColourId, Colour (0x6642a2c8));
    panSlider->setColour (Slider::textBoxOutlineColourId, Colour (0x80939d9f));
    panSlider->addListener (this);

    panSlider->setBounds (0, 122, 70, 76);

    reverbLabel.reset (new Label ("Reverb Label",
                                  TRANS("Reverb")));
    addAndMakeVisible (reverbLabel.get());
    reverbLabel->setFont (Font (15.40f, Font::plain).withTypefaceStyle ("Regular"));
    reverbLabel->setJustificationType (Justification::centredLeft);
    reverbLabel->setEditable (false, false, false);
    reverbLabel->setColour (TextEditor::textColourId, Colours::black);
    reverbLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    reverbLabel->setBounds (0, 196, 70, 24);

    reverbSlider.reset (new Slider ("Reverb Slider"));
    addAndMakeVisible (reverbSlider.get());
    reverbSlider->setRange (0, 127, 1);
    reverbSlider->setSliderStyle (Slider::RotaryHorizontalVerticalDrag);
    reverbSlider->setTextBoxStyle (Slider::TextBoxAbove, false, 50, 20);
    reverbSlider->setColour (Slider::textBoxOutlineColourId, Colour (0x80939d9f));
    reverbSlider->addListener (this);

    reverbSlider->setBounds (0, 228, 70, 76);

    volumeLabel.reset (new Label ("Volume Label",
                                  TRANS("Volume")));
    addAndMakeVisible (volumeLabel.get());
    volumeLabel->setFont (Font (15.40f, Font::plain).withTypefaceStyle ("Regular"));
    volumeLabel->setJustificationType (Justification::centredLeft);
    volumeLabel->setEditable (false, false, false);
    volumeLabel->setColour (TextEditor::textColourId, Colours::black);
    volumeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    volumeLabel->setBounds (0, 304, 70, 24);

    titleButton.reset (new TextButton ("Title Button"));
    addAndMakeVisible (titleButton.get());
    titleButton->setButtonText (String());
    titleButton->addListener (this);

    titleButton->setBounds (2, 8, 66, 52);

    titleLabel.reset (new Label ("Title Label",
                                 TRANS("Ch. 1")));
    addAndMakeVisible (titleLabel.get());
    titleLabel->setFont (Font (15.60f, Font::plain).withTypefaceStyle ("Regular"));
    titleLabel->setJustificationType (Justification::centred);
    titleLabel->setEditable (false, false, false);
    titleLabel->setColour (TextEditor::textColourId, Colours::black);
    titleLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    titleLabel->setBounds (2, 9, 66, 22);

    voiceLabel.reset (new Label ("Voice Label",
                                 TRANS("String Ensemble")));
    addAndMakeVisible (voiceLabel.get());
    voiceLabel->setFont (Font (14.00f, Font::plain).withTypefaceStyle ("Regular"));
    voiceLabel->setJustificationType (Justification::centred);
    voiceLabel->setEditable (false, false, false);
    voiceLabel->setColour (TextEditor::textColourId, Colours::black);
    voiceLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    voiceLabel->setBounds (2, 33, 66, 22);


    //[UserPreSize]
    titleButton->getProperties().set("toggle", "yes");
    titleLabel->setText(title, NotificationType::dontSendNotification);
	panLabel->setVisible(showLabels);
	reverbLabel->setVisible(showLabels);
	volumeLabel->setVisible(showLabels);
    menuButton->setVisible(showMenu);
    menuButton2->setVisible(showMenu);
    partLabel->setVisible(showMenu);

    if (shrinkMenu)
    {
    	int delta = 20;
		panLabel->setTopLeftPosition(panLabel->getX(), panLabel->getY() - delta);
		reverbLabel->setTopLeftPosition(reverbLabel->getX(), reverbLabel->getY() - delta);
		volumeLabel->setTopLeftPosition(volumeLabel->getX(), volumeLabel->getY() - delta);
		panSlider->setTopLeftPosition(panSlider->getX(), panSlider->getY() - delta);
		reverbSlider->setTopLeftPosition(reverbSlider->getX(), reverbSlider->getY() - delta);
	}
    //[/UserPreSize]

    setSize (70, 560);


    //[Constructor] You can add your own custom stuff here..
    titleLabel->addMouseListener(this, false);
    voiceLabel->addMouseListener(this, false);
    panSlider->addMouseListener(this, false);
    reverbSlider->addMouseListener(this, false);
    volumeSlider->addMouseListener(this, false);

    partLabel->getProperties().set("bg-status", "yes");

	panSlider->setViewportIgnoreDragFlag(true);
	reverbSlider->setViewportIgnoreDragFlag(true);
	volumeSlider->setViewportIgnoreDragFlag(true);

	panSlider->setScrollWheelEnabled(!scrollable);
	reverbSlider->setScrollWheelEnabled(!scrollable);
	volumeSlider->setScrollWheelEnabled(!scrollable);

    pianoController.AddListener(this);
    updateChannelState(PianoController::apActive);
    settings.addChangeListener(this);
    applySettings();
    //[/Constructor]
}

ChannelComponent::~ChannelComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    pianoController.RemoveListener(this);
    settings.removeChangeListener(this);
    //[/Destructor_pre]

    keyboardButton = nullptr;
    menuButton = nullptr;
    partLabel = nullptr;
    panLabel = nullptr;
    menuButton2 = nullptr;
    volumeSlider = nullptr;
    panSlider = nullptr;
    reverbLabel = nullptr;
    reverbSlider = nullptr;
    volumeLabel = nullptr;
    titleButton = nullptr;
    titleLabel = nullptr;
    voiceLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ChannelComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ChannelComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    volumeSlider->setBounds (0, 336, 70, getHeight() - 342);
    //[UserResized] Add your own custom resize handling here..
    if (shrinkMenu)
    {
    	int delta = 20;
		volumeSlider->setBounds(volumeSlider->getX(), volumeSlider->getY() - delta,
			volumeSlider->getWidth(), volumeSlider->getHeight() + delta);
	}
    //[/UserResized]
}

void ChannelComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == keyboardButton.get())
    {
        //[UserButtonCode_keyboardButton] -- add your button handler code here..
        showMenu(buttonThatWasClicked);
        //[/UserButtonCode_keyboardButton]
    }
    else if (buttonThatWasClicked == menuButton.get())
    {
        //[UserButtonCode_menuButton] -- add your button handler code here..
        showMenu(buttonThatWasClicked);
        //[/UserButtonCode_menuButton]
    }
    else if (buttonThatWasClicked == menuButton2.get())
    {
        //[UserButtonCode_menuButton2] -- add your button handler code here..
        showMenu(buttonThatWasClicked);
        //[/UserButtonCode_menuButton2]
    }
    else if (buttonThatWasClicked == titleButton.get())
    {
        //[UserButtonCode_titleButton] -- add your button handler code here..
        //[/UserButtonCode_titleButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void ChannelComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == volumeSlider.get())
    {
        //[UserSliderCode_volumeSlider] -- add your slider handling code here..
        inVolumeChange++;
		pianoController.SetVolume(channel, volumeSlider->getValue());
        //[/UserSliderCode_volumeSlider]
    }
    else if (sliderThatWasMoved == panSlider.get())
    {
        //[UserSliderCode_panSlider] -- add your slider handling code here..
        inPanChange++;
		pianoController.SetPan(channel, panSlider->getValue());
        //[/UserSliderCode_panSlider]
    }
    else if (sliderThatWasMoved == reverbSlider.get())
    {
        //[UserSliderCode_reverbSlider] -- add your slider handling code here..
        inReverbChange++;
		pianoController.SetReverb(channel, reverbSlider->getValue());
        //[/UserSliderCode_reverbSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void ChannelComponent::updateChannelState(PianoController::Aspect aspect)
{
	if (aspect == PianoController::apVolume && inVolumeChange && inVolumeChange--) return;
	if (aspect == PianoController::apPan && inPanChange && inPanChange--) return;
	if (aspect == PianoController::apReverb && inReverbChange && inReverbChange--) return;

	if (aspect == PianoController::apConnection)
	{
		inVolumeChange = 0;
		inPanChange = 0;
		inReverbChange = 0;
	}

	bool enabled = pianoController.GetEnabled(channel) && pianoController.IsConnected();
	bool active = pianoController.GetActive(channel);

	titleButton->setEnabled(enabled);
	titleButton->setToggleState(enabled && active, NotificationType::dontSendNotification);

	titleLabel->setEnabled(enabled);

	voiceLabel->setText(enabled ? Presets::VoiceTitle(pianoController.GetVoice(channel)) : "",
		NotificationType::dontSendNotification);
	voiceLabel->setTooltip(voiceLabel->getText());

	panLabel->setEnabled(pianoController.IsConnected());
	reverbLabel->setEnabled(pianoController.IsConnected());
	volumeLabel->setEnabled(pianoController.IsConnected());

	panSlider->setEnabled(enabled && active && channel != PianoController::chAuxIn);
	reverbSlider->setEnabled(enabled && active && channel != PianoController::chAuxIn);
	volumeSlider->setEnabled(enabled && active);

	panSlider->setValue(pianoController.GetPan(channel), NotificationType::dontSendNotification);
	reverbSlider->setValue(pianoController.GetReverb(channel), NotificationType::dontSendNotification);
	volumeSlider->setValue(pianoController.GetVolume(channel), NotificationType::dontSendNotification);

	menuButton->setEnabled(enabled);
	menuButton2->setEnabled(enabled);
	keyboardButton->setEnabled(enabled);

	partLabel->setText(pianoController.GetPartChannel(PianoController::paRight) == channel ? "R" : "L",
		NotificationType::dontSendNotification);
	partLabel->setVisible(showMenuRow &&
		(pianoController.GetPartChannel(PianoController::paRight) == channel ||
		pianoController.GetPartChannel(PianoController::paLeft) == channel));
	partLabel->setEnabled(enabled && active);
}

void ChannelComponent::applySettings()
{
	keyboardButton->setVisible(settings.keyboardVisible &&
		settings.keyboardChannel == channel - PianoController::chMidi0);
}

void ChannelComponent::mouseDoubleClick(const MouseEvent& event)
{
	if (event.eventComponent == panSlider.get())
	{
		pianoController.ResetPan(channel);
	}
	else if (event.eventComponent == reverbSlider.get())
	{
		pianoController.ResetReverb(channel);
	}
	else if (event.eventComponent == volumeSlider.get())
	{
		pianoController.ResetVolume(channel);
	}
}

void ChannelComponent::mouseUp(const MouseEvent& event)
{
	if ((event.eventComponent == titleLabel.get() || event.eventComponent == voiceLabel.get()) &&
		!event.mouseWasDraggedSinceMouseDown())
	{
        toggleChannel();
	}
}

void ChannelComponent::showMenu(Button* button)
{
	PopupMenu menu;

	menu.addSectionHeader("CHANNEL " + String(channel - PianoController::chMidi0));
	menu.addItem(1, "Select Only This Channel");
	menu.addItem(2, "Play on Virtual Keyboard", true,
		settings.keyboardChannel == channel - PianoController::chMidi0);

	menu.addSectionHeader("VOICE");
	String voice = Presets::VoiceTitle(pianoController.GetVoice(channel));
	menu.addItem(100 + PianoController::chMain, "Select " + voice + " for Main");
	menu.addItem(100 + PianoController::chLayer, "Select " + voice + " for Layer");
	menu.addItem(100 + PianoController::chLeft, "Select " + voice + " for Left");
	menu.addSeparator();

	menu.addSectionHeader("PART");
	bool right = pianoController.GetPartChannel(PianoController::paRight) == channel;
	bool left = pianoController.GetPartChannel(PianoController::paLeft) == channel;
	menu.addItem(200, "Right", true, right);
	menu.addItem(201, "Left", true, left);
	menu.addItem(202, "Backing", true, !right && !left);

	GuiHelper::ShowMenuAsync(menu, button,
		[this](int result)
		{
			int group = result / 100;

			if (result == 1)
			{
				for (PianoController::Channel ch : PianoController::MidiChannels)
				{
					pianoController.SetActive(ch, ch == channel);
				}
			}
			else if (result == 2)
			{
				settings.keyboardChannel = channel - PianoController::chMidi0;
				settings.Save();
			}
			else if (group == 1)
			{
				Voice* vc = Presets::FindVoice(pianoController.GetVoice(channel));
				if (vc)
				{
					pianoController.SetVoice(PianoController::Channel(result - 100), vc->path);
				}
			}
			else if (group == 2)
			{
				bool playng = pianoController.GetPlaying();
				PianoController::Position pos = pianoController.GetPosition();

				if (playng)
				{
					// part cannot be changed during playback
					pianoController.Pause();
				}

				if (result == 200)
				{
					if (pianoController.GetPartChannel(PianoController::paLeft) == channel)
					{
						pianoController.SetPartChannel(PianoController::paLeft, PianoController::chMidi0);
					}
					pianoController.SetPartChannel(PianoController::paRight, channel);
				}
				else if (result == 201)
				{
					if (pianoController.GetPartChannel(PianoController::paRight) == channel)
					{
						pianoController.SetPartChannel(PianoController::paRight, PianoController::chMidi0);
					}
					pianoController.SetPartChannel(PianoController::paLeft, channel);
				}
				else if (result == 202)
				{
					pianoController.SetPartChannel(
						pianoController.GetPartChannel(PianoController::paLeft) == channel ?
							PianoController::paLeft : PianoController::paRight,
						PianoController::chMidi0);
				}

				if (playng)
				{
					pianoController.SetPosition(pos);
					pianoController.Play();
				}
			}
		});
}

void ChannelComponent::toggleChannel()
{
	// using "shrinkMenu" to detect if we in Mixer dialog (not in Balance dialog)
	if (channel == PianoController::chMidiMaster && !shrinkMenu)
	{
		bool allChannelsActive = true;
		for (PianoController::Channel ch : PianoController::MidiChannels)
		{
			allChannelsActive = allChannelsActive &&
				(pianoController.GetActive(ch) || !pianoController.GetEnabled(ch));
		}
		for (PianoController::Channel ch : PianoController::MidiChannels)
		{
			pianoController.SetActive(ch, !allChannelsActive);
		}
	}
	else if (channel != PianoController::chAuxIn)
	{
       	pianoController.SetActive(channel, !pianoController.GetActive(channel));
	}
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ChannelComponent" componentName=""
                 parentClasses="public Component, public PianoController::Listener, public ChangeListener"
                 constructorParams="Settings&amp; settings, PianoController&amp; pianoController, PianoController::Channel channel, String title, bool showLabels, bool showMenu, bool shrinkMenu, bool scrollable"
                 variableInitialisers="settings(settings), pianoController(pianoController), channel(channel), title(title), showMenuRow(showMenu), shrinkMenu(shrinkMenu)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="70" initialHeight="560">
  <BACKGROUND backgroundColour="ff323e44"/>
  <IMAGEBUTTON name="Keyboard Button" id="311be94902dadf45" memberName="keyboardButton"
               virtualName="" explicitFocusOrder="0" pos="11 96 48 16" posRelativeX="f4f376ddb622016f"
               posRelativeY="c7b94b60aa96c6e2" tooltip="Target for Virtual Keyboard"
               buttonText="Menu" connectedEdges="0" needsCallback="1" radioGroupId="0"
               keepProportions="1" resourceNormal="BinaryData::buttonkeyboardwide_png"
               opacityNormal="1.0" colourNormal="0" resourceOver="" opacityOver="0.75"
               colourOver="0" resourceDown="" opacityDown="1.0" colourDown="0"/>
  <IMAGEBUTTON name="Menu Button" id="c87eaad1c0559e4c" memberName="menuButton"
               virtualName="" explicitFocusOrder="0" pos="4 66 28 28" posRelativeX="f4f376ddb622016f"
               posRelativeY="c7b94b60aa96c6e2" tooltip="Context Menu" buttonText="Menu"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="BinaryData::buttoncontextmenu_png" opacityNormal="1.0"
               colourNormal="0" resourceOver="" opacityOver="0.75" colourOver="0"
               resourceDown="" opacityDown="1.0" colourDown="0"/>
  <LABEL name="Part Label" id="857779c04097ab5b" memberName="partLabel"
         virtualName="" explicitFocusOrder="0" pos="37 69 22 21" posRelativeX="f4f376ddb622016f"
         bkgCol="ff42a2c8" textCol="fff0ffff" edTextCol="ff000000" edBkgCol="0"
         labelText="R" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="18.0"
         kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="Pan Label" id="83fd07e9ba9100c1" memberName="panLabel"
         virtualName="" explicitFocusOrder="0" pos="0 90 40 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Pan" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.4"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <IMAGEBUTTON name="Menu Button" id="8656dae8fdb73033" memberName="menuButton2"
               virtualName="" explicitFocusOrder="0" pos="33 66 28 28" posRelativeX="f4f376ddb622016f"
               posRelativeY="c7b94b60aa96c6e2" tooltip="Context Menu" buttonText="Menu"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="" opacityNormal="1.0" colourNormal="0" resourceOver=""
               opacityOver="0.75" colourOver="0" resourceDown="" opacityDown="1.0"
               colourDown="0"/>
  <SLIDER name="Volume Slider" id="9ebc7097d295b7c9" memberName="volumeSlider"
          virtualName="" explicitFocusOrder="0" pos="0 336 70 342M" textboxoutline="80939d9f"
          min="0.0" max="127.0" int="1.0" style="LinearVertical" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="50" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="Pan Slider" id="6dc8f196b2d9dabf" memberName="panSlider"
          virtualName="" explicitFocusOrder="0" pos="0 122 70 76" textboxhighlight="6642a2c8"
          textboxoutline="80939d9f" min="-64.0" max="63.0" int="1.0" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxAbove" textBoxEditable="1" textBoxWidth="50"
          textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <LABEL name="Reverb Label" id="5ba2a16ed7ba194a" memberName="reverbLabel"
         virtualName="" explicitFocusOrder="0" pos="0 196 70 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Reverb" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.4"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="Reverb Slider" id="ebd0ba792eb80390" memberName="reverbSlider"
          virtualName="" explicitFocusOrder="0" pos="0 228 70 76" textboxoutline="80939d9f"
          min="0.0" max="127.0" int="1.0" style="RotaryHorizontalVerticalDrag"
          textBoxPos="TextBoxAbove" textBoxEditable="1" textBoxWidth="50"
          textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <LABEL name="Volume Label" id="3a0483b1c68cf176" memberName="volumeLabel"
         virtualName="" explicitFocusOrder="0" pos="0 304 70 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Volume" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.4"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="Title Button" id="3c4e14578c159f0c" memberName="titleButton"
              virtualName="" explicitFocusOrder="0" pos="2 8 66 52" posRelativeX="f4f376ddb622016f"
              posRelativeY="56427593ca278ddd" buttonText="" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <LABEL name="Title Label" id="8ce81ddb03d15af6" memberName="titleLabel"
         virtualName="" explicitFocusOrder="0" pos="2 9 66 22" edTextCol="ff000000"
         edBkgCol="0" labelText="Ch. 1" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.6"
         kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="Voice Label" id="f5cfadfb4d3d78c7" memberName="voiceLabel"
         virtualName="" explicitFocusOrder="0" pos="2 33 66 22" edTextCol="ff000000"
         edBkgCol="0" labelText="String Ensemble" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="14.0" kerning="0.0" bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

