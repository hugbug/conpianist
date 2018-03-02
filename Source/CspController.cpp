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

#include "CspController.h"

void CspController::Init(AudioDeviceManager* audioDeviceManager)
{
	m_audioDeviceManager = audioDeviceManager;
}

void CspController::SwitchLocalControl(bool enabled)
{
	MidiMessage localControlMessage = MidiMessage::controllerEvent(1, 122, enabled ? 127 : 0);
	m_audioDeviceManager->getDefaultMidiOutput()->sendMessageNow(localControlMessage);
}

void CspController::SendCspMessage(const String& command)
{
	String CSP_PREFIX = "43 73 01 52 25 26 01 01 ";
	MemoryBlock rawData;
	rawData.loadFromHexString(CSP_PREFIX + command);
	MidiMessage message = MidiMessage::createSysExMessage(rawData.getData(), (int)rawData.getSize());
	m_audioDeviceManager->getDefaultMidiOutput()->sendMessageNow(message);
}

void CspController::Play()
{
	SendCspMessage("04 00 05 01 00 01 00 00 01 01");
}

void CspController::Pause()
{
	SendCspMessage("04 00 05 01 00 01 00 00 01 02");
}

void CspController::Guide(bool enable)
{
	SendCspMessage(String("04 03 00 01 00 01 00 00 01 ") + (enable ? "01" : "00"));
}

void CspController::StreamLights(bool enable)
{
	SendCspMessage(String("04 02 00 01 00 01 00 00 01 ") + (enable ? "01" : "00"));
}

