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

#include "VoiceComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...

class VoiceTreeItem : public TreeViewItem
{
public:
	VoiceTreeItem(Voice& voice) : m_voice(&voice), m_title(voice.title) {}
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

    voicesTree.reset (new TreeView ("Voices TreeView"));
    addAndMakeVisible (voicesTree.get());
    voicesTree->setRootItemVisible (false);

    targetGroup.reset (new GroupComponent ("Target Group",
                                           TRANS("Target")));
    addAndMakeVisible (targetGroup.get());
    targetGroup->setTextLabelPosition (Justification::centred);

    leftVoiceButton.reset (new TextButton ("Left Voice Button"));
    addAndMakeVisible (leftVoiceButton.get());
    leftVoiceButton->setButtonText (TRANS("None"));
    leftVoiceButton->addListener (this);

    mainVoiceButton.reset (new TextButton ("Main Voice Button"));
    addAndMakeVisible (mainVoiceButton.get());
    mainVoiceButton->setButtonText (TRANS("Yamaha CFX Grand"));
    mainVoiceButton->addListener (this);

    layerVoiceButton.reset (new TextButton ("Layer Voice Button"));
    addAndMakeVisible (layerVoiceButton.get());
    layerVoiceButton->setButtonText (TRANS("Strings"));
    layerVoiceButton->addListener (this);

    mainTitleButton.reset (new TextButton ("Main Title Button"));
    addAndMakeVisible (mainTitleButton.get());
    mainTitleButton->setButtonText (TRANS("Main"));
    mainTitleButton->addListener (this);

    leftTitleButton.reset (new TextButton ("Left Title Button"));
    addAndMakeVisible (leftTitleButton.get());
    leftTitleButton->setButtonText (TRANS("Left"));
    leftTitleButton->addListener (this);

    layerTitleButton.reset (new TextButton ("Layer Title Button"));
    addAndMakeVisible (layerTitleButton.get());
    layerTitleButton->setButtonText (TRANS("Layer"));
    layerTitleButton->addListener (this);

    leftIndicatorLabel.reset (new Label ("Left Indicator Label",
                                         String()));
    addAndMakeVisible (leftIndicatorLabel.get());
    leftIndicatorLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    leftIndicatorLabel->setJustificationType (Justification::centredLeft);
    leftIndicatorLabel->setEditable (false, false, false);
    leftIndicatorLabel->setColour (Label::backgroundColourId, Colour (0xfeee6c0a));
    leftIndicatorLabel->setColour (TextEditor::textColourId, Colours::black);
    leftIndicatorLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    mainIndicatorLabel.reset (new Label ("Main Indicator Label",
                                         String()));
    addAndMakeVisible (mainIndicatorLabel.get());
    mainIndicatorLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    mainIndicatorLabel->setJustificationType (Justification::centredLeft);
    mainIndicatorLabel->setEditable (false, false, false);
    mainIndicatorLabel->setColour (Label::backgroundColourId, Colour (0xfeee6c0a));
    mainIndicatorLabel->setColour (TextEditor::textColourId, Colours::black);
    mainIndicatorLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    layerIndicatorLabel.reset (new Label ("Layer Indicator Label",
                                          String()));
    addAndMakeVisible (layerIndicatorLabel.get());
    layerIndicatorLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    layerIndicatorLabel->setJustificationType (Justification::centredLeft);
    layerIndicatorLabel->setEditable (false, false, false);
    layerIndicatorLabel->setColour (Label::backgroundColourId, Colour (0xfeee6c0a));
    layerIndicatorLabel->setColour (TextEditor::textColourId, Colours::black);
    layerIndicatorLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    leftMenuButton.reset (new ImageButton ("Left Menu Button"));
    addAndMakeVisible (leftMenuButton.get());
    leftMenuButton->setTooltip (TRANS("Context Menu"));
    leftMenuButton->setButtonText (TRANS("Menu"));
    leftMenuButton->addListener (this);

    leftMenuButton->setImages (false, true, true,
                               ImageCache::getFromMemory (BinaryData::buttoncontextmenu_png, BinaryData::buttoncontextmenu_pngSize), 1.000f, Colour (0x00000000),
                               Image(), 0.750f, Colour (0x00000000),
                               Image(), 1.000f, Colour (0x00000000));
    mainMenuButton.reset (new ImageButton ("Main Menu Button"));
    addAndMakeVisible (mainMenuButton.get());
    mainMenuButton->setTooltip (TRANS("Context Menu"));
    mainMenuButton->setButtonText (TRANS("Menu"));
    mainMenuButton->addListener (this);

