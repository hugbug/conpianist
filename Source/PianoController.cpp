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

#include "PianoController.h"
#include "PianoMessage.h"

static const char* CSP_PREFIX = "43 73 01 52 25 26 ";
static const char* CSP_MODEL_STATE = "00 00 0f 01 18 01 00 01 00";
static const char* CSP_VERSION_STATE = "00 00 0f 01 0b 01 00 01 00";
static const char* CSP_GUIDE_STATE = "00 00 04 03 00 01 00 01 00 00 01";
static const char* CSP_POSITION_STATE = "00 00 04 00 0a 01 00 01 00 00 04";
static const char* CSP_LENGTH_STATE = "00 00 04 00 1b 01 00 01 00 00 04";
static const char* CSP_PLAY_STATE = "00 00 04 00 05 01 00 01 00 00 01";
static const char* CSP_STREAM_LIGHTS_STATE = "00 00 04 02 00 01 00 01 00 00 01";
static const char* CSP_STREAM_LIGHTS_SPEED_STATE = "00 00 04 02 02 01 00 01 00 00 01";
static const char* CSP_BACKING_PART_STATE = "00 00 04 00 0e 01 02 01 00 00 01";
static const char* CSP_LEFT_PART_STATE = "00 00 04 00 0e 01 01 01 00 00 01";
static const char* CSP_RIGHT_PART_STATE = "00 00 04 00 0e 01 00 01 00 00 01";
static const char* CSP_SONG_NAME_STATE = "00 00 04 00 01 01 00 01 00";
static const char* CSP_VOLUME_STATE = "00 00 0c 00 00 01";
static const char* CSP_PAN_STATE = "00 00 0c 00 03 01";
static const char* CSP_REVERB_STATE = "00 00 0c 00 04 01";
static const char* CSP_OCTAVE_STATE = "00 00 0c 00 12 01";
static const char* CSP_TEMPO_STATE = "00 00 08 00 00 01 01 01 00 00 02";
static const char* CSP_TRANSPOSE_STATE = "00 00 0a 00 00 01 02 01 00 00 01";
static const char* CSP_REVERB_EFFECT_STATE = "00 00 0c 01 00 01 00 01 00 00 03 00";
static const char* CSP_LOOP_STATE = "00 00 04 00 0d 01 00 01 00 00 09";
static const char* CSP_VOICE_SELECT_STATE = "00 00 02 00 00 01";
static const char* CSP_VOICE_SELECT_STATE2 = "00 01 02 00 00 01";
static const char* CSP_CHANNEL_ACTIVE_STATE = "00 00 0c 00 01 01";
static const char* CSP_CHANNEL_VOICE_STATE = "00 00 02 00 01 01";
static const char* CSP_CHANNEL_ENABLE_STATE = "00 00 04 01 00 01";

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


void PianoController::SetMidiConnector(MidiConnector* midiConnector)
{
	m_midiConnector = midiConnector;
	m_midiConnector->SetListener(this);
}

void PianoController::Connect()
{
	SendCspMessage(PianoMessage(Action::Get, Property::PianoModel));
	SendCspMessage(PianoMessage(Action::Get, Property::FirmwareVersion));
}

