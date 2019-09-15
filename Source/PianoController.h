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

	enum VoiceSlot
	{
		vsMain = 0,
		vsLayer = 1,
		vsLeft = 2
	};

	class Listener
	{
	public:
		virtual ~Listener() {}
		virtual void PianoStateChanged() {}
		virtual void PianoSongLoaded() {}
		virtual void PianoNoteMessage(const MidiMessage& message) {}
	};

	void SetMidiConnector(MidiConnector* midiConnector);
	void AddListener(Listener* listener);
	void RemoveListener(Listener* listener);
	void SetRemoteIp(const String& remoteIp) { m_remoteIp = remoteIp; }
	const String& GetRemoteIp() { return m_remoteIp; }
	void Connect();
	void Disconnect();
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
	int GetVolume() { return m_volume; }
	void SetVolume(int volume);
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
	const String& GetVoice(VoiceSlot slot) { return m_voice[slot]; }
	void SetVoice(VoiceSlot slot, const String& voice);
	bool GetVoiceActive(VoiceSlot slot) { return m_voiceActive[slot]; }
	void SetVoiceActive(VoiceSlot slot, bool active);
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
	int m_volume = 0;
	int m_tempo = 0;
	int m_transpose = 0;
	Position m_loopStart{0,0};
	Loop m_loop{{0,0},{0,0}};
	String m_voice[3];
	bool m_voiceActive[3]{true, false, false};
	String m_songFilename;

	void SendSysExMessage(const String& command);
	void SendCspMessage(const String& command, bool addDefaultCommandPrefix = true);
	static bool IsCspMessage(const MidiMessage& message, const char* messageHex);
	void ProcessVoiceEvent(const MidiMessage& message);

	void NotifyChanged();
	void NotifySongLoaded();
};
