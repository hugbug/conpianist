/*
 *  This file is part of ConPianist. See <https://github.com/hugbug/conpianist>.
 *
 *  Copyright (C) 2020 Andrey Prygunkov <hugbug@users.sourceforge.net>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "RegistrationMemory.h"
#include "Presets.h"

void RegistrationMemory::Save()
{
	XmlElement state("ConPianistRegistrationMemory");
	root = &state;

	if (options.voices)
	{
		SaveVoice(PianoController::chMain, "Main");
		SaveVoice(PianoController::chLeft, "Left");
		SaveVoice(PianoController::chLayer, "Layer");
		SaveSplitPoint();
	}

	if (options.balance || options.mixer)
	{
		SaveReverbEffect();
	}

	if (options.playback)
	{
		SavePlayback();
	}

	if (options.balance)
	{
		SaveChannel(PianoController::chMain, "Main");
		SaveChannel(PianoController::chLeft, "Left");
		SaveChannel(PianoController::chLayer, "Layer");
		SaveChannel(PianoController::chMidiMaster, "MidiMaster");
		SaveChannel(PianoController::chMic, "Mic");
		SaveChannel(PianoController::chAuxIn, "AuxIn");
	}

	if (options.mixer)
	{
		for (PianoController::Channel ch : PianoController::MidiChannels)
		{
			SaveChannel(ch, String("Midi") + String(ch - PianoController::chMidi0));
		}
	}

	if (options.settings)
	{
		SaveSettings();
	}

	state.writeTo(file);
}

void RegistrationMemory::Load()
{
	std::unique_ptr<XmlElement> savedState = XmlDocument::parse(file);
	if (!savedState) return;

	root = savedState.get();

	if (options.voices)
	{
		LoadVoice(PianoController::chMain, "Main");
		LoadVoice(PianoController::chLeft, "Left");
		LoadVoice(PianoController::chLayer, "Layer");
		LoadSplitPoint();
	}

	if (options.balance || options.mixer)
	{
		LoadReverbEffect();
	}

	if (options.playback)
	{
		LoadPlayback();
	}

	if (options.balance)
	{
		LoadChannel(PianoController::chMain, "Main");
		LoadChannel(PianoController::chLeft, "Left");
		LoadChannel(PianoController::chLayer, "Layer");
		LoadChannel(PianoController::chMidiMaster, "MidiMaster");
		LoadChannel(PianoController::chMic, "Mic");
		LoadChannel(PianoController::chAuxIn, "AuxIn");
	}

	if (options.mixer)
	{
		for (PianoController::Channel ch : PianoController::MidiChannels)
		{
			LoadChannel(ch, String("Midi") + String(ch - PianoController::chMidi0));
		}
	}

	if (options.settings)
	{
		LoadSettings();
	}
}

void RegistrationMemory::SaveChannel(PianoController::Channel channel, String name)
{
	XmlElement* listElement = root->getChildByName("Channels");
	if (!listElement)
	{
		listElement = root->createNewChildElement("Channels");
	}
	XmlElement* chElem = listElement->createNewChildElement(name);
	chElem->createNewChildElement("Active")->addTextElement(pianoController.GetActive(channel) ? "yes" : "no");
	chElem->createNewChildElement("Volume")->addTextElement(String(pianoController.GetVolume(channel)));
	chElem->createNewChildElement("Pan")->addTextElement(String(pianoController.GetPan(channel)));
	chElem->createNewChildElement("Reverb")->addTextElement(String(pianoController.GetReverb(channel)));
}

void RegistrationMemory::LoadChannel(PianoController::Channel channel, String name)
{
	XmlElement* listElement = root->getChildByName("Channels");
	if (!listElement) return;

	XmlElement* chElem = listElement->getChildByName(name);
	if (!chElem) return;

	XmlElement* el;
	if ((el = chElem->getChildByName("Active")) && channel != PianoController::chAuxIn)
	{
		String value = el->getAllSubText();
		pianoController.SetActive(channel, value.equalsIgnoreCase("yes"));
	}
	if ((el = chElem->getChildByName("Volume")))
	{
		int value = el->getAllSubText().getIntValue();
		pianoController.SetVolume(channel, value);
	}
	if ((el = chElem->getChildByName("Pan")))
	{
		int value = el->getAllSubText().getIntValue();
		pianoController.SetPan(channel, value);
	}
	if ((el = chElem->getChildByName("Reverb")))
	{
		int value = el->getAllSubText().getIntValue();
		pianoController.SetReverb(channel, value);
	}
}

void RegistrationMemory::SaveVoice(PianoController::Channel channel, String name)
{
	XmlElement* listElement = root->getChildByName("Voices");
	if (!listElement)
	{
		listElement = root->createNewChildElement("Voices");
	}

	XmlElement* chElem = listElement->createNewChildElement(name);

	String voiceNum = pianoController.GetVoice(channel);
	Voice* voice = Presets::FindVoice(voiceNum);
	chElem->createNewChildElement("Path")->addTextElement(voice ? voice->path : voiceNum);

	chElem->createNewChildElement("Octave")->addTextElement(String(pianoController.GetOctave(channel)));
}

void RegistrationMemory::LoadVoice(PianoController::Channel channel, String name)
{
	XmlElement* listElement = root->getChildByName("Voices");
	if (!listElement) return;

	XmlElement* chElem = listElement->getChildByName(name);
	if (!chElem) return;

	XmlElement* el;
	if ((el = chElem->getChildByName("Path")))
	{
		String value = el->getAllSubText();
		pianoController.SetVoice(channel, value);
	}
	if ((el = chElem->getChildByName("Octave")))
	{
		int value = el->getAllSubText().getIntValue();
		pianoController.SetOctave(channel, value);
	}
}

void RegistrationMemory::SaveSplitPoint()
{
	XmlElement* listElement = root->getChildByName("Voices");
	if (!listElement)
	{
		listElement = root->createNewChildElement("Voices");
	}
	listElement->createNewChildElement("SplitPoint")->addTextElement(String(pianoController.GetSplitPoint()));
}

void RegistrationMemory::LoadSplitPoint()
{
	XmlElement* listElement = root->getChildByName("Voices");
	if (!listElement) return;

	XmlElement* chElem = listElement->getChildByName("SplitPoint");
	if (!chElem) return;

	pianoController.SetSplitPoint(chElem->getAllSubText().getIntValue());
}

void RegistrationMemory::SaveReverbEffect()
{
	XmlElement* listElement = root->getChildByName("PianoRoom");
	if (!listElement)
	{
		listElement = root->createNewChildElement("PianoRoom");
	}
	listElement->createNewChildElement("ReverbEffect")->addTextElement(String(pianoController.GetReverbEffect()));
}

void RegistrationMemory::LoadReverbEffect()
{
	XmlElement* listElement = root->getChildByName("PianoRoom");
	if (!listElement) return;

	XmlElement* chElem = listElement->getChildByName("ReverbEffect");
	if (!chElem) return;

	pianoController.SetReverbEffect(chElem->getAllSubText().getIntValue());
}

void RegistrationMemory::SavePlayback()
{
	XmlElement* listElement = root->getChildByName("Playback");
	if (!listElement)
	{
		listElement = root->createNewChildElement("Playback");
	}
	listElement->createNewChildElement("StreamLights")->addTextElement(pianoController.GetStreamLights() ? "yes" : "no");
	listElement->createNewChildElement("StreamLightsSpeed")->addTextElement(pianoController.GetStreamFast() ? "fast" : "slow");
	listElement->createNewChildElement("Guide")->addTextElement(pianoController.GetGuide() ? "yes" : "no");
	listElement->createNewChildElement("GuideType")->addTextElement(
		pianoController.GetGuideType() == PianoController::gtAnyKey ? "any-key" :
		pianoController.GetGuideType() == PianoController::gtYourTempo ? "your-tempo" :
		"correct-key");
	listElement->createNewChildElement("Tempo")->addTextElement(String(pianoController.GetTempo()));
	listElement->createNewChildElement("Transpose")->addTextElement(String(pianoController.GetTranspose()));
	listElement->createNewChildElement("RightChannel")->addTextElement(
		String(pianoController.GetPartChannel(PianoController::paRight) - PianoController::chMidi0));
	listElement->createNewChildElement("LeftChannel")->addTextElement(
		String(pianoController.GetPartChannel(PianoController::paLeft) - PianoController::chMidi0));
	listElement->createNewChildElement("Right")->addTextElement(pianoController.GetPart(PianoController::paRight) ? "yes" : "no");
	listElement->createNewChildElement("Left")->addTextElement(pianoController.GetPart(PianoController::paLeft) ? "yes" : "no");
	listElement->createNewChildElement("Backing")->addTextElement(pianoController.GetPart(PianoController::paBacking) ? "yes" : "no");
	listElement->createNewChildElement("Position")->addTextElement(
		String(pianoController.GetPosition().measure) + "," + String(pianoController.GetPosition().beat));
	PianoController::Loop loop = pianoController.GetLoop();
	listElement->createNewChildElement("Loop")->addTextElement(
		String(loop.begin.measure) + "," + String(loop.begin.beat) + ":" +
		String(loop.end.measure) + "," + String(loop.end.beat));
}

void RegistrationMemory::LoadPlayback()
{
	XmlElement* listElement = root->getChildByName("Playback");
	if (!listElement) return;

	XmlElement* el;
	if ((el = listElement->getChildByName("StreamLights")))
	{
		String value = el->getAllSubText();
		pianoController.SetStreamLights(value.equalsIgnoreCase("yes"));
	}
	if ((el = listElement->getChildByName("StreamLightsSpeed")))
	{
		String value = el->getAllSubText();
		pianoController.SetStreamFast(value.equalsIgnoreCase("fast"));
	}
	if ((el = listElement->getChildByName("Guide")))
	{
		String value = el->getAllSubText();
		pianoController.SetGuide(value.equalsIgnoreCase("yes"));
	}
	if ((el = listElement->getChildByName("GuideType")))
	{
		String value = el->getAllSubText();
		pianoController.SetGuideType(value.equalsIgnoreCase("any-key") ? PianoController::gtAnyKey :
			value.equalsIgnoreCase("your-tempo") ? PianoController::gtYourTempo :
			PianoController::gtCorrectKey);
	}
	if ((el = listElement->getChildByName("Tempo")))
	{
		int value = el->getAllSubText().getIntValue();
		pianoController.SetTempo(value);
	}
	if ((el = listElement->getChildByName("Transpose")))
	{
		int value = el->getAllSubText().getIntValue();
		pianoController.SetTranspose(value);
	}
	if ((el = listElement->getChildByName("RightChannel")))
	{
		int value = el->getAllSubText().getIntValue();
		pianoController.SetPartChannel(PianoController::paRight, PianoController::Channel(value + PianoController::chMidi0));
	}
	if ((el = listElement->getChildByName("LeftChannel")))
	{
		int value = el->getAllSubText().getIntValue();
		pianoController.SetPartChannel(PianoController::paLeft, PianoController::Channel(value + PianoController::chMidi0));
	}
	if ((el = listElement->getChildByName("Right")))
	{
		String value = el->getAllSubText();
		pianoController.SetPart(PianoController::paRight, value.equalsIgnoreCase("yes"));
	}
	if ((el = listElement->getChildByName("Left")))
	{
		String value = el->getAllSubText();
		pianoController.SetPart(PianoController::paLeft, value.equalsIgnoreCase("yes"));
	}
	if ((el = listElement->getChildByName("Backing")))
	{
		String value = el->getAllSubText();
		pianoController.SetPart(PianoController::paBacking, value.equalsIgnoreCase("yes"));
	}
	if ((el = listElement->getChildByName("Loop")))
	{
		String value = el->getAllSubText();
		int delim = value.indexOf(":");
		if (delim > -1)
		{
			String begin = value.substring(0, delim);
			String end = value.substring(delim + 1);

			delim = begin.indexOf(",");
			if (delim > -1)
			{
				PianoController::Loop loop;
				loop.begin.measure = begin.substring(0, delim).getIntValue();
				loop.begin.beat = begin.substring(delim + 1).getIntValue();

				delim = end.indexOf(",");
				if (delim > -1)
				{
					loop.end.measure = end.substring(0, delim).getIntValue();
					loop.end.beat = end.substring(delim + 1).getIntValue();

					if (loop.begin.measure == 0 && loop.begin.beat == 0 &&
						loop.end.measure == 0 && loop.end.beat == 0)
					{
						pianoController.ResetLoop();
					}
					else
					{
						pianoController.SetLoop(loop);
					}
				}
			}
		}
	}
	if ((el = listElement->getChildByName("Position")))
	{
		String value = el->getAllSubText();
		int delim = value.indexOf(",");
		if (delim > -1)
		{
			int measure = value.substring(0, delim).getIntValue();
			int beat = value.substring(delim + 1).getIntValue();
			pianoController.SetPosition({measure, beat});
		}
	}
}

void RegistrationMemory::SaveSettings()
{
	XmlElement* listElement = root->getChildByName("Settings");
	if (!listElement)
	{
		listElement = root->createNewChildElement("Settings");
	}

	XmlElement* elem = listElement->createNewChildElement("Keyboard");
	elem->createNewChildElement("Visible")->addTextElement(settings.keyboardVisible ? "yes" : "no");
	elem->createNewChildElement("Channel")->addTextElement(String(settings.keyboardChannel));

	elem = listElement->createNewChildElement("Score");
	elem->createNewChildElement("InstrumentNames")->addTextElement(String(
		settings.scoreInstrumentNames == Settings::siHidden ? "hidden" :
		settings.scoreInstrumentNames == Settings::siShort ? "short" :
		settings.scoreInstrumentNames == Settings::siMixed ? "mixed" :
		"full"));
	elem->createNewChildElement("Part")->addTextElement(String(
		settings.scorePart == Settings::spRight ? "right" :
		settings.scorePart == Settings::spLeft ? "left" :
		settings.scorePart == Settings::spRightAndLeft ? "right-and-left" :
		"all"));
	elem->createNewChildElement("ShowMidiChannel")->addTextElement(settings.scoreShowMidiChannel ? "yes" : "no");
}

void RegistrationMemory::LoadSettings()
{
	XmlElement* listElement = root->getChildByName("Settings");
	if (!listElement) return;

	XmlElement* el;

	XmlElement* keyElem = listElement->getChildByName("Keyboard");
	if (keyElem)
	{
		if ((el = keyElem->getChildByName("Visible")))
		{
			String value = el->getAllSubText();
			settings.keyboardVisible = value.equalsIgnoreCase("yes");
		}
		if ((el = keyElem->getChildByName("Channel")))
		{
			int value = el->getAllSubText().getIntValue();
			settings.keyboardChannel = value;
		}
	}

	XmlElement* scoreElem = listElement->getChildByName("Score");
	if (scoreElem)
	{
		if ((el = scoreElem->getChildByName("InstrumentNames")))
		{
			String value = el->getAllSubText();
			settings.scoreInstrumentNames =
				value.equalsIgnoreCase("hidden") ? Settings::siHidden :
				value.equalsIgnoreCase("short") ? Settings::siShort :
				value.equalsIgnoreCase("mixed") ? Settings::siMixed :
				Settings::siFull;
		}
		if ((el = scoreElem->getChildByName("Part")))
		{
			String value = el->getAllSubText();
			settings.scorePart =
				value.equalsIgnoreCase("right") ? Settings::spRight :
				value.equalsIgnoreCase("left") ? Settings::spLeft :
				value.equalsIgnoreCase("right-and-left") ? Settings::spRightAndLeft :
				Settings::spAll;
		}
		if ((el = scoreElem->getChildByName("ShowMidiChannel")))
		{
			String value = el->getAllSubText();
			settings.scoreShowMidiChannel = value.equalsIgnoreCase("yes");
		}
	}

	settings.sendChangeMessage();
}