void PianoController::Reset()
{
	// Activate feedback events from piano
	SendCspMessage(PianoMessage(Action::Events, Property::Length));
	SendCspMessage(PianoMessage(Action::Events, Property::Position));
	SendCspMessage(PianoMessage(Action::Events, Property::Play));
	SendCspMessage(PianoMessage(Action::Events, Property::Part));
	SendCspMessage(PianoMessage(Action::Events, Property::Guide));
	SendCspMessage(PianoMessage(Action::Events, Property::StreamLights));
	SendCspMessage(PianoMessage(Action::Events, Property::StreamLightsSpeed));
	SendCspMessage(PianoMessage(Action::Events, Property::Volume));
	SendCspMessage(PianoMessage(Action::Events, Property::Pan));
	SendCspMessage(PianoMessage(Action::Events, Property::Reverb));
	SendCspMessage(PianoMessage(Action::Events, Property::Octave));
	SendCspMessage(PianoMessage(Action::Events, Property::Tempo));
	SendCspMessage(PianoMessage(Action::Events, Property::Transpose));
	SendCspMessage(PianoMessage(Action::Events, Property::ReverbEffect));
	SendCspMessage(PianoMessage(Action::Events, Property::Loop));
	SendCspMessage(PianoMessage(Action::Events, Property::VoicePreset));
	SendCspMessage(PianoMessage(Action::Events, Property::Active));
	SendCspMessage(PianoMessage(Action::Events, Property::Present));
	SendCspMessage(PianoMessage(Action::Events, Property::VoiceMidi));
	SendCspMessage(PianoMessage(Action::Events, Property::SongName));

	Stop();

	// Sleep is not nice, we should wait for a confirmation message instead.
	// Without waiting the config-commands below do not issue change events.
	Sleep(150);

	ResetSong();

	// Sleep is not nice, we should wait for a confirmation message instead.
	// Without waiting the config-commands below do not issue change events.
	Sleep(1000);

	SetLocalControl(true);

	SetGuide(true);
	SetStreamLights(false);
	SetStreamLightsFast(false);
	SetGuide(false);
	SetStreamLights(true);
	SetStreamLightsFast(true);

	for (Channel ch : ValidChannelIds)
	{
		m_channels[ch].enabled = (ch < chMidi1 || ch > chMidi16) && (ch != chMidiMaster);
		m_channels[ch].active = false;

		SetVolume(ch, MinVolume);
		SetVolume(ch, DefaultVolume);
		ResetVolume(ch);

		SetPan(ch, MinPan);
		SetPan(ch, DefaultPan);
		ResetPan(ch);

		SetReverb(ch, MinReverb);
		SetReverb(ch, DefaultReverb);
		ResetReverb(ch);

		// Sleep is not nice, we should wait for confirmation messages instead.
		// Without waiting the piano may miss some commands because there are too many.
		Sleep(20);
	}

	SetTempo(MinTempo);
	SetTempo(DefaultTempo);
	ResetTempo();
	SetTranspose(MinTranspose);
	SetTranspose(DefaultTranspose);
	SetReverbEffect(DefaultReverbEffect);

	SetOctave(chMain, 0);
	SetOctave(chLayer, 0);
	SetOctave(chLeft, 0);

	// set internal active for channels
	m_channels[chMain].active = true;
	m_channels[chLayer].active = false;
	m_channels[chLeft].active = false;
	m_channels[chMidiMaster].active = false;
	m_channels[chMic].active = true;
	m_channels[chAuxIn].active = true;

	SetActive(chMain, true);
	SetActive(chLayer, false);
	SetActive(chLeft, false);
	SetActive(chMidiMaster, false);
	SetActive(chMic, true);
	SetActive(chAuxIn, true);

	// By trying to set an invalid voice we cause the piano to fire
	// event "CSP_VOICE_SELECT_STATE2" containing info about current voice.
	// That's how we know which voice is selected without changing it
	SetVoice(chMain, "");
	SetVoice(chLayer, "");
	SetVoice(chLeft, "");
}

void PianoController::Disconnect()
{
	if (m_connected)
	{
		m_connected = false;
		NotifyChanged(apConnection);
	}
}

