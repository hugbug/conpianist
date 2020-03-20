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
//[/Headers]

#include "BalanceComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
BalanceComponent::BalanceComponent (PianoController& pianoController)
    : pianoController(pianoController)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    leftChannel.reset (new ChannelComponent (pianoController, PianoController::chLeft, "Left", true, true));
    addAndMakeVisible (leftChannel.get());
    mainChannel.reset (new ChannelComponent (pianoController, PianoController::chMain, "Main", false, true));
    addAndMakeVisible (mainChannel.get());
    layerChannel.reset (new ChannelComponent (pianoController, PianoController::chLayer, "Layer", false, true));
    addAndMakeVisible (layerChannel.get());
    songChannel.reset (new ChannelComponent (pianoController, PianoController::chMidiMaster, "Song", false, true));
    addAndMakeVisible (songChannel.get());
    micChannel.reset (new ChannelComponent (pianoController, PianoController::chMic, "Mic", false, true));
    addAndMakeVisible (micChannel.get());
    auxInChannel.reset (new ChannelComponent (pianoController, PianoController::chAuxIn, "Aux In", false, false));
    addAndMakeVisible (auxInChannel.get());

    //[UserPreSize]
    //[/UserPreSize]

    setSize (436, 560);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

BalanceComponent::~BalanceComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    leftChannel = nullptr;
    mainChannel = nullptr;
    layerChannel = nullptr;
    songChannel = nullptr;
    micChannel = nullptr;
    auxInChannel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void BalanceComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void BalanceComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    leftChannel->setBounds (8, 0, 70, getHeight() - 0);
    mainChannel->setBounds (78, 0, 70, getHeight() - 0);
    layerChannel->setBounds (148, 0, 70, getHeight() - 0);
    songChannel->setBounds (218, 0, 70, getHeight() - 0);
    micChannel->setBounds (288, 0, 70, getHeight() - 0);
    auxInChannel->setBounds (358, 0, 70, getHeight() - 0);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void BalanceComponent::showDialog(PianoController& pianoController)
{
	DialogWindow::LaunchOptions dialog;
	dialog.content.setOwned(new BalanceComponent(pianoController));
	dialog.dialogTitle = "Balance";
	dialog.useNativeTitleBar = (SystemStats::getOperatingSystemType() & SystemStats::Windows) ||
		(SystemStats::getOperatingSystemType() & SystemStats::MacOSX);
	dialog.resizable = false;
	dialog.launchAsync();
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="BalanceComponent" componentName=""
                 parentClasses="public Component" constructorParams="PianoController&amp; pianoController"
                 variableInitialisers="pianoController(pianoController)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="0"
                 initialWidth="436" initialHeight="560">
  <BACKGROUND backgroundColour="ff323e44"/>
  <JUCERCOMP name="Left Channel" id="97f9a699004cae9a" memberName="leftChannel"
             virtualName="" explicitFocusOrder="0" pos="8 0 70 0M" sourceFile="ChannelComponent.cpp"
             constructorParams="pianoController, PianoController::chLeft, &quot;Left&quot;, true, true"/>
  <JUCERCOMP name="Main Channel" id="74e25a6d700b5cc9" memberName="mainChannel"
             virtualName="" explicitFocusOrder="0" pos="78 0 70 0M" sourceFile="ChannelComponent.cpp"
             constructorParams="pianoController, PianoController::chMain, &quot;Main&quot;, false, true"/>
  <JUCERCOMP name="Layer Channel" id="ef551064ccb187e2" memberName="layerChannel"
             virtualName="" explicitFocusOrder="0" pos="148 0 70 0M" sourceFile="ChannelComponent.cpp"
             constructorParams="pianoController, PianoController::chLayer, &quot;Layer&quot;, false, true"/>
  <JUCERCOMP name="Song Channel" id="ea486fd33cd44e31" memberName="songChannel"
             virtualName="" explicitFocusOrder="0" pos="218 0 70 0M" sourceFile="ChannelComponent.cpp"
             constructorParams="pianoController, PianoController::chMidiMaster, &quot;Song&quot;, false, true"/>
  <JUCERCOMP name="Mic Channel" id="8f4c373ee8ae253f" memberName="micChannel"
             virtualName="" explicitFocusOrder="0" pos="288 0 70 0M" sourceFile="ChannelComponent.cpp"
             constructorParams="pianoController, PianoController::chMic, &quot;Mic&quot;, false, true"/>
  <JUCERCOMP name="AuxIn Channel" id="7ffff5d33c7b27f" memberName="auxInChannel"
             virtualName="" explicitFocusOrder="0" pos="358 0 70 0M" sourceFile="ChannelComponent.cpp"
             constructorParams="pianoController, PianoController::chAuxIn, &quot;Aux In&quot;, false, false"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

