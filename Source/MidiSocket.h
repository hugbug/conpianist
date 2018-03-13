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

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#include "AppleMidi.h"

BEGIN_APPLEMIDI_NAMESPACE

class MidiSocket
{
public:
	// Initializes the UDP library and network settings. 
	// Returns: 1 if successful, 0 if there are no sockets available to use. 
	// https://www.arduino.cc/en/Reference/EthernetUDPBegin
	int begin(int localPort);

	// Starts a connection to write UDP data to the remote connection 
	// Returns an int: 1 if successful, 0 if there was a problem resolving the hostname or port. 
	// https://www.arduino.cc/en/Reference/EthernetUDPBeginPacket
	int beginPacket(appleMidi::IPAddress ip, uint16_t port);

	// Called after writing UDP data to the remote connection. 
	// Returns an int: 1 if the packet was sent successfully, 0 if there was an error 
	// https://www.arduino.cc/en/Reference/EthernetUDPEndPacket
	int endPacket();

	// Writes UDP data to the remote connection. Must be wrapped between beginPacket() and endPacket().
	// beginPacket() initializes the packet of data, it is not sent until endPacket() is called. 
	// Returns: the number of characters sent. This does not have to be read 
	// https://www.arduino.cc/en/Reference/EthernetUDPWrite
	size_t write(const uint8_t* buf, size_t len);

	// Waits until all outgoing characters in buffer have been sent. 
	// https://www.arduino.cc/en/Reference/ClientFlush
	void flush();

	// Checks for the presence of a UDP packet, and reports the size.
	// parsePacket() must be called before reading the buffer with read(). 
	// Returns the size of the packet in bytes, or 0 if no packets are available
	// https://www.arduino.cc/en/Reference/EthernetUDPParsePacket
	int parsePacket();

	// Read up to len bytes from the current packet and place them into buffer
	// Returns the number of bytes read, or 0 if none are available
	// This function can only be successfully called after parsePacket(). 
	// https://www.arduino.cc/en/Reference/EthernetUDPRead
	int read(unsigned char* buffer, size_t len);

	// Gets the IP address of the remote connection. 
	// This function must be called after parsePacket(). 
	// https://www.arduino.cc/en/Reference/EthernetUDPRemoteIP
	appleMidi::IPAddress remoteIP() { return m_remoteIp; }

	uint16_t remotePort() { return m_remotePort; }

private:
	appleMidi::IPAddress m_remoteIp;
	uint16_t m_remotePort = 0;
	juce::DatagramSocket m_socket;
	std::vector<byte> m_packet;
};

END_APPLEMIDI_NAMESPACE


/* USAGE EXAMPLE:

#include "../JuceLibraryCode/JuceHeader.h"
#include <cstring>
#include <chrono>
#include <thread>

#include "AppleMidi.h"
#include "MidiSocket.h"

class RtpMidi : public appleMidi::AppleMidi_Class<appleMidi::MidiSocket>
{
public:
	void CheckConenction();
	virtual void OnActiveSensing(void* sender);
private:
	unsigned long m_lastSensing = 0;
};

void RtpMidi::OnActiveSensing(void* sender)
{
	appleMidi::AppleMidi_Class<appleMidi::MidiSocket>::OnActiveSensing(sender);
	m_lastSensing = appleMidi::millis();
}

void RtpMidi::CheckConenction()
{
	unsigned long lastTime = Sessions[0].syncronization.lastTime;
	if (lastTime > 0)
	{
		unsigned long delta = appleMidi::millis() - m_lastSensing;
		if (delta > 3000)
		{
			DeleteSession(0);
		}
	}
};


int main(int argc, char* argv[])
{
	std::srand((unsigned int)juce::Time::currentTimeMillis());

	appleMidi::IPAddress remoteIp("192.168.1.235");
	RtpMidi rtpMidi;

	rtpMidi.begin("Midi-Session", 5006);
	rtpMidi.invite(remoteIp);

	unsigned long t0 = appleMidi::millis();

	while (true)
	{
		// check connection lost and reinvite
		rtpMidi.CheckConenction();
		if (rtpMidi.GetFreeSessionSlot() == 0)
		{
			rtpMidi.invite(remoteIp);
		}

		// Listen to incoming notes
		rtpMidi.run();

		// send a note every second
		if ((appleMidi::millis() - t0) > 1000)
		{
			t0 = appleMidi::millis();
			printf(".");

			int note = 45;
			int velocity = 55;
			int channel = 1;

			rtpMidi.noteOn(note, velocity, channel);
			rtpMidi.noteOff(note, velocity, channel);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

    return 0;
}
*/
