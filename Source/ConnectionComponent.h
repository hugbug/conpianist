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
//[/Headers]

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ConnectionComponent  : public Component
{
public:
    //==============================================================================
    ConnectionComponent (AudioDeviceManager& audioDeviceManager, PianoController& pianoController);
    ~ConnectionComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	static void saveState(AudioDeviceManager& audioDeviceManager, PianoController& pianoController);
	static void loadState(AudioDeviceManager& audioDeviceManager, PianoController& pianoController);
	static void showDialog(AudioDeviceManager& audioDeviceManager, PianoController& pianoController);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	AudioDeviceManager& audioDeviceManager;
	PianoController& pianoController;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<AudioDeviceSelectorComponent> audioSelector;
    ScopedPointer<Label> remoteIpLabel;
    ScopedPointer<TextEditor> remoteIpEdit;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ConnectionComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
