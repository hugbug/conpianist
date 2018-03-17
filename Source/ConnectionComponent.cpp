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

#include "ConnectionComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ConnectionComponent::ConnectionComponent (Settings& settings)
    : settings(settings)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (pianoIpLabel = new Label ("Piano IP Label",
                                                 TRANS("Piano IP Address:")));
    pianoIpLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    pianoIpLabel->setJustificationType (Justification::centredRight);
    pianoIpLabel->setEditable (false, false, false);
    pianoIpLabel->setColour (TextEditor::textColourId, Colours::black);
    pianoIpLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    pianoIpLabel->setBounds (128, 16, 144, 24);

    addAndMakeVisible (pianoIpEdit = new TextEditor ("Piano IP Edit"));
    pianoIpEdit->setMultiLine (false);
    pianoIpEdit->setReturnKeyStartsNewLine (false);
    pianoIpEdit->setReadOnly (false);
    pianoIpEdit->setScrollbarsShown (false);
    pianoIpEdit->setCaretVisible (true);
    pianoIpEdit->setPopupMenuEnabled (true);
    pianoIpEdit->setText (TRANS("192.168.1.235"));

    addAndMakeVisible (midiPortLabel = new Label ("Midi Port Label",
                                                  TRANS("Piano Midi Port:")));
    midiPortLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    midiPortLabel->setJustificationType (Justification::centredRight);
    midiPortLabel->setEditable (false, false, false);
    midiPortLabel->setColour (TextEditor::textColourId, Colours::black);
    midiPortLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    midiPortLabel->setBounds (128, 56, 144, 24);

    addAndMakeVisible (midiPortComboBox = new ComboBox ("Midi Port ComboBox"));
    midiPortComboBox->setEditableText (false);
    midiPortComboBox->setJustificationType (Justification::centredLeft);
    midiPortComboBox->setTextWhenNothingSelected (String());
    midiPortComboBox->setTextWhenNoChoicesAvailable (TRANS("(no choices)"));
    midiPortComboBox->addListener (this);


    //[UserPreSize]
	pianoIpLabel->attachToComponent(pianoIpEdit, true);
	midiPortLabel->attachToComponent(midiPortComboBox, true);

	load();
    //[/UserPreSize]

    setSize (400, 90);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

ConnectionComponent::~ConnectionComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    save();
    //[/Destructor_pre]

    pianoIpLabel = nullptr;
    pianoIpEdit = nullptr;
    midiPortLabel = nullptr;
    midiPortComboBox = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ConnectionComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff323e44));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ConnectionComponent::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    pianoIpEdit->setBounds (proportionOfWidth (0.4000f), 16, 136, 24);
    midiPortComboBox->setBounds (proportionOfWidth (0.4000f), 56, proportionOfWidth (0.5425f), 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void ConnectionComponent::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == midiPortComboBox)
    {
        //[UserComboBoxCode_midiPortComboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_midiPortComboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void ConnectionComponent::save()
{
	auto oldPianoIp = settings.pianoIp;
	auto oldMidiPort = settings.midiPort;

	settings.pianoIp = pianoIpEdit->getText();
	settings.midiPort = midiPortComboBox->getSelectedId() == 1 ? "" : midiPortComboBox->getText();

	if (oldPianoIp != settings.pianoIp || oldMidiPort != settings.midiPort)
	{
		settings.Save();
	}
}

void ConnectionComponent::load()
{
	pianoIpEdit->setText(settings.pianoIp);

	midiPortComboBox->addItem("Connect via Network", 1);

	StringArray ports = MidiInput::getDevices();
	midiPortComboBox->addItemList(ports, 2);

	if (settings.midiPort == "")
	{
		midiPortComboBox->setSelectedId(1);
	}
	else
	{
		int ind = ports.indexOf(settings.midiPort);
		if (ind > -1)
		{
			midiPortComboBox->setSelectedId(ind + 2);
		}
	}
}

void ConnectionComponent::showDialog(Settings& settings)
{
	DialogWindow::LaunchOptions dialog;
	dialog.content.setOwned(new ConnectionComponent(settings));
	dialog.dialogTitle = "Connection Settings";
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

<JUCER_COMPONENT documentType="Component" className="ConnectionComponent" componentName=""
                 parentClasses="public Component" constructorParams="Settings&amp; settings"
                 variableInitialisers="settings(settings)" snapPixels="8" snapActive="1"
                 snapShown="1" overlayOpacity="0.330" fixedSize="0" initialWidth="400"
                 initialHeight="90">
  <BACKGROUND backgroundColour="ff323e44"/>
  <LABEL name="Piano IP Label" id="a2bb47b511220552" memberName="pianoIpLabel"
         virtualName="" explicitFocusOrder="0" pos="128 16 144 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Piano IP Address:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="34"/>
  <TEXTEDITOR name="Piano IP Edit" id="83358b622e96ec09" memberName="pianoIpEdit"
              virtualName="" explicitFocusOrder="0" pos="39.972% 16 136 24"
              initialText="192.168.1.235" multiline="0" retKeyStartsLine="0"
              readonly="0" scrollbars="0" caret="1" popupmenu="1"/>
  <LABEL name="Midi Port Label" id="75ce146a83116b83" memberName="midiPortLabel"
         virtualName="" explicitFocusOrder="0" pos="128 56 144 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Piano Midi Port:" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15.00000000000000000000" kerning="0.00000000000000000000"
         bold="0" italic="0" justification="34"/>
  <COMBOBOX name="Midi Port ComboBox" id="d5a3cb7506a2d491" memberName="midiPortComboBox"
            virtualName="" explicitFocusOrder="0" pos="39.972% 56 54.278% 24"
            editable="0" layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
