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
class PrTouchCurveComponent  : public PrBaseComponent,
                               public Button::Listener,
                               public Slider::Listener
{
public:
    //==============================================================================
    PrTouchCurveComponent (Settings& settings, PianoController& pianoController);
    ~PrTouchCurveComponent() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void PianoStateChanged(PianoController::Aspect ap, PianoController::Channel ch) override
		{ if (ap == PianoController::apTouchCurve || ap == PianoController::apConnection)
			MessageManager::callAsync([=](){updatePianoState(ap);}); }
	void updatePianoState(PianoController::Aspect aspect);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<TextButton> soft2Button;
    std::unique_ptr<TextButton> soft1Button;
    std::unique_ptr<Label> titleLabel;
    std::unique_ptr<TextButton> mediumButton;
    std::unique_ptr<TextButton> hard1Button;
    std::unique_ptr<TextButton> hard2Button;
    std::unique_ptr<TextButton> fixedButton;
    std::unique_ptr<Slider> slider;
    std::unique_ptr<Label> velocityLabel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PrTouchCurveComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

