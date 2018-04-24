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
#include "ConnectionComponent.h"
//[/Headers]

#include "SceneComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
SceneComponent::SceneComponent (Settings& settings)
    : playbackComponent(pianoController), voiceComponent(pianoController), keyboardComponent(pianoController, settings), settings(settings)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (topbarPanel = new GroupComponent ("Top Bar",
                                                         TRANS("Top Bar")));
    topbarPanel->setTextLabelPosition (Justification::centred);

    addAndMakeVisible (playbackPanel = new Component());
    playbackPanel->setName ("Playback Panel");

    addAndMakeVisible (largeContentPanel = new Component());
    largeContentPanel->setName ("Large Content");

    addAndMakeVisible (muteButton = new ImageButton ("Mute Button"));
    muteButton->setTooltip (TRANS("Local Control on/off"));
    muteButton->setButtonText (TRANS("Mute"));
    muteButton->addListener (this);

    muteButton->setImages (false, true, true,
                           ImageCache::getFromMemory (BinaryData::buttonvolume_png, BinaryData::buttonvolume_pngSize), 1.000f, Colour (0x00000000),
                           Image(), 0.750f, Colour (0x00000000),
                           Image(), 1.000f, Colour (0x00000000));
    addAndMakeVisible (statusLabel = new Label ("Status Label",
                                                TRANS("Looking for the instrument")));
    statusLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    statusLabel->setJustificationType (Justification::centredLeft);
    statusLabel->setEditable (false, false, false);
    statusLabel->setColour (TextEditor::textColourId, Colours::black);
    statusLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    statusLabel->setBounds (48, 11, 240, 24);

    addAndMakeVisible (connectionButton = new ImageButton ("Connection Button"));
    connectionButton->setTooltip (TRANS("Connection Settings"));
    connectionButton->setButtonText (TRANS("Mute"));
    connectionButton->addListener (this);

    connectionButton->setImages (false, true, true,
                                 ImageCache::getFromMemory (BinaryData::buttonport_png, BinaryData::buttonport_pngSize), 1.000f, Colour (0x00000000),
                                 Image(), 0.750f, Colour (0x00000000),
                                 Image(), 1.000f, Colour (0x00000000));
    connectionButton->setBounds (8, 8, 32, 28);

    addAndMakeVisible (zoomInButton = new ImageButton ("Zoom In UI Button"));
    zoomInButton->setTooltip (TRANS("Zoom In UI"));
    zoomInButton->setButtonText (TRANS("Mute"));
    zoomInButton->addListener (this);

    zoomInButton->setImages (false, true, true,
                             ImageCache::getFromMemory (BinaryData::buttonzoomin_png, BinaryData::buttonzoomin_pngSize), 1.000f, Colour (0x00000000),
                             Image(), 0.750f, Colour (0x00000000),
                             Image(), 1.000f, Colour (0x00000000));
    addAndMakeVisible (zoomOutButton = new ImageButton ("Zoom Out UI Button"));
    zoomOutButton->setTooltip (TRANS("Zoom Out UI"));
    zoomOutButton->setButtonText (TRANS("Mute"));
    zoomOutButton->addListener (this);

    zoomOutButton->setImages (false, true, true,
                              ImageCache::getFromMemory (BinaryData::buttonzoomout_png, BinaryData::buttonzoomout_pngSize), 1.000f, Colour (0x00000000),
                              Image(), 0.750f, Colour (0x00000000),
                              Image(), 1.000f, Colour (0x00000000));
    addAndMakeVisible (keyboardPanel = new Component());
    keyboardPanel->setName ("Keyboard Panel");

    addAndMakeVisible (keyboardButton = new ImageButton ("Virtual Keyboard Button"));
    keyboardButton->setTooltip (TRANS("Virtual Keyboard"));
    keyboardButton->setButtonText (TRANS("Virtual Keyboard"));
    keyboardButton->addListener (this);

    keyboardButton->setImages (false, true, true,
                               ImageCache::getFromMemory (BinaryData::buttonkeyboard_png, BinaryData::buttonkeyboard_pngSize), 1.000f, Colour (0x00000000),
                               Image(), 0.750f, Colour (0x00000000),
                               Image(), 1.000f, Colour (0x00000000));

    //[UserPreSize]
    topbarPanel->setColour(GroupComponent::outlineColourId, Colours::transparentBlack);
    topbarPanel->setText("");
    //[/UserPreSize]

    setSize (850, 550);


    //[Constructor] You can add your own custom stuff here..
	playbackPanel->addAndMakeVisible(playbackComponent);
	largeContentPanel->addAndMakeVisible(voiceComponent);
	keyboardPanel->addAndMakeVisible(keyboardComponent);

    pianoController.AddListener(this);
    settings.addChangeListener(this);
	applySettings();

	startTimer(250);
    //[/Constructor]
}

