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

class PianoController : public MidiInputCallback, public ChangeBroadcaster
{
public:
	void SetAudioDeviceManager(AudioDeviceManager* audioDeviceManager);
	void SetRemoteIp(const String& remoteIp) { m_remoteIp = remoteIp; }
	const String& GetRemoteIp() { return m_remoteIp; }
	void Connect();
	bool UploadSong(const File& file);
	void Play();
	void Pause();
	void Stop();
	const String& GetModel() { return m_model; }
	const String& GetVersion() { return m_version; }
	bool GetConnected() { return m_connected; }
	bool GetPlaying() { return m_playing; }
	bool GetGuide() { return m_guide; }
	void SetGuide(bool enable);
	bool GetLocalControl() { return m_localControl; }
	void SetLocalControl(bool enabled);
	bool GetStreamLights() { return m_streamLights; }
	void SetStreamLights(bool enable);
	bool GetStreamLightsFast() { return m_streamLightsFast; }
	void SetStreamLightsFast(bool fast);
	int GetSongLength() { return m_songLength; }
	int GetSongPosition() { return m_songPosition; }
	void SetSongPosition(int position);
	bool GetBackingPart() { return m_backingPart; }
	void SetBackingPart(bool enable);
	bool GetLeftPart() { return m_leftPart; }
	void SetLeftPart(bool enable);
	bool GetRightPart() { return m_rightPart; }
	void SetRightPart(bool enable);

	void handleIncomingMidiMessage(MidiInput* source, const MidiMessage& message) override;

private:
	AudioDeviceManager* m_audioDeviceManager;
	String m_remoteIp;
	String m_model;
	String m_version;
	bool m_connected = false;
	bool m_playing = false;
	bool m_localControl = true;
	bool m_guide = false;
	bool m_streamLights = false;
	bool m_streamLightsFast = false;
	int m_songLength = 0;
	int m_songPosition = 1;
	bool m_backingPart = false;
	bool m_leftPart = false;
	bool m_rightPart = false;

	void SendSysExMessage(const String& command);
	void SendCspMessage(const String& command, bool addDefaultCommandPrefix = true);
	bool IsCspMessage(const MidiMessage& message, const char* messageHex);
};
