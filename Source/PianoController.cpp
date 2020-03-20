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
static const char* CSP_SONG_NAME_EVENTS = "02 00 04 00 01 01";
static const char* CSP_VOLUME = "0c 00 00 01 NN 01 00 00 01 ";
static const char* CSP_VOLUME_STATE = "00 00 0c 00 00 01";
static const char* CSP_VOLUME_EVENTS = "02 00 0c 00 00 01";
static const char* CSP_PAN = "0c 00 03 01 NN 01 00 00 01 ";
static const char* CSP_PAN_STATE = "00 00 0c 00 03 01";
static const char* CSP_PAN_EVENTS = "02 00 0c 00 03 01";
static const char* CSP_REVERB = "0c 00 04 01 NN 01 00 00 01 ";
static const char* CSP_REVERB_STATE = "00 00 0c 00 04 01";
static const char* CSP_REVERB_EVENTS = "02 00 0c 00 04 01";
static const char* CSP_TEMPO = "08 00 00 01 00 01 00 00 02 ";
static const char* CSP_TEMPO_STATE = "00 00 08 00 00 01 01 01 00 00 02";
static const char* CSP_TEMPO_EVENTS = "02 00 08 00 00 01";
static const char* CSP_TEMPO_RESET = "04 01 08 00 00 01 00 01 00";
static const char* CSP_TRANSPOSE = "0a 00 00 01 02 01 00 00 01 ";
static const char* CSP_TRANSPOSE_STATE = "00 00 0a 00 00 01 02 01 00 00 01";
static const char* CSP_TRANSPOSE_EVENTS = "02 00 0a 00 00 01";
static const char* CSP_LOOP = "04 00 0d 01 00 01 00 00 09 01 ";
static const char* CSP_LOOP_STATE = "00 00 04 00 0d 01 00 01 00 00 09";
static const char* CSP_LOOP_EVENTS = "02 00 04 00 0d 01";
static const char* CSP_LOOP_RESET = "04 00 0d 01 00 01 00 00 09 00 00 01 00 01 00 02 00 01";
static const char* CSP_VOICE_SELECT = "02 00 00 01 NN 01 00 ";
static const char* CSP_VOICE_SELECT_EVENTS = "02 00 02 00 00 01";
static const char* CSP_VOICE_SELECT_STATE = "00 00 02 00 00 01";
static const char* CSP_VOICE_SELECT_STATE2 = "00 01 02 00 00 01";
static const char* CSP_CHANNEL_ENABLE = "0c 00 01 01 NN 01 00 00 01 ";
static const char* CSP_CHANNEL_ENABLE_STATE = "00 00 0c 00 01 01";
static const char* CSP_CHANNEL_ENABLE_EVENTS = "02 00 0c 00 01 01";

static const std::vector<PianoController::Channel> ValidChannelIds = {
	PianoController::chMain, PianoController::chLayer, PianoController::chLeft,
	PianoController::chMidi1, PianoController::chMidi2, PianoController::chMidi3,
	PianoController::chMidi4, PianoController::chMidi5, PianoController::chMidi6,
	PianoController::chMidi7, PianoController::chMidi8, PianoController::chMidi9,
	PianoController::chMidi10, PianoController::chMidi11, PianoController::chMidi12,
	PianoController::chMidi13, PianoController::chMidi14, PianoController::chMidi15,
	PianoController::chMidi16, PianoController::chMic, PianoController::chAuxIn,
	PianoController::chWave, PianoController::chMidiMaster, PianoController::chStyle };

void Sleep(int milliseconds)
{
	Time::waitForMillisecondCounter(Time::getMillisecondCounter() + milliseconds);
}

String ByteToHex(int value)
{
	return String::toHexString(value & 0x7f).paddedLeft('0', 2);
}

String WordToHex(int value)
{
	return ByteToHex(value >> 7 & 0x7f) + " " + ByteToHex(value & 0x7f);
}

