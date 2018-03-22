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

#include "PianoController.h"

static const char* CSP_PREFIX = "43 73 01 52 25 26 ";
static const char* CSP_COMMAND = "43 73 01 52 25 26 01 01 ";
static const char* CSP_DUMP_MODEL = "01 00 0f 01 18 01 00 01 00";
static const char* CSP_MODEL_STATE = "00 00 0f 01 18 01 00 01 00";
static const char* CSP_DUMP_VERSION = "01 00 0f 01 0b 01 00 01 00";
static const char* CSP_VERSION_STATE = "00 00 0f 01 0b 01 00 01 00";
static const char* CSP_GUIDE_ON = "04 03 00 01 00 01 00 00 01 01";
static const char* CSP_GUIDE_OFF = "04 03 00 01 00 01 00 00 01 00";
static const char* CSP_GUIDE_STATE = "00 00 04 03 00 01 00 01 00 00 01";
static const char* CSP_GUIDE_EVENTS = "02 00 04 03 00 01";
static const char* CSP_POSITION = "04 00 0a 01 00 01 00 00 04 ";
static const char* CSP_POSITION_STATE = "00 00 04 00 0a 01 00 01 00 00 04";
static const char* CSP_POSITION_EVENTS = "02 00 04 00 0a 01";
static const char* CSP_LENGTH_STATE = "00 00 04 00 1b 01 00 01 00 00 04";
static const char* CSP_LENGTH_EVENTS = "02 00 04 00 1b 01";
static const char* CSP_PLAY_STATE = "00 00 04 00 05 01 00 01 00 00 01";
static const char* CSP_PLAY_EVENTS = "02 00 04 00 05 01";
static const char* CSP_STREAM_LIGHTS_ON = "04 02 00 01 00 01 00 00 01 01";
static const char* CSP_STREAM_LIGHTS_OFF = "04 02 00 01 00 01 00 00 01 00";
static const char* CSP_STREAM_LIGHTS_STATE = "00 00 04 02 00 01 00 01 00 00 01";
static const char* CSP_STREAM_LIGHTS_EVENTS = "02 00 04 02 00 01";
static const char* CSP_STREAM_LIGHTS_FAST = "04 02 02 01 00 01 00 00 01 01";
static const char* CSP_STREAM_LIGHTS_SLOW = "04 02 02 01 00 01 00 00 01 00";
static const char* CSP_STREAM_LIGHTS_SPEED_STATE = "00 00 04 02 02 01 00 01 00 00 01";
static const char* CSP_STREAM_LIGHTS_SPEED_EVENTS = "02 00 04 02 02 01";
static const char* CSP_PLAY = "04 00 05 01 00 01 00 00 01 01";
static const char* CSP_PAUSE = "04 00 05 01 00 01 00 00 01 02";
static const char* CSP_STOP = "04 00 05 01 00 01 00 00 01 00";
static const char* CSP_BACKING_PART_ON = "04 00 0e 01 02 01 00 00 01 01";
static const char* CSP_BACKING_PART_OFF = "04 00 0e 01 02 01 00 00 01 00";
static const char* CSP_BACKING_PART_STATE = "00 00 04 00 0e 01 02 01 00 00 01";
static const char* CSP_LEFT_PART_ON = "04 00 0e 01 01 01 00 00 01 01";
static const char* CSP_LEFT_PART_OFF = "04 00 0e 01 01 01 00 00 01 00";
static const char* CSP_LEFT_PART_STATE = "00 00 04 00 0e 01 01 01 00 00 01";
static const char* CSP_RIGHT_PART_ON = "04 00 0e 01 00 01 00 00 01 01";
static const char* CSP_RIGHT_PART_OFF = "04 00 0e 01 00 01 00 00 01 00";
static const char* CSP_RIGHT_PART_STATE = "00 00 04 00 0e 01 00 01 00 00 01";
static const char* CSP_PART_EVENTS = "02 00 04 00 0e 01";
static const char* CSP_SONG_NAME_STATE = "00 00 04 00 01 01 00 01 00";
static const char* CSP_VOLUME = "0c 00 00 01 50 01 00 00 01 ";
static const char* CSP_VOLUME_STATE = "00 00 0c 00 00 01 50 01 00 00 01";
static const char* CSP_VOLUME_EVENTS = "02 00 0c 00 00 01";
static const char* CSP_TEMPO = "08 00 00 01 00 01 00 00 02 ";
static const char* CSP_TEMPO_STATE = "00 00 08 00 00 01 01 01 00 00 02";
static const char* CSP_TEMPO_EVENTS = "02 00 08 00 00 01";

