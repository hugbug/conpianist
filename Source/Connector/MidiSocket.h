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

#pragma once

#include "AppleMIDI.h"

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

	size_t write(uint8_t value) { return write(&value, 1); }

	// Waits until all outgoing characters in buffer have been sent. 
	// https://www.arduino.cc/en/Reference/ClientFlush
	void flush();

	// Checks for the presence of a UDP packet, and reports the size.
	// parsePacket() must be called before reading the buffer with read(). 
	// Returns the size of the packet in bytes, or 0 if no packets are available
	// https://www.arduino.cc/en/Reference/EthernetUDPParsePacket
	int parsePacket();

	// Get the number of bytes (characters) available for reading from the buffer. This is data that's already arrived.
	// This function can only be successfully called after UDP.parsePacket().
	// https://www.arduino.cc/en/Reference/EthernetUDPAvailable
	int available();

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

	void ResetDataTransferred() { m_dataTransferred = false; }
	bool WasDataTransferred() { return m_dataTransferred; }

private:
	static const int MAX_PACKET_SIZE = 1024*4;

	appleMidi::IPAddress m_remoteIp;
	uint16_t m_remotePort = 0;
	juce::DatagramSocket m_socket;
	byte m_outPacket[MAX_PACKET_SIZE];
	byte m_inPacket[MAX_PACKET_SIZE];
	int m_outSize = 0;
	int m_inSize = 0;
	int m_inIndex = 0;
	bool m_dataTransferred = false;
};