SceneComponent::~SceneComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    if (rtpMidiConnector)
    {
		rtpMidiConnector->stopThread(1000);
	}
    //[/Destructor_pre]

    topbarPanel = nullptr;
    playbackPanel = nullptr;
    largeContentPanel = nullptr;
    muteButton = nullptr;
    statusLabel = nullptr;
    connectionButton = nullptr;
    zoomInButton = nullptr;
    zoomOutButton = nullptr;
    keyboardPanel = nullptr;
    keyboardButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SceneComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    {
        int x = 0, y = 43, width = getWidth() - 0, height = 1;
        Colour fillColour = Colour (0xff4e5b62);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void SceneComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    topbarPanel->setBounds (0, -8, getWidth() - 0, 52);
    playbackPanel->setBounds (0, (-8) + 52, 290, getHeight() - 111);
    largeContentPanel->setBounds (0 + 290, (-8) + 52, getWidth() - 290, getHeight() - 111);
    muteButton->setBounds (getWidth() - 9 - 32, 8, 32, 28);
    zoomInButton->setBounds (getWidth() - 49 - 32, 8, 32, 28);
    zoomOutButton->setBounds (getWidth() - 89 - 32, 8, 32, 28);
    keyboardPanel->setBounds (0, getHeight() - 67, getWidth() - 0, 67);
    keyboardButton->setBounds (getWidth() - 129 - 32, 8, 32, 28);
    //[UserResized] Add your own custom resize handling here..
    playbackPanel->setBounds(playbackPanel->getX(), playbackPanel->getY(), playbackPanel->getWidth(),
    	playbackPanel->getHeight() + (keyboardPanel->isVisible() ? 0 : keyboardPanel->getHeight()));
    largeContentPanel->setBounds(largeContentPanel->getX(), largeContentPanel->getY(), largeContentPanel->getWidth(),
        largeContentPanel->getHeight() + (keyboardPanel->isVisible() ? 0 : keyboardPanel->getHeight()));
	playbackComponent.setBounds(0, 0, playbackPanel->getWidth(), playbackPanel->getHeight());
	voiceComponent.setBounds(0, 0, largeContentPanel->getWidth(), largeContentPanel->getHeight());
	keyboardComponent.setBounds(0, 0, keyboardPanel->getWidth(), keyboardPanel->getHeight());
    //[/UserResized]
}

void SceneComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == muteButton)
    {
        //[UserButtonCode_muteButton] -- add your button handler code here..
        pianoController.SetLocalControl(!pianoController.GetLocalControl());
        //[/UserButtonCode_muteButton]
    }
    else if (buttonThatWasClicked == connectionButton)
    {
        //[UserButtonCode_connectionButton] -- add your button handler code here..
		showConnectionDialog();
        //[/UserButtonCode_connectionButton]
    }
    else if (buttonThatWasClicked == zoomInButton)
    {
        //[UserButtonCode_zoomInButton] -- add your button handler code here..
        zoomUi(true);
        //[/UserButtonCode_zoomInButton]
    }
    else if (buttonThatWasClicked == zoomOutButton)
    {
        //[UserButtonCode_zoomOutButton] -- add your button handler code here..
        zoomUi(false);
        //[/UserButtonCode_zoomOutButton]
    }
    else if (buttonThatWasClicked == keyboardButton)
    {
        //[UserButtonCode_keyboardButton] -- add your button handler code here..
        toggleKeyboard();
        //[/UserButtonCode_keyboardButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void SceneComponent::changeListenerCallback(ChangeBroadcaster* source)
{
	if (source == &settings)
	{
		applySettings();
	}
}

void SceneComponent::updateSettingsState()
{
	if (pianoController.IsConnected())
	{
		statusLabel->setText(String("Connected to ") + pianoController.GetModel() +
			" (" + pianoController.GetVersion() + ")",
			NotificationType::dontSendNotification);
	}

	bool mute = !pianoController.GetLocalControl() && pianoController.IsConnected();
	muteButton->setImages(false, true, true, ImageCache::getFromMemory(
			mute ? BinaryData::buttonmute_png : BinaryData::buttonvolume_png,
			mute ? BinaryData::buttonmute_pngSize : BinaryData::buttonvolume_pngSize),
			1.000f, Colour (0x00000000), Image(), 0.750f, Colour (0x00000000), Image(), 1.000f, Colour (0x00000000));
	//keyboardButton->setToggleState(settings.keyboard, NotificationType::dontSendNotification);
}

void SceneComponent::showConnectionDialog()
{
	ConnectionComponent::showDialog(settings);
}

void SceneComponent::timerCallback()
{
	checkConnection();
}

void SceneComponent::checkConnection()
{
	if (!midiConnector->IsConnected())
	{
		pianoController.Disconnect();
	}

	if (!pianoController.IsConnected())
	{
		String prefix = midiConnector->IsConnected() ? "Connecting to the instrument" : "Looking for the instrument";
		String status = statusLabel->getText();
		if (status.startsWith(prefix) && status.length() < prefix.length() + 10)
		{
			status += ".";
		}
		else
		{
			status = prefix;
		}
		statusLabel->setText(status, NotificationType::dontSendNotification);

		pianoController.Connect();
	}
}

void SceneComponent::applySettings()
{
	if (currentPianoIp != settings.pianoIp ||
		currentMidiPort != settings.midiPort ||
		!midiConnector)
	{
		pianoController.Disconnect();
		if (midiConnector)
		{
			midiConnector->SetListener(nullptr);
		}

		pianoController.SetRemoteIp(settings.pianoIp);

		if (rtpMidiConnector)
		{
			rtpMidiConnector->stopThread(1000);
		}

		if (settings.midiPort == "")
		{
			rtpMidiConnector = new RtpMidiConnector(settings.pianoIp);
			midiConnector = rtpMidiConnector;
			pianoController.SetMidiConnector(midiConnector);
			rtpMidiConnector->startThread();
		}
		else
		{
			audioDeviceManager.setMidiInputEnabled(settings.midiPort, true);
			audioDeviceManager.setDefaultMidiOutput(settings.midiPort);
			localMidiConnector = new LocalMidiConnector(&audioDeviceManager);
			midiConnector = localMidiConnector;
			pianoController.SetMidiConnector(midiConnector);
		}

		currentPianoIp = settings.pianoIp;
		currentMidiPort = settings.midiPort;
	}

	float scale = settings.zoomUi;
	scale = std::min(std::max(scale, 0.25f), 4.0f);
	scale = round(scale * 20) / 20;
	Desktop::getInstance().setGlobalScaleFactor(scale);

	if (keyboardPanel->isVisible() != settings.keyboardVisible)
	{
		keyboardPanel->setVisible(settings.keyboardVisible);
		resized();
    }
}

void SceneComponent::zoomUi(bool zoomIn)
{
	float scale = Desktop::getInstance().getGlobalScaleFactor();
	scale += zoomIn ? + 0.05 : -0.05;
	scale = std::min(std::max(scale, 0.25f), 4.0f);
	scale = round(scale * 20) / 20;
	Desktop::getInstance().setGlobalScaleFactor(scale);
	settings.zoomUi = scale;
	settings.Save();
}

void SceneComponent::toggleKeyboard()
{
	settings.keyboardVisible = !settings.keyboardVisible;
	settings.Save();
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SceneComponent" componentName=""
                 parentClasses="public Component, public PianoController::Listener, public ChangeListener, public Timer"
                 constructorParams="Settings&amp; settings" variableInitialisers="playbackComponent(pianoController), voiceComponent(pianoController), keyboardComponent(pianoController, settings), settings(settings)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="850" initialHeight="550">
  <BACKGROUND backgroundColour="ff323e44">
    <RECT pos="0 43 0M 1" fill="solid: ff4e5b62" hasStroke="0"/>
  </BACKGROUND>
  <GROUPCOMPONENT name="Top Bar" id="69305d91c2150486" memberName="topbarPanel"
                  virtualName="" explicitFocusOrder="0" pos="0 -8 0M 52" title="Top Bar"
                  textpos="36"/>
  <GENERICCOMPONENT name="Playback Panel" id="cf6dcbcdc3b17ace" memberName="playbackPanel"
                    virtualName="" explicitFocusOrder="0" pos="0 52 290 111M" posRelativeY="69305d91c2150486"
                    class="Component" params=""/>
  <GENERICCOMPONENT name="Large Content" id="5d00b51e97f2c31f" memberName="largeContentPanel"
                    virtualName="" explicitFocusOrder="0" pos="0R 52 290M 111M" posRelativeX="cf6dcbcdc3b17ace"
                    posRelativeY="69305d91c2150486" class="Component" params=""/>
  <IMAGEBUTTON name="Mute Button" id="ca510a4be11fdde2" memberName="muteButton"
               virtualName="" explicitFocusOrder="0" pos="9Rr 8 32 28" posRelativeX="c7b94b60aa96c6e2"
               posRelativeY="c7b94b60aa96c6e2" tooltip="Local Control on/off"
               buttonText="Mute" connectedEdges="0" needsCallback="1" radioGroupId="0"
               keepProportions="1" resourceNormal="BinaryData::buttonvolume_png"
               opacityNormal="1.00000000000000000000" colourNormal="0" resourceOver=""
               opacityOver="0.75000000000000000000" colourOver="0" resourceDown=""
               opacityDown="1.00000000000000000000" colourDown="0"/>
  <LABEL name="Status Label" id="71086bde8935001" memberName="statusLabel"
         virtualName="" explicitFocusOrder="0" pos="48 11 240 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Looking for the instrument" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="33"/>
  <IMAGEBUTTON name="Connection Button" id="c87eaad1c0559e4c" memberName="connectionButton"
               virtualName="" explicitFocusOrder="0" pos="8 8 32 28" posRelativeX="c7b94b60aa96c6e2"
               posRelativeY="c7b94b60aa96c6e2" tooltip="Connection Settings"
               buttonText="Mute" connectedEdges="0" needsCallback="1" radioGroupId="0"
               keepProportions="1" resourceNormal="BinaryData::buttonport_png"
               opacityNormal="1.00000000000000000000" colourNormal="0" resourceOver=""
               opacityOver="0.75000000000000000000" colourOver="0" resourceDown=""
               opacityDown="1.00000000000000000000" colourDown="0"/>
  <IMAGEBUTTON name="Zoom In UI Button" id="8f2ba3f851b38bd8" memberName="zoomInButton"
               virtualName="" explicitFocusOrder="0" pos="49Rr 8 32 28" posRelativeX="c7b94b60aa96c6e2"
               posRelativeY="c7b94b60aa96c6e2" tooltip="Zoom In UI" buttonText="Mute"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="BinaryData::buttonzoomin_png" opacityNormal="1.00000000000000000000"
               colourNormal="0" resourceOver="" opacityOver="0.75000000000000000000"
               colourOver="0" resourceDown="" opacityDown="1.00000000000000000000"
               colourDown="0"/>
  <IMAGEBUTTON name="Zoom Out UI Button" id="9c93ecb0c87ce0c4" memberName="zoomOutButton"
               virtualName="" explicitFocusOrder="0" pos="89Rr 8 32 28" posRelativeX="c7b94b60aa96c6e2"
               posRelativeY="c7b94b60aa96c6e2" tooltip="Zoom Out UI" buttonText="Mute"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="BinaryData::buttonzoomout_png" opacityNormal="1.00000000000000000000"
               colourNormal="0" resourceOver="" opacityOver="0.75000000000000000000"
               colourOver="0" resourceDown="" opacityDown="1.00000000000000000000"
               colourDown="0"/>
  <GENERICCOMPONENT name="Keyboard Panel" id="d578dbfb8bf47c83" memberName="keyboardPanel"
                    virtualName="" explicitFocusOrder="0" pos="0 0Rr 0M 67" class="Component"
                    params=""/>
  <IMAGEBUTTON name="Virtual Keyboard Button" id="802f8ad4daaeee49" memberName="keyboardButton"
               virtualName="" explicitFocusOrder="0" pos="129Rr 8 32 28" posRelativeX="c7b94b60aa96c6e2"
               posRelativeY="c7b94b60aa96c6e2" tooltip="Virtual Keyboard" buttonText="Virtual Keyboard"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="BinaryData::buttonkeyboard_png" opacityNormal="1.00000000000000000000"
               colourNormal="0" resourceOver="" opacityOver="0.75000000000000000000"
               colourOver="0" resourceDown="" opacityDown="1.00000000000000000000"
               colourDown="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
