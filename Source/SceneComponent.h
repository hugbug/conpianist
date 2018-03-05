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
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class SceneComponent  : public Component,
                        public PianoControllerListener,
                        public Button::Listener,
                        public Slider::Listener
{
public:
    //==============================================================================
    SceneComponent ();
    ~SceneComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void chooseSong();
    void loadSong(const File& file);
	void PlaybackStateChanged() override { updateSongState(); };
	void SettingsChanged() override { updateSettingsState(); };
	void updateSongState();
	void updateSettingsState();
	void updateEnabledControls();
	void showSettingsDialog();
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    AudioDeviceManager audioDeviceManager;
    PianoController pianoController;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> songGroup;
    ScopedPointer<GroupComponent> playbackGroup;
    ScopedPointer<GroupComponent> systemGroup;
    ScopedPointer<TextButton> localControlButton;
    ScopedPointer<TextButton> playButton;
    ScopedPointer<TextButton> rewindButton;
    ScopedPointer<TextButton> forwardButton;
    ScopedPointer<TextButton> guideButton;
    ScopedPointer<Slider> positionSlider;
    ScopedPointer<Label> positionLabel;
    ScopedPointer<Label> lengthLabel;
    ScopedPointer<Label> songLabel;
    ScopedPointer<TextButton> chooseSongButton;
    ScopedPointer<TextButton> pauseButton;
    ScopedPointer<TextButton> lightsButton;
    ScopedPointer<TextButton> connectButton;
    ScopedPointer<TextButton> settingsButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SceneComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
