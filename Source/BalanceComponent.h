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
#include "ChannelComponent.h"
//[/Headers]

#include "ChannelComponent.h"
#include "ChannelComponent.h"
#include "ChannelComponent.h"
#include "ChannelComponent.h"
#include "ChannelComponent.h"
#include "ChannelComponent.h"


//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class BalanceComponent  : public Component,
                          public PianoController::Listener,
                          public ComboBox::Listener
{
public:
    //==============================================================================
    BalanceComponent (PianoController& pianoController);
    ~BalanceComponent() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void PianoStateChanged(PianoController::Aspect ap, PianoController::Channel ch) override
		{ if (ap == PianoController::apConnection || ap == PianoController::apReverbEffect)
			MessageManager::callAsync([=](){updateReverbEffectState();}); }
	void updateReverbEffectState();
	static void showDialog(PianoController& pianoController);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    PianoController& pianoController;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<ChannelComponent> leftChannel;
    std::unique_ptr<ChannelComponent> mainChannel;
    std::unique_ptr<ChannelComponent> layerChannel;
    std::unique_ptr<ChannelComponent> songChannel;
    std::unique_ptr<ChannelComponent> micChannel;
    std::unique_ptr<ChannelComponent> auxInChannel;
    std::unique_ptr<ComboBox> effectComboBox;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (BalanceComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

