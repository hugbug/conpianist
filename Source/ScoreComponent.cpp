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
#include <lomse_tasks.h>

#include "ScoreComponent.h"

using namespace lomse;

class LomseScoreComponent : public ScoreComponent
{
public:
	LomseScoreComponent(Settings& settings);

    void RenderScore();
    void paint (Graphics& g) override;
    void resized() override;
	void mouseDown(const MouseEvent& event) override;
	void mouseUp(const MouseEvent& event) override;
	void mouseDrag(const MouseEvent& event) override;
	void mouseWheelMove(const MouseEvent& event, const MouseWheelDetails& details) override;

private:
	lomse::LomseDoorway m_lomse;
	ScopedPointer<Presenter> m_presenter;
	RenderingBuffer m_rbuf_window;
    ScopedPointer<juce::Image> m_image;
    Settings& m_settings;
	int m_resolution;
	float m_scale = 1;

	void LoadDocument(String filename);
	void PrepareImage();

    void UpdateWindow(SpEventInfo event);
    static void UpdateWindowWrapper(void* obj, SpEventInfo event)
		{ static_cast<LomseScoreComponent*>(obj)->UpdateWindow(event); }

	unsigned GetMouseFlags(const MouseEvent& event);
};

ScoreComponent* ScoreComponent::Create(Settings& settings)
{
	return new LomseScoreComponent(settings);
}

LomseScoreComponent::LomseScoreComponent(Settings& settings) :
	m_settings(settings)
{
	m_scale = m_settings.zoomUi;
	m_resolution = 96 * m_scale;

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

void LomseScoreComponent::LoadDocument(String filename)
{
	//first, we will create a 'presenter'. It takes care of creating and maintaining
	//all objects and relationships between the document, its views and the interactors
	//to interact with the view
	m_presenter = m_lomse.open_document(lomse::k_view_vertical_book, filename.toStdString());

	//get the pointer to the interactor, set the rendering buffer and register for
	//receiving desired events
	SpInteractor interactor = m_presenter->get_interactor(0).lock();
	//connect the View with the window buffer
	interactor->set_rendering_buffer(&m_rbuf_window);

	//ask to receive desired events
	interactor->add_event_handler(k_update_window_event, this, UpdateWindowWrapper);

	interactor->switch_task(TaskFactory::k_task_drag_view);

	//set page height
	Document* pDoc = m_presenter->get_document_raw_ptr();
	ImoDocument* pImoDoc = pDoc->get_im_root();
	ImoPageInfo* pPageInfo = pImoDoc->get_page_info();
	pPageInfo->set_page_height(2000000.0f);
}

void LomseScoreComponent::PrepareImage()
{
	m_image = new juce::Image(juce::Image::PixelFormat::ARGB, getWidth() * m_scale, getHeight() * m_scale, false, SoftwareImageType());

	//creates a bitmap of specified size and associates it to the rendering
	//buffer for the view. Any existing buffer is automatically deleted
	juce::Image::BitmapData bitmap(*m_image, juce::Image::BitmapData::readWrite);

	m_rbuf_window.attach(bitmap.data, m_image->getWidth(), m_image->getHeight(), bitmap.lineStride);

	//adjust the number of measures to fit the area size
	//adjust page size
	SpInteractor interactor = m_presenter->get_interactor(0).lock();
	Document* pDoc = m_presenter->get_document_raw_ptr();
	ImoDocument* pImoDoc = pDoc->get_im_root();
	ImoPageInfo* pPageInfo = pImoDoc->get_page_info();
	pPageInfo->set_page_width(LUnits(m_image->getWidth()) * 26.5f / m_scale);
	pPageInfo->set_top_margin(500);
	pPageInfo->set_left_margin(200);
	pPageInfo->set_right_margin(200);
	pPageInfo->set_bottom_margin(500);
	pPageInfo->set_binding_margin(0);
	interactor->on_document_updated();  //This rebuilds GraphicModel and will generate a Paint event

	interactor->redraw_bitmap();
}

void LomseScoreComponent::UpdateWindow(SpEventInfo event)
{
	repaint();
}

void LomseScoreComponent::resized()
{
	PrepareImage();
}

void LomseScoreComponent::paint(Graphics& g)
{
	g.drawImage(*m_image, 0, 0, getWidth(), getHeight(), 0, 0, m_image->getWidth(), m_image->getHeight());
}

void LomseScoreComponent::mouseDown(const MouseEvent& event)
{
	SpInteractor interactor = m_presenter->get_interactor(0).lock();
	interactor->on_mouse_button_down(event.getMouseDownScreenX() * m_scale, event.getScreenY() * m_scale, GetMouseFlags(event));
}

void LomseScoreComponent::mouseUp(const MouseEvent& event)
{
	SpInteractor interactor = m_presenter->get_interactor(0).lock();
	interactor->on_mouse_button_up(event.getMouseDownScreenX() * m_scale, event.getScreenY() * m_scale, GetMouseFlags(event));
}

void LomseScoreComponent::mouseDrag(const MouseEvent& event)
{
	SpInteractor interactor = m_presenter->get_interactor(0).lock();
	interactor->on_mouse_move(event.getMouseDownScreenX() * m_scale, event.getScreenY() * m_scale, GetMouseFlags(event));
}

void LomseScoreComponent::mouseWheelMove(const MouseEvent& event, const MouseWheelDetails& details)
{
	float scrollY = details.deltaY * 256;

	SpInteractor interactor = m_presenter->get_interactor(0).lock();
	interactor->on_mouse_button_down(event.getMouseDownScreenX() * m_scale, event.getScreenY() * m_scale, k_mouse_left);
	interactor->on_mouse_move(event.getMouseDownScreenX() * m_scale, (event.getScreenY() + scrollY) * m_scale, k_mouse_left);
	interactor->on_mouse_button_up(event.getMouseDownScreenX() * m_scale, (event.getScreenY() + scrollY) * m_scale, k_mouse_left);
}

unsigned LomseScoreComponent::GetMouseFlags(const MouseEvent& event)
{
	unsigned flags = 0;
	if (event.mods.isLeftButtonDown()) flags |= k_mouse_left;
	if (event.mods.isRightButtonDown()) flags |= k_mouse_right;
	if (event.mods.isMiddleButtonDown()) flags |= k_mouse_middle;
	if (event.mods.isShiftDown()) flags |= k_kbd_shift;
	if (event.mods.isAltDown()) flags |= k_kbd_alt;
	if (event.mods.isCtrlDown()) flags |= k_kbd_ctrl;
	return flags;
}
