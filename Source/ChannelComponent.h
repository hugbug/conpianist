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
#include <JuceHeader.h>
#include "PianoController.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class ChannelComponent  : public Component,
                          public PianoController::Listener,
                          public Slider::Listener
{
public:
    //==============================================================================
    ChannelComponent (PianoController& pianoController, PianoController::Channel channel, String title, bool showLabels);
    ~ChannelComponent() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void PianoStateChanged() override { MessageManager::callAsync([=](){updateSongState();}); }
	void updateSongState();
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    PianoController& pianoController;
    PianoController::Channel channel;
    String title;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Label> titleLabel;
    std::unique_ptr<Slider> volumeSlider;
    std::unique_ptr<Slider> panSlider;
    std::unique_ptr<Label> panLabel;
    std::unique_ptr<Label> reverbLabel;
    std::unique_ptr<Slider> reverbSlider;
    std::unique_ptr<Label> volumeLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChannelComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

