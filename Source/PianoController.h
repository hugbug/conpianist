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

class PianoMessage;

class PianoController : public MidiConnector::Listener
{
public:
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
	static const int DefaultReverbEffect = 0x0118; // Recital Hall
	static const int MinOctave = -2;
	static const int MaxOctave = +2;
	static const int DefaultOctave = 0;
	static const int OctaveBase = 0x40;

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
		bool enabled = false; // channel is present in current song; only for Midi1..Midi16
		bool active = false; // channel is active for playback
		int volume = DefaultVolume; // 0..127
		int pan = DefaultPan; // 0..127
		int reverb = DefaultReverb; // 0..127
		int octave = DefaultOctave; // -2..+2
		String voice;
	};

	enum Part
	{
		paRight = 0,
		paLeft = 1,
		paBacking = 2
	};

	enum Aspect
	{
		apConnection,
		apLocalControl,
		apSongName,
		apLength,
		apPosition,
		apPlayback,
		apGuide,
		apStreamLights,
		apLoop,
		apTranspose,
		apTempo,
		apReverbEffect,
		apPart,
		apVolume,
		apPan,
		apReverb,
		apOctave,
		apEnable,
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

	PianoController();
	~PianoController() {}
	void SetMidiConnector(MidiConnector* midiConnector);
	void AddListener(Listener* listener);
	void RemoveListener(Listener* listener);
	void SetRemoteIp(const String& remoteIp) { m_remoteIp = remoteIp; }
	const String& GetRemoteIp() { return m_remoteIp; }
	void Connect();
	void Disconnect();
	void Reset();
	void Sync();
	void InitEvents();
	bool UploadSong(const File& file);
	void ResetSong();
	void Play();
	void Pause();
	void Stop();
	const String& GetModel() { return m_model; }
	const String& GetVersion() { return m_version; }
	bool IsConnected() { return m_connected; }
	bool IsSongLoaded() { return m_songLoaded; }
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
	int GetOctave(Channel ch) { return m_channels[ch].octave; }
	void SetOctave(Channel ch, int octave);
	int GetTempo() { return m_tempo; }
	void SetTempo(int tempo);
	void ResetTempo();
	int GetTranspose() { return m_transpose; }
	void SetTranspose(int transpose);
	bool GetPart(Part part) { return m_parts[part]; }
	void SetPart(Part part, bool enable);
	const String& GetVoice(Channel ch) { return m_channels[ch].voice; }
	void SetVoice(Channel ch, const String& voice);
	bool GetActive(Channel ch) { return m_channels[ch].active; }
	void SetActive(Channel ch, bool active);
	bool GetEnabled(Channel ch) { return m_channels[ch].enabled; }
	int GetReverbEffect() { return m_reverbEffect; }
	void SetReverbEffect(int effect);
	const String& GetSongName() { return m_songName; }

	void SendMidiMessage(const MidiMessage& message);
	void IncomingMidiMessage(const MidiMessage& message) override;

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
	bool m_parts[3]{false,false,false};
	int m_tempo = DefaultTempo;
	int m_transpose = DefaultTranspose;
	Position m_loopStart{0,0};
	Loop m_loop{{0,0},{0,0}};
	ChannelInfo m_channels[127];
	int m_reverbEffect = 0;
	String m_songName;
	bool m_songLoaded = false;

	void SendCspMessage(const PianoMessage& message);
	void NotifyChanged(Aspect aspect, Channel channel = chNone);
	void ResyncStateFromPiano();
};
