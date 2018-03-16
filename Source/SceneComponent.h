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

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
#include "PianoController.h"
#include "PlaybackComponent.h"
#include "LocalMidiConnector.h"
#include "RtpMidiConnector.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class SceneComponent  : public Component,
                        public ChangeListener,
                        public Button::Listener
{
public:
    //==============================================================================
    SceneComponent ();
    ~SceneComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void changeListenerCallback(ChangeBroadcaster* source) override;
	void updateSettingsState();
	void showSettingsDialog();
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    AudioDeviceManager audioDeviceManager;
    PianoController pianoController;
    PlaybackComponent playbackComponent;
	ScopedPointer<LocalMidiConnector> localMidiConnector;
	ScopedPointer<RtpMidiConnector> rtpMidiConnector;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> topbarPanel;
    ScopedPointer<TextButton> connectButton;
    ScopedPointer<TextButton> settingsButton;
    ScopedPointer<Component> playbackPanel;
    ScopedPointer<Component> largeContentPanel;
    ScopedPointer<ImageButton> muteButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SceneComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
