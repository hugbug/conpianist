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

#include "ChannelComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ChannelComponent::ChannelComponent (PianoController& pianoController, PianoController::Channel channel, String title, bool showLabels, bool canPanAndReverb)
    : pianoController(pianoController), channel(channel), title(title),  canPanAndReverb(canPanAndReverb)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    volumeSlider.reset (new Slider ("Volume Slider"));
    addAndMakeVisible (volumeSlider.get());
    volumeSlider->setRange (0, 127, 1);
    volumeSlider->setSliderStyle (Slider::LinearVertical);
    volumeSlider->setTextBoxStyle (Slider::TextBoxAbove, false, 50, 20);
    volumeSlider->addListener (this);

    panSlider.reset (new Slider ("Pan Slider"));
    addAndMakeVisible (panSlider.get());
    panSlider->setRange (-64, 63, 1);
    panSlider->setSliderStyle (Slider::RotaryHorizontalDrag);
    panSlider->setTextBoxStyle (Slider::TextBoxAbove, false, 50, 20);
    panSlider->addListener (this);

    panSlider->setBounds (0, 80, 70, 76);

    panLabel.reset (new Label ("Pan Label",
                               TRANS("Pan")));
    addAndMakeVisible (panLabel.get());
    panLabel->setFont (Font (15.40f, Font::plain).withTypefaceStyle ("Regular"));
    panLabel->setJustificationType (Justification::centredLeft);
    panLabel->setEditable (false, false, false);
    panLabel->setColour (TextEditor::textColourId, Colours::black);
    panLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    panLabel->setBounds (0, 52, 70, 24);

    reverbLabel.reset (new Label ("Reverb Label",
                                  TRANS("Reverb")));
    addAndMakeVisible (reverbLabel.get());
    reverbLabel->setFont (Font (15.40f, Font::plain).withTypefaceStyle ("Regular"));
    reverbLabel->setJustificationType (Justification::centredLeft);
    reverbLabel->setEditable (false, false, false);
    reverbLabel->setColour (TextEditor::textColourId, Colours::black);
    reverbLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    reverbLabel->setBounds (0, 160, 70, 24);

    reverbSlider.reset (new Slider ("Reverb Slider"));
    addAndMakeVisible (reverbSlider.get());
    reverbSlider->setRange (0, 127, 1);
    reverbSlider->setSliderStyle (Slider::RotaryHorizontalDrag);
    reverbSlider->setTextBoxStyle (Slider::TextBoxAbove, false, 50, 20);
    reverbSlider->addListener (this);

    reverbSlider->setBounds (0, 188, 70, 76);

    volumeLabel.reset (new Label ("Volume Label",
                                  TRANS("Volume")));
    addAndMakeVisible (volumeLabel.get());
    volumeLabel->setFont (Font (15.40f, Font::plain).withTypefaceStyle ("Regular"));
    volumeLabel->setJustificationType (Justification::centredLeft);
    volumeLabel->setEditable (false, false, false);
    volumeLabel->setColour (TextEditor::textColourId, Colours::black);
    volumeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    volumeLabel->setBounds (0, 272, 70, 24);

    titleButton.reset (new TextButton ("Title Button"));
    addAndMakeVisible (titleButton.get());
    titleButton->setButtonText (TRANS("Ch. 1"));
    titleButton->addListener (this);

    titleButton->setBounds (2, 8, 66, 28);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (70, 560);


    //[Constructor] You can add your own custom stuff here..
    titleButton->getProperties().set("toggle", "yes");
    titleButton->setButtonText(title);
	panLabel->setVisible(showLabels);
	reverbLabel->setVisible(showLabels);
	volumeLabel->setVisible(showLabels);

    pianoController.AddListener(this);
    updateSongState();
    //[/Constructor]
}

