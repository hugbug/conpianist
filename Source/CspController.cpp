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

static const char* CSP_PREFIX = "43 73 01 52 25 26 ";
static const char* CSP_COMMAND = "43 73 01 52 25 26 01 01 ";
static const char* CSP_GUIDE_ON = "04 03 00 01 00 01 00 00 01 01";
static const char* CSP_GUIDE_OFF = "04 03 00 01 00 01 00 00 01 00";
static const char* CSP_GUIDE_STATE = "00 01 04 03 00 01 00 01 00 00 00 00 01";
static const char* CSP_POSITION_STATE = "00 00 04 00 0a 01 00 01 00 00 04";
static const char* CSP_LENGTH_STATE = "00 00 04 00 1b 01 00 01 00 00 04";
static const char* CSP_STREAM_LIGHTS_ON = "04 02 00 01 00 01 00 00 01 01";
static const char* CSP_STREAM_LIGHTS_OFF = "04 02 00 01 00 01 00 00 01 00";
static const char* CSP_STREAM_LIGHTS_STATE = "00 01 04 02 00 01 00 01 00 00 00 00 01";
static const char* CSP_PLAY = "04 00 05 01 00 01 00 00 01 01";
static const char* CSP_PAUSE = "04 00 05 01 00 01 00 00 01 02";
static const char* CSP_DUMP_MODEL = "01 00 0f 01 18 01 00 01 00";
static const char* CSP_MODEL_STATE = "00 00 0f 01 18 01 00 01 00";
static const char* CSP_DUMP_VERSION = "01 00 0f 01 0b 01 00 01 00";
static const char* CSP_VERSION_STATE = "00 00 0f 01 0b 01 00 01 00";

void CspController::Init(AudioDeviceManager* audioDeviceManager, const String& remoteIp)
{
	m_audioDeviceManager = audioDeviceManager;
	m_remoteIp = remoteIp;
    audioDeviceManager->addMidiInputCallback("", this);
}

void CspController::Connect()
{
	SendCspMessage(CSP_DUMP_MODEL, false);
	SendCspMessage(CSP_DUMP_VERSION, false);

	// Activate song length events
	SendCspMessage("02 00 04 00 1b 01", false);
	// Activate song position events
	SendCspMessage("02 00 04 00 0a 01", false);

	Pause();

	m_guide = false;
	m_streamLights = true;
	m_localControl = true;

	Guide(false);
	StreamLights(true);
	LocalControl(true);
	if (m_listener) m_listener->PlaybackStateChanged();
}

void CspController::LocalControl(bool enabled)
{
	if (!m_audioDeviceManager->getDefaultMidiOutput())
	{
		return;
	}

	m_localControl = enabled;
	MidiMessage localControlMessage = MidiMessage::controllerEvent(1, 122, enabled ? 127 : 0);
	m_audioDeviceManager->getDefaultMidiOutput()->sendMessageNow(localControlMessage);
	if (m_listener) m_listener->SettingsChanged();
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

	Pause();
	usleep(1000*10);   // this is not nice, we should wait for a confirmation message instead

	StreamingSocket socket;
	bool ok = socket.connect(m_remoteIp, 10504) &&
		socket.write(message.getData(), (int)message.getSize());

	return ok;
}

void CspController::SendSysExMessage(const String& command)
{
	if (!m_audioDeviceManager->getDefaultMidiOutput())
	{
		return;
	}

	MemoryBlock rawData;
	rawData.loadFromHexString(command);
	MidiMessage message = MidiMessage::createSysExMessage(rawData.getData(), (int)rawData.getSize());
	m_audioDeviceManager->getDefaultMidiOutput()->sendMessageNow(message);
}

void CspController::SendCspMessage(const String& command, bool addDefaultCommandPrefix)
{
	if (addDefaultCommandPrefix)
	{
		SendSysExMessage(CSP_COMMAND + command);
	}
	else
	{
		SendSysExMessage(String(CSP_PREFIX) + command);
	}
}

void CspController::Play()
{
	SendCspMessage(CSP_PLAY);
}

void CspController::Pause()
{
	SendCspMessage(CSP_PAUSE);
}

void CspController::Guide(bool enable)
{
	SendCspMessage(enable ? CSP_GUIDE_ON : CSP_GUIDE_OFF);
}

void CspController::StreamLights(bool enable)
{
	SendCspMessage(enable ? CSP_STREAM_LIGHTS_ON : CSP_STREAM_LIGHTS_OFF);
}

bool CspController::IsCspMessage(const MidiMessage& message, const char* messageHex)
{
	MemoryBlock sig;
	sig.loadFromHexString(String(CSP_PREFIX) + messageHex);
	bool ret = message.getSysExDataSize() >= sig.getSize() &&
		memcmp(message.getSysExData(), sig.getData(), sig.getSize()) == 0;
	return ret;
}

void CspController::handleIncomingMidiMessage(MidiInput* source, const MidiMessage& message)
{
	if (message.isSysEx())
	{
		if (IsCspMessage(message, CSP_POSITION_STATE))
		{
			m_songPosition = (message.getSysExData()[17] << 7) + message.getSysExData()[18];
			if (m_listener) m_listener->PlaybackStateChanged();
		}
		else if (IsCspMessage(message, CSP_LENGTH_STATE))
		{
			m_songLength = (message.getSysExData()[17] << 7) + message.getSysExData()[18];
			if (m_listener) m_listener->PlaybackStateChanged();
		}
		else if (IsCspMessage(message, CSP_GUIDE_STATE))
		{
			m_guide = message.getSysExData()[19];
			if (m_listener) m_listener->SettingsChanged();
		}
		else if (IsCspMessage(message, CSP_STREAM_LIGHTS_STATE))
		{
			m_streamLights = message.getSysExData()[19];
			if (m_listener) m_listener->SettingsChanged();
		}
		else if (IsCspMessage(message, CSP_MODEL_STATE))
		{
			int len = (message.getSysExData()[15] << 7) + message.getSysExData()[16];
			String str((char*)(message.getSysExData() + 18), len-1);
			//TODO: make thread safe
			m_model = str;
		}
		else if (IsCspMessage(message, CSP_VERSION_STATE))
		{
			int len = (message.getSysExData()[15] << 7) + message.getSysExData()[16];
			String str((char*)(message.getSysExData() + 18), len-1);
			//TODO: make thread safe
			m_version = str;
			m_connected = true;
			if (m_listener) m_listener->SettingsChanged();
		}
	}
}
