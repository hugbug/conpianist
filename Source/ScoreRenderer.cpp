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

#include <lomse_doorway.h>
#include <lomse_document.h>
#include <lomse_graphic_view.h>
#include <lomse_interactor.h>
#include <lomse_presenter.h>

#include "ScoreRenderer.h"
#include "Settings.h"

class LomseRenderer : public ScoreRender
{
public:
	LomseRenderer();

	void LoadDocument(String filename) override;
	void Render(Image* image) override;

	// Global variables
	// In this first example we are just going to display an score on the main window.
	// Let's define the necessary variables:
	//
	lomse::LomseDoorway m_lomse;        //the Lomse library doorway
	ScopedPointer<lomse::Presenter> m_pPresenter;

	//the Lomse View renders its content on a bitmap. To manage it, Lomse
	//associates the bitmap to a RenderingBuffer object.
	//It is your responsibility to render the bitmap on a window.
	//Here you define the rendering buffer and its associated bitmap
	lomse::RenderingBuffer m_rbuf_window;
};

ScoreRender* ScoreRender::Create()
{
	return new LomseRenderer();
}

LomseRenderer::LomseRenderer()
{
	lomse::logger.set_logging_mode(lomse::Logger::k_trace_mode);

	// Lomse knows nothing about windows. It renders everything on a bitmap and the
	// user application uses this bitmap. For instance, to display it on a window.
	// Lomse supports a lot of bitmap formats and pixel formats. Therefore, before
	// using the Lomse library you MUST specify which bitmap formap to use.

	//the pixel format
	int pixel_format = lomse::k_pix_format_rgba32;
	int bpp = 32;

	//the desired resolution. For MS Windows use 96 pixels per inch
	int resolution = 96 * 2;    //96 ppi

	//Lomse default y axis direction is 0 coordinate at top and increases
	//downwards. For JUCE the Lomse default behaviour is the right behaviour.
	bool reverse_y_axis = false;

	//initialize the Lomse library with these values
	m_lomse.init_library(pixel_format, resolution, reverse_y_axis);

	m_lomse.set_default_fonts_path((Settings::ResourcesPath() + "/fonts/").toStdString());
}

void LomseRenderer::LoadDocument(String filename)
{
	//first, we will create a 'presenter'. It takes care of creating and maintaining
	//all objects and relationships between the document, its views and the interactors
	//to interact with the view
	m_pPresenter = m_lomse.open_document(lomse::k_view_vertical_book, filename.toStdString());

	//get the pointer to the interactor, set the rendering buffer and register for
	//receiving desired events
	if (lomse::SpInteractor spInteractor = m_pPresenter->get_interactor(0).lock())
	{
		//connect the View with the window buffer
		spInteractor->set_rendering_buffer(&m_rbuf_window);
	}
}

void LomseRenderer::Render(Image* image)
{
	//creates a bitmap of specified size and associates it to the rendering
	//buffer for the view. Any existing buffer is automatically deleted
	Image::BitmapData bitmap(*image, Image::BitmapData::readWrite);

	m_rbuf_window.attach(bitmap.data, image->getWidth(), image->getHeight(), bitmap.lineStride);

	if (lomse::SpInteractor spInteractor = m_pPresenter->get_interactor(0).lock())
	{
		spInteractor->force_redraw();
	}

	m_rbuf_window.attach(nullptr, 0, 0, 0);
}