String TextToHex(const String& text)
{
	String encoded = "";
	int len = 0;
	char highbits = 0;
	String chunk = "";
	for (int i = 0; i < text.length(); i++)
	{
		if (i % 7 == 0 && i > 0)
		{
			encoded += String(" ") + ByteToHex(highbits) + chunk;
			len++;
			chunk = "";
			highbits = 0;
		}
		wchar_t ch = text[i];
		highbits = (highbits << 1) + (ch > 0x7f ? 1 : 0);
		chunk += " " + ByteToHex(ch);
		len++;
	}

	if (!chunk.isEmpty())
	{
		encoded += String(" ") + ByteToHex(highbits) + chunk;
		len++;
	}

	return WordToHex(len) + encoded;
}

String BytesToText(const uint8* buf, int size)
{
	if (size < 3)
	{
		return String();
	}

	int textSize = (buf[0] << 7) + buf[1];
	if (size < textSize + 2)
	{
		return String();
	}

	String text;
	buf += 2;
	int highbits = 0;
	int chunkSize = 0;
	wchar_t chunk[7];

	auto addChunk = [&]()
		{
			for (int a = 0; a < chunkSize; a++)
			{
				wchar_t ch = chunk[a];
				ch += (highbits >> (chunkSize - a - 1) & 1) ? 0x80 : 0;
				text += ch;
			}
		};

	for (int i = 0; i < textSize; i++)
	{
		if (i % 8 == 0)
		{
			addChunk();
			highbits = buf[i];
			chunkSize = 0;
			continue;
		}

		chunk[chunkSize++] = buf[i];
	}
	addChunk();

	return text;
}

void PianoController::SetMidiConnector(MidiConnector* midiConnector)
{
	m_midiConnector = midiConnector;
	m_midiConnector->SetListener(this);
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
	//   pan info
	SendCspMessage(CSP_PAN_EVENTS, false);
	//   reverb info
	SendCspMessage(CSP_REVERB_EVENTS, false);
	//   tempo info
	SendCspMessage(CSP_TEMPO_EVENTS, false);
	//   transpose info
	SendCspMessage(CSP_TRANSPOSE_EVENTS, false);
	//   A->B loop info
	SendCspMessage(CSP_LOOP_EVENTS, false);
	//   voice info
	SendCspMessage(CSP_VOICE_SELECT_EVENTS, false);
	//   voice slot enabled/disabled
	SendCspMessage(CSP_CHANNEL_ENABLE_EVENTS, false);
	//   song name info (after a song is loaded)
	SendCspMessage(CSP_SONG_NAME_EVENTS, false);

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

	for (Channel ch : ValidChannelIds)
	{
		SetVolume(ch, MinVolume);
		SetVolume(ch, DefaultVolume);

		SetPan(ch, MinPan);
		SetPan(ch, DefaultPan);

		SetReverb(ch, MinReverb);
		SetReverb(ch, DefaultReverb);

		// Sleep is not nice, we should wait for confirmation messages instead.
		// Without waiting the piano may miss some commands because there are too many.
		Sleep(20);
	}

	SetTempo(MinTempo);
	SetTempo(DefaultTempo);
	ResetTempo();
	SetTranspose(MinTranspose);
	SetTranspose(DefaultTranspose);

	// set internal active for channels
	m_channels[chMain].enabled = true;
	m_channels[chLayer].enabled = false;
	m_channels[chLeft].enabled = false;
	m_channels[chMidiMaster].enabled = true;
	m_channels[chMic].enabled = true;
	m_channels[chAuxIn].enabled = true;

	SetActive(chMain, true);
	SetActive(chLayer, false);
	SetActive(chLeft, false);
	SetActive(chMidiMaster, true);
	SetActive(chMic, true);
	SetActive(chAuxIn, true);

	// By trying to set an invalid voice we cause the piano to fire
	// event "CSP_VOICE_SELECT_STATE2" containing info about current voice.
	// That's how we know which voice is selected without changing it
	SetVoice(chMain, "");
	SetVoice(chLayer, "");
	SetVoice(chLeft, "");

	NotifyChanged();
}

void PianoController::Disconnect()
{
	m_connected = false;
	NotifyChanged();
}

