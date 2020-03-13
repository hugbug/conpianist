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

#include "KeyboardComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
KeyboardComponent::KeyboardComponent (PianoController& pianoController, Settings& settings)
    : pianoController(pianoController), settings(settings)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    midiKeyboardComponent.reset (new MidiKeyboardComponent (keyState, MidiKeyboardComponent::horizontalKeyboard));
    addAndMakeVisible (midiKeyboardComponent.get());
    midiKeyboardComponent->setName ("Midi Keyboard Component");

    channelComboBox.reset (new ComboBox ("Channel Combo Box"));
    addAndMakeVisible (channelComboBox.get());
    channelComboBox->setTooltip (TRANS("MIDI Channel"));
    channelComboBox->setEditableText (false);
    channelComboBox->setJustificationType (Justification::centred);
    channelComboBox->setTextWhenNothingSelected (String());
    channelComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    channelComboBox->addItem (TRANS("1"), 1);
    channelComboBox->addItem (TRANS("2"), 2);
    channelComboBox->addItem (TRANS("3"), 3);
    channelComboBox->addItem (TRANS("4"), 4);
    channelComboBox->addItem (TRANS("5"), 5);
    channelComboBox->addItem (TRANS("6"), 6);
    channelComboBox->addItem (TRANS("7"), 7);
    channelComboBox->addItem (TRANS("8"), 8);
    channelComboBox->addItem (TRANS("9"), 9);
    channelComboBox->addItem (TRANS("10"), 10);
    channelComboBox->addItem (TRANS("11"), 11);
    channelComboBox->addItem (TRANS("12"), 12);
    channelComboBox->addItem (TRANS("13"), 13);
    channelComboBox->addItem (TRANS("14"), 14);
    channelComboBox->addItem (TRANS("15"), 15);
    channelComboBox->addItem (TRANS("16"), 16);
    channelComboBox->addListener (this);

    channelComboBox->setBounds (12, 26, 56, 24);

    label.reset (new Label ("new label",
                            TRANS("Channel")));
    addAndMakeVisible (label.get());
    label->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    label->setBounds (8, 2, 64, 24);


    //[UserPreSize]
	midiKeyboardComponent->setAvailableRange(21, 120);
	midiKeyboardComponent->setColour(MidiKeyboardComponent::ColourIds::keyDownOverlayColourId, Colour(0xFEEE6C0A));
	midiKeyboardComponent->setColour(MidiKeyboardComponent::ColourIds::mouseOverKeyOverlayColourId, Colour(0xAEEE6C0A));
	keyState.addListener(this);
	pianoController.AddListener(this);

    settings.addChangeListener(this);
	applySettings();

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
    channelComboBox = nullptr;
    label = nullptr;


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
    float offset = channelComboBox->getX() * 2 + channelComboBox->getWidth();
	float requiredWidth = midiKeyboardComponent->getTotalKeyboardWidth();
	if (requiredWidth < getWidth() - offset * 2)
	{
		midiKeyboardComponent->setBounds((getWidth() - requiredWidth) / 2,
			midiKeyboardComponent->getY(), requiredWidth, midiKeyboardComponent->getHeight());
	}
	else if (requiredWidth < getWidth() - offset)
	{
    	midiKeyboardComponent->setBounds(offset, midiKeyboardComponent->getY(), requiredWidth, midiKeyboardComponent->getHeight());
	}
	else
	{
    	midiKeyboardComponent->setBounds(offset, midiKeyboardComponent->getY(), getWidth() - offset, midiKeyboardComponent->getHeight());
	}
    //[/UserResized]
}

void KeyboardComponent::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == channelComboBox.get())
    {
        //[UserComboBoxCode_channelComboBox] -- add your combo box handling code here..
        settings.keyboardChannel = channelComboBox->getSelectedItemIndex() + 1;
        settings.Save();
        //[/UserComboBoxCode_channelComboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
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

void KeyboardComponent::changeListenerCallback(ChangeBroadcaster* source)
{
	if (source == &settings)
	{
		applySettings();
	}
}

void KeyboardComponent::applySettings()
{
	midiKeyboardComponent->setMidiChannel(settings.keyboardChannel);
	channelComboBox->setSelectedItemIndex(settings.keyboardChannel - 1);
}

void KeyboardComponent::updateKeyboardState()
{
	updateEnabledControls();
}

void KeyboardComponent::updateEnabledControls()
{
	for (Component* co : getChildren())
	{
		co->setEnabled(pianoController.IsConnected());
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
                 parentClasses="public Component, public MidiKeyboardStateListener, public PianoController::Listener, public ChangeListener"
                 constructorParams="PianoController&amp; pianoController, Settings&amp; settings"
                 variableInitialisers="pianoController(pianoController), settings(settings)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="70">
  <BACKGROUND backgroundColour="ff323e44">
    <RECT pos="0 0 0M 1" fill="solid: ff283237" hasStroke="0"/>
  </BACKGROUND>
  <GENERICCOMPONENT name="Midi Keyboard Component" id="d578dbfb8bf47c83" memberName="midiKeyboardComponent"
                    virtualName="MidiKeyboardComponent" explicitFocusOrder="0" pos="0 2 0M 2M"
                    class="Component" params="keyState, MidiKeyboardComponent::horizontalKeyboard"/>
  <COMBOBOX name="Channel Combo Box" id="1961c4e77abdba4e" memberName="channelComboBox"
            virtualName="" explicitFocusOrder="0" pos="12 26 56 24" tooltip="MIDI Channel"
            editable="0" layout="36" items="1&#10;2&#10;3&#10;4&#10;5&#10;6&#10;7&#10;8&#10;9&#10;10&#10;11&#10;12&#10;13&#10;14&#10;15&#10;16"
            textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <LABEL name="new label" id="92ffa529bd029da5" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="8 2 64 24" edTextCol="ff000000" edBkgCol="0"
         labelText="Channel" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

