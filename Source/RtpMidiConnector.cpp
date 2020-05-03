/*
 *  This file is part of ConPianist. See <https://github.com/hugbug/conpianist>.
 *
 *  Copyright (C) 2018-2020 Andrey Prygunkov <hugbug@users.sourceforge.net>
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
#include "RtpMidiConnector.h"

#define APPLEMIDI_INITIATOR
#include "AppleMIDI.h"
#include "MidiSocket.h"

struct MidiSettings
{
	/*! Running status enables short messages when sending multiple values
	of the same type and channel.\n
	Must be disabled to send USB MIDI messages to a computer
	Warning: does not work with some hardware, enable with caution.
	*/
	static const bool UseRunningStatus = false;

	/*! NoteOn with 0 velocity should be handled as NoteOf.\n
	Set to true  to get NoteOff events when receiving null-velocity NoteOn messages.\n
	Set to false to get NoteOn  events when receiving null-velocity NoteOn messages.
	*/
	static const bool HandleNullVelocityNoteOnAsNoteOff = true;

	/*! Setting this to true will make MIDI.read parse only one byte of data for each
	call when data is available. This can speed up your application if receiving
	a lot of traffic, but might induce MIDI Thru and treatment latency.
	*/
	static const bool Use1ByteParsing = false;

	/*! Maximum size of SysEx receivable. Decrease to save RAM if you don't expect
	to receive SysEx, or adjust accordingly.
	*/
	static const unsigned SysExMaxSize = 1024;

	/*! Global switch to turn on/off sender ActiveSensing
	Set to true to send ActiveSensing
	Set to false will not send ActiveSensing message (will also save memory)
	*/
	static const bool UseSenderActiveSensing = false;

	/*! Global switch to turn on/off receiver ActiveSensing
	Set to true to check for message timeouts (via ErrorCallback)
	Set to false will not check if chained device are still alive (if they use ActiveSensing) (will also save memory)
	*/
	static const bool UseReceiverActiveSensing = true;

	/*! Active Sensing is intended to be sent
	repeatedly by the sender to tell the receiver that a connection is alive. Use
	of this message is optional. When initially received, the
	receiver will expect to receive another Active Sensing
	message each 300ms (max), and if it does not then it will
	assume that the connection has been terminated. At
	termination, the receiver will turn off all voices and return to
	normal (non- active sensing) operation.

	Typical value is 250 (ms) - an Active Sensing command is send every 250ms.
	(All Roland devices send Active Sensing every 250ms)

	Setting this field to 0 will disable sending MIDI active sensing.
	*/
	static const uint16_t SenderActiveSensingPeriodicity = 250;
};

struct MidiPlatform
{
   static unsigned long now() { return appleMidi::millis(); };
};

struct RtpMidiSettings
{
    static const size_t UdpTxPacketMaxSize = 1024*4;

	static const size_t MaxBufferSize = 1024*4;

	static const size_t MaxSessionNameLen = 24;

	static const uint8_t MaxNumberOfParticipants = 2;

	// The recovery journal mechanism requires that the receiver periodically
	// inform the sender of the sequence number of the most recently received packet.
	// This allows the sender to reduce the size of the recovery journal, to encapsulate
	// only those changes to the MIDI stream state occurring after the specified packet number.
	//
	// Each partner then sends cyclically to the other partner the RS message, indicating
	// the last sequence number received correctly, in other words, without any gap between
	// two sequence numbers. The sender can then free the memory containing old journalling data if necessary.
	static const unsigned long ReceiversFeedbackThreshold = 1000;

	// Should not be lower than 11000 (15s)
	// MacOS sends CK messages every 10 seconds
	// rtpMIDI on Windows sends CK messages every x seconds
	static const unsigned long CK_MaxTimeOut = 15000;

	// when set to true, the lower 32-bits of the rtpClock ae send
	// when set to false, 0 will be set for immediate playout.
	static const bool TimestampRtpPackets = true;

	static const uint8_t MaxSessionInvitesAttempts = 100;

	static const uint8_t MaxSynchronizationCK0Attempts = 5;

	static const unsigned long SynchronizationHeartBeat = 10000;
};