void PianoController::SetLocalControl(bool enabled)
{
	m_localControl = enabled;
	MidiMessage localControlMessage = MidiMessage::controllerEvent(1, 122, enabled ? 127 : 0);
	m_midiConnector->SendMessage(localControlMessage);
	NotifyChanged();
}

bool PianoController::UploadSong(const File& file)
{
	m_songFilename = file.getFullPathName();

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

void PianoController::SetPosition(const Position position)
{
	SendCspMessage(String(CSP_POSITION) + WordToHex(position.measure) + " " + WordToHex(position.beat));
}

void PianoController::SetVolume(Channel ch, int volume)
{
	String command = String(CSP_VOLUME).replace("NN", ByteToHex(ch)) + ByteToHex(volume);
	SendCspMessage(command);
}

void PianoController::SetPan(Channel ch, int pan)
{
	String command = String(CSP_PAN).replace("NN", ByteToHex(ch)) + ByteToHex(pan + PanBase);
	SendCspMessage(command);
}

void PianoController::SetReverb(Channel ch, int reverb)
{
	String command = String(CSP_REVERB).replace("NN", ByteToHex(ch)) + ByteToHex(reverb);
	SendCspMessage(command);
}

void PianoController::SetTempo(int tempo)
{
	SendCspMessage(String(CSP_TEMPO) + WordToHex(tempo));
}

void PianoController::ResetTempo()
{
	SendCspMessage(CSP_TEMPO_RESET, false);
}

void PianoController::SetTranspose(int transpose)
{
	SendCspMessage(String(CSP_TRANSPOSE) + ByteToHex(transpose + TransposeBase));
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

void PianoController::SetLoop(Loop loop)
{
	m_loopStart = {0,0};
	SendCspMessage(String(CSP_LOOP) +
		WordToHex(loop.begin.measure) + " " + WordToHex(loop.begin.beat) + " " +
		WordToHex(loop.end.measure) + " " + WordToHex(loop.end.beat));
}

void PianoController::ResetLoop()
{
	m_loopStart = {0,0};
	SendCspMessage(CSP_LOOP_RESET);
}

void PianoController::SetLoopStart(const Position loopStart)
{
	m_loopStart = loopStart;
	NotifyChanged();
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
			m_position = {(message.getSysExData()[17] << 7) + message.getSysExData()[18],
				(message.getSysExData()[19] << 7) + message.getSysExData()[20]};
			NotifyChanged();
		}
		else if (IsCspMessage(message, CSP_LENGTH_STATE))
		{
			m_length = {(message.getSysExData()[17] << 7) + message.getSysExData()[18],
				(message.getSysExData()[19] << 7) + message.getSysExData()[20]};
			NotifyChanged();
		}
		else if (IsCspMessage(message, CSP_PLAY_STATE))
		{
			m_playing = message.getSysExData()[17] == 1;
			NotifyChanged();
		}
		else if (IsCspMessage(message, CSP_GUIDE_STATE))
		{
			m_guide = message.getSysExData()[17] == 1;
			NotifyChanged();
		}
		else if (IsCspMessage(message, CSP_STREAM_LIGHTS_STATE))
		{
			m_streamLights = message.getSysExData()[17] == 1;
			NotifyChanged();
		}
		else if (IsCspMessage(message, CSP_STREAM_LIGHTS_SPEED_STATE))
		{
			m_streamLightsFast = message.getSysExData()[17] == 1;
			NotifyChanged();
		}
		else if (IsCspMessage(message, CSP_BACKING_PART_STATE))
		{
			m_backingPart = message.getSysExData()[17] == 1;
			NotifyChanged();
		}
		else if (IsCspMessage(message, CSP_LEFT_PART_STATE))
		{
			m_leftPart = message.getSysExData()[17] == 1;
			NotifyChanged();
		}
		else if (IsCspMessage(message, CSP_RIGHT_PART_STATE))
		{
			m_rightPart = message.getSysExData()[17] == 1;
			NotifyChanged();
		}
		else if (IsCspMessage(message, CSP_VOLUME_STATE))
		{
			Channel ch = (Channel)message.getSysExData()[12];
			m_channels[ch].volume = message.getSysExData()[17];
			NotifyChanged();
		}
		else if (IsCspMessage(message, CSP_PAN_STATE))
		{
			Channel ch = (Channel)message.getSysExData()[12];
			m_channels[ch].pan = message.getSysExData()[17] - PanBase;
			NotifyChanged();
		}
		else if (IsCspMessage(message, CSP_REVERB_STATE))
		{
			Channel ch = (Channel)message.getSysExData()[12];
			m_channels[ch].reverb = message.getSysExData()[17];
			NotifyChanged();
		}
		else if (IsCspMessage(message, CSP_CHANNEL_ENABLE_STATE))
		{
			Channel ch = (Channel)message.getSysExData()[12];
			m_channels[ch].enabled = message.getSysExData()[17] == 1;
			NotifyChanged();
		}
		else if (IsCspMessage(message, CSP_TEMPO_STATE))
		{
			m_tempo = (message.getSysExData()[17] << 7) + message.getSysExData()[18];
			NotifyChanged();
		}
		else if (IsCspMessage(message, CSP_TRANSPOSE_STATE))
		{
			m_transpose = (int)(message.getSysExData()[17]) - TransposeBase;
			NotifyChanged();
		}
		else if (IsCspMessage(message, CSP_LOOP_STATE))
		{
			bool enabled = message.getSysExData()[17] == 1;
			if (enabled)
			{
				m_loop = {{(message.getSysExData()[18] << 7) + message.getSysExData()[19],
					(message.getSysExData()[20] << 7) + message.getSysExData()[21]},
					{(message.getSysExData()[22] << 7) + message.getSysExData()[23],
					(message.getSysExData()[24] << 7) + message.getSysExData()[25]}};
				m_loopStart = {0,0};
			}
			else
			{
				m_loop = {{0,0},{0,0}};
			}
			NotifyChanged();
		}
		else if (IsCspMessage(message, CSP_VOICE_SELECT_STATE) ||
			IsCspMessage(message, CSP_VOICE_SELECT_STATE2))
		{
			ProcessVoiceEvent(message);
			NotifyChanged();
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
			NotifyChanged();
		}
		else if (IsCspMessage(message, CSP_SONG_NAME_STATE))
		{
			m_position = {1,1};
			NotifySongLoaded();
		}
	}
	else if (message.isNoteOnOrOff())
	{
		for (auto listener : m_listeners)
		{
			listener->PianoNoteMessage(message);
		}
	}
}

