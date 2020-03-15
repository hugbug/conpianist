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
//[/Headers]

#include "BalanceComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
BalanceComponent::BalanceComponent (PianoController& pianoController)
    : pianoController(pianoController)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    leftLabel.reset (new Label ("Left Label",
                                TRANS("Left")));
    addAndMakeVisible (leftLabel.get());
    leftLabel->setFont (Font (15.40f, Font::plain).withTypefaceStyle ("Regular"));
    leftLabel->setJustificationType (Justification::centredTop);
    leftLabel->setEditable (false, false, false);
    leftLabel->setColour (TextEditor::textColourId, Colours::black);
    leftLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    leftLabel->setBounds (8, 8, 50, 24);

    mainLabel.reset (new Label ("Main Label",
                                TRANS("Main")));
    addAndMakeVisible (mainLabel.get());
    mainLabel->setFont (Font (15.40f, Font::plain).withTypefaceStyle ("Regular"));
    mainLabel->setJustificationType (Justification::centredTop);
    mainLabel->setEditable (false, false, false);
    mainLabel->setColour (TextEditor::textColourId, Colours::black);
    mainLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    mainLabel->setBounds (68, 8, 50, 24);

    layerLabel.reset (new Label ("Layer Label",
                                 TRANS("Layer")));
    addAndMakeVisible (layerLabel.get());
    layerLabel->setFont (Font (15.40f, Font::plain).withTypefaceStyle ("Regular"));
    layerLabel->setJustificationType (Justification::centredTop);
    layerLabel->setEditable (false, false, false);
    layerLabel->setColour (TextEditor::textColourId, Colours::black);
    layerLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    layerLabel->setBounds (128, 8, 50, 24);

    songLabel.reset (new Label ("Song Label",
                                TRANS("Song")));
    addAndMakeVisible (songLabel.get());
    songLabel->setFont (Font (15.40f, Font::plain).withTypefaceStyle ("Regular"));
    songLabel->setJustificationType (Justification::centredTop);
    songLabel->setEditable (false, false, false);
    songLabel->setColour (TextEditor::textColourId, Colours::black);
    songLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    songLabel->setBounds (188, 8, 50, 24);

    micLabel.reset (new Label ("Mic Label",
                               TRANS("Mic")));
    addAndMakeVisible (micLabel.get());
    micLabel->setFont (Font (15.40f, Font::plain).withTypefaceStyle ("Regular"));
    micLabel->setJustificationType (Justification::centredTop);
    micLabel->setEditable (false, false, false);
    micLabel->setColour (TextEditor::textColourId, Colours::black);
    micLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    micLabel->setBounds (248, 8, 50, 24);

    auxInLabel.reset (new Label ("AuxIn Label",
                                 TRANS("Aux In")));
    addAndMakeVisible (auxInLabel.get());
    auxInLabel->setFont (Font (15.40f, Font::plain).withTypefaceStyle ("Regular"));
    auxInLabel->setJustificationType (Justification::centredTop);
    auxInLabel->setEditable (false, false, false);
    auxInLabel->setColour (TextEditor::textColourId, Colours::black);
    auxInLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    auxInLabel->setBounds (308, 8, 50, 24);

    leftSlider.reset (new Slider ("Left Slider"));
    addAndMakeVisible (leftSlider.get());
    leftSlider->setRange (0, 127, 1);
    leftSlider->setSliderStyle (Slider::LinearVertical);
    leftSlider->setTextBoxStyle (Slider::TextBoxAbove, false, 80, 20);
    leftSlider->addListener (this);

    mainSlider.reset (new Slider ("Main Slider"));
    addAndMakeVisible (mainSlider.get());
    mainSlider->setRange (0, 127, 1);
    mainSlider->setSliderStyle (Slider::LinearVertical);
    mainSlider->setTextBoxStyle (Slider::TextBoxAbove, false, 80, 20);
    mainSlider->addListener (this);

    layerSlider.reset (new Slider ("Layer Slider"));
    addAndMakeVisible (layerSlider.get());
    layerSlider->setRange (0, 127, 1);
    layerSlider->setSliderStyle (Slider::LinearVertical);
    layerSlider->setTextBoxStyle (Slider::TextBoxAbove, false, 80, 20);
    layerSlider->addListener (this);

    songSlider.reset (new Slider ("Song Slider"));
    addAndMakeVisible (songSlider.get());
    songSlider->setRange (0, 127, 1);
    songSlider->setSliderStyle (Slider::LinearVertical);
    songSlider->setTextBoxStyle (Slider::TextBoxAbove, false, 80, 20);
    songSlider->addListener (this);

    micSlider.reset (new Slider ("Mic Slider"));
    addAndMakeVisible (micSlider.get());
    micSlider->setRange (0, 127, 1);
    micSlider->setSliderStyle (Slider::LinearVertical);
    micSlider->setTextBoxStyle (Slider::TextBoxAbove, false, 80, 20);
    micSlider->addListener (this);

    auxInSlider.reset (new Slider ("AuxIn Slider"));
    addAndMakeVisible (auxInSlider.get());
    auxInSlider->setRange (0, 127, 1);
    auxInSlider->setSliderStyle (Slider::LinearVertical);
    auxInSlider->setTextBoxStyle (Slider::TextBoxAbove, false, 80, 20);
    auxInSlider->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (366, 264);


    //[Constructor] You can add your own custom stuff here..
    pianoController.AddListener(this);
    updateSongState();
    //[/Constructor]
}

