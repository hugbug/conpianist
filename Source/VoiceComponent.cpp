/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.3.0

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "VoiceComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...

class VoiceTreeItem : public TreeViewItem
{
public:
	VoiceTreeItem(Voice& voice) : m_voice(&voice),
		m_title(VoiceComponent::voiceTitle(m_voice->path)) {}
	VoiceTreeItem(const String& title) : m_title(title) {}

	bool mightContainSubItems() override
	{
		return getNumSubItems() != 0;
	}

	int getItemHeight() const override
	{
		return 28;
	}

	void paintItem(Graphics& g, int width, int height) override
	{
		g.setColour(Colours::white);
		g.drawText(m_title, 8, 0, width - 8, height, Justification::left);
	}

	void itemClicked(const MouseEvent&) override
	{
		if (m_voice)
		{
			((VoiceComponent*)(getOwnerView()->getParentComponent()))->voiceItemClicked(m_voice);
		}
	}

	Voice* m_voice = nullptr;
	String m_title;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(VoiceTreeItem)
};

//[/MiscUserDefs]

//==============================================================================
VoiceComponent::VoiceComponent (PianoController& pianoController)
    : pianoController(pianoController)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (targetGroup = new GroupComponent ("Target Group",
                                                         TRANS("Target")));
    targetGroup->setTextLabelPosition (Justification::centred);

    addAndMakeVisible (mainTitleLabel = new Label ("Main Title Label",
                                                   TRANS("Main\n")));
    mainTitleLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    mainTitleLabel->setJustificationType (Justification::centred);
    mainTitleLabel->setEditable (false, false, false);
    mainTitleLabel->setColour (TextEditor::textColourId, Colours::black);
    mainTitleLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (leftTitlelabel = new Label ("Left Title Label",
                                                   TRANS("Left")));
    leftTitlelabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    leftTitlelabel->setJustificationType (Justification::centred);
    leftTitlelabel->setEditable (false, false, false);
    leftTitlelabel->setColour (TextEditor::textColourId, Colours::black);
    leftTitlelabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (layerTitleLabel = new Label ("Layer Title Label",
                                                    TRANS("Layer")));
    layerTitleLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    layerTitleLabel->setJustificationType (Justification::centred);
    layerTitleLabel->setEditable (false, false, false);
    layerTitleLabel->setColour (TextEditor::textColourId, Colours::black);
    layerTitleLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (voicesTree = new TreeView ("Voices TreeView"));
    voicesTree->setRootItemVisible (false);

    addAndMakeVisible (leftVoiceButton = new TextButton ("Left Voice Button"));
    leftVoiceButton->setButtonText (TRANS("None"));
    leftVoiceButton->addListener (this);

    addAndMakeVisible (mainVoiceButton = new TextButton ("Main Voice Button"));
    mainVoiceButton->setButtonText (TRANS("Yamaha CFX Grand"));
    mainVoiceButton->addListener (this);

    addAndMakeVisible (layerVoiceButton = new TextButton ("Layer Voice Button"));
    layerVoiceButton->setButtonText (TRANS("Strings"));
    layerVoiceButton->addListener (this);

    addAndMakeVisible (leftIndicatorLabel = new Label ("Left Indicator Label",
                                                       String()));
    leftIndicatorLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    leftIndicatorLabel->setJustificationType (Justification::centredLeft);
    leftIndicatorLabel->setEditable (false, false, false);
    leftIndicatorLabel->setColour (Label::backgroundColourId, Colour (0xfeee6c0a));
    leftIndicatorLabel->setColour (TextEditor::textColourId, Colours::black);
    leftIndicatorLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (mainIndicatorLabel = new Label ("Main Indicator Label",
                                                       String()));
    mainIndicatorLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    mainIndicatorLabel->setJustificationType (Justification::centredLeft);
    mainIndicatorLabel->setEditable (false, false, false);
    mainIndicatorLabel->setColour (Label::backgroundColourId, Colour (0xfeee6c0a));
    mainIndicatorLabel->setColour (TextEditor::textColourId, Colours::black);
    mainIndicatorLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (layerIndicatorLabel = new Label ("Layer Indicator Label",
                                                        String()));
    layerIndicatorLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    layerIndicatorLabel->setJustificationType (Justification::centredLeft);
    layerIndicatorLabel->setEditable (false, false, false);
    layerIndicatorLabel->setColour (Label::backgroundColourId, Colour (0xfeee6c0a));
    layerIndicatorLabel->setColour (TextEditor::textColourId, Colours::black);
    layerIndicatorLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    targetGroup->setColour(GroupComponent::outlineColourId, Colours::transparentBlack);
    targetGroup->setText("");

   	voicesTree->setColour(TreeView::ColourIds::selectedItemBackgroundColourId, Colour(0xFEEE6C0A));

    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    buildVoiceTree();
    pianoController.addChangeListener(this);

    leftVoiceButton->getProperties().set("toggle", "yes");
    mainVoiceButton->getProperties().set("toggle", "yes");
    layerVoiceButton->getProperties().set("toggle", "yes");

	mainIndicatorLabel->setVisible(true);
	layerIndicatorLabel->setVisible(false);
	leftIndicatorLabel->setVisible(false);
    //[/Constructor]
}

