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
    ~SceneComponent() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void changeListenerCallback(ChangeBroadcaster* source) override;
    void PianoStateChanged() override { MessageManager::callAsync([=](){updateSettingsState();}); }
	void updateSettingsState();
	void showMenu();
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
    std::unique_ptr<PlaybackComponent> playbackComponent;
    std::unique_ptr<VoiceComponent> voiceComponent;
    std::unique_ptr<ScoreComponent> scoreComponent;
    std::unique_ptr<KeyboardComponent> keyboardComponent;
	std::unique_ptr<LocalMidiConnector> localMidiConnector;
	std::unique_ptr<RtpMidiConnector> rtpMidiConnector;
	MidiConnector* midiConnector = nullptr;
	String currentPianoIp;
	String currentMidiPort;
	Settings& settings;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<GroupComponent> topbarPanel;
    std::unique_ptr<Component> playbackPanel;
    std::unique_ptr<Component> largeContentPanel;
    std::unique_ptr<ImageButton> muteButton;
    std::unique_ptr<Label> statusLabel;
    std::unique_ptr<ImageButton> menuButton;
    std::unique_ptr<ImageButton> zoomInButton;
    std::unique_ptr<ImageButton> zoomOutButton;
    std::unique_ptr<Component> keyboardPanel;
    std::unique_ptr<ImageButton> keyboardButton;
    std::unique_ptr<TextButton> scoreButton;
    std::unique_ptr<TextButton> voiceButton;
    std::unique_ptr<ImageButton> balanceButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SceneComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

