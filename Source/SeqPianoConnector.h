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

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "PianoConnector.h"
#include "MidiConnector.h"
#include "PianoMessage.h"

class SeqPianoConnector : public PianoConnector, public MidiConnector::Listener, public Thread
{
public:
	SeqPianoConnector() : Thread("SeqPianoConnector") {}
	~SeqPianoConnector() {}
	void SetMidiConnector(MidiConnector* midiConnector);
	void SendMidiMessage(const MidiMessage& message) override;
	void SendPianoMessage(const PianoMessage& message) override;
	bool IsConnected() override { return m_midiConnector->IsConnected(); }
	void IncomingMidiMessage(const MidiMessage& message) override;
	void SetRepeatInterval(int repeatInterval) { m_repeatInterval = repeatInterval; };
	int GetAttempt() { return m_attempt; }
	void run() override;
	int QueueSize();
	void ClearQueue();

private:
	MidiConnector* m_midiConnector;
	std::deque<MidiMessage> m_queue;
	std::mutex m_mutex;
	MidiMessage m_lastMessage;
	bool m_waitConfirmation = false;
	Time m_lastTime;
	int m_attempt = 0;
	int m_repeatInterval = 5000;

	void ProcessQueue();
	void PrintLog(const String& prefix, const MidiMessage& message);
};
