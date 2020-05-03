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
#include "MidiSocket.h"

// Initializes the ethernet UDP library and network settings. 
// Returns: 1 if successful, 0 if there are no sockets available to use. 
// https://www.arduino.cc/en/Reference/EthernetUDPBegin
int MidiSocket::begin(int localPort)
{
	bool ret = m_socket.bindToPort(localPort);
	return ret;
}

// Starts a connection to write UDP data to the remote connection 
// Returns an int: 1 if successful, 0 if there was a problem resolving the hostname or port. 
// https://www.arduino.cc/en/Reference/EthernetUDPBeginPacket
int MidiSocket::beginPacket(appleMidi::IPAddress ip, uint16_t port)
{
	m_remoteIp = ip;
	m_remotePort = port;
	m_outSize = 0;
	return 1;
}

// Writes UDP data to the remote connection. Must be wrapped between beginPacket() and endPacket().
// beginPacket() initializes the packet of data, it is not sent until endPacket() is called. 
// Returns: the number of characters sent. This does not have to be read 
// https://www.arduino.cc/en/Reference/EthernetUDPWrite
size_t MidiSocket::write(const uint8_t* buf, size_t len)
{
	len = std::min(len, sizeof(m_outPacket) - m_outSize);
	memcpy(m_outPacket + m_outSize, buf, len);
	m_outSize += len;
	return len;
}

// Called after writing UDP data to the remote connection. 
// Returns an int: 1 if the packet was sent successfully, 0 if there was an error 
// https://www.arduino.cc/en/Reference/EthernetUDPEndPacket
int MidiSocket::endPacket()
{
	m_dataTransferred = true;
	int ret = m_socket.write((const char*)m_remoteIp, m_remotePort, m_outPacket, m_outSize);
	return ret > 0;
}

// Waits until all outgoing characters in buffer have been sent. 
// https://www.arduino.cc/en/Reference/ClientFlush
void MidiSocket::flush()
{
}

// Checks for the presence of a UDP packet, and reports the size.
// parsePacket() must be called before reading the buffer with read(). 
// Returns the size of the packet in bytes, or 0 if no packets are available
// https://www.arduino.cc/en/Reference/EthernetUDPParsePacket
int MidiSocket::parsePacket()
{
	juce::String ip;
	int port;

	if (!m_socket.waitUntilReady(true, 1))
	{
		return 0;
	}

	int ret = m_socket.read(m_inPacket, sizeof(m_inPacket), false, ip, port);

	m_inSize = std::max(ret, 0);
	m_inIndex = 0;

	if (ret > 0 && !ip.isEmpty())
	{
		m_remoteIp = ip.getCharPointer();
	}

	m_remotePort = port;

	return m_inSize;
}

// Get the number of bytes (characters) available for reading from the buffer. This is data that's already arrived.
// This function can only be successfully called after UDP.parsePacket().
// https://www.arduino.cc/en/Reference/EthernetUDPAvailable
int MidiSocket::available()
{
	return m_inSize;
}

// Read up to len bytes from the current packet and place them into buffer
// Returns the number of bytes read, or 0 if none are available
// This function can only be successfully called after parsePacket(). 
// https://www.arduino.cc/en/Reference/EthernetUDPRead
int MidiSocket::read(unsigned char* buffer, size_t len)
{
	int ret = std::min((int)len, m_inSize);
	memcpy(buffer, m_inPacket + m_inIndex, ret);

	m_inIndex += ret;
	m_inSize -= ret;
	m_dataTransferred = true;

	return ret;
}
