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

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "PianoController.h"
#include "Settings.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class KeyboardComponent  : public Component,
                           public MidiKeyboardStateListener,
                           public PianoController::Listener,
                           public ChangeListener
{
public:
    //==============================================================================
    KeyboardComponent (Settings& settings, PianoController& pianoController);
    ~KeyboardComponent() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void handleNoteOn(MidiKeyboardState *source, int midiChannel, int midiNoteNumber, float velocity) override;
    void handleNoteOff(MidiKeyboardState *source, int midiChannel, int midiNoteNumber, float velocity) override;
    void changeListenerCallback(ChangeBroadcaster* source) override { if (source == &settings) applySettings(); }
	void PianoNoteMessage(const MidiMessage& message) override;
    void PianoStateChanged(PianoController::Aspect aspect, PianoController::Channel channel) override;
	void applySettings();
    void updateKeyboardState();
	void updateEnabledControls();
	bool GetSplitMode() { return m_splitMode; }
    void SetSplitMode(bool splitMode);

	class SplitMidiKeyboardComponent : public MidiKeyboardComponent
	{
	public:
		SplitMidiKeyboardComponent(PianoController& pianoController, MidiKeyboardState& state,
			Orientation orientation) : MidiKeyboardComponent(state, orientation),
			pianoController(pianoController) {}
	protected:
		virtual void drawWhiteNote(int midiNoteNumber, Graphics& g, Rectangle<float> area,
			bool isDown, bool isOver, Colour lineColour, Colour textColour);
		virtual void drawBlackNote(int midiNoteNumber, Graphics& g, Rectangle<float> area,
			bool isDown, bool isOver, Colour noteFillColour);

		PianoController& pianoController;
    	bool m_splitMode = false;
    	friend class KeyboardComponent;
	};
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	MidiKeyboardState keyState;
	Settings& settings;
    PianoController& pianoController;
    bool m_splitMode = false;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<SplitMidiKeyboardComponent> midiKeyboardComponent;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (KeyboardComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

