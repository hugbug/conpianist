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
		int offset = 8;
		if (m_voice)
		{
			g.setColour(isSelected() && getOwnerView()->isEnabled() ? Colours::white : Colours::grey);
			g.drawRoundedRectangle(offset, 6, 45, height - 12, 2, 1);
			g.setFont(10);
			g.drawText(m_voice->type, offset, 0, 45, height, Justification::centred);
			offset += 55;
		}

		g.setColour(getOwnerView()->isEnabled() ? Colours::white : Colours::grey);
		g.setFont(16);
		g.drawText(m_title, offset, 0, width - offset, height, Justification::left);
	}

    void paintOpenCloseButton(Graphics& g, const Rectangle<float>& area,
		Colour backgroundColour, bool isMouseOver) override
	{
		Path p;
		p.addTriangle (0.0f, 0.0f, 1.0f, isOpen() ? 0.0f : 0.5f, isOpen() ? 0.5f : 0.0f, 1.0f);

		g.setColour(getOwnerView()->isEnabled() ? Colour(0xFFB0B0B0) : Colours::grey);
		g.fillPath(p, p.getTransformToScaleToFit(area.reduced (4, area.getHeight() / 4), true));
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

    addAndMakeVisible (voicesTree = new TreeView ("Voices TreeView"));
    voicesTree->setRootItemVisible (false);

    addAndMakeVisible (targetGroup = new GroupComponent ("Target Group",
                                                         TRANS("Target")));
    targetGroup->setTextLabelPosition (Justification::centred);

    addAndMakeVisible (leftVoiceButton = new TextButton ("Left Voice Button"));
    leftVoiceButton->setButtonText (TRANS("None"));
    leftVoiceButton->addListener (this);

    addAndMakeVisible (mainVoiceButton = new TextButton ("Main Voice Button"));
    mainVoiceButton->setButtonText (TRANS("Yamaha CFX Grand"));
    mainVoiceButton->addListener (this);

    addAndMakeVisible (layerVoiceButton = new TextButton ("Layer Voice Button"));
    layerVoiceButton->setButtonText (TRANS("Strings"));
    layerVoiceButton->addListener (this);

    addAndMakeVisible (mainTitleButton = new TextButton ("Main Title Button"));
    mainTitleButton->setButtonText (TRANS("Main"));
    mainTitleButton->addListener (this);

    addAndMakeVisible (leftTitleButton = new TextButton ("Left Title Button"));
    leftTitleButton->setButtonText (TRANS("Left"));
    leftTitleButton->addListener (this);

    addAndMakeVisible (layerTitleButton = new TextButton ("Layer Title Button"));
    layerTitleButton->setButtonText (TRANS("Layer"));
    layerTitleButton->addListener (this);

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
	updateEnabledControls();
    buildVoiceTree();
    pianoController.AddListener(this);

    leftTitleButton->getProperties().set("toggle", "yes");
    mainTitleButton->getProperties().set("toggle", "yes");
    layerTitleButton->getProperties().set("toggle", "yes");

	mainIndicatorLabel->setVisible(true);
	layerIndicatorLabel->setVisible(false);
	leftIndicatorLabel->setVisible(false);
    //[/Constructor]
}