class RtpMidi : public appleMidi::AppleMIDISession<MidiSocket,RtpMidiSettings>
{
public:
	RtpMidi(MidiConnector::Listener* listener, bool& connected, bool& detailLogging, const char* name, int port) :
		appleMidi::AppleMIDISession<MidiSocket,RtpMidiSettings>(name, port),
		m_listener(listener), m_connected(connected), m_detailLogging(detailLogging) {}
	void SetupEvents();
	void ResetDataTransferred();
	bool WasDataTransferred();

	bool wantsInvite = true;

private:
	MidiConnector::Listener* m_listener = nullptr;
	bool& m_connected;
	bool& m_detailLogging;
	std::vector<byte> m_buf;

	void OnSysEx(const byte* data, uint16_t size);

	static void OnAppleMidiConnected(const appleMidi::ssrc_t & ssrc, const char* name);
	static void OnAppleMidiDisconnected(const appleMidi::ssrc_t & ssrc);
	static void OnAppleMidiByte(const appleMidi::ssrc_t & ssrc, byte data);
	static void OnAppleMidiReceivedRtp(const appleMidi::ssrc_t&, const appleMidi::Rtp_t&, const int32_t&);
	static void OnAppleMidiError(const appleMidi::ssrc_t&, int32_t errcode);
	static void OnMidiNoteOn(byte channel, byte note, byte velocity);
	static void OnMidiNoteOff(byte channel, byte note, byte velocity);
	static void OnMidiSystemExclusive(byte* data, unsigned size);
	static void OnMidiActiveSensing();
	static void OnMidiError(const int8_t errcode);
};

typedef midi::MidiInterface<RtpMidi,MidiSettings,MidiPlatform> Midi_t;

RtpMidi* g_rtpMidi = nullptr;
Midi_t* g_midi = nullptr;

void RtpMidi::SetupEvents()
{
	g_rtpMidi->setHandleConnected(OnAppleMidiConnected);
	g_rtpMidi->setHandleDisconnected(OnAppleMidiDisconnected);
	g_rtpMidi->setHandleReceivedMidi(OnAppleMidiByte);
	g_rtpMidi->setHandleReceivedRtp(OnAppleMidiReceivedRtp);
	g_rtpMidi->setHandleError(OnAppleMidiError);

	g_midi->setHandleNoteOn(OnMidiNoteOn);
	g_midi->setHandleNoteOff(OnMidiNoteOff);
	g_midi->setHandleSystemExclusive(OnMidiSystemExclusive);
	g_midi->setHandleActiveSensing(OnMidiActiveSensing);
	g_midi->setHandleError(OnMidiError);
}

void RtpMidi::OnAppleMidiConnected(const appleMidi::ssrc_t & ssrc, const char* name)
{
	g_rtpMidi->m_connected = true;
	Logger::writeToLog("[RTP-MIDI] Connected to session " + String(name));
}

void RtpMidi::OnAppleMidiDisconnected(const appleMidi::ssrc_t & ssrc)
{
	g_rtpMidi->m_connected = false;
	g_rtpMidi->wantsInvite = true;
	Logger::writeToLog("[RTP-MIDI] Disconnected");
}

void RtpMidi::OnAppleMidiReceivedRtp(const appleMidi::ssrc_t&, const appleMidi::Rtp_t&, const int32_t&)
{
	if (g_rtpMidi->m_detailLogging) Logger::writeToLog("[RTP-MIDI] ReceivedRtp");
}

void RtpMidi::OnMidiActiveSensing()
{
	if (g_rtpMidi->m_detailLogging) Logger::writeToLog("[RTP-MIDI] ActiveSensing");
}

void RtpMidi::OnAppleMidiByte(const appleMidi::ssrc_t & ssrc, byte data)
{
	//printf("[RTP-MIDI] %02x\n", data);
}

void RtpMidi::OnAppleMidiError(const appleMidi::ssrc_t&, int32_t errcode)
{
	if (g_rtpMidi->m_detailLogging) Logger::writeToLog("[RTP-MIDI] RtpError " + String(errcode));
}

void RtpMidi::OnMidiError(const int8_t errcode)
{
	if (g_rtpMidi->m_detailLogging) Logger::writeToLog("[RTP-MIDI] MidiError " + String(errcode));
}

