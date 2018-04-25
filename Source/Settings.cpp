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

#include "Settings.h"

String Settings::ResourcesPath()
{
	return File::getSpecialLocation(File::currentApplicationFile).getParentDirectory().getFullPathName() + "/Resources";
}

void Settings::Save()
{
	XmlElement state("ConPianistState");
	state.createNewChildElement("PianoIp")->addTextElement(pianoIp);
	state.createNewChildElement("MidiPort")->addTextElement(midiPort);
	state.createNewChildElement("ZoomUi")->addTextElement(String(zoomUi));
	state.createNewChildElement("Window.X")->addTextElement(String(windowPos.getX()));
	state.createNewChildElement("Window.Y")->addTextElement(String(windowPos.getY()));
	state.createNewChildElement("Window.Width")->addTextElement(String(windowPos.getWidth()));
	state.createNewChildElement("Window.Height")->addTextElement(String(windowPos.getHeight()));
	state.createNewChildElement("Keyboard.Visible")->addTextElement(keyboardVisible ? "1" : "0");
	state.createNewChildElement("Keyboard.Channel")->addTextElement(String(keyboardChannel));

	File stateFile = (File::getSpecialLocation(File::userHomeDirectory)).getFullPathName() + "/.conpianist";
	state.writeToFile(stateFile, "");

	sendChangeMessage();
}

void Settings::Load()
{
	File stateFile = (File::getSpecialLocation(File::userHomeDirectory)).getFullPathName() + "/.conpianist";
	if (!stateFile.exists())
	{
		return;
	}

	ScopedPointer<XmlElement> savedState = XmlDocument::parse(stateFile);
	if (!savedState)
	{
		return;
	}

	XmlElement* el;

	if ((el = savedState->getChildByName("PianoIp")))
	{
		pianoIp = el->getAllSubText();
	}

	if ((el = savedState->getChildByName("MidiPort")))
	{
		midiPort = el->getAllSubText();
	}

	if ((el = savedState->getChildByName("ZoomUi")))
	{
		zoomUi = el->getAllSubText().getFloatValue();
	}

	if ((el = savedState->getChildByName("Window.X")))
	{
		windowPos.setX(el->getAllSubText().getIntValue());
	}

	if ((el = savedState->getChildByName("Window.Y")))
	{
		windowPos.setY(el->getAllSubText().getIntValue());
	}

	if ((el = savedState->getChildByName("Window.Width")))
	{
		windowPos.setWidth(el->getAllSubText().getIntValue());
	}

	if ((el = savedState->getChildByName("Window.Height")))
	{
		windowPos.setHeight(el->getAllSubText().getIntValue());
	}

	if ((el = savedState->getChildByName("Keyboard.Visible")))
	{
		keyboardVisible = el->getAllSubText().getIntValue() != 0;
	}

	if ((el = savedState->getChildByName("Keyboard.Channel")))
	{
		keyboardChannel = el->getAllSubText().getIntValue();
	}
}
