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

#include "MixerComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MixerComponent::MixerComponent (PianoController& pianoController)
    : pianoController(pianoController)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    channelViewport.reset (new Viewport ("Channel Viewport"));
    addAndMakeVisible (channelViewport.get());

    leftChannel.reset (new ChannelComponent (pianoController, PianoController::chMidiMaster, "Master", true));
    addAndMakeVisible (leftChannel.get());
    channelPanel.reset (new Component());
    addAndMakeVisible (channelPanel.get());
    channelPanel->setName ("Channels");


    //[UserPreSize]
    for (PianoController::Channel ch = PianoController::chMidi1; ch <= PianoController::chMidi16;
    	ch = PianoController::Channel(ch + 1))
    {
    	std::unique_ptr<ChannelComponent> comp;
    	comp.reset(new ChannelComponent(pianoController, ch,
    		String("Ch. ") + String(ch - PianoController::chMidi1 + 1), false));
    	channelPanel->addAndMakeVisible(comp.get());
		channels.push_back(std::move(comp));
	}
	channelViewport->setViewedComponent(channelPanel.get(), false);
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

MixerComponent::~MixerComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    channelViewport = nullptr;
    leftChannel = nullptr;
    channelPanel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void MixerComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    {
        int x = 84, y = 10, width = 1, height = getHeight() - 20;
        Colour fillColour = Colour (0xff4e5b62);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MixerComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    channelViewport->setBounds (88, 0, getWidth() - 96, getHeight() - 0);
    leftChannel->setBounds (8, 0, 70, getHeight() - 8);
    channelPanel->setBounds (96, 0, 280, getHeight() - 8);
    //[UserResized] Add your own custom resize handling here..
    int num = 0;
	for(auto& comp : channels)
	{
		comp->setBounds(num++ * leftChannel->getWidth(), 0, leftChannel->getWidth(), leftChannel->getHeight());
	}
	channelPanel->setBounds(0, 0, leftChannel->getWidth() * 16, channelPanel->getHeight());
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MixerComponent" componentName=""
                 parentClasses="public Component, public PianoController::Listener"
                 constructorParams="PianoController&amp; pianoController" variableInitialisers="pianoController(pianoController)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff323e44">
    <RECT pos="84 10 1 20M" fill="solid: ff4e5b62" hasStroke="0"/>
  </BACKGROUND>
  <VIEWPORT name="Channel Viewport" id="58db405ab1d794e4" memberName="channelViewport"
            virtualName="" explicitFocusOrder="0" pos="88 0 96M 0M" vscroll="1"
            hscroll="1" scrollbarThickness="8" contentType="0" jucerFile=""
            contentClass="" constructorParams=""/>
  <JUCERCOMP name="Left Channel" id="97f9a699004cae9a" memberName="leftChannel"
             virtualName="" explicitFocusOrder="0" pos="8 0 70 8M" sourceFile="ChannelComponent.cpp"
             constructorParams="pianoController, PianoController::chMidiMaster, &quot;Master&quot;, true"/>
  <GENERICCOMPONENT name="Channels" id="256e91213f333b3c" memberName="channelPanel"
                    virtualName="" explicitFocusOrder="0" pos="96 0 280 8M" class="Component"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

