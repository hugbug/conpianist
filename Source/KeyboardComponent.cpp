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
//[/Headers]

#include "KeyboardComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
KeyboardComponent::KeyboardComponent (PianoController& pianoController)
    : pianoController(pianoController)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (midiKeyboardComponent = new MidiKeyboardComponent (keyState, MidiKeyboardComponent::horizontalKeyboard));
    midiKeyboardComponent->setName ("Midi Keyboard Component");


    //[UserPreSize]
	midiKeyboardComponent->setAvailableRange(21, 120);
	midiKeyboardComponent->setMidiChannel(1);
	midiKeyboardComponent->setColour(MidiKeyboardComponent::ColourIds::keyDownOverlayColourId, Colour(0xFEEE6C0A));
	midiKeyboardComponent->setColour(MidiKeyboardComponent::ColourIds::mouseOverKeyOverlayColourId, Colour(0xAEEE6C0A));
	keyState.addListener(this);
	pianoController.AddListener(this);
    //[/UserPreSize]

    setSize (600, 70);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

KeyboardComponent::~KeyboardComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    midiKeyboardComponent = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void KeyboardComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    {
        int x = 0, y = 0, width = getWidth() - 0, height = 1;
        Colour fillColour = Colour (0xff283237);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRect (x, y, width, height);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void KeyboardComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    midiKeyboardComponent->setBounds (0, 2, getWidth() - 0, getHeight() - 2);
    //[UserResized] Add your own custom resize handling here..
	float requiredWidth = midiKeyboardComponent->getTotalKeyboardWidth();
	if (requiredWidth < getWidth())
	{
		midiKeyboardComponent->setBounds((getWidth() - requiredWidth) / 2,
			midiKeyboardComponent->getY(), requiredWidth, midiKeyboardComponent->getHeight());
	}
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void KeyboardComponent::handleNoteOn(MidiKeyboardState *source, int midiChannel, int midiNoteNumber, float velocity)
{
	if (velocity > 0.0001)
	{
		pianoController.SendMidiMessage(MidiMessage::noteOn(midiChannel, midiNoteNumber, velocity));
	}
}

void KeyboardComponent::handleNoteOff(MidiKeyboardState *source, int midiChannel, int midiNoteNumber, float velocity)
{
	if (velocity > 0.0001)
	{
		pianoController.SendMidiMessage(MidiMessage::noteOff(midiChannel, midiNoteNumber, velocity));
	}
}

void KeyboardComponent::PianoNoteMessage(const MidiMessage& message)
{
	if (message.isNoteOn())
	{
		keyState.noteOn(1, message.getNoteNumber(), 0.0001);
	}
	else if (message.isNoteOff())
	{
		keyState.noteOff(1, message.getNoteNumber(), 0.0001);
	}
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="KeyboardComponent" componentName=""
                 parentClasses="public Component, public MidiKeyboardStateListener, public PianoController::Listener"
                 constructorParams="PianoController&amp; pianoController" variableInitialisers="pianoController(pianoController)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="70">
  <BACKGROUND backgroundColour="ff323e44">
    <RECT pos="0 0 0M 1" fill="solid: ff283237" hasStroke="0"/>
  </BACKGROUND>
  <GENERICCOMPONENT name="Midi Keyboard Component" id="d578dbfb8bf47c83" memberName="midiKeyboardComponent"
                    virtualName="MidiKeyboardComponent" explicitFocusOrder="0" pos="0 2 0M 2M"
                    class="Component" params="keyState, MidiKeyboardComponent::horizontalKeyboard"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