    mainMenuButton->setImages (false, true, true,
                               ImageCache::getFromMemory (BinaryData::buttoncontextmenu_png, BinaryData::buttoncontextmenu_pngSize), 1.000f, Colour (0x00000000),
                               Image(), 0.750f, Colour (0x00000000),
                               Image(), 1.000f, Colour (0x00000000));
    layerMenuButton.reset (new ImageButton ("Layer Menu Button"));
    addAndMakeVisible (layerMenuButton.get());
    layerMenuButton->setTooltip (TRANS("Context Menu"));
    layerMenuButton->setButtonText (TRANS("Menu"));
    layerMenuButton->addListener (this);

    layerMenuButton->setImages (false, true, true,
                                ImageCache::getFromMemory (BinaryData::buttoncontextmenu_png, BinaryData::buttoncontextmenu_pngSize), 1.000f, Colour (0x00000000),
                                Image(), 0.750f, Colour (0x00000000),
                                Image(), 1.000f, Colour (0x00000000));

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
    leftMenuButton = nullptr;
    mainMenuButton = nullptr;
    layerMenuButton = nullptr;


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
    leftVoiceButton->setBounds (0 + 16, (-8) + 55, proportionOfWidth (0.3029f), 28);
    mainVoiceButton->setBounds (0 + (getWidth() - 0) / 2 - (proportionOfWidth (0.3029f) / 2), (-8) + 55, proportionOfWidth (0.3029f), 28);
    layerVoiceButton->setBounds (0 + (getWidth() - 0) - 16 - proportionOfWidth (0.3029f), (-8) + 55, proportionOfWidth (0.3029f), 28);
    mainTitleButton->setBounds ((0 + (getWidth() - 0) / 2 - (proportionOfWidth (0.3029f) / 2)) + proportionOfWidth (0.3029f) / 2 - (80 / 2), (-8) + 16, 80, 28);
    leftTitleButton->setBounds ((0 + 16) + proportionOfWidth (0.3029f) / 2 - (80 / 2), (-8) + 16, 80, 28);
    layerTitleButton->setBounds ((0 + (getWidth() - 0) - 16 - proportionOfWidth (0.3029f)) + proportionOfWidth (0.3029f) / 2 - (80 / 2), (-8) + 16, 80, 28);
    leftIndicatorLabel->setBounds (0 + 16, (-8) + 90, roundToInt ((getWidth() - 0) * 0.3029f), 3);
    mainIndicatorLabel->setBounds (0 + (getWidth() - 0) / 2 - ((roundToInt ((getWidth() - 0) * 0.3029f)) / 2), (-8) + 90, roundToInt ((getWidth() - 0) * 0.3029f), 3);
    layerIndicatorLabel->setBounds (0 + (getWidth() - 0) - 16 - (roundToInt ((getWidth() - 0) * 0.3029f)), (-8) + 90, roundToInt ((getWidth() - 0) * 0.3029f), 3);
    leftMenuButton->setBounds ((0 + 16) + 0, 8, 32, 28);
    mainMenuButton->setBounds ((0 + (getWidth() - 0) / 2 - (proportionOfWidth (0.3029f) / 2)) + 0, 8, 32, 28);
    layerMenuButton->setBounds ((0 + (getWidth() - 0) - 16 - proportionOfWidth (0.3029f)) + 0, 8, 32, 28);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void VoiceComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == leftVoiceButton.get())
    {
        //[UserButtonCode_leftVoiceButton] -- add your button handler code here..
        voiceButtonClicked(buttonThatWasClicked);
        //[/UserButtonCode_leftVoiceButton]
    }
    else if (buttonThatWasClicked == mainVoiceButton.get())
    {
        //[UserButtonCode_mainVoiceButton] -- add your button handler code here..
        voiceButtonClicked(buttonThatWasClicked);
        //[/UserButtonCode_mainVoiceButton]
    }
    else if (buttonThatWasClicked == layerVoiceButton.get())
    {
        //[UserButtonCode_layerVoiceButton] -- add your button handler code here..
        voiceButtonClicked(buttonThatWasClicked);
        //[/UserButtonCode_layerVoiceButton]
    }
    else if (buttonThatWasClicked == mainTitleButton.get())
    {
        //[UserButtonCode_mainTitleButton] -- add your button handler code here..
        pianoController.SetActive(PianoController::chMain,
        	!pianoController.GetActive(PianoController::chMain));
        //[/UserButtonCode_mainTitleButton]
    }
    else if (buttonThatWasClicked == leftTitleButton.get())
    {
        //[UserButtonCode_leftTitleButton] -- add your button handler code here..
        pianoController.SetActive(PianoController::chLeft,
        	!pianoController.GetActive(PianoController::chLeft));
        //[/UserButtonCode_leftTitleButton]
    }
    else if (buttonThatWasClicked == layerTitleButton.get())
    {
        //[UserButtonCode_layerTitleButton] -- add your button handler code here..
        pianoController.SetActive(PianoController::chLayer,
        	!pianoController.GetActive(PianoController::chLayer));
        //[/UserButtonCode_layerTitleButton]
    }
    else if (buttonThatWasClicked == leftMenuButton.get())
    {
        //[UserButtonCode_leftMenuButton] -- add your button handler code here..
        showMenu(buttonThatWasClicked, PianoController::chLeft);
        //[/UserButtonCode_leftMenuButton]
    }
    else if (buttonThatWasClicked == mainMenuButton.get())
    {
        //[UserButtonCode_mainMenuButton] -- add your button handler code here..
        showMenu(buttonThatWasClicked, PianoController::chMain);
        //[/UserButtonCode_mainMenuButton]
    }
    else if (buttonThatWasClicked == layerMenuButton.get())
    {
        //[UserButtonCode_layerMenuButton] -- add your button handler code here..
        showMenu(buttonThatWasClicked, PianoController::chLayer);
        //[/UserButtonCode_layerMenuButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void VoiceComponent::PianoStateChanged(PianoController::Aspect aspect, PianoController::Channel channel)
{
	if (aspect == PianoController::apConnection)
	{
		MessageManager::callAsync([=](){updateEnabledControls();});
	}
	else if ((aspect == PianoController::apVoice ||
		aspect == PianoController::apActive ||
		aspect == PianoController::apOctave) &&
		(channel == PianoController::chMain ||
		channel == PianoController::chLayer ||
		channel == PianoController::chLeft))
	{
		MessageManager::callAsync([=](){updateVoiceState();});
	}
}

void VoiceComponent::updateVoiceState()
{
	int octave = pianoController.GetOctave(PianoController::chMain);
	mainTitleButton->setButtonText(String("Main") + (octave == 0 ? "" :
		String(" (") + (octave > 0 ? "+" : "") + String(octave) + ")"));

	octave = pianoController.GetOctave(PianoController::chLayer);
	layerTitleButton->setButtonText(String("Layer") + (octave == 0 ? "" :
		String(" (") + (octave > 0 ? "+" : "") + String(octave) + ")"));

	octave = pianoController.GetOctave(PianoController::chLeft);
	leftTitleButton->setButtonText(String("Left") + (octave == 0 ? "" :
		String(" (") + (octave > 0 ? "+" : "") + String(octave) + ")"));

	mainVoiceButton->setButtonText(Presets::VoiceTitle(pianoController.GetVoice(PianoController::chMain)));
	layerVoiceButton->setButtonText(Presets::VoiceTitle(pianoController.GetVoice(PianoController::chLayer)));
	leftVoiceButton->setButtonText(Presets::VoiceTitle(pianoController.GetVoice(PianoController::chLeft)));

	mainTitleButton->setToggleState(pianoController.GetActive(PianoController::chMain), NotificationType::dontSendNotification);
	layerTitleButton->setToggleState(pianoController.GetActive(PianoController::chLayer), NotificationType::dontSendNotification);
	leftTitleButton->setToggleState(pianoController.GetActive(PianoController::chLeft), NotificationType::dontSendNotification);
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
	PianoController::Channel channel =
		layerIndicatorLabel->isVisible() ? PianoController::chLayer :
		leftIndicatorLabel->isVisible() ? PianoController::chLeft :
		PianoController::chMain;

	pianoController.SetActive(channel, true);
	pianoController.SetVoice(channel, voice->path);
}

void VoiceComponent::voiceButtonClicked(Button* button)
{
	mainIndicatorLabel->setVisible(button == mainVoiceButton.get());
	layerIndicatorLabel->setVisible(button == layerVoiceButton.get());
	leftIndicatorLabel->setVisible(button == leftVoiceButton.get());

	String voice = button == layerVoiceButton.get() ?
		pianoController.GetVoice(PianoController::chLayer) :
		button == leftVoiceButton.get() ? pianoController.GetVoice(PianoController::chLeft) :
		pianoController.GetVoice(PianoController::chMain);

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

void VoiceComponent::showMenu(Button* button, PianoController::Channel channel)
{
	PopupMenu menu;
	menu.addSectionHeader("OCTAVE");
	menu.addItem(100-2, "-2", true, pianoController.GetOctave(channel) == -2);
	menu.addItem(100-1, "-1", true, pianoController.GetOctave(channel) == -1);
	menu.addItem(100-0, " 0", true, pianoController.GetOctave(channel) == 0);
	menu.addItem(100+1, "+1", true, pianoController.GetOctave(channel) == +1);
	menu.addItem(100+2, "+2", true, pianoController.GetOctave(channel) == +2);

	const int result = menu.showAt(button, 0, 0, 0, 35);

	if (100-2 <= result && result <= 100+2)
	{
		int octave = result - 100;
		pianoController.SetOctave(channel, octave);
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
         fontname="Default font" fontsize="15.0" kerning="0.0" bold="0"
         italic="0" justification="33"/>
  <LABEL name="Main Indicator Label" id="236984f4049a87bf" memberName="mainIndicatorLabel"
         virtualName="" explicitFocusOrder="0" pos="0Cc 90 30.295% 3"
         posRelativeX="56427593ca278ddd" posRelativeY="56427593ca278ddd"
         posRelativeW="56427593ca278ddd" bkgCol="feee6c0a" edTextCol="ff000000"
         edBkgCol="0" labelText="" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <LABEL name="Layer Indicator Label" id="66b7f4c6c601497b" memberName="layerIndicatorLabel"
         virtualName="" explicitFocusOrder="0" pos="16Rr 90 30.295% 3"
         posRelativeX="56427593ca278ddd" posRelativeY="56427593ca278ddd"
         posRelativeW="56427593ca278ddd" bkgCol="feee6c0a" edTextCol="ff000000"
         edBkgCol="0" labelText="" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
  <IMAGEBUTTON name="Left Menu Button" id="c87eaad1c0559e4c" memberName="leftMenuButton"
               virtualName="" explicitFocusOrder="0" pos="0 8 32 28" posRelativeX="f4f376ddb622016f"
               posRelativeY="c7b94b60aa96c6e2" tooltip="Context Menu" buttonText="Menu"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="BinaryData::buttoncontextmenu_png" opacityNormal="1.0"
               colourNormal="0" resourceOver="" opacityOver="0.75" colourOver="0"
               resourceDown="" opacityDown="1.0" colourDown="0"/>
  <IMAGEBUTTON name="Main Menu Button" id="d7280e4dca735b29" memberName="mainMenuButton"
               virtualName="" explicitFocusOrder="0" pos="0 8 32 28" posRelativeX="a44dda5da363325"
               posRelativeY="c7b94b60aa96c6e2" tooltip="Context Menu" buttonText="Menu"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="BinaryData::buttoncontextmenu_png" opacityNormal="1.0"
               colourNormal="0" resourceOver="" opacityOver="0.75" colourOver="0"
               resourceDown="" opacityDown="1.0" colourDown="0"/>
  <IMAGEBUTTON name="Layer Menu Button" id="3fc472f3e7ad73d0" memberName="layerMenuButton"
               virtualName="" explicitFocusOrder="0" pos="0 8 32 28" posRelativeX="e72441cfef2070c4"
               posRelativeY="c7b94b60aa96c6e2" tooltip="Context Menu" buttonText="Menu"
               connectedEdges="0" needsCallback="1" radioGroupId="0" keepProportions="1"
               resourceNormal="BinaryData::buttoncontextmenu_png" opacityNormal="1.0"
               colourNormal="0" resourceOver="" opacityOver="0.75" colourOver="0"
               resourceDown="" opacityDown="1.0" colourDown="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

