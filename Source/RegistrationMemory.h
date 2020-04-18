/*
 *  This file is part of ConPianist. See <https://github.com/hugbug/conpianist>.
 *
 *  Copyright (C) 2020 Andrey Prygunkov <hugbug@users.sourceforge.net>
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

#include "PianoController.h"
#include "Settings.h"

class RegistrationMemory
{
public:
	struct Options
	{
		bool songname = true;
		bool voices = true;
		bool mixer = true;
		bool balance = true;
		bool playback = true;
		bool settings = true;
	};

	RegistrationMemory(PianoController& pianoController, Settings& settings, const Options options, const URL url) :
		pianoController(pianoController), settings(settings), options(options), url(url) {}
	void Save();
	void Load();

private:
	PianoController& pianoController;
	Settings& settings;
	Options options;
	URL url;
	XmlElement* root = nullptr;

	void SaveChannel(PianoController::Channel channel, String name);
	void LoadChannel(PianoController::Channel channel, String name);
	void SaveVoice(PianoController::Channel channel, String name);
	void LoadVoice(PianoController::Channel channel, String name);
	void SaveSplitPoint();
	void LoadSplitPoint();
	void SaveReverbEffect();
	void LoadReverbEffect();
	void SavePlayback();
	void LoadPlayback();
	void SaveSettings();
	void LoadSettings();
};
