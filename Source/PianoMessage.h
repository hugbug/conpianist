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

struct Action
{
	Action(const char* signature);
	Action(int signature) : signature(signature) {}
	bool operator==(const Action& other) const { return other.signature == signature; }
	bool operator!=(const Action& other) const { return other.signature != signature; }

	int signature;

	// ACTIONS

	// Unknown Action (may occur only when parsing sysex)
	const static Action Unknown;

	// Request Property Value from Piano
	const static Action Get;

	// Set Property Value
	const static Action Set;

	// Info from Piano, Containing Property Value
	const static Action Info;

	// Response from Piano to Set-Action; Contains New Property Value
	const static Action Response;

	// Reset Property to Default Value
	const static Action Reset;

	// Activate Events for Property Change
	const static Action Events;
};

struct Property
{
	Property(const char* signature, int length);
	Property(int signature, int length) : signature(signature), length(length) {}
	bool operator==(const Property& other) const { return other.signature == signature; }
	bool operator!=(const Property& other) const { return other.signature != signature; }

	int signature;
	int length;

	// PROPERTIES

	// Unknown Property (may occur only when parsing sysex)
	const static Property Unknown;

	// Value: Piano Model Name (variable length)
	const static Property PianoModel;

	// Value: Firmware Version String (variable length)
	const static Property FirmwareVersion;

	// Value: 0 - Guide Off, 1 - Guide On
	const static Property Guide;

	// Value: 0 - Correct Key, 1 - Any Key, 5 - Your Tempo
	const static Property GuideType;

	// Value (4 Bytes): 2 Bytes for Measure, 2 Bytes for Beat
	const static Property Position;

	// Value (4 Bytes): 2 Bytes for Measure, 2 Bytes for Beat
	const static Property Length;

	// Value: 0 - Stream Lights Off, 1 - Stream Light On
	const static Property StreamLights;

	// Value: 0 - Stream Lights Slow, 1 - Stream Lights Fast
	const static Property StreamSpeed;

	// Value: 0 - Stop, 1 - Play, 2 - Pause
	const static Property Play;

	// Index: 0 - Right Hand, 1 - Left Hand, 3 - Backing
	// Value: 0 - Off, 1 - On
	const static Property Part;

	// Index: 0 - Right Hand, 1 - Left Hand, 3 - Backing
	// Value: 0..F (Midi-Channel 1..16)
	const static Property PartChannel;

	// Value: 0 - Off, 1 - On
	const static Property PartAuto;

	// Value: Song Name (variable length)
	const static Property SongName;

	// Index: Channel; Value: 0..127
	const static Property Volume;

	// Index: Channel; Value: 0..127
	const static Property Pan;

	// Index: Channel; Value: 0..127
	const static Property Reverb;

	// Index: Channel; Value: -2..+2 (Base 0x40)
	const static Property Octave;

	// Value: 5..280 (2 Bytes)
	const static Property Tempo;

	// Index: 2 (const); Value: -12..+12 (Base 0x40)
	const static Property Transpose;

	// Value: 3 Bytes
	const static Property ReverbEffect;

	// Value: 9 Bytes:
	//   1 byte: 0 - Loop Off, 1 - Loop On
	//   4 bytes: Start Position (Measure + Beat)
	//   4 bytes: End Position (Measure + Beat)
	// For Loop Off Use Start Position 1/1 and End Position 2/1 (00 00 01 00 01 00 02 00 01)
	const static Property Loop;

	// Index: Channel; Value: Voice Name from Presets (variable length)
	const static Property VoicePreset;

	// Index: Channel; Value: 4 Bytes
	// Value: combine four 7-bit MIDI-bytes into an integer, then split it into four 8-bit bytes:
	//   0x00MMLLPP (MM - MSB, LL - LSB, PP - PC)
	const static Property VoiceMidi;

	// Index: Channel; Value: 0 - Inactive, 1 - Active
	const static Property Active;

	// Index: Channel; Value: 0 - Not Present, 1 - Channel is Present in MIDI-Song
	const static Property Present;

	// Value: 0 Bytes
	const static Property SongReset;
};

class PianoMessage
{
public:
	PianoMessage(const Action action, const Property property, int index, int value);
	PianoMessage(const Action action, const Property property) :
		PianoMessage(action, property, 0, 0) {}
	PianoMessage(const Action action, const Property property, int value) :
		PianoMessage(action, property, 0, value) {}
	PianoMessage(const Action action, const Property property, int index, const uint8_t* value, int size);
	PianoMessage(const Action action, const Property property, int index, String value);
	PianoMessage(const uint8_t* sysExData, int size);
	const bool DataEqualsTo(const PianoMessage& other) const;
	const MemoryBlock& GetSysExData() const { return m_data; }
	static const bool IsCspMessage(const uint8_t* sysExData, int size);
	const Action GetAction() const;
	const Property GetProperty() const;
	const int GetIndex() const;
	const int GetIntValue() const;
	const String GetStrValue() const;
	const int GetSize() const;
	const uint8_t* GetRawValue() const;

private: 
	void Init(const Action action, const Property property, int index, const uint8_t* value, int size);
	const int LengthOffset() const;
	const int GetSize(int lengthOffset) const;
	const uint8_t* GetRawValue(int lengthOffset) const;

	MemoryBlock m_data;
};

String BytesToText(const uint8* buf, int size);
