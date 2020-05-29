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

#include "PrEnvironmentComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PrEnvironmentComponent::PrEnvironmentComponent (Settings& settings, PianoController& pianoController)
    : PrBaseComponent(settings, pianoController)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    slider.reset (new Slider (String()));
    addAndMakeVisible (slider.get());
    slider->setRange (-64, 64, 1);
    slider->setSliderStyle (Slider::LinearHorizontal);
    slider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    slider->addListener (this);

    slider->setBounds (272, 38, 344, 24);

    depthLabel.reset (new Label (String(),
                                 TRANS("Depth")));
    addAndMakeVisible (depthLabel.get());
    depthLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    depthLabel->setJustificationType (Justification::centred);
    depthLabel->setEditable (false, false, false);
    depthLabel->setColour (TextEditor::textColourId, Colours::black);
    depthLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    depthLabel->setBounds (400, 12, 88, 24);

    titleLabel.reset (new Label (String(),
                                 TRANS("Environment")));
    addAndMakeVisible (titleLabel.get());
    titleLabel->setFont (Font (16.00f, Font::plain).withTypefaceStyle ("Regular"));
    titleLabel->setJustificationType (Justification::centredLeft);
    titleLabel->setEditable (false, false, false);
    titleLabel->setColour (TextEditor::textColourId, Colours::black);
    titleLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    titleLabel->setBounds (18, 12, 238, 24);

    effectComboBox.reset (new ComboBox ("Reverb Effect Combo Box"));
    addAndMakeVisible (effectComboBox.get());
    effectComboBox->setTooltip (TRANS("Reverb Effect"));
    effectComboBox->setEditableText (false);
    effectComboBox->setJustificationType (Justification::centredLeft);
    effectComboBox->setTextWhenNothingSelected (TRANS("Reverb Effect"));
    effectComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    effectComboBox->addItem (TRANS("Real Large Hall"), 1);
    effectComboBox->addItem (TRANS("Real Medium Hall"), 2);
    effectComboBox->addItem (TRANS("Concert Hall"), 3);
    effectComboBox->addListener (this);

    effectComboBox->setBounds (288, 79, 316, 24);


    //[UserPreSize]
	slider->setScrollWheelEnabled(false);
    //[/UserPreSize]

    setSize (640, 125);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

PrEnvironmentComponent::~PrEnvironmentComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    slider = nullptr;
    depthLabel = nullptr;
    titleLabel = nullptr;
    effectComboBox = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PrEnvironmentComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    PrBaseComponent::paint(g);
	drawSliderMark(g, slider.get());
    //[/UserPaint]
}

void PrEnvironmentComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void PrEnvironmentComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == slider.get())
    {
        //[UserSliderCode_slider] -- add your slider handling code here..
        //[/UserSliderCode_slider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void PrEnvironmentComponent::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == effectComboBox.get())
    {
        //[UserComboBoxCode_effectComboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_effectComboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PrEnvironmentComponent" componentName=""
                 parentClasses="public PrBaseComponent" constructorParams="Settings&amp; settings, PianoController&amp; pianoController"
                 variableInitialisers="PrBaseComponent(settings, pianoController)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="640" initialHeight="125">
  <BACKGROUND backgroundColour="ff323e44"/>
  <SLIDER name="" id="6c9229af42a2aa6a" memberName="slider" virtualName=""
          explicitFocusOrder="0" pos="272 38 344 24" min="-64.0" max="64.0"
          int="1.0" style="LinearHorizontal" textBoxPos="NoTextBox" textBoxEditable="1"
          textBoxWidth="80" textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <LABEL name="" id="a814cd8b3a7a385d" memberName="depthLabel" virtualName=""
         explicitFocusOrder="0" pos="400 12 88 24" posRelativeY="c7b94b60aa96c6e2"
         edTextCol="ff000000" edBkgCol="0" labelText="Depth" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.0" kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="" id="dc20d157ffc118c5" memberName="titleLabel" virtualName=""
         explicitFocusOrder="0" pos="18 12 238 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Environment" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="16.0" kerning="0.0" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="Reverb Effect Combo Box" id="486cacdf50ec1ba7" memberName="effectComboBox"
            virtualName="" explicitFocusOrder="0" pos="288 79 316 24" tooltip="Reverb Effect"
            editable="0" layout="33" items="Real Large Hall&#10;Real Medium Hall&#10;Concert Hall"
            textWhenNonSelected="Reverb Effect" textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