VoiceComponent::~VoiceComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    voicesTree = nullptr;
    targetGroup = nullptr;
    leftVoiceButton = nullptr;
    mainVoiceButton = nullptr;
    layerVoiceButton = nullptr;
    mainTitleButton = nullptr;
    leftTitleButton = nullptr;
    layerTitleButton = nullptr;
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

    voicesTree->setBounds (8, (-8) + 104, getWidth() - 16, getHeight() - 98);
    targetGroup->setBounds (0, -8, getWidth() - 0, 104);
    leftVoiceButton->setBounds (0 + 16, (-8) + 55, proportionOfWidth (0.3030f), 28);
    mainVoiceButton->setBounds (0 + (getWidth() - 0) / 2 - (proportionOfWidth (0.3030f) / 2), (-8) + 55, proportionOfWidth (0.3030f), 28);
    layerVoiceButton->setBounds (0 + (getWidth() - 0) - 16 - proportionOfWidth (0.3030f), (-8) + 55, proportionOfWidth (0.3030f), 28);
    mainTitleButton->setBounds ((0 + (getWidth() - 0) / 2 - (proportionOfWidth (0.3030f) / 2)) + proportionOfWidth (0.3030f) / 2 - (80 / 2), (-8) + 16, 80, 28);
    leftTitleButton->setBounds ((0 + 16) + proportionOfWidth (0.3030f) / 2 - (80 / 2), (-8) + 16, 80, 28);
    layerTitleButton->setBounds ((0 + (getWidth() - 0) - 16 - proportionOfWidth (0.3030f)) + proportionOfWidth (0.3030f) / 2 - (80 / 2), (-8) + 16, 80, 28);
    leftIndicatorLabel->setBounds (0 + 16, (-8) + 90, roundToInt ((getWidth() - 0) * 0.3030f), 3);
    mainIndicatorLabel->setBounds (0 + (getWidth() - 0) / 2 - ((roundToInt ((getWidth() - 0) * 0.3030f)) / 2), (-8) + 90, roundToInt ((getWidth() - 0) * 0.3030f), 3);
    layerIndicatorLabel->setBounds (0 + (getWidth() - 0) - 16 - (roundToInt ((getWidth() - 0) * 0.3030f)), (-8) + 90, roundToInt ((getWidth() - 0) * 0.3030f), 3);
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
    else if (buttonThatWasClicked == mainTitleButton)
    {
        //[UserButtonCode_mainTitleButton] -- add your button handler code here..
        pianoController.SetVoiceActive(PianoController::vsMain, !pianoController.GetVoiceActive(PianoController::vsMain));
        //[/UserButtonCode_mainTitleButton]
    }
    else if (buttonThatWasClicked == leftTitleButton)
    {
        //[UserButtonCode_leftTitleButton] -- add your button handler code here..
        pianoController.SetVoiceActive(PianoController::vsLeft, !pianoController.GetVoiceActive(PianoController::vsLeft));
        //[/UserButtonCode_leftTitleButton]
    }
    else if (buttonThatWasClicked == layerTitleButton)
    {
        //[UserButtonCode_layerTitleButton] -- add your button handler code here..
        pianoController.SetVoiceActive(PianoController::vsLayer, !pianoController.GetVoiceActive(PianoController::vsLayer));
        //[/UserButtonCode_layerTitleButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void VoiceComponent::updateVoiceState()
{
	mainVoiceButton->setButtonText(voiceTitle(pianoController.GetVoice(PianoController::vsMain)));
	layerVoiceButton->setButtonText(voiceTitle(pianoController.GetVoice(PianoController::vsLayer)));
	leftVoiceButton->setButtonText(voiceTitle(pianoController.GetVoice(PianoController::vsLeft)));

	mainTitleButton->setToggleState(pianoController.GetVoiceActive(PianoController::vsMain), NotificationType::dontSendNotification);
	layerTitleButton->setToggleState(pianoController.GetVoiceActive(PianoController::vsLayer), NotificationType::dontSendNotification);
	leftTitleButton->setToggleState(pianoController.GetVoiceActive(PianoController::vsLeft), NotificationType::dontSendNotification);

	updateEnabledControls();
}

String VoiceComponent::voiceTitle(String preset)
{
	int begin = preset.lastIndexOf("/");
	int end = preset.indexOf(begin, ".");
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
	mainIndicatorLabel->setVisible(button == mainVoiceButton);
	layerIndicatorLabel->setVisible(button == layerVoiceButton);
	leftIndicatorLabel->setVisible(button == leftVoiceButton);

	String voice = button == layerVoiceButton ?
		pianoController.GetVoice(PianoController::vsLayer) :
		button == leftVoiceButton ? pianoController.GetVoice(PianoController::vsLeft) :
		pianoController.GetVoice(PianoController::vsMain);

	scrollToVoice(voice);
}

void VoiceComponent::scrollToVoice(const String& preset)
{
	struct Traversal // a trick to decalre local function
	{
		static VoiceTreeItem* Find(TreeViewItem* item, const String& preset)
		{
			for (int i = 0; i < item->getNumSubItems(); i++)
			{
				VoiceTreeItem* sub = (VoiceTreeItem*)item->getSubItem(i);
				if (sub->getNumSubItems() > 0)
				{
					VoiceTreeItem* ret = Find(sub, preset);
					if (ret)
					{
						return ret;
					}
				}
				if (sub->m_voice && preset == sub->m_voice->path)
				{
					return sub;
				}
			}
			return nullptr;
		}

		static void CollapseAll(TreeViewItem* item)
		{
			for (int i = 0; i < item->getNumSubItems(); i++)
			{
				VoiceTreeItem* sub = (VoiceTreeItem*)item->getSubItem(i);
				if (sub->getNumSubItems() > 0)
				{
					sub->setOpen(false);
					CollapseAll(sub);
				}
			}
		}
	};

	Traversal::CollapseAll(voicesTree->getRootItem());

	VoiceTreeItem* voiceItem = Traversal::Find(voicesTree->getRootItem(), preset);
	if (voiceItem)
	{
		for (TreeViewItem* node = voiceItem; node; node = node->getParentItem())
		{
			node->setOpen(true);
		}
		voiceItem->setSelected(true, true);
		voicesTree->scrollToKeepItemVisible(voiceItem);
	}
}

void VoiceComponent::updateEnabledControls()
{
	for (Component* co : getChildren())
	{
		co->setEnabled(pianoController.IsConnected());
	}
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="VoiceComponent" componentName=""
                 parentClasses="public Component, public PianoController::Listener"
                 constructorParams="PianoController&amp; pianoController" variableInitialisers="pianoController(pianoController)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff323e44"/>
  <TREEVIEW name="Voices TreeView" id="5c337882807de41a" memberName="voicesTree"
            virtualName="" explicitFocusOrder="0" pos="8 0R 16M 98M" posRelativeY="56427593ca278ddd"
            rootVisible="0" openByDefault="0"/>
  <GROUPCOMPONENT name="Target Group" id="56427593ca278ddd" memberName="targetGroup"
                  virtualName="" explicitFocusOrder="0" pos="0 -8 0M 104" title="Target"
                  textpos="36"/>
  <TEXTBUTTON name="Left Voice Button" id="f4f376ddb622016f" memberName="leftVoiceButton"
              virtualName="" explicitFocusOrder="0" pos="16 55 30.295% 28"
              posRelativeX="56427593ca278ddd" posRelativeY="56427593ca278ddd"
              buttonText="None" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Main Voice Button" id="a44dda5da363325" memberName="mainVoiceButton"
              virtualName="" explicitFocusOrder="0" pos="0Cc 55 30.295% 28"
              posRelativeX="56427593ca278ddd" posRelativeY="56427593ca278ddd"
              buttonText="Yamaha CFX Grand" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="Layer Voice Button" id="e72441cfef2070c4" memberName="layerVoiceButton"
              virtualName="" explicitFocusOrder="0" pos="16Rr 55 30.295% 28"
              posRelativeX="56427593ca278ddd" posRelativeY="56427593ca278ddd"
              buttonText="Strings" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Main Title Button" id="9fa4d9ce58b1b951" memberName="mainTitleButton"
              virtualName="" explicitFocusOrder="0" pos="0Cc 16 80 28" posRelativeX="a44dda5da363325"
              posRelativeY="56427593ca278ddd" buttonText="Main" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Left Title Button" id="3c4e14578c159f0c" memberName="leftTitleButton"
              virtualName="" explicitFocusOrder="0" pos="0Cc 16 80 28" posRelativeX="f4f376ddb622016f"
              posRelativeY="56427593ca278ddd" buttonText="Left" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="Layer Title Button" id="1146e54ffb4cf467" memberName="layerTitleButton"
              virtualName="" explicitFocusOrder="0" pos="0Cc 16 80 28" posRelativeX="e72441cfef2070c4"
              posRelativeY="56427593ca278ddd" buttonText="Layer" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <LABEL name="Left Indicator Label" id="6dca46264bc44c03" memberName="leftIndicatorLabel"
         virtualName="" explicitFocusOrder="0" pos="16 90 30.295% 3" posRelativeX="56427593ca278ddd"
         posRelativeY="56427593ca278ddd" posRelativeW="56427593ca278ddd"
         bkgCol="feee6c0a" edTextCol="ff000000" edBkgCol="0" labelText=""
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="33"/>
  <LABEL name="Main Indicator Label" id="236984f4049a87bf" memberName="mainIndicatorLabel"
         virtualName="" explicitFocusOrder="0" pos="0Cc 90 30.295% 3"
         posRelativeX="56427593ca278ddd" posRelativeY="56427593ca278ddd"
         posRelativeW="56427593ca278ddd" bkgCol="feee6c0a" edTextCol="ff000000"
         edBkgCol="0" labelText="" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.00000000000000000000"
         kerning="0.00000000000000000000" bold="0" italic="0" justification="33"/>
  <LABEL name="Layer Indicator Label" id="66b7f4c6c601497b" memberName="layerIndicatorLabel"
         virtualName="" explicitFocusOrder="0" pos="16Rr 90 30.295% 3"
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
