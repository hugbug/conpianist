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
class BalanceComponent  : public Component,
                          public PianoController::Listener,
                          public Slider::Listener
{
public:
    //==============================================================================
    BalanceComponent (PianoController& pianoController);
    ~BalanceComponent() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	static void showDialog(PianoController& pianoController);
    void PianoStateChanged() override { MessageManager::callAsync([=](){updateSongState();}); }
	void updateSongState();
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    PianoController& pianoController;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Label> leftLabel;
    std::unique_ptr<Label> mainLabel;
    std::unique_ptr<Label> layerLabel;
    std::unique_ptr<Label> songLabel;
    std::unique_ptr<Label> micLabel;
    std::unique_ptr<Label> auxInLabel;
    std::unique_ptr<Slider> leftSlider;
    std::unique_ptr<Slider> mainSlider;
    std::unique_ptr<Slider> layerSlider;
    std::unique_ptr<Slider> songSlider;
    std::unique_ptr<Slider> micSlider;
    std::unique_ptr<Slider> auxInSlider;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BalanceComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

