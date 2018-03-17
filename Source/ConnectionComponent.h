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
class ConnectionComponent  : public Component,
                             public ComboBox::Listener
{
public:
    //==============================================================================
    ConnectionComponent (Settings& settings);
    ~ConnectionComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	static void showDialog(Settings& settings);
	void save();
	void load();
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	Settings& settings;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<Label> pianoIpLabel;
    ScopedPointer<TextEditor> pianoIpEdit;
    ScopedPointer<Label> midiPortLabel;
    ScopedPointer<ComboBox> midiPortComboBox;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConnectionComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
