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
                          public Button::Listener,
                          public Slider::Listener
{
public:
    //==============================================================================
    ChannelComponent (PianoController& pianoController, PianoController::Channel channel, String title, bool showLabels, bool canPanAndReverb, bool showMenu, bool shrinkMenu);
    ~ChannelComponent() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void PianoStateChanged(PianoController::Aspect ap, PianoController::Channel ch) override
		{ if (ch == channel || ap == PianoController::apConnection) MessageManager::callAsync([=](){updateChannelState(ap);}); }
	void updateChannelState(PianoController::Aspect aspect);
    void mouseDoubleClick(const MouseEvent& event) override;
    void mouseDown(const MouseEvent& event) override;
	void showMenu(Button* button);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    PianoController& pianoController;
    PianoController::Channel channel;
    String title;
    bool canPanAndReverb;
    bool showMenuRow;
    bool shrinkMenu;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<ImageButton> menuButton;
    std::unique_ptr<Label> partLabel;
    std::unique_ptr<Label> panLabel;
    std::unique_ptr<ImageButton> menuButton2;
    std::unique_ptr<Slider> volumeSlider;
    std::unique_ptr<Slider> panSlider;
    std::unique_ptr<Label> reverbLabel;
    std::unique_ptr<Slider> reverbSlider;
    std::unique_ptr<Label> volumeLabel;
    std::unique_ptr<TextButton> titleButton;
    std::unique_ptr<Label> titleLabel;
    std::unique_ptr<Label> voiceLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChannelComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

