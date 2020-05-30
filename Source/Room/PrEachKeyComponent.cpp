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

#include "PrEachKeyComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PrEachKeyComponent::PrEachKeyComponent (Settings& settings, PianoController& pianoController)
    : PrBaseComponent(settings, pianoController)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    titleLabel.reset (new Label (String(),
                                 TRANS("Each Key Setting")));
    addAndMakeVisible (titleLabel.get());
    titleLabel->setFont (Font (16.00f, Font::plain).withTypefaceStyle ("Regular"));
    titleLabel->setJustificationType (Justification::centredLeft);
    titleLabel->setEditable (false, false, false);
    titleLabel->setColour (TextEditor::textColourId, Colours::black);
    titleLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    titleLabel->setBounds (18, 12, 238, 24);

    keySlider.reset (new Slider (String()));
    addAndMakeVisible (keySlider.get());
    keySlider->setRange (0, 127, 1);
    keySlider->setSliderStyle (Slider::LinearHorizontal);
    keySlider->setTextBoxStyle (Slider::TextBoxAbove, false, 80, 20);
    keySlider->addListener (this);

    keySlider->setBounds (272, 14, 344, 52);

    tuneSlider.reset (new Slider (String()));
    addAndMakeVisible (tuneSlider.get());
    tuneSlider->setRange (-10, 10, 1);
    tuneSlider->setSliderStyle (Slider::LinearHorizontal);
    tuneSlider->setTextBoxStyle (Slider::TextBoxAbove, false, 80, 20);
    tuneSlider->addListener (this);

    tuneSlider->setBounds (272, 72, 344, 52);

    volumeSlider.reset (new Slider (String()));
    addAndMakeVisible (volumeSlider.get());
    volumeSlider->setRange (-10, 10, 1);
    volumeSlider->setSliderStyle (Slider::LinearHorizontal);
    volumeSlider->setTextBoxStyle (Slider::TextBoxAbove, false, 80, 20);
    volumeSlider->addListener (this);

    volumeSlider->setBounds (272, 136, 344, 52);

    keyLabel.reset (new Label (String(),
                               TRANS("Key")));
    addAndMakeVisible (keyLabel.get());
    keyLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    keyLabel->setJustificationType (Justification::centredLeft);
    keyLabel->setEditable (false, false, false);
    keyLabel->setColour (TextEditor::textColourId, Colours::black);
    keyLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    keyLabel->setBounds (280, 16, 104, 24);

    tuneLabel.reset (new Label (String(),
                                TRANS("Tune")));
    addAndMakeVisible (tuneLabel.get());
    tuneLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    tuneLabel->setJustificationType (Justification::centredLeft);
    tuneLabel->setEditable (false, false, false);
    tuneLabel->setColour (TextEditor::textColourId, Colours::black);
    tuneLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    tuneLabel->setBounds (280, 75, 104, 24);

    volumeLabel.reset (new Label (String(),
                                  TRANS("Volume")));
    addAndMakeVisible (volumeLabel.get());
    volumeLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    volumeLabel->setJustificationType (Justification::centredLeft);
    volumeLabel->setEditable (false, false, false);
    volumeLabel->setColour (TextEditor::textColourId, Colours::black);
    volumeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    volumeLabel->setBounds (280, 139, 104, 24);


    //[UserPreSize]
    // not yet implemented
    titleLabel->setEnabled(false);
    keyLabel->setEnabled(false);
    tuneLabel->setEnabled(false);
    volumeLabel->setEnabled(false);
    keySlider->setEnabled(false);
    tuneSlider->setEnabled(false);
    volumeSlider->setEnabled(false);
    //[/UserPreSize]

    setSize (640, 200);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

PrEachKeyComponent::~PrEachKeyComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    titleLabel = nullptr;
    keySlider = nullptr;
    tuneSlider = nullptr;
    volumeSlider = nullptr;
    keyLabel = nullptr;
    tuneLabel = nullptr;
    volumeLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PrEachKeyComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    PrBaseComponent::paint(g);
    //[/UserPaint]
}

void PrEachKeyComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void PrEachKeyComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == keySlider.get())
    {
        //[UserSliderCode_keySlider] -- add your slider handling code here..
        //[/UserSliderCode_keySlider]
    }
    else if (sliderThatWasMoved == tuneSlider.get())
    {
        //[UserSliderCode_tuneSlider] -- add your slider handling code here..
        //[/UserSliderCode_tuneSlider]
    }
    else if (sliderThatWasMoved == volumeSlider.get())
    {
        //[UserSliderCode_volumeSlider] -- add your slider handling code here..
        //[/UserSliderCode_volumeSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PrEachKeyComponent" componentName=""
                 parentClasses="public PrBaseComponent" constructorParams="Settings&amp; settings, PianoController&amp; pianoController"
                 variableInitialisers="PrBaseComponent(settings, pianoController)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="640" initialHeight="200">
  <BACKGROUND backgroundColour="ff323e44"/>
  <LABEL name="" id="dc20d157ffc118c5" memberName="titleLabel" virtualName=""
         explicitFocusOrder="0" pos="18 12 238 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Each Key Setting" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="16.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="" id="cb1eec80b99d9306" memberName="keySlider" virtualName=""
          explicitFocusOrder="0" pos="272 14 344 52" min="0.0" max="127.0"
          int="1.0" style="LinearHorizontal" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="" id="3e6011b9480d8548" memberName="tuneSlider" virtualName=""
          explicitFocusOrder="0" pos="272 72 344 52" min="-10.0" max="10.0"
          int="1.0" style="LinearHorizontal" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="" id="91ca8d7009fb7e79" memberName="volumeSlider" virtualName=""
          explicitFocusOrder="0" pos="272 136 344 52" min="-10.0" max="10.0"
          int="1.0" style="LinearHorizontal" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="" id="6f97de9f7ce2b377" memberName="keyLabel" virtualName=""
         explicitFocusOrder="0" pos="280 16 104 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Key" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="" id="17c0eed6e271e668" memberName="tuneLabel" virtualName=""
         explicitFocusOrder="0" pos="280 75 104 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Tune" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="" id="544fb6f67ec3de1f" memberName="volumeLabel" virtualName=""
         explicitFocusOrder="0" pos="280 139 104 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Volume" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