BalanceComponent::~BalanceComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    pianoController.RemoveListener(this);
    //[/Destructor_pre]

    leftLabel = nullptr;
    mainLabel = nullptr;
    layerLabel = nullptr;
    songLabel = nullptr;
    micLabel = nullptr;
    auxInLabel = nullptr;
    leftSlider = nullptr;
    mainSlider = nullptr;
    layerSlider = nullptr;
    songSlider = nullptr;
    micSlider = nullptr;
    auxInSlider = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void BalanceComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void BalanceComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    leftSlider->setBounds (8, 40, 50, getHeight() - 40);
    mainSlider->setBounds (68, 40, 50, getHeight() - 40);
    layerSlider->setBounds (128, 40, 50, getHeight() - 40);
    songSlider->setBounds (188, 40, 50, getHeight() - 40);
    micSlider->setBounds (248, 40, 50, getHeight() - 40);
    auxInSlider->setBounds (308, 40, 50, getHeight() - 40);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void BalanceComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == leftSlider.get())
    {
        //[UserSliderCode_leftSlider] -- add your slider handling code here..
        pianoController.SetVolume(PianoController::BalanceSlot::bsLeft, leftSlider->getValue());
        //[/UserSliderCode_leftSlider]
    }
    else if (sliderThatWasMoved == mainSlider.get())
    {
        //[UserSliderCode_mainSlider] -- add your slider handling code here..
        pianoController.SetVolume(PianoController::BalanceSlot::bsMain, mainSlider->getValue());
        //[/UserSliderCode_mainSlider]
    }
    else if (sliderThatWasMoved == layerSlider.get())
    {
        //[UserSliderCode_layerSlider] -- add your slider handling code here..
        pianoController.SetVolume(PianoController::BalanceSlot::bsLayer, layerSlider->getValue());
        //[/UserSliderCode_layerSlider]
    }
    else if (sliderThatWasMoved == songSlider.get())
    {
        //[UserSliderCode_songSlider] -- add your slider handling code here..
        pianoController.SetVolume(PianoController::BalanceSlot::bsMidi, songSlider->getValue());
        //[/UserSliderCode_songSlider]
    }
    else if (sliderThatWasMoved == micSlider.get())
    {
        //[UserSliderCode_micSlider] -- add your slider handling code here..
        pianoController.SetVolume(PianoController::BalanceSlot::bsMic, micSlider->getValue());
        //[/UserSliderCode_micSlider]
    }
    else if (sliderThatWasMoved == auxInSlider.get())
    {
        //[UserSliderCode_auxInSlider] -- add your slider handling code here..
        pianoController.SetVolume(PianoController::BalanceSlot::bsAuxIn, auxInSlider->getValue());
        //[/UserSliderCode_auxInSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void BalanceComponent::updateSongState()
{
	leftSlider->setValue(pianoController.GetVolume(PianoController::BalanceSlot::bsLeft), NotificationType::dontSendNotification);
	mainSlider->setValue(pianoController.GetVolume(PianoController::BalanceSlot::bsMain), NotificationType::dontSendNotification);
	layerSlider->setValue(pianoController.GetVolume(PianoController::BalanceSlot::bsLayer), NotificationType::dontSendNotification);
	songSlider->setValue(pianoController.GetVolume(PianoController::BalanceSlot::bsMidi), NotificationType::dontSendNotification);
	micSlider->setValue(pianoController.GetVolume(PianoController::BalanceSlot::bsMic), NotificationType::dontSendNotification);
	auxInSlider->setValue(pianoController.GetVolume(PianoController::BalanceSlot::bsAuxIn), NotificationType::dontSendNotification);
}

void BalanceComponent::showDialog(PianoController& pianoController)
{
	DialogWindow::LaunchOptions dialog;
	dialog.content.setOwned(new BalanceComponent(pianoController));
	dialog.dialogTitle = "Balance";
	dialog.useNativeTitleBar = (SystemStats::getOperatingSystemType() & SystemStats::Windows) ||
		(SystemStats::getOperatingSystemType() & SystemStats::MacOSX);
	dialog.resizable = false;
	dialog.launchAsync();
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="BalanceComponent" componentName=""
                 parentClasses="public Component, public PianoController::Listener"
                 constructorParams="PianoController&amp; pianoController" variableInitialisers="pianoController(pianoController)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="366" initialHeight="264">
  <BACKGROUND backgroundColour="ff323e44"/>
  <LABEL name="Left Label" id="bb1cad2ba1283943" memberName="leftLabel"
         virtualName="" explicitFocusOrder="0" pos="8 8 50 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Left" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.4"
         kerning="0.0" bold="0" italic="0" justification="12"/>
  <LABEL name="Main Label" id="ed8c54c71261d2ff" memberName="mainLabel"
         virtualName="" explicitFocusOrder="0" pos="68 8 50 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Main" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.4"
         kerning="0.0" bold="0" italic="0" justification="12"/>
  <LABEL name="Layer Label" id="a9eb5bfd0406b350" memberName="layerLabel"
         virtualName="" explicitFocusOrder="0" pos="128 8 50 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Layer" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.4"
         kerning="0.0" bold="0" italic="0" justification="12"/>
  <LABEL name="Song Label" id="19b588b7e3e3c762" memberName="songLabel"
         virtualName="" explicitFocusOrder="0" pos="188 8 50 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Song" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.4"
         kerning="0.0" bold="0" italic="0" justification="12"/>
  <LABEL name="Mic Label" id="dc48ad248a60d8bb" memberName="micLabel"
         virtualName="" explicitFocusOrder="0" pos="248 8 50 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Mic" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.4"
         kerning="0.0" bold="0" italic="0" justification="12"/>
  <LABEL name="AuxIn Label" id="6d30436cc5a96a61" memberName="auxInLabel"
         virtualName="" explicitFocusOrder="0" pos="308 8 50 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Aux In" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.4"
         kerning="0.0" bold="0" italic="0" justification="12"/>
  <SLIDER name="Left Slider" id="9ebc7097d295b7c9" memberName="leftSlider"
          virtualName="" explicitFocusOrder="0" pos="8 40 50 40M" min="0.0"
          max="127.0" int="1.0" style="LinearVertical" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="Main Slider" id="2d1e3b364abcc81b" memberName="mainSlider"
          virtualName="" explicitFocusOrder="0" pos="68 40 50 40M" min="0.0"
          max="127.0" int="1.0" style="LinearVertical" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="Layer Slider" id="bf3995f54a85f1a2" memberName="layerSlider"
          virtualName="" explicitFocusOrder="0" pos="128 40 50 40M" min="0.0"
          max="127.0" int="1.0" style="LinearVertical" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="Song Slider" id="caa681bfb755af7c" memberName="songSlider"
          virtualName="" explicitFocusOrder="0" pos="188 40 50 40M" min="0.0"
          max="127.0" int="1.0" style="LinearVertical" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="Mic Slider" id="aa06cf9cdd804fbf" memberName="micSlider"
          virtualName="" explicitFocusOrder="0" pos="248 40 50 40M" min="0.0"
          max="127.0" int="1.0" style="LinearVertical" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="AuxIn Slider" id="4bfcc4e67ad3baa8" memberName="auxInSlider"
          virtualName="" explicitFocusOrder="0" pos="308 40 50 40M" min="0.0"
          max="127.0" int="1.0" style="LinearVertical" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

