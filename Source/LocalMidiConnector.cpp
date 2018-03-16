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

#include "../JuceLibraryCode/JuceHeader.h"

#include "LocalMidiConnector.h"

LocalMidiConnector::LocalMidiConnector(AudioDeviceManager* audioDeviceManager)
	: m_audioDeviceManager(audioDeviceManager)
{
	m_audioDeviceManager->addMidiInputCallback("", this);
}

void LocalMidiConnector::handleIncomingMidiMessage(MidiInput* source, const MidiMessage& message)
{
	if (m_listener) m_listener->IncomingMidiMessage(message);
}

void LocalMidiConnector::SendMessage(const MidiMessage& message)
{
	if (m_audioDeviceManager->getDefaultMidiOutput())
	{
		m_audioDeviceManager->getDefaultMidiOutput()->sendMessageNow(message);
	}
}

bool LocalMidiConnector::IsConnected()
{
	return m_audioDeviceManager->getDefaultMidiOutput() != nullptr;
}
