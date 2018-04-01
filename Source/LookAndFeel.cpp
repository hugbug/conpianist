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

#include "LookAndFeel.h"

void ::LookAndFeel::drawButtonBackground(Graphics& gr, Button& btn, const Colour& backgroundColour,
	bool isMouseOverButton, bool isButtonDown)
{
	bool toggle = btn.getProperties().contains("toggle");

	Colour outline = Colour(toggle ? 0xFEEE6C0A : 0xff4e5b62);
	Colour fill = Colour(0x0);

	if (((isMouseOverButton || isButtonDown) && !toggle) || (btn.getToggleState() && toggle))
	{
		fill = Colour(toggle ? 0xFEEE6C0A : 0xff3D484E);
	}

	Rectangle<int> r = btn.getLocalBounds();

	gr.setColour(fill);
	gr.fillRoundedRectangle(r.getX(), r.getY(), r.getWidth(), r.getHeight(), 5);

	gr.setColour(outline);
	gr.drawRoundedRectangle(r.getX(), r.getY(), r.getWidth(), r.getHeight(), 5, 2);
}

void ::LookAndFeel::drawImageButton(Graphics& gr, Image* im,
	int imageX, int imageY, int imageW, int imageH,
	const Colour& overlayColour, float imageOpacity, ImageButton& btn)
{
	Rectangle<int> r = btn.getLocalBounds();
	gr.setColour(Colour(0xFEEE6C0A));

	if (btn.getToggleState())
	{
		gr.fillRoundedRectangle(r.getX(), r.getY(), r.getWidth(), r.getHeight(), 5);
		gr.drawRoundedRectangle(r.getX(), r.getY(), r.getWidth(), r.getHeight(), 5, 2);
	}

	LookAndFeel_V4::drawImageButton(gr, im, imageX, imageY, imageW, imageH, overlayColour, imageOpacity, btn);
}
