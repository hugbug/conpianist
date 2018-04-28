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

#include "ScoreComponent.h"

using namespace lomse;

class LomseScoreComponent : public ScoreComponent
{
public:
	LomseScoreComponent(Settings& settings);

    void RenderScore();
    void paint (Graphics& g) override;
    void resized() override;

private:
	lomse::LomseDoorway m_lomse;
	ScopedPointer<Presenter> m_presenter;
	RenderingBuffer m_rbuf_window;
    ScopedPointer<juce::Image> m_image;
    Settings& m_settings;
	int m_resolution;

	void LoadDocument(String filename);
	void UpdateImage();
};

ScoreComponent* ScoreComponent::Create(Settings& settings)
{
	return new LomseScoreComponent(settings);
}

LomseScoreComponent::LomseScoreComponent(Settings& settings) :
	m_settings(settings)
{
	m_resolution = 96 * m_settings.zoomUi;

	lomse::logger.set_logging_mode(lomse::Logger::k_trace_mode);

	// Lomse knows nothing about windows. It renders everything on a bitmap and the
	// user application uses this bitmap. For instance, to display it on a window.
	// Lomse supports a lot of bitmap formats and pixel formats. Therefore, before
	// using the Lomse library you MUST specify which bitmap formap to use.

	//the pixel format
	int pixel_format = k_pix_format_rgba32;

	//Lomse default y axis direction is 0 coordinate at top and increases
	//downwards. For JUCE the Lomse default behaviour is the right behaviour.
	bool reverse_y_axis = false;

	//initialize the Lomse library with these values
	m_lomse.init_library(pixel_format, m_resolution, reverse_y_axis);

	m_lomse.set_default_fonts_path((m_settings.resourcesPath + "/fonts/").toStdString());

	LoadDocument(m_settings.resourcesPath + "/sample.musicxml");
}

void LomseScoreComponent::paint(Graphics& g)
{
	g.drawImage(*m_image, 0, 0, getWidth(), getHeight(), 0, 0, m_image->getWidth(), m_image->getHeight());
	//g.drawImageAt(*scoreImage, 0, 0);
}

void LomseScoreComponent::resized()
{
	UpdateImage();
}

void LomseScoreComponent::LoadDocument(String filename)
{
	//first, we will create a 'presenter'. It takes care of creating and maintaining
	//all objects and relationships between the document, its views and the interactors
	//to interact with the view
	m_presenter = m_lomse.open_document(lomse::k_view_vertical_book, filename.toStdString());

	//get the pointer to the interactor, set the rendering buffer and register for
	//receiving desired events
	SpInteractor spInteractor = m_presenter->get_interactor(0).lock();
	//connect the View with the window buffer
	spInteractor->set_rendering_buffer(&m_rbuf_window);

	//set page height
	Document* pDoc = m_presenter->get_document_raw_ptr();
	ImoDocument* pImoDoc = pDoc->get_im_root();
	ImoPageInfo* pPageInfo = pImoDoc->get_page_info();
	pPageInfo->set_page_height(2000000.0f);
}

void LomseScoreComponent::UpdateImage()
{
	float scale = m_resolution / 96.0f;

	m_image = new juce::Image(juce::Image::PixelFormat::ARGB, getWidth() * scale, getHeight() * scale, false);

	//creates a bitmap of specified size and associates it to the rendering
	//buffer for the view. Any existing buffer is automatically deleted
	juce::Image::BitmapData bitmap(*m_image, juce::Image::BitmapData::readWrite);

	m_rbuf_window.attach(bitmap.data, m_image->getWidth(), m_image->getHeight(), bitmap.lineStride);

	//adjust the number of measures to fit the area size
	//adjust page size
	SpInteractor spInteractor = m_presenter->get_interactor(0).lock();
	Document* pDoc = m_presenter->get_document_raw_ptr();
	ImoDocument* pImoDoc = pDoc->get_im_root();
	ImoPageInfo* pPageInfo = pImoDoc->get_page_info();
	pPageInfo->set_page_width(LUnits(m_image->getWidth()) * 26.5f / scale);
	pPageInfo->set_top_margin(500);
	pPageInfo->set_left_margin(200);
	pPageInfo->set_right_margin(200);
	pPageInfo->set_bottom_margin(500);
	pPageInfo->set_binding_margin(0);
	spInteractor->on_document_updated();  //This rebuilds GraphicModel and will generate a Paint event

	spInteractor->force_redraw();

	m_rbuf_window.attach(nullptr, 0, 0, 0);
}