void Sleep(int milliseconds)
{
	Time::waitForMillisecondCounter(Time::getMillisecondCounter() + milliseconds);
}

String PianoController::WordToHex(int value)
{
	String str = String::toHexString(value >> 7 & 0x7f).paddedLeft('0', 2) +
		" " + String::toHexString(value & 0x7f).paddedLeft('0', 2);
	return str;
}

void PianoController::SetMidiConnector(MidiConnector* midiConnector)
{
	m_midiConnector = midiConnector;
	midiConnector->SetListener(this);
}

void PianoController::Connect()
{
	SendCspMessage(CSP_DUMP_MODEL, false);
	SendCspMessage(CSP_DUMP_VERSION, false);

	// Activate feedback events from piano:
	//   song length info after a song is loaded
	SendCspMessage(CSP_LENGTH_EVENTS, false);
	//   song position info
	SendCspMessage(CSP_POSITION_EVENTS, false);
	//   playback status (playing,paused,stop)
  	SendCspMessage(CSP_PLAY_EVENTS, false);
	//   playing parts on/off
  	SendCspMessage(CSP_PART_EVENTS, false);
	//   guide-mode on/off
  	SendCspMessage(CSP_GUIDE_EVENTS, false);
  	//   stream lights on/off
  	SendCspMessage(CSP_STREAM_LIGHTS_EVENTS, false);
  	//   stream lights slow/fast
  	SendCspMessage(CSP_STREAM_LIGHTS_SPEED_EVENTS, false);
	//   volume info
	SendCspMessage(CSP_VOLUME_EVENTS, false);
	//   tempo info
	SendCspMessage(CSP_TEMPO_EVENTS, false);

	Stop();

	// Sleep is not nice, we should wait for a confirmation message instead.
	// Without waiting the config-commands below do not issue change events.
	Sleep(150);

	SetLocalControl(true);

	SetGuide(true);
	SetStreamLights(false);
	SetStreamLightsFast(false);
	SetGuide(false);
	SetStreamLights(true);
	SetStreamLightsFast(true);
	SetVolume(0);
	SetVolume(100);
	SetTempo(0);
	SetTempo(140);

	sendChangeMessage();
}

void PianoController::Disconnect()
{
	m_connected = false;
	sendChangeMessage();
}

void PianoController::SetLocalControl(bool enabled)
{
	m_localControl = enabled;
	MidiMessage localControlMessage = MidiMessage::controllerEvent(1, 122, enabled ? 127 : 0);
	m_midiConnector->SendMessage(localControlMessage);
	sendChangeMessage();
}

bool PianoController::UploadSong(const File& file)
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
	Sleep(10);   // this is not nice, we should wait for a confirmation message instead

	char response[16];
	StreamingSocket socket;
	bool ok = socket.connect(m_remoteIp, 10504) &&
		socket.write(message.getData(), (int)message.getSize()) &&
		socket.read(response, 16, true);

	return ok;
}

void PianoController::SendSysExMessage(const String& command)
{
	MemoryBlock rawData;
	rawData.loadFromHexString(command);
	MidiMessage message = MidiMessage::createSysExMessage(rawData.getData(), (int)rawData.getSize());
	m_midiConnector->SendMessage(message);
}

void PianoController::SendCspMessage(const String& command, bool addDefaultCommandPrefix)
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

void PianoController::Play()
{
	SendCspMessage(CSP_PLAY);
}

void PianoController::Pause()
{
	SendCspMessage(CSP_PAUSE);
}

void PianoController::Stop()
{
	SendCspMessage(CSP_STOP);
}

void PianoController::SetGuide(bool enable)
{
	SendCspMessage(enable ? CSP_GUIDE_ON : CSP_GUIDE_OFF);
}

