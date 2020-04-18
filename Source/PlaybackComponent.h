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
class PlaybackComponent  : public Component,
                           public PianoController::Listener,
                           public Slider::Listener,
                           public Button::Listener
{
public:
    //==============================================================================
    PlaybackComponent (Settings& settings, PianoController& pianoController);
    ~PlaybackComponent() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void chooseSong();
    void loadSong(const URL& url);
    void PianoStateChanged(PianoController::Aspect aspect, PianoController::Channel channel) override;
	void updatePlaybackState(PianoController::Aspect aspect);
	void updateChannelState();
	void updateSettingsState();
	void updateEnabledControls();
	void mouseUp(const MouseEvent& event) override;
	void mouseDoubleClick (const MouseEvent& event) override;
	void loopButtonClicked();
	void showStreamLightsMenu();
	void showGuideMenu();
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    Settings& settings;
    PianoController& pianoController;
    bool menuShown = false;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<GroupComponent> songGroup;
    std::unique_ptr<Label> songLabel;
    std::unique_ptr<GroupComponent> playbackGroup;
    std::unique_ptr<Slider> positionSlider;
    std::unique_ptr<Label> positionLabel;
    std::unique_ptr<Label> lengthLabel;
    std::unique_ptr<ImageButton> playButton;
    std::unique_ptr<ImageButton> rewindButton;
    std::unique_ptr<ImageButton> forwardButton;
    std::unique_ptr<ImageButton> chooseSongButton;
    std::unique_ptr<TextButton> backingPartButton;
    std::unique_ptr<Label> partLabel;
    std::unique_ptr<TextButton> leftPartButton;
    std::unique_ptr<TextButton> rightPartButton;
    std::unique_ptr<ImageButton> guideButton;
    std::unique_ptr<ImageButton> loopButton;
    std::unique_ptr<ImageButton> lightsButton;
    std::unique_ptr<Label> volumeTitleLabel;
    std::unique_ptr<Slider> volumeSlider;
    std::unique_ptr<Label> volumeLabel;
    std::unique_ptr<Label> tempoTitleLabel;
    std::unique_ptr<Slider> tempoSlider;
    std::unique_ptr<Label> tempoLabel;
    std::unique_ptr<Label> transposeTitleLabel;
    std::unique_ptr<Slider> transposeSlider;
    std::unique_ptr<Label> transposeLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaybackComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

