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

#include "CspController.h"

void CspController::Init(AudioDeviceManager* audioDeviceManager, const String& remoteIp)
{
	m_audioDeviceManager = audioDeviceManager;
	m_remoteIp = remoteIp;
}

void CspController::SwitchLocalControl(bool enabled)
{
	if (!m_audioDeviceManager->getDefaultMidiOutput())
	{
		return;
	}

	MidiMessage localControlMessage = MidiMessage::controllerEvent(1, 122, enabled ? 127 : 0);
	m_audioDeviceManager->getDefaultMidiOutput()->sendMessageNow(localControlMessage);
}

bool CspController::UploadSong(const File& file)
{
	String headerHex =
		"01 00 00 06 00 00 00 01 00 00 00 00 00 00 00 01 "
		"00 00 00 00 00 00 00 16 45 58 54 45 52 4e 41 4c "
		"3a 2f 41 70 70 53 6f 6e 67 2e 6d 69 64 00 00 00 "
		"00 00";

	MemoryBlock message;
	message.loadFromHexString(headerHex);

	int size = (int)file.getSize();
	message[8] = ((size + 38) & (0xFF << (8 * 3))) >> (8 * 3);
	message[9] = ((size + 38) & (0xFF << (8 * 2))) >> (8 * 2);
	message[10] = ((size + 38) & (0xFF << (8 * 1))) >> (8 * 1);
	message[11] = ((size + 38) & (0xFF << (8 * 0))) >> (8 * 0);

	message[46] = (size & (0xFF << (8 * 3))) >> (8 * 3);
	message[47] = (size & (0xFF << (8 * 2))) >> (8 * 2);
	message[48] = (size & (0xFF << (8 * 1))) >> (8 * 1);
	message[49] = (size & (0xFF << (8 * 0))) >> (8 * 0);

	file.loadFileAsData(message);

	String base = message.toBase64Encoding();

	StreamingSocket socket;
	bool ok = socket.connect(m_remoteIp, 10504) &&
		socket.write(message.getData(), (int)message.getSize());

	return ok;
}

void CspController::SendCspMessage(const String& command)
{
	if (!m_audioDeviceManager->getDefaultMidiOutput())
	{
		return;
	}

	String CSP_PREFIX = "43 73 01 52 25 26 01 01 ";
	MemoryBlock rawData;
	rawData.loadFromHexString(CSP_PREFIX + command);
	MidiMessage message = MidiMessage::createSysExMessage(rawData.getData(), (int)rawData.getSize());
	m_audioDeviceManager->getDefaultMidiOutput()->sendMessageNow(message);
}

void CspController::Play()
{
	SendCspMessage("04 00 05 01 00 01 00 00 01 01");
}

void CspController::Pause()
{
	SendCspMessage("04 00 05 01 00 01 00 00 01 02");
}

void CspController::Guide(bool enable)
{
	SendCspMessage(String("04 03 00 01 00 01 00 00 01 ") + (enable ? "01" : "00"));
}

void CspController::StreamLights(bool enable)
{
	SendCspMessage(String("04 02 00 01 00 01 00 00 01 ") + (enable ? "01" : "00"));
}

