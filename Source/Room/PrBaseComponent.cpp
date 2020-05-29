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

#include "../JuceLibraryCode/JuceHeader.h"
#include "PrBaseComponent.h"

//==============================================================================
PrBaseComponent::PrBaseComponent (Settings& settings, PianoController& pianoController)
   : settings(settings), pianoController(pianoController)
{

}

PrBaseComponent::~PrBaseComponent()
{
}

void PrBaseComponent::paint (Graphics& g)
{
    g.fillAll(backgroundColor);

	//height = getHeight() - 8;
	//g.drawRect(x, y, width, height);
}

void PrBaseComponent::drawSliderMark(Graphics& g, Slider* slider, int pos)
{
	int width = 2;
	int height = 4;
	int y = slider->getY() + 4;
	if (pos == -1)
	{
		// default pos is center of slider
		pos = slider->proportionOfWidth(0.5000f);
	}
	int x = slider->getX() + pos - width / 2;

	g.setColour(Colour(0xabf0ffff));
	g.fillRect(x, y, width, height);
}