void PianoController::SetStreamLights(bool enable)
{
	SendCspMessage(enable ? CSP_STREAM_LIGHTS_ON : CSP_STREAM_LIGHTS_OFF);
}

void PianoController::SetStreamLightsFast(bool fast)
{
	SendCspMessage(fast ? CSP_STREAM_LIGHTS_FAST : CSP_STREAM_LIGHTS_SLOW);
}

void PianoController::SetSongPosition(int position)
{
	SendCspMessage(String(CSP_POSITION) + WordToHex(position) + " 00 00");
}

void PianoController::SetVolume(int volume)
{
	String pos = String::toHexString(volume).paddedLeft('0', 2);
	SendCspMessage(String(CSP_VOLUME) + pos);
}

void PianoController::SetTempo(int tempo)
{
	SendCspMessage(String(CSP_TEMPO) + WordToHex(tempo));
}

void PianoController::SetBackingPart(bool enable)
{
	SendCspMessage(enable ? CSP_BACKING_PART_ON : CSP_BACKING_PART_OFF);
}

void PianoController::SetLeftPart(bool enable)
{
	SendCspMessage(enable ? CSP_LEFT_PART_ON : CSP_LEFT_PART_OFF);
}

void PianoController::SetRightPart(bool enable)
{
	SendCspMessage(enable ? CSP_RIGHT_PART_ON : CSP_RIGHT_PART_OFF);
}

bool PianoController::IsCspMessage(const MidiMessage& message, const char* messageHex)
{
	MemoryBlock sig;
	sig.loadFromHexString(String(CSP_PREFIX) + messageHex);
	bool ret = message.getSysExDataSize() >= sig.getSize() &&
		memcmp(message.getSysExData(), sig.getData(), sig.getSize()) == 0;
	return ret;
}

void PianoController::IncomingMidiMessage(const MidiMessage& message)
{
	if (message.isSysEx())
	{
		if (IsCspMessage(message, CSP_POSITION_STATE))
		{
			m_songPosition = (message.getSysExData()[17] << 7) + message.getSysExData()[18];
			sendChangeMessage();
		}
		else if (IsCspMessage(message, CSP_LENGTH_STATE))
		{
			m_songLength = (message.getSysExData()[17] << 7) + message.getSysExData()[18];
			sendChangeMessage();
		}
		else if (IsCspMessage(message, CSP_PLAY_STATE))
		{
			m_playing = message.getSysExData()[17] == 1;
			sendChangeMessage();
		}
		else if (IsCspMessage(message, CSP_GUIDE_STATE))
		{
			m_guide = message.getSysExData()[17] == 1;
			sendChangeMessage();
		}
		else if (IsCspMessage(message, CSP_STREAM_LIGHTS_STATE))
		{
			m_streamLights = message.getSysExData()[17] == 1;
			sendChangeMessage();
		}
		else if (IsCspMessage(message, CSP_STREAM_LIGHTS_SPEED_STATE))
		{
			m_streamLightsFast = message.getSysExData()[17] == 1;
			sendChangeMessage();
		}
		else if (IsCspMessage(message, CSP_BACKING_PART_STATE))
		{
			m_backingPart = message.getSysExData()[17] == 1;
			sendChangeMessage();
		}
		else if (IsCspMessage(message, CSP_LEFT_PART_STATE))
		{
			m_leftPart = message.getSysExData()[17] == 1;
			sendChangeMessage();
		}
		else if (IsCspMessage(message, CSP_RIGHT_PART_STATE))
		{
			m_rightPart = message.getSysExData()[17] == 1;
			sendChangeMessage();
		}
		else if (IsCspMessage(message, CSP_VOLUME_STATE))
		{
			m_volume = message.getSysExData()[17];
			sendChangeMessage();
		}
		else if (IsCspMessage(message, CSP_TEMPO_STATE))
		{
			m_tempo = (message.getSysExData()[17] << 7) + message.getSysExData()[18];
			sendChangeMessage();
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
			sendChangeMessage();
		}
		else if (IsCspMessage(message, CSP_SONG_NAME_STATE))
		{
			// if (m_listener) m_listener->SongLoaded();
		}
	}
}
