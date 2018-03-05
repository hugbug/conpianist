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

class PianoControllerListener
{
public:
	virtual ~PianoControllerListener() {}
	virtual void PlaybackStateChanged() {}
	virtual void SettingsChanged() {}
};

class PianoController : public MidiInputCallback
{
public:
	void SetListener(PianoControllerListener* listener) { m_listener = listener; }
	void SetAudioDeviceManager(AudioDeviceManager* audioDeviceManager);
	void SetRemoteIp(const String& remoteIp) { m_remoteIp = remoteIp; }
	const String& GetRemoteIp() { return m_remoteIp; }
	void Connect();
	void LocalControl(bool enabled);
	bool UploadSong(const File& file);
	void Play();
	void Pause();
	void Stop();
	void Guide(bool enable);
	void StreamLights(bool enable);
	bool GetConnected() { return m_connected; }
	bool GetPlaying() { return m_playing; }
	bool GetGuide() { return m_guide; }
	bool GetStreamLights() { return m_streamLights; }
	bool GetLocalControl() { return m_localControl; }
	int GetSongLength() { return m_songLength; }
	int GetSongPosition() { return m_songPosition; }
	const String& GetModel() { return m_model; }
	const String& GetVersion() { return m_version; }

	void handleIncomingMidiMessage(MidiInput* source, const MidiMessage& message) override;

private:
	PianoControllerListener* m_listener = nullptr;
	AudioDeviceManager* m_audioDeviceManager;
	String m_remoteIp;
	bool m_connected = false;
	bool m_localControl = false;
	bool m_guide = false;
	bool m_streamLights = false;
	bool m_playing = false;
	int m_songLength = 0;
	int m_songPosition = 1;
	String m_model;
	String m_version;

	void SendSysExMessage(const String& command);
	void SendCspMessage(const String& command, bool addDefaultCommandPrefix = true);
	bool IsCspMessage(const MidiMessage& message, const char* messageHex);
};
