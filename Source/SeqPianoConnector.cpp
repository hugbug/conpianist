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
	std::lock_guard<std::mutex> guard(m_mutex);
	m_midiConnector = midiConnector;
	m_midiConnector->SetListener(this);
}

void SeqPianoConnector::SendMidiMessage(const MidiMessage& message)
{
	PrintLog("ENQUEUE", message);
	std::lock_guard<std::mutex> guard(m_mutex);
	m_queue.push_back(message);
}

void SeqPianoConnector::SendPianoMessage(const PianoMessage& message)
{
	MidiMessage midiMessage = MidiMessage::createSysExMessage(
		message.GetSysExData().getData(), (int)message.GetSysExData().getSize());
	PrintLog("ENQUEUE", midiMessage);
	std::lock_guard<std::mutex> guard(m_mutex);
	m_queue.push_back(midiMessage);
}

void SeqPianoConnector::IncomingMidiMessage(const MidiMessage& message)
{
	PrintLog("RECEIVE", message);

	if (message.isSysEx() &&
		PianoMessage::IsCspMessage(message.getSysExData(), message.getSysExDataSize()))
	{
		PianoMessage pianoMessage(message.getSysExData(), message.getSysExDataSize());
		{
			std::lock_guard<std::mutex> guard(m_mutex);
			if (m_waitConfirmation)
			{
				PianoMessage prevMessage = PianoMessage(m_lastMessage.getSysExData(), m_lastMessage.getSysExDataSize());
				if (prevMessage.GetProperty() == pianoMessage.GetProperty() &&
					prevMessage.GetIndex() == pianoMessage.GetIndex())
				{
					m_waitConfirmation = false;
					PrintLog("CONFIRM", m_lastMessage);
				}
			}
		}
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

void SeqPianoConnector::run()
{
	while (!threadShouldExit())
	{
		ProcessQueue();
		Thread::sleep(1);
	}
}

void SeqPianoConnector::ProcessQueue()
{
	while (true)
	{
		std::lock_guard<std::mutex> guard(m_mutex);
		if (m_waitConfirmation && (Time::getCurrentTime() - m_lastTime).inMilliseconds() > 5000)
		{
			if (m_attempt >= 3)
			{
				Logger::writeToLog("[MIDI] CLEAR STALLED QUEUE");
				for (const MidiMessage& message : m_queue)
				{
					PrintLog("DELETE   " , message);
				}
				m_queue.clear();
				m_waitConfirmation = false;
			}
			else
			{
				PrintLog((m_attempt == 1 ? "REPEAT " : "REPEAT2"), m_lastMessage);
				m_midiConnector->SendMessage(m_lastMessage);
				m_lastTime = Time::getCurrentTime();
				m_attempt++;
			}
		}
		if (m_queue.empty() || m_waitConfirmation)
		{
			return;
		}
		MidiMessage message = m_queue.front();
		m_queue.pop_front();

		PrintLog("SEND   ", message);
		m_midiConnector->SendMessage(message);
		m_waitConfirmation = PianoMessage::IsCspMessage(message.getSysExData(), message.getSysExDataSize());
		if (m_waitConfirmation)
		{
			m_lastMessage = message;
			m_lastTime = Time::getCurrentTime();
			m_attempt = 1;
		}
	}
}

int SeqPianoConnector::QueueSize()
{
	std::lock_guard<std::mutex> guard(m_mutex);
	return (int)m_queue.size();
}

void SeqPianoConnector::ClearQueue()
{
	std::lock_guard<std::mutex> guard(m_mutex);
	m_queue.clear();
	m_waitConfirmation = false;
}
