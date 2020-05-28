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

void ::LookAndFeel::showModalDialog(Component* comp, const String& title)
{
	DialogWindow::LaunchOptions dialog;
	dialog.content.setOwned(comp);
	dialog.dialogTitle = title;
	dialog.useNativeTitleBar = (SystemStats::getOperatingSystemType() & SystemStats::Windows) ||
		(SystemStats::getOperatingSystemType() & SystemStats::MacOSX);
	dialog.resizable = false;

	TopLevelWindow* win = TopLevelWindow::getActiveTopLevelWindow();
	win->getChildren()[0]->setAlpha(0.3);
	dialog.runModal();
	win->getChildren()[0]->setAlpha(1.0);
}

void ::LookAndFeel::drawButtonBackground(Graphics& gr, Button& btn, const Colour& backgroundColour,
	bool isMouseOverButton, bool isButtonDown)
{
	bool toggle = btn.getProperties().contains("toggle");
	bool tab = btn.getProperties().contains("tab");
	bool enabled = btn.isEnabled();

	Colour outline = Colour(toggle && enabled ? 0xFEEE6C0A : 0xff4e5b62);
	Colour fill = Colour(0x0);

	if (((isMouseOverButton || isButtonDown) && !toggle) || (btn.getToggleState() && (toggle || tab)))
	{
		fill = Colour(!enabled ? 0xff4e5b62 : toggle ? 0xFEEE6C0A : tab ? 0xff4e5b62 : 0xff3D484E);
	}

	Rectangle<int> r = btn.getLocalBounds();

	gr.setColour(fill);
	if (tab)
	{
		gr.fillRect(r.getX(), r.getY(), r.getWidth(), r.getHeight());
		gr.setColour(outline);
		gr.drawRect(r.getX(), r.getY(), r.getWidth(), r.getHeight());
	}
	else
	{
		gr.fillRoundedRectangle(r.getX(), r.getY(), r.getWidth(), r.getHeight(), 5);
		gr.setColour(outline);
		gr.drawRoundedRectangle(r.getX(), r.getY(), r.getWidth(), r.getHeight(), 5, 2);
	}
}

void ::LookAndFeel::drawImageButton(Graphics& gr, Image* im,
	int imageX, int imageY, int imageW, int imageH,
	const Colour& overlayColour, float imageOpacity, ImageButton& btn)
{
	bool enabled = btn.isEnabled();

	Rectangle<int> r = btn.getLocalBounds();
	gr.setColour(Colour(enabled ? 0xFEEE6C0A : 0xff4e5b62));

	if (btn.getToggleState())
	{
		gr.fillRoundedRectangle(r.getX(), r.getY(), r.getWidth(), r.getHeight(), 5);
		gr.drawRoundedRectangle(r.getX(), r.getY(), r.getWidth(), r.getHeight(), 5, 2);
	}

	LookAndFeel_V4::drawImageButton(gr, im, imageX, imageY, imageW, imageH, overlayColour, imageOpacity, btn);
}

void ::LookAndFeel::drawLinearSlider(Graphics& g, int x, int y, int width, int height,
	float sliderPos, float minSliderPos, float maxSliderPos,
	const Slider::SliderStyle style, Slider& slider)
{
	Colour thumbColor = Colour(slider.isEnabled() ? 0xFF42A2C8 : 0xFF48626D);
	if (slider.findColour(Slider::thumbColourId) != thumbColor)
	{
		slider.setColour(Slider::thumbColourId, thumbColor);
	}

	LookAndFeel_V4::drawLinearSlider(g, x, y, width, height, sliderPos, minSliderPos, maxSliderPos, style, slider);
}

void ::LookAndFeel::drawRotarySlider(Graphics& g, int x, int y, int width, int height,
	float sliderPosProportional, float rotaryStartAngle,
	float rotaryEndAngle, Slider& slider)
{
	Colour thumbColor = Colour(slider.isEnabled() ? 0xFF42A2C8 : 0xFF48626D);
	if (slider.findColour(Slider::thumbColourId) != thumbColor)
	{
		slider.setColour(Slider::thumbColourId, thumbColor);
	}

	LookAndFeel_V4::drawRotarySlider(g, x, y, width, height, sliderPosProportional, rotaryStartAngle, rotaryEndAngle, slider);
}

void ::LookAndFeel::drawLabel(Graphics& gr, Label& label)
{
	bool bgstatus = label.getProperties().contains("bg-status");

	if (bgstatus)
	{
		if (label.findColour(Label::backgroundColourId) != Colours::transparentBlack)
		{
			label.setColour(Label::backgroundColourId, Colours::transparentBlack);
		}

		gr.setColour(Colour(label.isEnabled() ? 0xFF42A2C8 : 0xFF48626D));
		Rectangle<int> r = label.getLocalBounds();
		gr.fillRoundedRectangle(r.getX(), r.getY(), r.getWidth(), r.getHeight(), 5);
		gr.drawRoundedRectangle(r.getX(), r.getY(), r.getWidth(), r.getHeight(), 5, 2);
	}

	LookAndFeel_V4::drawLabel(gr, label);
}