ChannelComponent::~ChannelComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    pianoController.RemoveListener(this);
    //[/Destructor_pre]

    volumeSlider = nullptr;
    panSlider = nullptr;
    panLabel = nullptr;
    reverbLabel = nullptr;
    reverbSlider = nullptr;
    volumeLabel = nullptr;
    titleButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ChannelComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ChannelComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    volumeSlider->setBounds (0, 300, 70, getHeight() - 301);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ChannelComponent::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == volumeSlider.get())
    {
        //[UserSliderCode_volumeSlider] -- add your slider handling code here..
		pianoController.SetVolume(channel, volumeSlider->getValue());
        //[/UserSliderCode_volumeSlider]
    }
    else if (sliderThatWasMoved == panSlider.get())
    {
        //[UserSliderCode_panSlider] -- add your slider handling code here..
		pianoController.SetPan(channel, panSlider->getValue());
        //[/UserSliderCode_panSlider]
    }
    else if (sliderThatWasMoved == reverbSlider.get())
    {
        //[UserSliderCode_reverbSlider] -- add your slider handling code here..
		pianoController.SetReverb(channel, reverbSlider->getValue());
        //[/UserSliderCode_reverbSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void ChannelComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == titleButton.get())
    {
        //[UserButtonCode_titleButton] -- add your button handler code here..
        pianoController.SetActive(channel, !pianoController.GetActive(channel));
        //[/UserButtonCode_titleButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void ChannelComponent::updateSongState()
{
	titleButton->setToggleState(pianoController.GetActive(channel), NotificationType::dontSendNotification);

	panSlider->setEnabled(pianoController.GetActive(channel) && canPanAndReverb);
	reverbSlider->setEnabled(pianoController.GetActive(channel) && canPanAndReverb);
	volumeSlider->setEnabled(pianoController.GetActive(channel));

	panSlider->setValue(pianoController.GetPan(channel), NotificationType::dontSendNotification);
	reverbSlider->setValue(pianoController.GetReverb(channel), NotificationType::dontSendNotification);
	volumeSlider->setValue(pianoController.GetVolume(channel), NotificationType::dontSendNotification);

	panSlider->setColour(Slider::thumbColourId, Colour(panSlider->isEnabled() ? 0xFF42A2A8 : 0xFF48626D));
	reverbSlider->setColour(Slider::thumbColourId, Colour(reverbSlider->isEnabled() ? 0xFF42A2A8 : 0xFF48626D));
	volumeSlider->setColour(Slider::thumbColourId, Colour(volumeSlider->isEnabled() ? 0xFF42A2A8 : 0xFF48626D));
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ChannelComponent" componentName=""
                 parentClasses="public Component, public PianoController::Listener"
                 constructorParams="PianoController&amp; pianoController, PianoController::Channel channel, String title, bool showLabels, bool canPanAndReverb"
                 variableInitialisers="pianoController(pianoController), channel(channel), title(title),  canPanAndReverb(canPanAndReverb)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="70" initialHeight="560">
  <BACKGROUND backgroundColour="ff323e44"/>
  <SLIDER name="Volume Slider" id="9ebc7097d295b7c9" memberName="volumeSlider"
          virtualName="" explicitFocusOrder="0" pos="0 300 70 301M" min="0.0"
          max="127.0" int="1.0" style="LinearVertical" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="50" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="Pan Slider" id="6dc8f196b2d9dabf" memberName="panSlider"
          virtualName="" explicitFocusOrder="0" pos="0 80 70 76" min="-64.0"
          max="63.0" int="1.0" style="RotaryHorizontalDrag" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="50" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="Pan Label" id="83fd07e9ba9100c1" memberName="panLabel"
         virtualName="" explicitFocusOrder="0" pos="0 52 70 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Pan" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.4"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="Reverb Label" id="5ba2a16ed7ba194a" memberName="reverbLabel"
         virtualName="" explicitFocusOrder="0" pos="0 160 70 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Reverb" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.4"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="Reverb Slider" id="ebd0ba792eb80390" memberName="reverbSlider"
          virtualName="" explicitFocusOrder="0" pos="0 188 70 76" min="0.0"
          max="127.0" int="1.0" style="RotaryHorizontalDrag" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="50" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="Volume Label" id="3a0483b1c68cf176" memberName="volumeLabel"
         virtualName="" explicitFocusOrder="0" pos="0 272 70 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Volume" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.4"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="Title Button" id="3c4e14578c159f0c" memberName="titleButton"
              virtualName="" explicitFocusOrder="0" pos="2 8 66 28" posRelativeX="f4f376ddb622016f"
              posRelativeY="56427593ca278ddd" buttonText="Ch. 1" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

