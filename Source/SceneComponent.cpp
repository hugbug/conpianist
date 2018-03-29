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
    : playbackComponent(pianoController), voiceComponent(pianoController), settings(settings)
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

    //[UserPreSize]
    topbarPanel->setColour(GroupComponent::outlineColourId, Colours::transparentBlack);
    topbarPanel->setText("");
    //[/UserPreSize]

    setSize (850, 550);


    //[Constructor] You can add your own custom stuff here..
	playbackPanel->addAndMakeVisible(playbackComponent);
	largeContentPanel->addAndMakeVisible(voiceComponent);

    pianoController.addChangeListener(this);
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
        int x = 290, y = 44, width = getWidth() - 288, height = getHeight() - 36;
        Colour strokeColour = Colour (0xff4e5b62);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (strokeColour);
        g.drawRect (x, y, width, height, 2);

    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void SceneComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    topbarPanel->setBounds (0, -8, getWidth() - 0, 52);
    playbackPanel->setBounds (0, (-8) + 52, 290, getHeight() - 42);
    largeContentPanel->setBounds (0 + 290, (-8) + 52, getWidth() - 290, getHeight() - 42);
    muteButton->setBounds (getWidth() - 9 - 32, 8, 32, 28);
    zoomInButton->setBounds (getWidth() - 49 - 32, 8, 32, 28);
    zoomOutButton->setBounds (getWidth() - 89 - 32, 8, 32, 28);
    //[UserResized] Add your own custom resize handling here..
    voiceComponent.setBounds(2, 2, largeContentPanel->getWidth() - 2, largeContentPanel->getHeight() - 2);
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

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void SceneComponent::changeListenerCallback(ChangeBroadcaster* source)
{
	if (source == &pianoController)
	{
		updateSettingsState();
	}
	else if (source == &settings)
	{
		applySettings();
	}
}

void SceneComponent::updateSettingsState()
{
	MessageManager::callAsync([=] ()
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
		});
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
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SceneComponent" componentName=""
                 parentClasses="public Component, public ChangeListener, public Timer"
                 constructorParams="Settings&amp; settings" variableInitialisers="playbackComponent(pianoController), voiceComponent(pianoController), settings(settings)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="850" initialHeight="550">
  <BACKGROUND backgroundColour="ff323e44">
    <RECT pos="290 44 288M 36M" fill="solid: f0ffff" hasStroke="1" stroke="2.1, mitered, butt"
          strokeColour="solid: ff4e5b62"/>
  </BACKGROUND>
  <GROUPCOMPONENT name="Top Bar" id="69305d91c2150486" memberName="topbarPanel"
                  virtualName="" explicitFocusOrder="0" pos="0 -8 0M 52" title="Top Bar"
                  textpos="36"/>
  <GENERICCOMPONENT name="Playback Panel" id="cf6dcbcdc3b17ace" memberName="playbackPanel"
                    virtualName="" explicitFocusOrder="0" pos="0 52 290 42M" posRelativeY="69305d91c2150486"
                    class="Component" params=""/>
  <GENERICCOMPONENT name="Large Content" id="5d00b51e97f2c31f" memberName="largeContentPanel"
                    virtualName="" explicitFocusOrder="0" pos="0R 52 290M 42M" posRelativeX="cf6dcbcdc3b17ace"
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
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
