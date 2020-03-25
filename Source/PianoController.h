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

#include "../JuceLibraryCode/JuceHeader.h"

#include "MidiConnector.h"

class PianoController : public MidiConnector::Listener
{
public:
	struct Position
	{
		int measure;
		int beat;
		bool operator==(const Position& rhs) { return rhs.measure == measure && rhs.beat == beat; }
	};

	struct Loop
	{
		Position begin;
		Position end;
	};

	enum Channel
	{
		chNone = -1,
		chMain = 0x00,
		chLayer = 0x01,
		chLeft = 0x02,
		chMidi1 = 0x10,
		chMidi2, chMidi3, chMidi4, chMidi5, chMidi6, chMidi7, chMidi8,
		chMidi9, chMidi10, chMidi11, chMidi12, chMidi13, chMidi14, chMidi15,
		chMidi16 = 0x1F,
		chMic = 0x40,
		chAuxIn = 0x41,
		chWave = 0x44,
		chMidiMaster = 0x50,
		chStyle = 0x51
	};

	struct ChannelInfo
	{
		bool enabled = false;
		int volume = 0; // 0..127
		int pan = 0; // 0..127
		int reverb = 0; // 0..127
		String voice;
	};

	enum Aspect
	{
		apConnection,
		apLocalControl,
		apSongLoaded,
		apPosition,
		apPlayback,
		apGuide,
		apStreamLights,
		apLoop,
		apTranspose,
		apTempo,
		apPart,
		apVolume,
		apPan,
		apReverb,
		apActive,
		apVoice
	};

	class Listener
	{
	public:
		virtual ~Listener() {}
		virtual void PianoStateChanged(Aspect aspect, Channel channel) {}
		virtual void PianoNoteMessage(const MidiMessage& message) {}
	};

	void SetMidiConnector(MidiConnector* midiConnector);
	void AddListener(Listener* listener);
	void RemoveListener(Listener* listener);
	void SetRemoteIp(const String& remoteIp) { m_remoteIp = remoteIp; }
	const String& GetRemoteIp() { return m_remoteIp; }
	void Connect();
	void Disconnect();
	void Reset();
	bool UploadSong(const File& file);
	void Play();
	void Pause();
	void Stop();
	const String& GetModel() { return m_model; }
	const String& GetVersion() { return m_version; }
	bool IsConnected() { return m_connected; }
	bool GetPlaying() { return m_playing; }
	bool GetGuide() { return m_guide; }
	void SetGuide(bool enable);
	bool GetLocalControl() { return m_localControl; }
	void SetLocalControl(bool enabled);
	bool GetStreamLights() { return m_streamLights; }
	void SetStreamLights(bool enable);
	bool GetStreamLightsFast() { return m_streamLightsFast; }
	void SetStreamLightsFast(bool fast);
	Position GetLength() { return m_length; }
	Position GetPosition() { return m_position; }
	void SetPosition(const Position position);
	Loop GetLoop() { return m_loop; }
	void SetLoop(Loop loop);
	Position GetLoopStart() { return m_loopStart; }
	void SetLoopStart(const Position loopStart);
	void ResetLoop();
	int GetVolume(Channel ch) { return m_channels[ch].volume; }
	void SetVolume(Channel ch, int volume);
	void ResetVolume(Channel ch);
	int GetPan(Channel ch) { return m_channels[ch].pan; }
	void SetPan(Channel ch, int pan);
	void ResetPan(Channel ch);
	int GetReverb(Channel ch) { return m_channels[ch].reverb; }
	void SetReverb(Channel ch, int reverb);
	void ResetReverb(Channel ch);
	int GetTempo() { return m_tempo; }
	void SetTempo(int tempo);
	void ResetTempo();
	int GetTranspose() { return m_transpose; }
	void SetTranspose(int transpose);
	bool GetBackingPart() { return m_backingPart; }
	void SetBackingPart(bool enable);
	bool GetLeftPart() { return m_leftPart; }
	void SetLeftPart(bool enable);
	bool GetRightPart() { return m_rightPart; }
	void SetRightPart(bool enable);
	const String& GetVoice(Channel ch) { return m_channels[ch].voice; }
	void SetVoice(Channel ch, const String& voice);
	bool GetActive(Channel ch) { return m_channels[ch].enabled; }
	void SetActive(Channel ch, bool active);
	const String& GetSongFilename() { return m_songFilename; }

	void SendMidiMessage(const MidiMessage& message);
	void IncomingMidiMessage(const MidiMessage& message);

	static const int MinVolume = 0;
	static const int MaxVolume = 127;
	static const int DefaultVolume = 100;
	static const int MinTempo = 5;
	static const int MaxTempo = 280;
	static const int DefaultTempo = 120;
	static const int MinTranspose = -12;
	static const int MaxTranspose = +12;
	static const int DefaultTranspose = 0;
	static const int TransposeBase = 0x40;
	static const int MinPan = -64;
	static const int MaxPan = -63;
	static const int DefaultPan = 0;
	static const int PanBase = 0x40;
	static const int MinReverb = 0;
	static const int MaxReverb = 127;
	static const int DefaultReverb = 0;

private:
	MidiConnector* m_midiConnector;
	std::vector<Listener*> m_listeners;
	String m_remoteIp;
	String m_model;
	String m_version;
	bool m_connected = false;
	bool m_playing = false;
	bool m_localControl = true;
	bool m_guide = false;
	bool m_streamLights = false;
	bool m_streamLightsFast = false;
	Position m_length{0,0};
	Position m_position{0,0};
	bool m_backingPart = false;
	bool m_leftPart = false;
	bool m_rightPart = false;
	int m_tempo = 0;
	int m_transpose = 0;
	Position m_loopStart{0,0};
	Loop m_loop{{0,0},{0,0}};
	ChannelInfo m_channels[127];
	String m_songFilename;

	void SendSysExMessage(const String& command);
	void SendCspMessage(const String& command, bool addDefaultCommandPrefix = true);
	static bool IsCspMessage(const MidiMessage& message, const char* messageHex);
	void ProcessVoiceEvent(const MidiMessage& message);

	void NotifyChanged(Aspect aspect, Channel channel = chNone);
};
