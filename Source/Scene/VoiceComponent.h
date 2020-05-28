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
#include "Presets.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class VoiceComponent  : public Component,
                        public PianoController::Listener,
                        public Button::Listener
{
public:
    //==============================================================================
    VoiceComponent (PianoController& pianoController);
    ~VoiceComponent() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void PianoStateChanged(PianoController::Aspect aspect, PianoController::Channel channel) override;
    void updateVoiceState();
    void buildVoiceTree();
    void voiceItemClicked(Voice* voice);
    void voiceButtonClicked(Button* button);
    void scrollToVoice(const String& preset);
	void updateEnabledControls();
	void showMenu(Button* button, PianoController::Channel channel);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    PianoController& pianoController;
    TreeViewItem* rootItem;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<GroupComponent> targetGroup;
    std::unique_ptr<TreeView> voicesTree;
    std::unique_ptr<TextButton> leftVoiceButton;
    std::unique_ptr<TextButton> mainVoiceButton;
    std::unique_ptr<TextButton> layerVoiceButton;
    std::unique_ptr<TextButton> mainTitleButton;
    std::unique_ptr<TextButton> leftTitleButton;
    std::unique_ptr<TextButton> layerTitleButton;
    std::unique_ptr<Label> leftIndicatorLabel;
    std::unique_ptr<Label> mainIndicatorLabel;
    std::unique_ptr<Label> layerIndicatorLabel;
    std::unique_ptr<Label> layerOctaveLabel;
    std::unique_ptr<Label> leftOctaveLabel;
    std::unique_ptr<Label> mainOctaveLabel;
    std::unique_ptr<ImageButton> leftMenuButton2;
    std::unique_ptr<ImageButton> layerMenuButton2;
    std::unique_ptr<ImageButton> layerMenuButton;
    std::unique_ptr<ImageButton> leftMenuButton;
    std::unique_ptr<ImageButton> mainMenuButton2;
    std::unique_ptr<ImageButton> mainMenuButton;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (VoiceComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

