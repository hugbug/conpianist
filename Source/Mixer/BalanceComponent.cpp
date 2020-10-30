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
#include "GuiHelper.h"
//[/Headers]

#include "BalanceComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
BalanceComponent::BalanceComponent (Settings& settings, PianoController& pianoController)
    : pianoController(pianoController)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    leftChannel.reset (new ChannelComponent (settings, pianoController, PianoController::chLeft, "Left", true, false, true, false));
    addAndMakeVisible (leftChannel.get());
    mainChannel.reset (new ChannelComponent (settings, pianoController, PianoController::chMain, "Main", false, false, true, false));
    addAndMakeVisible (mainChannel.get());
    layerChannel.reset (new ChannelComponent (settings, pianoController, PianoController::chLayer, "Layer", false, false, true, false));
    addAndMakeVisible (layerChannel.get());
    songChannel.reset (new ChannelComponent (settings, pianoController, PianoController::chMidiMaster, "Song", false, false, true, false));
    addAndMakeVisible (songChannel.get());
    micChannel.reset (new ChannelComponent (settings, pianoController, PianoController::chMic, "Mic", false, false, true, false));
    addAndMakeVisible (micChannel.get());
    auxInChannel.reset (new ChannelComponent (settings, pianoController, PianoController::chAuxIn, "Aux In", false, false, true, false));
    addAndMakeVisible (auxInChannel.get());
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

    effectComboBox->setBounds (74, 176, 176, 24);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (436, 560);


    //[Constructor] You can add your own custom stuff here..
	effectComboBox->clear();
	for (ReverbEffect& re : Presets::ReverbEffects())
	{
		effectComboBox->addItem(re.title, re.num + 1000000);
	}

    pianoController.AddListener(this);
    updateReverbEffectState();
    //[/Constructor]
}

BalanceComponent::~BalanceComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    pianoController.RemoveListener(this);
    //[/Destructor_pre]

    leftChannel = nullptr;
    mainChannel = nullptr;
    layerChannel = nullptr;
    songChannel = nullptr;
    micChannel = nullptr;
    auxInChannel = nullptr;
    effectComboBox = nullptr;


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

    leftChannel->setBounds (8, 0, 70, getHeight() - 0);
    mainChannel->setBounds (78, 0, 70, getHeight() - 0);
    layerChannel->setBounds (148, 0, 70, getHeight() - 0);
    songChannel->setBounds (218, 0, 70, getHeight() - 0);
    micChannel->setBounds (288, 0, 70, getHeight() - 0);
    auxInChannel->setBounds (358, 0, 70, getHeight() - 0);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void BalanceComponent::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == effectComboBox.get())
    {
        //[UserComboBoxCode_effectComboBox] -- add your combo box handling code here..
        pianoController.SetReverbEffect(effectComboBox->getSelectedId() - 1000000);
        //[/UserComboBoxCode_effectComboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void BalanceComponent::updateReverbEffectState()
{
	effectComboBox->setEnabled(pianoController.IsConnected());
	effectComboBox->setSelectedId(pianoController.GetReverbEffect() + 1000000, NotificationType::dontSendNotification);
	if (effectComboBox->getSelectedId() != pianoController.GetReverbEffect() + 1000000)
	{
		effectComboBox->setSelectedItemIndex(-1); // unknown effect
	}
}

void BalanceComponent::showDialog(Settings& settings, PianoController& pianoController)
{
	GuiHelper::ShowModalDialog(new BalanceComponent(settings, pianoController), "Balance");
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
                 constructorParams="Settings&amp; settings, PianoController&amp; pianoController"
                 variableInitialisers="pianoController(pianoController)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="0"
                 initialWidth="436" initialHeight="560">
  <BACKGROUND backgroundColour="ff323e44"/>
  <JUCERCOMP name="Left Channel" id="97f9a699004cae9a" memberName="leftChannel"
             virtualName="" explicitFocusOrder="0" pos="8 0 70 0M" sourceFile="ChannelComponent.cpp"
             constructorParams="settings, pianoController, PianoController::chLeft, &quot;Left&quot;, true, false, true, false"/>
  <JUCERCOMP name="Main Channel" id="74e25a6d700b5cc9" memberName="mainChannel"
             virtualName="" explicitFocusOrder="0" pos="78 0 70 0M" sourceFile="ChannelComponent.cpp"
             constructorParams="settings, pianoController, PianoController::chMain, &quot;Main&quot;, false, false, true, false"/>
  <JUCERCOMP name="Layer Channel" id="ef551064ccb187e2" memberName="layerChannel"
             virtualName="" explicitFocusOrder="0" pos="148 0 70 0M" sourceFile="ChannelComponent.cpp"
             constructorParams="settings, pianoController, PianoController::chLayer, &quot;Layer&quot;, false, false, true, false"/>
  <JUCERCOMP name="Song Channel" id="ea486fd33cd44e31" memberName="songChannel"
             virtualName="" explicitFocusOrder="0" pos="218 0 70 0M" sourceFile="ChannelComponent.cpp"
             constructorParams="settings, pianoController, PianoController::chMidiMaster, &quot;Song&quot;, false, false, true, false"/>
  <JUCERCOMP name="Mic Channel" id="8f4c373ee8ae253f" memberName="micChannel"
             virtualName="" explicitFocusOrder="0" pos="288 0 70 0M" sourceFile="ChannelComponent.cpp"
             constructorParams="settings, pianoController, PianoController::chMic, &quot;Mic&quot;, false, false, true, false"/>
  <JUCERCOMP name="AuxIn Channel" id="7ffff5d33c7b27f" memberName="auxInChannel"
             virtualName="" explicitFocusOrder="0" pos="358 0 70 0M" sourceFile="ChannelComponent.cpp"
             constructorParams="settings, pianoController, PianoController::chAuxIn, &quot;Aux In&quot;, false, false, true, false"/>
  <COMBOBOX name="Reverb Effect Combo Box" id="486cacdf50ec1ba7" memberName="effectComboBox"
            virtualName="" explicitFocusOrder="0" pos="74 176 176 24" tooltip="Reverb Effect"
            editable="0" layout="33" items="Real Large Hall&#10;Real Medium Hall&#10;Concert Hall"
            textWhenNonSelected="Reverb Effect" textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

