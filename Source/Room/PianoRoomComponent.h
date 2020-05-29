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
class PianoRoomComponent  : public Component,
                            public PianoController::Listener
{
public:
    //==============================================================================
    PianoRoomComponent (Settings& settings, PianoController& pianoController);
    ~PianoRoomComponent() override;

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	static void showDialog(Settings& settings, PianoController& pianoController);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
	void AddComponent(PrBaseComponent* comp);

    Settings& settings;
    PianoController& pianoController;
    std::vector<std::unique_ptr<PrBaseComponent>> sections;
    //[/UserVariables]

    //==============================================================================
    std::unique_ptr<Viewport> contentViewport;
    std::unique_ptr<Component> contentPanel;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PianoRoomComponent)
};

//[EndFile] You can add extra defines here...
//[/EndFile]

