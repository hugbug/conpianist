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

//[Headers] You can add your own extra header files here...
#include "PrBrightnessComponent.h"
#include "PrLidPositionComponent.h"
#include "PrDamperResonanceComponent.h"
#include "PrVrmComponent.h"
#include "PrEnvironmentComponent.h"
#include "PrMasterTuneComponent.h"
#include "PrStringResonanceComponent.h"
#include "PrEachKeyComponent.h"
#include "PrTouchCurveComponent.h"
#include "PrHalfPedalPointComponent.h"
#include "PrKeyOffSamplingComponent.h"
#include "LookAndFeel.h"
//[/Headers]

#include "PianoRoomComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PianoRoomComponent::PianoRoomComponent (Settings& settings, PianoController& pianoController)
    : settings(settings), pianoController(pianoController)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    contentViewport.reset (new Viewport (String()));
    addAndMakeVisible (contentViewport.get());
    contentViewport->setScrollBarsShown (true, false);

    contentPanel.reset (new Component());
    addAndMakeVisible (contentPanel.get());

    contentPanel->setBounds (48, 32, 336, 360);


    //[UserPreSize]
	contentViewport->setViewedComponent(contentPanel.get(), false);
    AddComponent(new PrLidPositionComponent(settings, pianoController));
    AddComponent(new PrBrightnessComponent(settings, pianoController));
    AddComponent(new PrTouchCurveComponent(settings, pianoController));
    AddComponent(new PrEnvironmentComponent(settings, pianoController));
    AddComponent(new PrMasterTuneComponent(settings, pianoController));
    AddComponent(new PrVrmComponent(settings, pianoController));
    AddComponent(new PrDamperResonanceComponent(settings, pianoController));
    AddComponent(new PrStringResonanceComponent(settings, pianoController));
    AddComponent(new PrKeyOffSamplingComponent(settings, pianoController));
    //AddComponent(new PrHalfPedalPointComponent(settings, pianoController));
    AddComponent(new PrEachKeyComponent(settings, pianoController));
    //[/UserPreSize]

    setSize (640, 700);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

PianoRoomComponent::~PianoRoomComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    contentViewport = nullptr;
    contentPanel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PianoRoomComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PianoRoomComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    contentViewport->setBounds (0, 0, getWidth() - 0, getHeight() - 0);
    //[UserResized] Add your own custom resize handling here..
    int top = 10;
    bool odd = false;
    for (auto& comp : sections)
    {
    	if (odd)
    	{
    		comp->setBackgroundColor(Colour(0xFF424E54));
    	}
    	comp->setBounds(0, top, getWidth(), comp->getHeight());
    	top += comp->getHeight();
    	odd = !odd;
	}
	contentPanel->setBounds(0, 0, getWidth(), top);
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PianoRoomComponent::AddComponent(PrBaseComponent* comp)
{
	std::unique_ptr<PrBaseComponent> ucomp(comp);
    sections.push_back(std::move(ucomp));
    contentPanel->addAndMakeVisible(comp);
}

void PianoRoomComponent::showDialog(Settings& settings, PianoController& pianoController)
{
	::LookAndFeel::showModalDialog(new PianoRoomComponent(settings, pianoController), "Piano Room");
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PianoRoomComponent" componentName=""
                 parentClasses="public Component, public PianoController::Listener"
                 constructorParams="Settings&amp; settings, PianoController&amp; pianoController"
                 variableInitialisers="settings(settings), pianoController(pianoController)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="640" initialHeight="700">
  <BACKGROUND backgroundColour="ff323e44"/>
  <VIEWPORT name="" id="58db405ab1d794e4" memberName="contentViewport" virtualName=""
            explicitFocusOrder="0" pos="0 0 0M 0M" vscroll="1" hscroll="0"
            scrollbarThickness="8" contentType="0" jucerFile="" contentClass=""
            constructorParams=""/>
  <GENERICCOMPONENT name="" id="ff555d787a6f0df9" memberName="contentPanel" virtualName=""
                    explicitFocusOrder="0" pos="48 32 336 360" class="Component"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

