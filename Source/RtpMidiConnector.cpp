/*
 *  This file is part of ConPianist. See <https://github.com/hugbug/conpianist>.
 *
 *  Copyright (C) 2018 Andrey Prygunkov <hugbug@users.sourceforge.net>
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
#include "AppleMidi.h"
#include "MidiSocket.h"
#include "RtpMidiConnector.h"

class RtpMidi : public appleMidi::AppleMidi_Class<appleMidi::MidiSocket>
{
public:
	RtpMidi(MidiConnector::Listener* listener, bool& connected)
		: m_listener(listener), m_connected(connected) {}
	void CheckConnection();
	void OnActiveSensing(void* sender) override;
	void OnSysEx(void* sender, const byte* data, uint16_t size) override;

private:
	unsigned long m_lastSensing = 0;
	MidiConnector::Listener* m_listener = nullptr;
	bool& m_connected;
	std::vector<byte> m_buf;
};

void RtpMidi::OnActiveSensing(void* sender)
{
	appleMidi::AppleMidi_Class<appleMidi::MidiSocket>::OnActiveSensing(sender);
	m_lastSensing = appleMidi::millis();
	if (!m_connected) Logger::writeToLog("[RTP-MIDI] Connected");
	m_connected = true;
}

void RtpMidi::OnSysEx(void* sender, const byte* data, uint16_t size)
{
	if (!m_listener)
	{
		return;
	}

	if (data[0] == 0xf0 && data[size-1] == 0xf7)
	{
		m_listener->IncomingMidiMessage(MidiMessage::createSysExMessage(data + 1, size - 2));
		m_buf.clear();
		return;
	}

	m_buf.insert(m_buf.end(), data, data + size);

	if (data[size-1] == 0xf7)
	{
		m_listener->IncomingMidiMessage(MidiMessage::createSysExMessage(m_buf.data() + 1, (int)m_buf.size() - 2));
		m_buf.clear();
	}
}

void RtpMidi::CheckConnection()
{
	unsigned long lastTime = Sessions[0].syncronization.lastTime;
	if (lastTime > 0)
	{
		unsigned long delta = appleMidi::millis() - m_lastSensing;
		if (delta > 3000)
		{
			if (m_connected) Logger::writeToLog("[RTP-MIDI] Disconnected");
			DeleteSession(0);
			m_connected = false;
		}
	}
}

void RtpMidiConnector::run()
{
	std::srand((unsigned int)juce::Time::currentTimeMillis());

	appleMidi::IPAddress remoteIp(m_remoteIp.getCharPointer());

	RtpMidi rtpMidi(m_listener, m_connected);
	m_socket = &rtpMidi;

	int port = FindFreePort();
	if (port == 0)
	{
		Logger::writeToLog("[RTP-MIDI] ERROR: could not find free port");
		return;
	}

	Logger::writeToLog("[RTP-MIDI] Starting session on port " + String(port));
	rtpMidi.begin("ConPianist", port);

	while (!threadShouldExit())
	{
		// check connection lost and reinvite
		rtpMidi.CheckConnection();
		if (rtpMidi.GetFreeSessionSlot() == 0)
		{
			Logger::writeToLog("[RTP-MIDI] Inviting");
			rtpMidi.invite(remoteIp);
		}

		// process incoming messages
		rtpMidi.run();
	}
}

int RtpMidiConnector::FindFreePort()
{
	DatagramSocket socket1;
	DatagramSocket socket2;
	int port = 5004;
	while ((!socket1.bindToPort(port) || !socket2.bindToPort(port+1)) && port < 65534)
	{
		port += 2;
	}

	return port >= 65534 ? 0 : port;
}

void RtpMidiConnector::SendMessage(const MidiMessage& message)
{
	RtpMidi* rtpMidi = (RtpMidi*)m_socket;

	if (message.isController())
	{
		rtpMidi->controlChange(message.getControllerNumber(), message.getControllerValue(), message.getChannel());
	}
	else if (message.isSysEx())
	{
		rtpMidi->sysEx(message.getSysExData() - 1, message.getSysExDataSize() + 2);
	}
	else if (message.isNoteOn())
	{
		rtpMidi->noteOn(message.getNoteNumber(), message.getVelocity(), message.getChannel());
	}
	else if (message.isNoteOff())
	{
		rtpMidi->noteOff(message.getNoteNumber(), message.getVelocity(), message.getChannel());
	}
}
