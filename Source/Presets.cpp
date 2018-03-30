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

#include "Presets.h"

namespace
{
	VoiceList voices {
		{"PRESET:/VOICE/Piano/Grand Piano/CFX Grand.T542.VRM", "VRM", "Piano", "Grand Piano"},
		{"PRESET:/VOICE/Piano/Grand Piano/Pop Grand.T228.VRM", "VRM", "Piano", "Grand Piano"},
		{"PRESET:/VOICE/Piano/Upright Piano/Upright Piano.T544.VRM", "VRM", "Piano", "Upright Piano"},
		{"PRESET:/VOICE/Piano/Upright Piano/Pop Upright.T229.NLV", "Natural!", "Piano", "Upright Piano"},
		{"PRESET:/VOICE/Synth/Synth Effects/Pitch Fall.T270.VCE", "Regular", "Synth", "Synth Effects"},
	};
}

VoiceList& Presets::Voices()
{
	return voices;
}