void PianoController::SetVoice(Channel ch, const String& voice)
{
	String command = String(CSP_VOICE_SELECT).replace("NN", ByteToHex(ch)) + TextToHex(voice);
	SendCspMessage(command);
}

void PianoController::ProcessVoiceEvent(const MidiMessage& message)
{
	Channel ch = (Channel)message.getSysExData()[12];
	int off = message.getSysExData()[7] == 1 ? 17 : 15;
	String voice = BytesToText(message.getSysExData() + off, message.getSysExDataSize() - off);
	m_channels[ch].voice = voice;
}

void PianoController::SetActive(Channel ch, bool active)
{
	String command = String(CSP_CHANNEL_ENABLE).replace("NN", ByteToHex(ch)) +
		(active ? "01" : "00");
	SendCspMessage(command);
}

void PianoController::AddListener(Listener* listener)
{
	RemoveListener(listener);
	m_listeners.push_back(listener);
}

void PianoController::RemoveListener(Listener* listener)
{
	std::vector<Listener*>::iterator pos = std::find(m_listeners.begin(), m_listeners.end(), listener);
	if (pos != m_listeners.end())
	{
		m_listeners.erase(pos);
	}
}

void PianoController::SendMidiMessage(const MidiMessage& message)
{
	m_midiConnector->SendMessage(message);
}

void PianoController::NotifyChanged()
{
	for (auto listener : m_listeners)
	{
		listener->PianoStateChanged();
	}
}

void PianoController::NotifySongLoaded()
{
	for (auto listener : m_listeners)
	{
		listener->PianoSongLoaded();
	}
}

