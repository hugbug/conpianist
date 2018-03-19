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



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PlaybackComponent  : public Component,
                           public ChangeListener,
                           public Slider::Listener,
                           public Button::Listener
{
public:
    //==============================================================================
    PlaybackComponent (PianoController& pianoController);
    ~PlaybackComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void changeListenerCallback(ChangeBroadcaster* source) override;
    void chooseSong();
    void loadSong(const File& file);
	void updateSongState();
	void updateSettingsState();
	void updateEnabledControls();
	void mouseUp(const MouseEvent& event) override;
	void loopButtonClicked();
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    PianoController& pianoController;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> songGroup;
    ScopedPointer<Label> songLabel;
    ScopedPointer<GroupComponent> playbackGroup;
    ScopedPointer<Slider> positionSlider;
    ScopedPointer<Label> positionLabel;
    ScopedPointer<Label> lengthLabel;
    ScopedPointer<ImageButton> playButton;
    ScopedPointer<ImageButton> rewindButton;
    ScopedPointer<ImageButton> forwardButton;
    ScopedPointer<ImageButton> chooseSongButton;
    ScopedPointer<TextButton> backingPartButton;
    ScopedPointer<Label> partLabel;
    ScopedPointer<TextButton> leftPartButton;
    ScopedPointer<TextButton> rightPartButton;
    ScopedPointer<ImageButton> guideButton;
    ScopedPointer<ImageButton> loopButton;
    ScopedPointer<ImageButton> lightsButton;
    ScopedPointer<Label> volumeTitleLabel;
    ScopedPointer<Slider> volumeSlider;
    ScopedPointer<Label> volumeLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaybackComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
