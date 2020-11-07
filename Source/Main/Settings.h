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

class Settings : public ChangeBroadcaster
{
public:
	Settings();
	void Save();
	void Load();

	enum ScoreInstrumentNames
	{
		siHidden,
		siShort,
		siMixed,
		siFull
	};

	enum ScorePart
	{
		spAll,
		spRightAndLeft,
		spRight,
		spLeft
	};

	String pianoIp = "192.168.0.150";
	String midiPort;
	float zoomUi = 1.0;
	Rectangle<int> windowPos;
	bool keyboardVisible = false;
	int keyboardChannel = 1;
	String resourcesPath;
	ScoreInstrumentNames scoreInstrumentNames = siMixed;
	ScorePart scorePart = spRightAndLeft;
	bool scoreShowMidiChannel = true;
	String workingDirectory;
	bool logging = false;
	bool rtpLogging = false;

private:
	PropertiesFile::Options opt;

	void PrepareResources();
};
