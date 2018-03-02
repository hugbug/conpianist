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

    addAndMakeVisible (audioSelector = new AudioDeviceSelectorComponent (audioDeviceManager, 0, 0, 0, 0, true, true, false, false));
    addAndMakeVisible (localControlGroup = new GroupComponent ("Local Control",
                                                               TRANS("Local Control")));
    localControlGroup->setTextLabelPosition (Justification::centred);

    addAndMakeVisible (localControlOnButton = new TextButton ("Local-Control On Button"));
    localControlOnButton->setButtonText (TRANS("Tone On"));
    localControlOnButton->addListener (this);

    addAndMakeVisible (localControlOffButton = new TextButton ("Local-Control Off Button"));
    localControlOffButton->setButtonText (TRANS("Tone Off"));
    localControlOffButton->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 600);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

SceneComponent::~SceneComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    audioSelector = nullptr;
    localControlGroup = nullptr;
    localControlOnButton = nullptr;
    localControlOffButton = nullptr;


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

    audioSelector->setBounds (16, -20, getWidth() - 30, 132);
    localControlGroup->setBounds (16, (-20) + 132 - -24, getWidth() - 32, 64);
    localControlOnButton->setBounds (16 + 50 - (70 / 2), ((-20) + 132 - -24) + 24, 70, 24);
    localControlOffButton->setBounds (16 + 131 - (70 / 2), ((-20) + 132 - -24) + 24, 70, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void SceneComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == localControlOnButton)
    {
        //[UserButtonCode_localControlOnButton] -- add your button handler code here..
	    MidiMessage localControlMessage = MidiMessage::controllerEvent(1, 122, 127);
	    audioDeviceManager.getDefaultMidiOutput()->sendMessageNow(localControlMessage);
        //[/UserButtonCode_localControlOnButton]
    }
    else if (buttonThatWasClicked == localControlOffButton)
    {
        //[UserButtonCode_localControlOffButton] -- add your button handler code here..
	    MidiMessage localControlMessage = MidiMessage::controllerEvent(1, 122, 0);
	    audioDeviceManager.getDefaultMidiOutput()->sendMessageNow(localControlMessage);
        //[/UserButtonCode_localControlOffButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SceneComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="600">
  <BACKGROUND backgroundColour="ff323e44"/>
  <JUCERCOMP name="Audio Selector" id="ddeb8c497281f468" memberName="audioSelector"
             virtualName="AudioDeviceSelectorComponent" explicitFocusOrder="0"
             pos="16 -20 30M 132" sourceFile="../../JUCE/modules/juce_audio_utils/juce_audio_utils.h"
             constructorParams="audioDeviceManager, 0, 0, 0, 0, true, true, false, false"/>
  <GROUPCOMPONENT name="Local Control" id="69305d91c2150486" memberName="localControlGroup"
                  virtualName="" explicitFocusOrder="0" pos="16 -24R 32M 64" posRelativeY="ddeb8c497281f468"
                  title="Local Control" textpos="36"/>
  <TEXTBUTTON name="Local-Control On Button" id="99f311ed53591c70" memberName="localControlOnButton"
              virtualName="" explicitFocusOrder="0" pos="50c 24 70 24" posRelativeX="69305d91c2150486"
              posRelativeY="69305d91c2150486" buttonText="Tone On" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Local-Control Off Button" id="55c13d8af41edb4e" memberName="localControlOffButton"
              virtualName="" explicitFocusOrder="0" pos="131c 24 70 24" posRelativeX="69305d91c2150486"
              posRelativeY="69305d91c2150486" buttonText="Tone Off" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
