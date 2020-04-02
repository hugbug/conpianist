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
#include "Presets.h"
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
    volumeSlider->setColour (Slider::textBoxOutlineColourId, Colour (0x80939d9f));
    volumeSlider->addListener (this);

    panSlider.reset (new Slider ("Pan Slider"));
    addAndMakeVisible (panSlider.get());
    panSlider->setRange (-64, 63, 1);
    panSlider->setSliderStyle (Slider::RotaryHorizontalDrag);
    panSlider->setTextBoxStyle (Slider::TextBoxAbove, false, 50, 20);
    panSlider->setColour (Slider::textBoxHighlightColourId, Colour (0x6642a2c8));
    panSlider->setColour (Slider::textBoxOutlineColourId, Colour (0x80939d9f));
    panSlider->addListener (this);

    panSlider->setBounds (0, 100, 70, 76);

    panLabel.reset (new Label ("Pan Label",
                               TRANS("Pan")));
    addAndMakeVisible (panLabel.get());
    panLabel->setFont (Font (15.40f, Font::plain).withTypefaceStyle ("Regular"));
    panLabel->setJustificationType (Justification::centredLeft);
    panLabel->setEditable (false, false, false);
    panLabel->setColour (TextEditor::textColourId, Colours::black);
    panLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    panLabel->setBounds (0, 68, 70, 24);

    reverbLabel.reset (new Label ("Reverb Label",
                                  TRANS("Reverb")));
    addAndMakeVisible (reverbLabel.get());
    reverbLabel->setFont (Font (15.40f, Font::plain).withTypefaceStyle ("Regular"));
    reverbLabel->setJustificationType (Justification::centredLeft);
    reverbLabel->setEditable (false, false, false);
    reverbLabel->setColour (TextEditor::textColourId, Colours::black);
    reverbLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    reverbLabel->setBounds (0, 174, 70, 24);

    reverbSlider.reset (new Slider ("Reverb Slider"));
    addAndMakeVisible (reverbSlider.get());
    reverbSlider->setRange (0, 127, 1);
    reverbSlider->setSliderStyle (Slider::RotaryHorizontalDrag);
    reverbSlider->setTextBoxStyle (Slider::TextBoxAbove, false, 50, 20);
    reverbSlider->setColour (Slider::textBoxOutlineColourId, Colour (0x80939d9f));
    reverbSlider->addListener (this);

    reverbSlider->setBounds (0, 206, 70, 76);

    volumeLabel.reset (new Label ("Volume Label",
                                  TRANS("Volume")));
    addAndMakeVisible (volumeLabel.get());
    volumeLabel->setFont (Font (15.40f, Font::plain).withTypefaceStyle ("Regular"));
    volumeLabel->setJustificationType (Justification::centredLeft);
    volumeLabel->setEditable (false, false, false);
    volumeLabel->setColour (TextEditor::textColourId, Colours::black);
    volumeLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    volumeLabel->setBounds (0, 282, 70, 24);

    titleButton.reset (new TextButton ("Title Button"));
    addAndMakeVisible (titleButton.get());
    titleButton->setButtonText (String());
    titleButton->addListener (this);

    titleButton->setBounds (2, 8, 66, 52);

    titleLabel.reset (new Label ("Title Label",
                                 TRANS("Ch. 1")));
    addAndMakeVisible (titleLabel.get());
    titleLabel->setFont (Font (15.60f, Font::plain).withTypefaceStyle ("Regular"));
    titleLabel->setJustificationType (Justification::centred);
    titleLabel->setEditable (false, false, false);
    titleLabel->setColour (TextEditor::textColourId, Colours::black);
    titleLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    titleLabel->setBounds (2, 9, 66, 22);

    voiceLabel.reset (new Label ("Voice Label",
                                 TRANS("String Ensemble")));
    addAndMakeVisible (voiceLabel.get());
    voiceLabel->setFont (Font (14.00f, Font::plain).withTypefaceStyle ("Regular"));
    voiceLabel->setJustificationType (Justification::centred);
    voiceLabel->setEditable (false, false, false);
    voiceLabel->setColour (TextEditor::textColourId, Colours::black);
    voiceLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    voiceLabel->setBounds (2, 33, 66, 22);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (70, 560);


    //[Constructor] You can add your own custom stuff here..
    titleButton->getProperties().set("toggle", "yes");
    titleLabel->setText(title, NotificationType::dontSendNotification);
	panLabel->setVisible(showLabels);
	reverbLabel->setVisible(showLabels);
	volumeLabel->setVisible(showLabels);

    titleLabel->addMouseListener(this, false);
    voiceLabel->addMouseListener(this, false);
    panSlider->addMouseListener(this, false);
    reverbSlider->addMouseListener(this, false);
    volumeSlider->addMouseListener(this, false);

    pianoController.AddListener(this);
    updateChannelState(PianoController::apActive);
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
    titleLabel = nullptr;
    voiceLabel = nullptr;


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

    volumeSlider->setBounds (0, 314, 70, getHeight() - 320);
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
        if (pianoController.GetActive(channel))
        {
        	pianoController.SetActive(channel, !pianoController.GetActive(channel));
		}
        //[/UserButtonCode_titleButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void ChannelComponent::updateChannelState(PianoController::Aspect aspect)
{
	bool enabled = pianoController.GetEnabled(channel) && pianoController.IsConnected();
	bool active = pianoController.GetActive(channel);

	titleButton->setEnabled(enabled);
	titleButton->setToggleState(enabled && active, NotificationType::dontSendNotification);

	titleLabel->setEnabled(enabled);

	voiceLabel->setText(enabled ? Presets::VoiceTitle(pianoController.GetVoice(channel)) : "",
		NotificationType::dontSendNotification);
	voiceLabel->setTooltip(voiceLabel->getText());

	panLabel->setEnabled(pianoController.IsConnected());
	reverbLabel->setEnabled(pianoController.IsConnected());
	volumeLabel->setEnabled(pianoController.IsConnected());

	panSlider->setEnabled(enabled && active && canPanAndReverb);
	reverbSlider->setEnabled(enabled && active && canPanAndReverb);
	volumeSlider->setEnabled(enabled && active);

	panSlider->setValue(pianoController.GetPan(channel), NotificationType::dontSendNotification);
	reverbSlider->setValue(pianoController.GetReverb(channel), NotificationType::dontSendNotification);
	volumeSlider->setValue(pianoController.GetVolume(channel), NotificationType::dontSendNotification);
}