void RtpMidi::OnMidiNoteOn(byte channel, byte note, byte velocity)
{
	if (g_rtpMidi->m_detailLogging) Logger::writeToLog("[RTP-MIDI] Incoming NoteOn: channel:" +
		String(channel) + ", note:" + String(note) + ", velocity:" + String(velocity));

	if (g_rtpMidi->m_listener)
	{
		MidiMessage msg = MidiMessage::noteOn(channel, note, velocity);
		g_rtpMidi->m_listener->IncomingMidiMessage(msg);
	}
}

void RtpMidi::OnMidiNoteOff(byte channel, byte note, byte velocity)
{
	if (g_rtpMidi->m_detailLogging) Logger::writeToLog("[RTP-MIDI] Incoming NoteOff: channel:" +
		String(channel) + ", note:" + String(note) + ", velocity:" + String(velocity));

	if (g_rtpMidi->m_listener)
	{
		MidiMessage msg = MidiMessage::noteOff(channel, note, velocity);
		g_rtpMidi->m_listener->IncomingMidiMessage(msg);
	}
}

void RtpMidi::OnMidiSystemExclusive(byte* data, unsigned size)
{
	if (g_rtpMidi->m_detailLogging) Logger::writeToLog("[RTP-MIDI] Incoming SysEx: size:" + String(size));
	g_rtpMidi->OnSysEx(data, size);
}

void RtpMidi::OnSysEx(const byte* data, uint16_t size)
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

	m_buf.insert(m_buf.end(), data + 1, data + size - 1);

	if (data[size-1] == 0xf7)
	{
		MidiMessage msg = MidiMessage::createSysExMessage(m_buf.data(), (int)m_buf.size());
		m_listener->IncomingMidiMessage(msg);
		m_buf.clear();
	}
}

void RtpMidi::ResetDataTransferred()
{
	controlPort.ResetDataTransferred();
	dataPort.ResetDataTransferred();
}

bool RtpMidi::WasDataTransferred()
{
	return controlPort.WasDataTransferred() || dataPort.WasDataTransferred();
}

void RtpMidiConnector::run()
{
	std::srand((unsigned int)juce::Time::currentTimeMillis());

	int port = FindFreePort();
	if (port == 0)
	{
		Logger::writeToLog("[RTP-MIDI] ERROR: could not find free port");
		return;
	}

	Logger::writeToLog("[RTP-MIDI] Starting session on port " + String(port));

	appleMidi::IPAddress remoteIp(m_remoteIp.getCharPointer());
	RtpMidi rtpMidi(m_listener, m_connected, m_detailLogging, "ConPianist", port);
	g_rtpMidi = &rtpMidi;
	Midi_t midi(rtpMidi);
	g_midi = &midi;

	rtpMidi.SetupEvents();

	midi.begin(MIDI_CHANNEL_OMNI);

	while (!threadShouldExit())
	{
		bool processed = false;
		{
			std::lock_guard<std::mutex> guard(m_mutex);
			rtpMidi.ResetDataTransferred();

			// reinvite if necessary
			if (rtpMidi.wantsInvite)
			{
				rtpMidi.wantsInvite = false;
				if (m_detailLogging) Logger::writeToLog("[RTP-MIDI] Inviting");
				rtpMidi.sendInvite(remoteIp);
			}

			// process incoming messages
			midi.read();

			processed = rtpMidi.WasDataTransferred();
		}

		if (!processed)
		{
			Thread::sleep(5);
		}
	}

	rtpMidi.sendEndSession();
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
	std::lock_guard<std::mutex> guard(m_mutex);
	if (message.isController())
	{
		g_midi->sendControlChange(message.getControllerNumber(), message.getControllerValue(), message.getChannel());
	}
	else if (message.isSysEx()) 
	{
		g_midi->sendSysEx(message.getSysExDataSize() + 2, message.getSysExData() - 1, true);
	}
	else if (message.isNoteOn())
	{
		g_midi->sendNoteOn(message.getNoteNumber(), message.getVelocity(), message.getChannel());
	}
	else if (message.isNoteOff())
	{
		g_midi->sendNoteOff(message.getNoteNumber(), message.getVelocity(), message.getChannel());
	}
}

