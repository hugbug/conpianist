/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.3.1

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
#include "VoiceComponent.h"
#include "ScoreComponent.h"
#include "KeyboardComponent.h"
#include "LocalMidiConnector.h"
#include "RtpMidiConnector.h"
#include "Settings.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class SceneComponent  : public Component,
                        public PianoController::Listener,
                        public ChangeListener,
                        public Timer,
                        public Button::Listener
{
public:
    //==============================================================================
    SceneComponent (Settings& settings);
    ~SceneComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void changeListenerCallback(ChangeBroadcaster* source) override;
    void PianoStateChanged() override { MessageManager::callAsync([=](){updateSettingsState();}); }
	void updateSettingsState();
	void showConnectionDialog();
	void timerCallback() override;
	void applySettings();
	void checkConnection();
	void zoomUi(bool zoomIn);
    void toggleKeyboard();
	void switchLargePanel(Button* button);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    AudioDeviceManager audioDeviceManager;
    PianoController pianoController;
    ScopedPointer<PlaybackComponent> playbackComponent;
    ScopedPointer<VoiceComponent> voiceComponent;
    ScopedPointer<ScoreComponent> scoreComponent;
    ScopedPointer<KeyboardComponent> keyboardComponent;
	ScopedPointer<LocalMidiConnector> localMidiConnector;
	ScopedPointer<RtpMidiConnector> rtpMidiConnector;
	MidiConnector* midiConnector = nullptr;
	String currentPianoIp;
	String currentMidiPort;
	Settings& settings;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> topbarPanel;
    ScopedPointer<Component> playbackPanel;
    ScopedPointer<Component> largeContentPanel;
    ScopedPointer<ImageButton> muteButton;
    ScopedPointer<Label> statusLabel;
    ScopedPointer<ImageButton> connectionButton;
    ScopedPointer<ImageButton> zoomInButton;
    ScopedPointer<ImageButton> zoomOutButton;
    ScopedPointer<Component> keyboardPanel;
    ScopedPointer<ImageButton> keyboardButton;
    ScopedPointer<TextButton> scoreButton;
    ScopedPointer<TextButton> voiceButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SceneComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