void ChannelComponent::mouseDoubleClick(const MouseEvent& event)
{
	if (event.eventComponent == panSlider.get())
	{
		pianoController.ResetPan(channel);
	}
	else if (event.eventComponent == reverbSlider.get())
	{
		pianoController.ResetReverb(channel);
	}
	else if (event.eventComponent == volumeSlider.get())
	{
		pianoController.ResetVolume(channel);
	}
}

void ChannelComponent::mouseDown(const MouseEvent& event)
{
	if (event.eventComponent == titleLabel.get() || event.eventComponent == voiceLabel.get())
	{
        pianoController.SetActive(channel, !pianoController.GetActive(channel));
	}
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
          virtualName="" explicitFocusOrder="0" pos="0 314 70 320M" textboxoutline="80939d9f"
          min="0.0" max="127.0" int="1.0" style="LinearVertical" textBoxPos="TextBoxAbove"
          textBoxEditable="1" textBoxWidth="50" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <SLIDER name="Pan Slider" id="6dc8f196b2d9dabf" memberName="panSlider"
          virtualName="" explicitFocusOrder="0" pos="0 100 70 76" textboxhighlight="6642a2c8"
          textboxoutline="80939d9f" min="-64.0" max="63.0" int="1.0" style="RotaryHorizontalDrag"
          textBoxPos="TextBoxAbove" textBoxEditable="1" textBoxWidth="50"
          textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <LABEL name="Pan Label" id="83fd07e9ba9100c1" memberName="panLabel"
         virtualName="" explicitFocusOrder="0" pos="0 68 70 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Pan" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.4"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="Reverb Label" id="5ba2a16ed7ba194a" memberName="reverbLabel"
         virtualName="" explicitFocusOrder="0" pos="0 174 70 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Reverb" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.4"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <SLIDER name="Reverb Slider" id="ebd0ba792eb80390" memberName="reverbSlider"
          virtualName="" explicitFocusOrder="0" pos="0 206 70 76" textboxoutline="80939d9f"
          min="0.0" max="127.0" int="1.0" style="RotaryHorizontalDrag"
          textBoxPos="TextBoxAbove" textBoxEditable="1" textBoxWidth="50"
          textBoxHeight="20" skewFactor="1.0" needsCallback="1"/>
  <LABEL name="Volume Label" id="3a0483b1c68cf176" memberName="volumeLabel"
         virtualName="" explicitFocusOrder="0" pos="0 282 70 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Volume" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.4"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="Title Button" id="3c4e14578c159f0c" memberName="titleButton"
              virtualName="" explicitFocusOrder="0" pos="2 8 66 52" posRelativeX="f4f376ddb622016f"
              posRelativeY="56427593ca278ddd" buttonText="" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <LABEL name="Title Label" id="8ce81ddb03d15af6" memberName="titleLabel"
         virtualName="" explicitFocusOrder="0" pos="2 9 66 22" edTextCol="ff000000"
         edBkgCol="0" labelText="Ch. 1" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.6"
         kerning="0.0" bold="0" italic="0" justification="36"/>
  <LABEL name="Voice Label" id="f5cfadfb4d3d78c7" memberName="voiceLabel"
         virtualName="" explicitFocusOrder="0" pos="2 33 66 22" edTextCol="ff000000"
         edBkgCol="0" labelText="String Ensemble" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="14.0" kerning="0.0" bold="0" italic="0" justification="36"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

