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
#include "PrBaseComponent.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PrKeyOffSamplingComponent  : public PrBaseComponent,
                                   public Slider::Listener
{
public:
    //==============================================================================
    PrKeyOffSamplingComponent (Settings& settings, PianoController& pianoController);
    ~PrKeyOffSamplingComponent() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void PianoStateChanged(PianoController::Aspect ap, PianoController::Channel ch) override
		{ if (ap == PianoController::apKeyOffSampling || ap == PianoController::apConnection)
			MessageManager::callAsync([=](){updatePianoState(ap);}); }
	void updatePianoState(PianoController::Aspect aspect);
    void mouseDoubleClick (const MouseEvent& e) override;
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    int inSliderChange = 0;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Slider> slider;
    std::unique_ptr<Label> depthLabel;
    std::unique_ptr<Label> titleLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PrKeyOffSamplingComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

