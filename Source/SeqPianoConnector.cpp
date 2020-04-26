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

#include "../JuceLibraryCode/JuceHeader.h"
#include "SeqPianoConnector.h"
#include "PianoMessage.h"

void SeqPianoConnector::SetMidiConnector(MidiConnector* midiConnector)
{
	m_midiConnector = midiConnector;
	m_midiConnector->SetListener(this);
}

void SeqPianoConnector::SendMidiMessage(const MidiMessage& message)
{
	PrintLog("SEND", message);
	m_midiConnector->SendMessage(message);
}

void SeqPianoConnector::SendPianoMessage(const PianoMessage& message)
{
	MidiMessage midiMessage = MidiMessage::createSysExMessage(
		message.GetSysExData().getData(), (int)message.GetSysExData().getSize());
	SendMidiMessage(midiMessage);
}

void SeqPianoConnector::IncomingMidiMessage(const MidiMessage& message)
{
	PrintLog("RECV", message);

	if (message.isSysEx() &&
		PianoMessage::IsCspMessage(message.getSysExData(), message.getSysExDataSize()))
	{
		PianoMessage pianoMessage(message.getSysExData(), message.getSysExDataSize());
		m_listener->IncomingPianoMessage(pianoMessage);
	}
	else
	{
		m_listener->IncomingMidiMessage(message);
	}
}

void SeqPianoConnector::PrintLog(const String& prefix, const MidiMessage& message)
{
	if (Logger::getCurrentLogger())
	{
		int size = message.getRawDataSize();
		const uint8* data = message.getRawData();
		String text("[MIDI] " + prefix + " " + String::toHexString(data, size, 1) + "  ");
		for (int i = 0; i < size; i++)
		{
			uint8 b = data[i];
			char ch = b >= 32 && b < 128 ? b : '.';
			text += ch;
		}
		Logger::writeToLog(text);
	}
}