VoiceComponent::~VoiceComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    targetGroup = nullptr;
    mainTitleLabel = nullptr;
    leftTitlelabel = nullptr;
    layerTitleLabel = nullptr;
    voicesTree = nullptr;
    leftVoiceButton = nullptr;
    mainVoiceButton = nullptr;
    layerVoiceButton = nullptr;
    leftIndicatorLabel = nullptr;
    mainIndicatorLabel = nullptr;
    layerIndicatorLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    delete (VoiceTreeItem*)rootItem;
    //[/Destructor]
}

//==============================================================================
void VoiceComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void VoiceComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    targetGroup->setBounds (0, -8, getWidth() - 0, 90);
    mainTitleLabel->setBounds (0 + (getWidth() - 0) / 2 - (proportionOfWidth (0.3030f) / 2), (-8) + 16, proportionOfWidth (0.3030f), 24);
    leftTitlelabel->setBounds (0 + 16, (-8) + 16, proportionOfWidth (0.3030f), 24);
    layerTitleLabel->setBounds (0 + (getWidth() - 0) - 16 - proportionOfWidth (0.3030f), (-8) + 16, proportionOfWidth (0.3030f), 24);
    voicesTree->setBounds (8, (-8) + 90, getWidth() - 16, getHeight() - 88);
    leftVoiceButton->setBounds (0 + 16, (-8) + 45, proportionOfWidth (0.3030f), 28);
    mainVoiceButton->setBounds (0 + (getWidth() - 0) / 2 - (proportionOfWidth (0.3030f) / 2), (-8) + 45, proportionOfWidth (0.3030f), 28);
    layerVoiceButton->setBounds (0 + (getWidth() - 0) - 16 - proportionOfWidth (0.3030f), (-8) + 45, proportionOfWidth (0.3030f), 28);
    leftIndicatorLabel->setBounds (0 + 16, (-8) + 80, roundToInt ((getWidth() - 0) * 0.3030f), 3);
    mainIndicatorLabel->setBounds (0 + (getWidth() - 0) / 2 - ((roundToInt ((getWidth() - 0) * 0.3030f)) / 2), (-8) + 80, roundToInt ((getWidth() - 0) * 0.3030f), 3);
    layerIndicatorLabel->setBounds (0 + (getWidth() - 0) - 16 - (roundToInt ((getWidth() - 0) * 0.3030f)), (-8) + 80, roundToInt ((getWidth() - 0) * 0.3030f), 3);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void VoiceComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == leftVoiceButton)
    {
        //[UserButtonCode_leftVoiceButton] -- add your button handler code here..
        voiceButtonClicked(buttonThatWasClicked);
        //[/UserButtonCode_leftVoiceButton]
    }
    else if (buttonThatWasClicked == mainVoiceButton)
    {
        //[UserButtonCode_mainVoiceButton] -- add your button handler code here..
        voiceButtonClicked(buttonThatWasClicked);
        //[/UserButtonCode_mainVoiceButton]
    }
    else if (buttonThatWasClicked == layerVoiceButton)
    {
        //[UserButtonCode_layerVoiceButton] -- add your button handler code here..
        voiceButtonClicked(buttonThatWasClicked);
        //[/UserButtonCode_layerVoiceButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void VoiceComponent::changeListenerCallback(ChangeBroadcaster* source)
{
	if (source == &pianoController)
	{
		updateVoiceState();
	}
}

void VoiceComponent::updateVoiceState()
{
	mainVoiceButton->setButtonText(voiceTitle(pianoController.GetVoice(PianoController::vsMain)));
	layerVoiceButton->setButtonText(voiceTitle(pianoController.GetVoice(PianoController::vsLayer)));
	leftVoiceButton->setButtonText(voiceTitle(pianoController.GetVoice(PianoController::vsLeft)));

	mainVoiceButton->setToggleState(pianoController.GetVoiceActive(PianoController::vsMain), NotificationType::dontSendNotification);
	layerVoiceButton->setToggleState(pianoController.GetVoiceActive(PianoController::vsLayer), NotificationType::dontSendNotification);
	leftVoiceButton->setToggleState(pianoController.GetVoiceActive(PianoController::vsLeft), NotificationType::dontSendNotification);
}

String VoiceComponent::voiceTitle(String preset)
{
	int begin = preset.lastIndexOf("/");
	int end = preset.indexOf(".");
	if (begin > -1 && end > -1)
	{
		return preset.substring(begin + 1, end);
	}
	else
	{
		return preset;
	}
}

void VoiceComponent::buildVoiceTree()
{
	voicesTree->setRootItem(rootItem = new VoiceTreeItem(""));

	VoiceTreeItem* category1 = nullptr;
	VoiceTreeItem* category2 = nullptr;
	for (Voice& voice : Presets::Voices())
	{
		if (!category1 || category1->m_title != voice.category1)
		{
			rootItem->addSubItem(category1 = new VoiceTreeItem(voice.category1));
		}

		if (!category2 || category2->m_title != voice.category2)
		{
			category1->addSubItem(category2 = new VoiceTreeItem(voice.category2));
		}

		category2->addSubItem(new VoiceTreeItem(voice));
	}
}

void VoiceComponent::voiceItemClicked(Voice* voice)
{
	PianoController::VoiceSlot slot =
		layerIndicatorLabel->isVisible() ? PianoController::vsLayer :
		leftIndicatorLabel->isVisible() ? PianoController::vsLeft :
		PianoController::vsMain;

	pianoController.SetVoiceActive(slot, true);
	pianoController.SetVoice(slot, voice->path);
}

void VoiceComponent::voiceButtonClicked(Button* button)
{
	if (button == mainVoiceButton && mainIndicatorLabel->isVisible())
	{
		pianoController.SetVoiceActive(PianoController::vsMain, !pianoController.GetVoiceActive(PianoController::vsMain));
	}
	else if (button == layerVoiceButton && layerIndicatorLabel->isVisible())
	{
		pianoController.SetVoiceActive(PianoController::vsLayer, !pianoController.GetVoiceActive(PianoController::vsLayer));
	}
	else if (button == leftVoiceButton && leftIndicatorLabel->isVisible())
	{
		pianoController.SetVoiceActive(PianoController::vsLeft, !pianoController.GetVoiceActive(PianoController::vsLeft));
	}

	mainIndicatorLabel->setVisible(button == mainVoiceButton);
	layerIndicatorLabel->setVisible(button == layerVoiceButton);
	leftIndicatorLabel->setVisible(button == leftVoiceButton);
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="VoiceComponent" componentName=""
                 parentClasses="public Component, public ChangeListener" constructorParams="PianoController&amp; pianoController"
                 variableInitialisers="pianoController(pianoController)" snapPixels="8"
                 snapActive="1" snapShown="1" overlayOpacity="0.330" fixedSize="0"
                 initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff323e44"/>
  <GROUPCOMPONENT name="Target Group" id="56427593ca278ddd" memberName="targetGroup"
                  virtualName="" explicitFocusOrder="0" pos="0 -8 0M 90" title="Target"
                  textpos="36"/>
  <LABEL name="Main Title Label" id="9fa4d9ce58b1b951" memberName="mainTitleLabel"
         virtualName="" explicitFocusOrder="0" pos="0Cc 16 30.295% 24"
         posRelativeX="56427593ca278ddd" posRelativeY="56427593ca278ddd"
         edTextCol="ff000000" edBkgCol="0" labelText="Main&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="36"/>
  <LABEL name="Left Title Label" id="3c4e14578c159f0c" memberName="leftTitlelabel"
         virtualName="" explicitFocusOrder="0" pos="16 16 30.295% 24"
         posRelativeX="56427593ca278ddd" posRelativeY="56427593ca278ddd"
         edTextCol="ff000000" edBkgCol="0" labelText="Left" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="36"/>
  <LABEL name="Layer Title Label" id="1146e54ffb4cf467" memberName="layerTitleLabel"
         virtualName="" explicitFocusOrder="0" pos="16Rr 16 30.295% 24"
         posRelativeX="56427593ca278ddd" posRelativeY="56427593ca278ddd"
         edTextCol="ff000000" edBkgCol="0" labelText="Layer" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="36"/>
  <TREEVIEW name="Voices TreeView" id="5c337882807de41a" memberName="voicesTree"
            virtualName="" explicitFocusOrder="0" pos="8 0R 16M 88M" posRelativeY="56427593ca278ddd"
            rootVisible="0" openByDefault="0"/>
  <TEXTBUTTON name="Left Voice Button" id="f4f376ddb622016f" memberName="leftVoiceButton"
              virtualName="" explicitFocusOrder="0" pos="16 45 30.295% 28"
              posRelativeX="56427593ca278ddd" posRelativeY="56427593ca278ddd"
              buttonText="None" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Main Voice Button" id="a44dda5da363325" memberName="mainVoiceButton"
              virtualName="" explicitFocusOrder="0" pos="0Cc 45 30.295% 28"
              posRelativeX="56427593ca278ddd" posRelativeY="56427593ca278ddd"
              buttonText="Yamaha CFX Grand" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="Layer Voice Button" id="e72441cfef2070c4" memberName="layerVoiceButton"
              virtualName="" explicitFocusOrder="0" pos="16Rr 45 30.295% 28"
              posRelativeX="56427593ca278ddd" posRelativeY="56427593ca278ddd"
              buttonText="Strings" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <LABEL name="Left Indicator Label" id="6dca46264bc44c03" memberName="leftIndicatorLabel"
         virtualName="" explicitFocusOrder="0" pos="16 80 30.295% 3" posRelativeX="56427593ca278ddd"
         posRelativeY="56427593ca278ddd" posRelativeW="56427593ca278ddd"
         bkgCol="feee6c0a" edTextCol="ff000000" edBkgCol="0" labelText=""
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="33"/>
  <LABEL name="Main Indicator Label" id="236984f4049a87bf" memberName="mainIndicatorLabel"
         virtualName="" explicitFocusOrder="0" pos="0Cc 80 30.295% 3"
         posRelativeX="56427593ca278ddd" posRelativeY="56427593ca278ddd"
         posRelativeW="56427593ca278ddd" bkgCol="feee6c0a" edTextCol="ff000000"
         edBkgCol="0" labelText="" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.00000000000000000000"
         kerning="0.00000000000000000000" bold="0" italic="0" justification="33"/>
  <LABEL name="Layer Indicator Label" id="66b7f4c6c601497b" memberName="layerIndicatorLabel"
         virtualName="" explicitFocusOrder="0" pos="16Rr 80 30.295% 3"
         posRelativeX="56427593ca278ddd" posRelativeY="56427593ca278ddd"
         posRelativeW="56427593ca278ddd" bkgCol="feee6c0a" edTextCol="ff000000"
         edBkgCol="0" labelText="" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.00000000000000000000"
         kerning="0.00000000000000000000" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
