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

#include "ChannelComponent.h"


//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MixerComponent  : public Component,
                        public PianoController::Listener,
                        public ComboBox::Listener
{
public:
    //==============================================================================
    MixerComponent (PianoController& pianoController);
    ~MixerComponent() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void PianoStateChanged(PianoController::Aspect ap, PianoController::Channel ch) override
		{ if (ap == PianoController::apConnection || ap == PianoController::apReverbEffect)
			MessageManager::callAsync([=](){updateReverbEffectState();}); }
	void updateReverbEffectState();
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    PianoController& pianoController;
    std::vector<std::unique_ptr<ChannelComponent>> channels;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Viewport> channelViewport;
    std::unique_ptr<ChannelComponent> leftChannel;
    std::unique_ptr<Component> channelPanel;
    std::unique_ptr<ComboBox> effectComboBox;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MixerComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