void PianoController::SetLocalControl(bool enabled)
{
	m_localControl = enabled;
	MidiMessage localControlMessage = MidiMessage::controllerEvent(1, 122, enabled ? 127 : 0);
	m_midiConnector->SendMessage(localControlMessage);
	NotifyChanged(apLocalControl);
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

void PianoController::SendCspMessage(const PianoMessage& message)
{
	MidiMessage midiMessage = MidiMessage::createSysExMessage(message.GetData().getData(), (int)message.GetData().getSize());
	m_midiConnector->SendMessage(midiMessage);
}

void PianoController::ResetSong()
{
	SendCspMessage(PianoMessage(Action::Set, Property::SongReset));
}

void PianoController::Play()
{
	SendCspMessage(PianoMessage(Action::Set, Property::Play, 1));
}

void PianoController::Pause()
{
	SendCspMessage(PianoMessage(Action::Set, Property::Play, 2));
}

void PianoController::Stop()
{
	SendCspMessage(PianoMessage(Action::Set, Property::Play, 0));
}

void PianoController::SetGuide(bool enable)
{
	SendCspMessage(PianoMessage(Action::Set, Property::Guide, enable ? 1 : 0));
}

void PianoController::SetStreamLights(bool enable)
{
	SendCspMessage(PianoMessage(Action::Set, Property::StreamLights, enable ? 1 : 0));
}

void PianoController::SetStreamLightsFast(bool fast)
{
	SendCspMessage(PianoMessage(Action::Set, Property::StreamLightsSpeed, fast ? 1 : 0));
}

void PianoController::SetPosition(const Position position)
{
	uint8_t data[4];
	data[0] = (position.measure >> 7) & 0x7f;
	data[1] = (position.measure >> 0) & 0x7f;
	data[2] = (position.beat >> 7) & 0x7f;
	data[3] = (position.beat >> 0) & 0x7f;
	SendCspMessage(PianoMessage(Action::Set, Property::Position, 0, 4, data));
}

void PianoController::SetVolume(Channel ch, int volume)
{
	SendCspMessage(PianoMessage(Action::Set, Property::Volume, ch, volume));
}

void PianoController::ResetVolume(Channel ch)
{
	SendCspMessage(PianoMessage(Action::Reset, Property::Volume, ch, 0));
}

void PianoController::SetPan(Channel ch, int pan)
{
	SendCspMessage(PianoMessage(Action::Set, Property::Pan, ch, pan));
}

void PianoController::ResetPan(Channel ch)
{
	SendCspMessage(PianoMessage(Action::Reset, Property::Pan, ch, 0));
}

void PianoController::SetReverb(Channel ch, int reverb)
{
	SendCspMessage(PianoMessage(Action::Set, Property::Reverb, ch, reverb));
}

void PianoController::ResetReverb(Channel ch)
{
	SendCspMessage(PianoMessage(Action::Reset, Property::Reverb, ch, 0));
}

void PianoController::SetOctave(Channel ch, int octave)
{
	SendCspMessage(PianoMessage(Action::Set, Property::Octave, ch, octave + OctaveBase));
}

void PianoController::SetTempo(int tempo)
{
	SendCspMessage(PianoMessage(Action::Set, Property::Tempo, tempo));
}

void PianoController::ResetTempo()
{
	SendCspMessage(PianoMessage(Action::Reset, Property::Tempo));
}

void PianoController::SetTranspose(int transpose)
{
	SendCspMessage(PianoMessage(Action::Set, Property::Transpose, 2, transpose + TransposeBase));
}

void PianoController::SetReverbEffect(int effect)
{
	SendCspMessage(PianoMessage(Action::Set, Property::ReverbEffect, 0, effect));
}

void PianoController::SetBackingPart(bool enable)
{
	SendCspMessage(PianoMessage(Action::Set, Property::Part, 2, enable ? 1 : 0));
}

void PianoController::SetLeftPart(bool enable)
{
	SendCspMessage(PianoMessage(Action::Set, Property::Part, 1, enable ? 1 : 0));
}

void PianoController::SetRightPart(bool enable)
{
	SendCspMessage(PianoMessage(Action::Set, Property::Part, 0, enable ? 1 : 0));
}

void PianoController::SetLoop(Loop loop)
{
	m_loopStart = {0,0};
	uint8_t data[9] = {1,
		(uint8_t)((loop.begin.measure >> 7) & 0x7f),
		(uint8_t)((loop.begin.measure >> 0) & 0x7f),
		(uint8_t)((loop.begin.beat >> 7) & 0x7f),
		(uint8_t)((loop.begin.beat >> 0) & 0x7f),
		(uint8_t)((loop.end.measure >> 7) & 0x7f),
		(uint8_t)((loop.end.measure >> 0) & 0x7f),
		(uint8_t)((loop.end.beat >> 7) & 0x7f),
		(uint8_t)((loop.end.beat >> 0) & 0x7f)};
	SendCspMessage(PianoMessage(Action::Set, Property::Loop, 0, 9, data));
}

void PianoController::ResetLoop()
{
	m_loopStart = {0,0};
	uint8_t data[9] = {0,0,1,0,1,0,2,0,1};
	SendCspMessage(PianoMessage(Action::Set, Property::Loop, 0, 9, data));
}

void PianoController::SetLoopStart(const Position loopStart)
{
	m_loopStart = loopStart;
	NotifyChanged(apLoop);
}

void PianoController::SetVoice(Channel ch, const String& voice)
{
	SendCspMessage(PianoMessage(Action::Set, Property::VoicePreset, ch, voice));
}

void PianoController::SetActive(Channel ch, bool active)
{
	SendCspMessage(PianoMessage(Action::Set, Property::Active, ch, active ? 1 : 0));
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
			NotifyChanged(apPosition);
		}
		else if (IsCspMessage(message, CSP_LENGTH_STATE))
		{
			m_length = {(message.getSysExData()[17] << 7) + message.getSysExData()[18],
				(message.getSysExData()[19] << 7) + message.getSysExData()[20]};
			m_songLoaded = m_length.measure > 1 || m_length.beat > 1;
			m_channels[chMidiMaster].enabled = m_songLoaded;
			m_channels[chMidiMaster].active = m_songLoaded;
			NotifyChanged(apLength);
			NotifyChanged(apEnable, chMidiMaster);
		}
		else if (IsCspMessage(message, CSP_PLAY_STATE))
		{
			m_playing = message.getSysExData()[17] == 1;
			NotifyChanged(apPlayback);
		}
		else if (IsCspMessage(message, CSP_GUIDE_STATE))
		{
			m_guide = message.getSysExData()[17] == 1;
			NotifyChanged(apGuide);
		}
		else if (IsCspMessage(message, CSP_STREAM_LIGHTS_STATE))
		{
			m_streamLights = message.getSysExData()[17] == 1;
			NotifyChanged(apStreamLights);
		}
		else if (IsCspMessage(message, CSP_STREAM_LIGHTS_SPEED_STATE))
		{
			m_streamLightsFast = message.getSysExData()[17] == 1;
			NotifyChanged(apStreamLights);
		}
		else if (IsCspMessage(message, CSP_BACKING_PART_STATE))
		{
			m_backingPart = message.getSysExData()[17] == 1;
			NotifyChanged(apPart);
		}
		else if (IsCspMessage(message, CSP_LEFT_PART_STATE))
		{
			m_leftPart = message.getSysExData()[17] == 1;
			NotifyChanged(apPart);
		}
		else if (IsCspMessage(message, CSP_RIGHT_PART_STATE))
		{
			m_rightPart = message.getSysExData()[17] == 1;
			NotifyChanged(apPart);
		}
		else if (IsCspMessage(message, CSP_VOLUME_STATE))
		{
			Channel ch = (Channel)message.getSysExData()[12];
			m_channels[ch].volume = message.getSysExData()[17];
			NotifyChanged(apVolume, ch);
		}
		else if (IsCspMessage(message, CSP_PAN_STATE))
		{
			Channel ch = (Channel)message.getSysExData()[12];
			m_channels[ch].pan = message.getSysExData()[17] - PanBase;
			NotifyChanged(apPan, ch);
		}
		else if (IsCspMessage(message, CSP_REVERB_STATE))
		{
			Channel ch = (Channel)message.getSysExData()[12];
			m_channels[ch].reverb = message.getSysExData()[17];
			NotifyChanged(apReverb, ch);
		}
		else if (IsCspMessage(message, CSP_OCTAVE_STATE))
		{
			Channel ch = (Channel)message.getSysExData()[12];
			m_channels[ch].octave = message.getSysExData()[17] - OctaveBase;
			NotifyChanged(apOctave, ch);
		}
		else if (IsCspMessage(message, CSP_CHANNEL_ACTIVE_STATE))
		{
			Channel ch = (Channel)message.getSysExData()[12];
			m_channels[ch].active = message.getSysExData()[17] == 1;
			NotifyChanged(apActive, ch);
		}
		else if (IsCspMessage(message, CSP_CHANNEL_ENABLE_STATE))
		{
			Channel ch = (Channel)message.getSysExData()[12];
			m_channels[ch].enabled = message.getSysExData()[17] == 1;
			NotifyChanged(apEnable, ch);
		}
		else if (IsCspMessage(message, CSP_CHANNEL_VOICE_STATE))
		{
			Channel ch = (Channel)message.getSysExData()[12];
			m_channels[ch].voice = String(
				(message.getSysExData()[17] << 7 * 3) +
				(message.getSysExData()[18] << 7 * 2) +
				(message.getSysExData()[19] << 7) +
				 message.getSysExData()[20]);
			NotifyChanged(apVoice, ch);
		}
		else if (IsCspMessage(message, CSP_TEMPO_STATE))
		{
			m_tempo = (message.getSysExData()[17] << 7) + message.getSysExData()[18];
			NotifyChanged(apTempo);
		}
		else if (IsCspMessage(message, CSP_TRANSPOSE_STATE))
		{
			m_transpose = (int)(message.getSysExData()[17]) - TransposeBase;
			NotifyChanged(apTranspose);
		}
		else if (IsCspMessage(message, CSP_REVERB_EFFECT_STATE))
		{
			m_reverbEffect = (message.getSysExData()[18] << 7) + message.getSysExData()[19];
			NotifyChanged(apReverbEffect);
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
			NotifyChanged(apLoop);
		}
		else if (IsCspMessage(message, CSP_VOICE_SELECT_STATE) ||
			IsCspMessage(message, CSP_VOICE_SELECT_STATE2))
		{
			ProcessVoiceEvent(message);
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
			NotifyChanged(apConnection);
		}
		else if (IsCspMessage(message, CSP_SONG_NAME_STATE))
		{
			m_position = {1,1};
			NotifyChanged(apSongLoaded);
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

void PianoController::ProcessVoiceEvent(const MidiMessage& message)
{
	Channel ch = (Channel)message.getSysExData()[12];
	int off = message.getSysExData()[7] == 1 ? 17 : 15;
	String voice = BytesToText(message.getSysExData() + off, message.getSysExDataSize() - off);
	m_channels[ch].voice = voice;
	NotifyChanged(apVoice, ch);
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

void PianoController::NotifyChanged(Aspect aspect, Channel channel)
{
	for (auto listener : m_listeners)
	{
		listener->PianoStateChanged(aspect, channel);
	}
}
