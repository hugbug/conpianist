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

#include "Settings.h"

Settings::Settings()
{
#if TARGET_OS_IPHONE
	resourcesPath = File::getSpecialLocation(File::currentApplicationFile).getFullPathName();
#elif __APPLE__
	resourcesPath = File::getSpecialLocation(File::currentApplicationFile).getFullPathName() + "/Contents/Resources";
#else
	resourcesPath = File::getSpecialLocation(File::currentApplicationFile).getParentDirectory(). getFullPathName() + "/Resources";
#endif

	opt.storageFormat = PropertiesFile::StorageFormat::storeAsXML;
	opt.applicationName = "ConPianist";
	opt.osxLibrarySubFolder = "Application Support";
	opt.filenameSuffix = "settings";
}

void Settings::Save()
{
	PropertiesFile prop(opt);

	prop.setValue("PianoIp", pianoIp);
	prop.setValue("MidiPort", midiPort);
	prop.setValue("ZoomUi", zoomUi);
	prop.setValue("Window.X", windowPos.getX());
	prop.setValue("Window.Y", windowPos.getY());
	prop.setValue("Window.Width", windowPos.getWidth());
	prop.setValue("Window.Height", windowPos.getHeight());
	prop.setValue("Keyboard.Visible", keyboardVisible);
	prop.setValue("Keyboard.Channel", keyboardChannel);
	prop.setValue("Score.InstrumentNames", scoreInstrumentNames);
	prop.setValue("Score.Part", scorePart);
	prop.setValue("Score.ShowMidiChannel", scoreShowMidiChannel);

	prop.save();
	sendChangeMessage();
}

void Settings::Load()
{
	PropertiesFile prop(opt);

	pianoIp = prop.getValue("PianoIp", pianoIp);
	midiPort = prop.getValue("MidiPort", midiPort);
	zoomUi = prop.getDoubleValue("ZoomUi", zoomUi);
	windowPos.setX(prop.getIntValue("Window.X", windowPos.getX()));
	windowPos.setY(prop.getIntValue("Window.Y", windowPos.getY()));
	windowPos.setWidth(prop.getIntValue("Window.Width", windowPos.getWidth()));
	windowPos.setHeight(prop.getIntValue("Window.Height", windowPos.getHeight()));
	keyboardVisible = prop.getIntValue("Keyboard.Visible", keyboardVisible);
	keyboardChannel = prop.getIntValue("Keyboard.Channel", keyboardChannel);
	scoreInstrumentNames = (ScoreInstrumentNames)prop.getIntValue("Score.InstrumentNames", scoreInstrumentNames);
	scoreShowMidiChannel = prop.getIntValue("Score.ShowMidiChannel", scoreShowMidiChannel);
	scorePart = (ScorePart)prop.getIntValue("Score.Part", scorePart);
}
