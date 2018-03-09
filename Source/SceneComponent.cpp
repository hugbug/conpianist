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
    : playbackComponent(pianoController)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //Desktop::getInstance().setGlobalScaleFactor(1);
    //[/Constructor_pre]

    addAndMakeVisible (topbarPanel = new GroupComponent ("Top Bar",
                                                         TRANS("Top Bar")));
    topbarPanel->setTextLabelPosition (Justification::centred);

    addAndMakeVisible (connectButton = new TextButton ("Connect Button"));
    connectButton->setButtonText (TRANS("Connect"));
    connectButton->addListener (this);

    addAndMakeVisible (settingsButton = new TextButton ("Settings Button"));
    settingsButton->setButtonText (TRANS("Settings..."));
    settingsButton->addListener (this);

    addAndMakeVisible (playbackPanel = new Component());
    playbackPanel->setName ("Playback Panel");

    addAndMakeVisible (largeContentPanel = new Component());
    largeContentPanel->setName ("Large Content");


    //[UserPreSize]
    topbarPanel->setColour(GroupComponent::outlineColourId, Colours::transparentBlack);
    topbarPanel->setText("");
    //[/UserPreSize]

    setSize (850, 550);


    //[Constructor] You can add your own custom stuff here..
	playbackPanel->addAndMakeVisible(playbackComponent);

	SettingsComponent::loadState(audioDeviceManager, pianoController);
	pianoController.SetAudioDeviceManager(&audioDeviceManager);
    pianoController.addChangeListener(this);
    //[/Constructor]
}

SceneComponent::~SceneComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    topbarPanel = nullptr;
    connectButton = nullptr;
    settingsButton = nullptr;
    playbackPanel = nullptr;
    largeContentPanel = nullptr;


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
        int x = 290, y = 56, width = getWidth() - 288, height = getHeight() - 52;
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

    topbarPanel->setBounds (0, -8, getWidth() - 0, 64);
    connectButton->setBounds (0 + 124 - (216 / 2), (-8) + 21, 216, 28);
    settingsButton->setBounds (0 + 284 - (88 / 2), (-8) + 21, 88, 28);
    playbackPanel->setBounds (0, (-8) + 64, 290, getHeight() - 54);
    largeContentPanel->setBounds (0 + 290, (-8) + 64, getWidth() - 290, getHeight() - 54);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void SceneComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == connectButton)
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



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void SceneComponent::changeListenerCallback(ChangeBroadcaster* source)
{
	if (source == &pianoController)
	{
		updateSettingsState();
	}
}

void SceneComponent::updateSettingsState()
{
	MessageManager::callAsync([=] ()
		{
			connectButton->setToggleState(pianoController.GetConnected(), NotificationType::dontSendNotification);
			connectButton->setButtonText(!pianoController.GetConnected() ? "Connect" :
				String("Connected to ") + pianoController.GetModel() + " (" + pianoController.GetVersion() + ")");
		});
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
                 parentClasses="public Component, public ChangeListener" constructorParams=""
                 variableInitialisers="playbackComponent(pianoController)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="0"
                 initialWidth="850" initialHeight="550">
  <BACKGROUND backgroundColour="ff323e44">
    <RECT pos="290 56 288M 52M" fill="solid: f0ffff" hasStroke="1" stroke="2.1, mitered, butt"
          strokeColour="solid: ff4e5b62"/>
  </BACKGROUND>
  <GROUPCOMPONENT name="Top Bar" id="69305d91c2150486" memberName="topbarPanel"
                  virtualName="" explicitFocusOrder="0" pos="0 -8 0M 64" title="Top Bar"
                  textpos="36"/>
  <TEXTBUTTON name="Connect Button" id="a82c92b5d1470311" memberName="connectButton"
              virtualName="" explicitFocusOrder="0" pos="124c 21 216 28" posRelativeX="69305d91c2150486"
              posRelativeY="69305d91c2150486" buttonText="Connect" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Settings Button" id="bf47ed7d30088c39" memberName="settingsButton"
              virtualName="" explicitFocusOrder="0" pos="284c 21 88 28" posRelativeX="69305d91c2150486"
              posRelativeY="69305d91c2150486" buttonText="Settings..." connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <GENERICCOMPONENT name="Playback Panel" id="cf6dcbcdc3b17ace" memberName="playbackPanel"
                    virtualName="" explicitFocusOrder="0" pos="0 64 290 54M" posRelativeY="69305d91c2150486"
                    class="Component" params=""/>
  <GENERICCOMPONENT name="Large Content" id="5d00b51e97f2c31f" memberName="largeContentPanel"
                    virtualName="" explicitFocusOrder="0" pos="0R 64 290M 54M" posRelativeX="cf6dcbcdc3b17ace"
                    posRelativeY="69305d91c2150486" class="Component" params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
