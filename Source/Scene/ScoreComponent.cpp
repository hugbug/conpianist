/*
 *  This file is part of ConPianist. See <https://github.com/hugbug/conpianist>.
 *
 *  Copyright (C) 2018-2020 Andrey Prygunkov <hugbug@users.sourceforge.net>
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

#ifdef DISABLE_LOMSE

#include "ScoreComponent.h"
ScoreComponent* ScoreComponent::Create(Settings& settings, PianoController& pianoController)
{
	return new ScoreComponent();
}
#else

#include <lomse_doorway.h>
#include <lomse_document.h>
#include <lomse_graphic_view.h>
#include <lomse_interactor.h>
#include <lomse_presenter.h>
#include <lomse_tasks.h>
#include <lomse_tempo_line.h>
#include <lomse_score_algorithms.h>
#include <lomse_fragment_mark.h>

#include "GuiHelper.h"
#include "ScoreComponent.h"

using namespace lomse;

class LomseScoreComponent : public ScoreComponent, public PianoController::Listener,
	public Button::Listener, public ChangeListener
{
public:
	LomseScoreComponent(Settings& settings, PianoController& pianoController);
	~LomseScoreComponent() override;

	void paint (Graphics& g) override;
	void resized() override;
	void mouseDown(const MouseEvent& event) override;
	void mouseUp(const MouseEvent& event) override;
	void mouseMove(const MouseEvent& event) override;
	void mouseDrag(const MouseEvent& event) override;
	void mouseWheelMove(const MouseEvent& event, const MouseWheelDetails& details) override;
    void buttonClicked (Button* buttonThatWasClicked) override;

	void PianoStateChanged(PianoController::Aspect aspect, PianoController::Channel channel) override;
    void changeListenerCallback(ChangeBroadcaster* source) override { if (source == &m_settings) ApplySettings(); }

private:
	Settings& m_settings;
	PianoController& m_pianoController;
	lomse::LomseDoorway m_lomse;
	std::unique_ptr<Presenter> m_presenter;
	RenderingBuffer m_rbuf_window;
	std::unique_ptr<juce::Image> m_image;
	float m_scale = 1;
	float m_docScale = 1;
	int m_scoreId = 0;
	PianoController::Loop loop{{0,0},{0,0}};
	PianoController::Position loopStart{0,0};
	FragmentMark* loopStartMark = nullptr;
	FragmentMark* loopEndMark = nullptr;
    std::unique_ptr<Button> loadButton;
    std::unique_ptr<ImageButton> menuButton;
    std::vector<std::string> m_instrNames;
    std::vector<std::string> m_instrAbbrevs;
    std::vector<ImoInstrument*> m_instruments;
    std::vector<ImoInstrGroup*> m_instrgroups;
    PianoController::Channel m_rightChannel = PianoController::chMidi0;
    PianoController::Channel m_leftChannel = PianoController::chMidi0;
	Settings::ScoreInstrumentNames m_scoreInstrumentNames = Settings::siMixed;
	Settings::ScorePart m_scorePart = Settings::spRightAndLeft;
	bool m_scoreShowMidiChannel = true;
	String m_error;
	bool m_firstSync = true;

	void LoadDocument(String filename);
	void PrepareImage();
	LUnits ScaledUnits(int pixels);
	unsigned GetMouseFlags(const MouseEvent& event);
	void UpdateTempoLine(bool scroll);
	void UpdateABMarks(bool force);
	void BuildControls();
	void LoadScore(const File& file);
	void LoadScore(const URL& url);
	void ChooseScoreFile();
	void ShowMenu();
	void ApplySettings();
	void PrepareInstruments();
	void ConfigureInstruments();
	void UpdateInstruments(bool force);
	int MidiChannelOfInstrument(ImoInstrument* instr);
	void Cleanup();

	// Piano controller callbacks
	void UpdateSongState();
	void LoadSong();

	// Lomse callbacks
	void UpdateWindow(SpEventInfo event);
	void LomseEvent(SpEventInfo event);
	static void UpdateWindowWrapper(void* obj, SpEventInfo event)
		{ static_cast<LomseScoreComponent*>(obj)->UpdateWindow(event); }
	static void LomseEventWrapper(void* obj, SpEventInfo event)
		{ static_cast<LomseScoreComponent*>(obj)->LomseEvent(event); }
};


ScoreComponent* ScoreComponent::Create(Settings& settings, PianoController& pianoController)
{
	return new LomseScoreComponent(settings, pianoController);
}

LomseScoreComponent::LomseScoreComponent(Settings& settings, PianoController& pianoController) :
	m_settings(settings), m_pianoController(pianoController)
{
	m_scale = m_settings.zoomUi * Desktop::getInstance().getDisplays().getMainDisplay().scale;
	int resolution = int(96 * m_scale);

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
	m_lomse.init_library(pixel_format, resolution, reverse_y_axis);

	m_lomse.set_default_fonts_path((m_settings.resourcesPath + "/fonts/").toStdString());

	//set required callbacks
	m_lomse.set_notify_callback(this, LomseEventWrapper);

	BuildControls();

	pianoController.AddListener(this);
	settings.addChangeListener(this);
}

LomseScoreComponent::~LomseScoreComponent()
{
	Cleanup();
}

void LomseScoreComponent::BuildControls()
{
    loadButton.reset(new TextButton("Load Button"));
    addAndMakeVisible(loadButton.get());
    loadButton->setButtonText("Load Score");
    loadButton->addListener(this);

	menuButton.reset(new ImageButton("Menu Button"));
	addAndMakeVisible(menuButton.get());
	menuButton->setTooltip("Context Menu");
	menuButton->setButtonText("Menu");
	menuButton->addListener(this);
	menuButton->setImages(false, true, true,
		ImageCache::getFromMemory(BinaryData::buttoncontextmenuscore_png,
			BinaryData::buttoncontextmenuscore_pngSize), 1.000f, Colour (0x00000000),
		juce::Image(), 0.750f, Colour (0x00000000),
		juce::Image(), 1.000f, Colour (0x00000000));
    menuButton->setBounds(8, 8, 28, 28);
}

void LomseScoreComponent::LoadDocument(String filename)
{
	//first, we will create a 'presenter'. It takes care of creating and maintaining
	//all objects and relationships between the document, its views and the interactors
	//to interact with the view
	if (filename.isNotEmpty())
	{
		// load from file
		m_presenter.reset(m_lomse.open_document(lomse::k_view_vertical_book, filename.toStdString()));
	}
	else
	{
		// empty document
		m_presenter.reset(m_lomse.new_document(lomse::k_view_vertical_book));
	}

	//get the pointer to the interactor, set the rendering buffer and register for
	//receiving desired events
	SpInteractor interactor = m_presenter->get_interactor(0).lock();
	//connect the View with the window buffer
	interactor->set_rendering_buffer(&m_rbuf_window);
	//ask to receive desired events
	interactor->add_event_handler(k_update_window_event, this, UpdateWindowWrapper);

	// beat definition for yamaha
	interactor->define_beat(k_beat_bottom_ts);

	// visuals
	interactor->set_view_background(Color(68,62,50)); // dark grey
	interactor->set_visual_tracking_mode(k_tracking_tempo_line);

	TempoLine* tempoLine = static_cast<TempoLine*>(interactor->get_tracking_effect(k_tracking_tempo_line));
	tempoLine->set_color(Color(15, 90, 235, 128));   // light orange

	interactor->switch_task(TaskFactory::k_task_drag_view);

	PrepareInstruments();
	ConfigureInstruments();

	loop = {{0,0},{0,0}};
}

void LomseScoreComponent::PrepareImage()
{
	try
	{
		m_image.reset();

		int width = int(getWidth() * m_scale);
		int height = int(getHeight() * m_scale);

		//adjust the number of measures to fit the area size
		//adjust page size
		SpInteractor interactor = m_presenter->get_interactor(0).lock();
		Document* doc = m_presenter->get_document_raw_ptr();
		ImoDocument* imoDoc = doc->get_im_root();
		ImoPageInfo* pageInfo = imoDoc->get_page_info();

		imoDoc->set_page_content_scale(1.0); // reset scale
		pageInfo->set_page_width(ScaledUnits(width));
		pageInfo->set_page_height(ScaledUnits(height));
		pageInfo->set_top_margin(500);
		pageInfo->set_left_margin(300);
		pageInfo->set_right_margin(300);
		pageInfo->set_bottom_margin(500);
		pageInfo->set_binding_margin(0);

		interactor->on_document_updated();  //This rebuilds GraphicModel

		m_docScale = imoDoc->get_page_content_scale(); // Scale is calculated when rebuliding GraphicModel

		// create image to fit the whole page
		m_image.reset(new juce::Image(juce::Image::PixelFormat::ARGB,
			int(width / m_docScale), int(height / m_docScale), false, SoftwareImageType()));
		//creates a bitmap of specified size and associates it to the rendering
		//buffer for the view. Any existing buffer is automatically deleted
		juce::Image::BitmapData bitmap(*m_image, juce::Image::BitmapData::readWrite);
		m_rbuf_window.attach(bitmap.data, m_image->getWidth(), m_image->getHeight(), bitmap.lineStride);

		interactor->redraw_bitmap();

		UpdateABMarks(true);
		UpdateTempoLine(false);
	}
	catch (runtime_error e)
	{
		m_error = e.what();
		juce::Logger::writeToLog("[SCORE] runtime_error: " + m_error);
	}
}

LUnits LomseScoreComponent::ScaledUnits(int pixels)
{
	return LUnits(pixels) * 26.5f / m_scale;
}

void LomseScoreComponent::UpdateWindow(SpEventInfo event)
{
	repaint();
}

void LomseScoreComponent::LomseEvent(SpEventInfo event)
{
	if (event->get_event_type() == k_update_viewport_event)
	{
		SpEventUpdateViewport viewportEvent(static_pointer_cast<EventUpdateViewport>(event));
		SpInteractor interactor = m_presenter->get_interactor(0).lock();
		const int OFFSET_CORRECTION = 19; // empirical value
		int yPos = std::max(viewportEvent->get_new_viewport_y() - OFFSET_CORRECTION, 0);
		interactor->new_viewport(0, yPos);
	}
}

void LomseScoreComponent::resized()
{
	if (m_presenter)
	{
		PrepareImage();
	}

	loadButton->setBounds(getWidth() / 2 - 50, 30, 100, 30);
}

void LomseScoreComponent::paint(Graphics& g)
{
	if (m_presenter && m_image)
	{
		g.drawImage(*m_image, 0, 0, getWidth(), getHeight(), 0, 0, m_image->getWidth(), m_image->getHeight());
	}
	else if (m_presenter && !m_image)
	{
		String text = "An error occured when drawing the score:\n" + m_error;
		g.setColour(Colours::white);
		g.fillRect(0, 0, getWidth(), getHeight());
		g.setColour(Colours::red);
		g.setFont(16);
		juce::Rectangle<int> rec(20, 80, getWidth() - 40, getHeight() - 100);
		g.drawFittedText(text, rec, Justification::centredTop, 100, 1);
	}
	else
	{
		String text =
			"To automatically load score for a song put the score-file in MusicXML format near MIDI-file. "
			"The score-file should have the same name as MIDI-file and extension .musicxml or .xml.";
		g.setColour(Colour(167,172,176));
		g.setFont(16);
		juce::Rectangle<int> rec(20, 80, getWidth() - 40, getHeight() - 100);
		g.drawFittedText(text, rec, Justification::centredTop, 100, 1);
	}
}

void LomseScoreComponent::buttonClicked(Button* buttonThatWasClicked)
{
	if (buttonThatWasClicked == loadButton.get())
	{
		ChooseScoreFile();
	}
	else if (buttonThatWasClicked == menuButton.get())
	{
		ShowMenu();
	}
}

void LomseScoreComponent::ChooseScoreFile()
{
	String songName = File(m_pianoController.GetSongName()).getFileNameWithoutExtension();
	String title = "Please select the score" + (songName == "" ? "" : String(" for ") + songName);

	GuiHelper::ShowFileOpenDialogAsync(title, m_settings.workingDirectory, "*.xml;*.musicxml",
		[this](const URL& url)
		{
			m_settings.workingDirectory = url.getLocalFile().getParentDirectory().getFullPathName();
			m_settings.Save();
			MessageManager::callAsync([=](){LoadScore(url);});
    	});
}

void LomseScoreComponent::LoadScore(const URL& url)
{
	// generate access token on sandboxed platforms (iOS)
	std::unique_ptr<juce::InputStream> inp(url.createInputStream(false));

	LoadScore(url.getLocalFile());
}

void LomseScoreComponent::mouseDown(const MouseEvent& event)
{
	if (!m_presenter || !m_image) return;

	SpInteractor interactor = m_presenter->get_interactor(0).lock();
	interactor->on_mouse_button_down(int(event.getMouseDownScreenX() * m_scale),
		int(event.getScreenY() * m_scale), GetMouseFlags(event));
}

void LomseScoreComponent::mouseUp(const MouseEvent& event)
{
	if (!m_presenter || !m_image) return;

	SpInteractor interactor = m_presenter->get_interactor(0).lock();
	interactor->on_mouse_button_up(int(event.getMouseDownScreenX() * m_scale),
		int(event.getScreenY() * m_scale), GetMouseFlags(event));
}

void LomseScoreComponent::mouseMove(const MouseEvent& event)
{
	if (!m_presenter || !m_image) return;

	SpInteractor interactor = m_presenter->get_interactor(0).lock();
	interactor->on_mouse_move(int(event.getMouseDownScreenX() * m_scale),
		int(event.getScreenY() * m_scale), GetMouseFlags(event));
}

void LomseScoreComponent::mouseDrag(const MouseEvent& event)
{
	mouseMove(event);
}

void LomseScoreComponent::mouseWheelMove(const MouseEvent& event, const MouseWheelDetails& details)
{
	if (!m_presenter || !m_image) return;

	float scrollY = details.deltaY * 256;

	SpInteractor interactor = m_presenter->get_interactor(0).lock();
	interactor->on_mouse_button_down(int(event.getMouseDownScreenX() * m_scale),
		int(event.getScreenY() * m_scale), k_mouse_left);
	interactor->on_mouse_move(int(event.getMouseDownScreenX() * m_scale),
		int((event.getScreenY() + scrollY) * m_scale), k_mouse_left);
	interactor->on_mouse_button_up(int(event.getMouseDownScreenX() * m_scale),
		int((event.getScreenY() + scrollY) * m_scale), k_mouse_left);
}

unsigned LomseScoreComponent::GetMouseFlags(const MouseEvent& event)
{
	unsigned mouseFlags = 0;
	if (event.mods.isLeftButtonDown()) mouseFlags |= k_mouse_left;
	if (event.mods.isRightButtonDown()) mouseFlags |= k_mouse_right;
	if (event.mods.isMiddleButtonDown()) mouseFlags |= k_mouse_middle;
	if (event.mods.isShiftDown()) mouseFlags |= k_kbd_shift;
	if (event.mods.isAltDown()) mouseFlags |= k_kbd_alt;
	if (event.mods.isCtrlDown()) mouseFlags |= k_kbd_ctrl;
	return mouseFlags;
}

void LomseScoreComponent::PianoStateChanged(PianoController::Aspect aspect, PianoController::Channel channel)
{
	if (aspect == PianoController::apPosition || aspect == PianoController::apLoop)
	{
		MessageManager::callAsync([=](){UpdateSongState();});
	}
	else if (aspect == PianoController::apSongLoaded ||
		(aspect == PianoController::apSongName && m_firstSync))
	{
		m_firstSync = false;
		MessageManager::callAsync([=](){LoadSong();});
	}
	else if (aspect == PianoController::apPartChannel &&
		m_settings.scorePart != Settings::spAll &&
		(channel == m_pianoController.GetPartChannel(PianoController::paRight) ||
		channel == m_pianoController.GetPartChannel(PianoController::paLeft)))
	{
		MessageManager::callAsync([=](){UpdateInstruments(false);});
	}
}

void LomseScoreComponent::UpdateSongState()
{
	if (!m_presenter || !m_image) return;

	UpdateABMarks(false);
	UpdateTempoLine(true);
}

void LomseScoreComponent::UpdateTempoLine(bool scroll)
{
	// highlight playback position
	SpInteractor interactor = m_presenter->get_interactor(0).lock();
	PianoController::Position songPosition = m_pianoController.GetPosition();
	if (scroll)
	{
		interactor->move_tempo_line_and_scroll_if_necessary(m_scoreId,
			songPosition.measure - 1, songPosition.beat - 1);
	}
	else
	{
		interactor->move_tempo_line(m_scoreId,
			songPosition.measure - 1, songPosition.beat - 1);
	}
}

void LomseScoreComponent::UpdateABMarks(bool force)
{
	SpInteractor interactor = m_presenter->get_interactor(0).lock();
	Document* doc = m_presenter->get_document_raw_ptr();
	ImoScore* score = dynamic_cast<ImoScore*>(doc->get_im_root()->get_content_item(0));

	// highlight AB-Loop
	PianoController::Loop curLoop = m_pianoController.GetLoop();
	PianoController::Position curLoopStart = m_pianoController.GetLoopStart();
	if (!(loop.begin == curLoop.begin && loop.end == curLoop.end && loopStart == curLoopStart) || force)
	{
		loop = curLoop;
		loopStart = curLoopStart;

		interactor->remove_mark(loopStartMark);
		interactor->remove_mark(loopEndMark);

		if (loop.begin.measure > 0 || loopStart.measure > 0)
		{
			TimeUnits timepos = ScoreAlgorithms::get_timepos_for(score,
				loop.begin.measure > 0 ? loop.begin.measure - 1 : loopStart.measure - 1,
				loop.begin.measure > 0 ? loop.begin.beat - 1 : loopStart.beat - 1);
			loopStartMark = interactor->add_fragment_mark_at_note_rest(m_scoreId, timepos);
			loopStartMark->color(Color(15, 90, 235, 128)); // light orange
			loopStartMark->type(k_mark_open_rounded);
			loopStartMark->x_shift(-5);
		}

		if (loop.end.measure > 0)
		{
			TimeUnits timepos = ScoreAlgorithms::get_timepos_for(score, loop.end.measure - 1, loop.end.beat - 1);
			timepos -= 1;
			loopEndMark = interactor->add_fragment_mark_at_note_rest(m_scoreId, timepos);
			loopEndMark->color(Color(15, 90, 235, 128)); // light orange
			loopEndMark->type(k_mark_close_rounded);
		}
	}
}

void LomseScoreComponent::LoadSong()
{
	Cleanup();

	File file = File(m_pianoController.GetSongName()).withFileExtension(".musicxml");
	if (!file.existsAsFile())
	{
		file = File(m_pianoController.GetSongName()).withFileExtension(".xml");
	}

	if (file.existsAsFile() && file.getSize() > 0)
	{
		LoadScore(file);
		return;
	}
	else
	{
		loadButton->setVisible(m_presenter == nullptr);
		repaint();
	}
}

void LomseScoreComponent::LoadScore(const File& file)
{
	Cleanup();

	LoadDocument(file.getFullPathName());

	if (m_presenter)
	{
		PrepareImage();
	}

	loadButton->setVisible(m_presenter == nullptr);
	repaint();
}

void LomseScoreComponent::ShowMenu()
{
	PopupMenu menu;
	menu.addSectionHeader("SCORE");
	menu.addItem(1, "Load Score");
	menu.addSectionHeader("PARTS");
	menu.addItem(300 + Settings::spRight, "Right", true, m_settings.scorePart == Settings::spRight);
	menu.addItem(300 + Settings::spLeft, "Left", true, m_settings.scorePart == Settings::spLeft);
	menu.addItem(300 + Settings::spRightAndLeft, "Right and Left", true, m_settings.scorePart == Settings::spRightAndLeft);
	menu.addItem(300 + Settings::spAll, "All", true, m_settings.scorePart == Settings::spAll);
	menu.addSectionHeader("INSTRUMENT NAMES");
	menu.addItem(100 + Settings::siHidden, "Hidden", true, m_settings.scoreInstrumentNames == Settings::siHidden);
	menu.addItem(100 + Settings::siShort, "Short", true, m_settings.scoreInstrumentNames == Settings::siShort);
	menu.addItem(100 + Settings::siMixed, "Mixed", true, m_settings.scoreInstrumentNames == Settings::siMixed);
	menu.addItem(100 + Settings::siFull, "Full", true, m_settings.scoreInstrumentNames == Settings::siFull);
	menu.addSeparator();
	menu.addItem(201, "Show MIDI-Channel", true, m_settings.scoreShowMidiChannel);

	GuiHelper::ShowMenuAsync(menu, menuButton.get(),
		[this](int result)
		{
			const int group = result / 100;

			if (result == 1)
			{
				ChooseScoreFile();
			}
			else if (group == 1)
			{
				m_settings.scoreInstrumentNames = Settings::ScoreInstrumentNames(result - 100);
			}
			else if (group == 2)
			{
				m_settings.scoreShowMidiChannel = !m_settings.scoreShowMidiChannel;
			}
			else if (group == 3)
			{
				m_settings.scorePart = Settings::ScorePart(result - 300);
			}

			if (group == 1 || group == 2 || group == 3)
			{
				m_settings.Save();
			}
		});
}

void LomseScoreComponent::UpdateInstruments(bool force)
{
	if (m_presenter && (force ||
		m_rightChannel != m_pianoController.GetPartChannel(PianoController::paRight) ||
		m_leftChannel != m_pianoController.GetPartChannel(PianoController::paLeft)))
	{
		ConfigureInstruments();

		m_rightChannel = m_pianoController.GetPartChannel(PianoController::paRight);
		m_leftChannel = m_pianoController.GetPartChannel(PianoController::paLeft);

		PrepareImage();
		repaint();
	}
}

void LomseScoreComponent::PrepareInstruments()
{
	m_instrNames.clear();
	m_instrAbbrevs.clear();
	m_instruments.clear();
	m_instrgroups.clear();

	ImoDocument* imoDoc = m_presenter->get_document_raw_ptr()->get_im_root();
	ImoScore* score = dynamic_cast<ImoScore*>(imoDoc->get_content_item(0));
	if (!score) return;

	m_scoreId = score->get_id();
	while (score->get_num_instruments() > 0)
	{
		ImoInstrument* instr = score->get_instrument(0);

		m_instruments.push_back(instr);
		m_instrNames.push_back(instr->get_name().get_text());
		m_instrAbbrevs.push_back(instr->get_abbrev().get_text());

		//show measure numbers
		instr->set_measures_numbering(ImoInstrument::k_system);

		// hide instrument
		score->get_instruments()->remove_child(instr);
	}

	while (score->get_instrument_groups() &&
		score->get_instrument_groups()->get_num_items() > 0)
	{
		ImoInstrGroup* group = (ImoInstrGroup*)score->get_instrument_groups()->get_child(0);
		m_instrgroups.push_back(group);
		score->get_instrument_groups()->remove_child(group);
	}

	score->end_of_changes();
}

void LomseScoreComponent::ConfigureInstruments()
{
	m_scoreInstrumentNames = m_settings.scoreInstrumentNames;
	m_scorePart = m_settings.scorePart;
	m_scoreShowMidiChannel = m_settings.scoreShowMidiChannel;

	ImoDocument* imoDoc = m_presenter->get_document_raw_ptr()->get_im_root();
	ImoScore* score = dynamic_cast<ImoScore*>(imoDoc->get_content_item(0));
	if (!score) return;

	// hide all instruments
	while (score->get_num_instruments() > 0)
	{
		ImoInstrument* instr = score->get_instrument(0);
		score->get_instruments()->remove_child(instr);
	}

	// hide all groups
	while (score->get_instrument_groups() &&
		score->get_instrument_groups()->get_num_items() > 0)
	{
		ImoInstrGroup* group = (ImoInstrGroup*)score->get_instrument_groups()->get_child(0);
		score->get_instrument_groups()->remove_child(group);
	}

	int num = 0;
	for (ImoInstrument* instr : m_instruments)
	{
		//hide instrument names if necessary or restore names if were previously hidden
		switch (m_settings.scoreInstrumentNames)
		{
			case Settings::siHidden:
				instr->set_name("");
				instr->set_abbrev("");
				break;
			case Settings::siShort:
				instr->set_name(m_instrAbbrevs[num]);
				instr->set_abbrev(m_instrAbbrevs[num]);
				break;
			case Settings::siMixed:
				instr->set_name(m_instrNames[num]);
				instr->set_abbrev(m_instrAbbrevs[num]);
				break;
			case Settings::siFull:
				instr->set_name(m_instrNames[num]);
				instr->set_abbrev(m_instrNames[num]);
				break;
		}

		// add midi-channel(s) to instrument name
		int midiChannel = MidiChannelOfInstrument(instr);
		if (midiChannel > 0 && m_settings.scoreShowMidiChannel)
		{
			instr->set_name((String("#") + String(midiChannel) + " " + String(instr->get_name().get_text())).toStdString());
			instr->set_abbrev((String("#") + String(midiChannel) + " " + String(instr->get_abbrev().get_text())).toStdString());
		}

		num++;
	}

	int rightChannel = m_pianoController.GetPartChannel(PianoController::paRight) - PianoController::chMidi0;
	int leftChannel = m_pianoController.GetPartChannel(PianoController::paLeft) - PianoController::chMidi0;

	// add right hand part to score
	for (ImoInstrument* instr : m_instruments)
	{
		int midiChannel = MidiChannelOfInstrument(instr);
		if (midiChannel == rightChannel &&
			(m_settings.scorePart == Settings::spRight || m_settings.scorePart == Settings::spRightAndLeft))
		{
			score->add_instrument(instr);
		}
	}

	// add left hand part to score
	for (ImoInstrument* instr : m_instruments)
	{
		int midiChannel = MidiChannelOfInstrument(instr);
		if (midiChannel == leftChannel &&
			(m_settings.scorePart == Settings::spLeft || m_settings.scorePart == Settings::spRightAndLeft))
		{
			score->add_instrument(instr);
		}
	}

	// add other parts to score
	for (ImoInstrument* instr : m_instruments)
	{
		if (m_settings.scorePart == Settings::spAll ||
			// add at least one instrument
			score->get_num_instruments() == 0)
		{
			score->add_instrument(instr);
		}
	}

	// add groups for added instruments
	for (ImoInstrGroup* group : m_instrgroups)
	{
		for (int i = 0; i < score->get_num_instruments(); i++)
		{
			ImoInstrument* instr = score->get_instrument(i);
			if (group->get_first_instrument() == instr)
			{
				score->add_instruments_group(group);
				break;
			}
		}
	}

	score->end_of_changes();
}

int LomseScoreComponent::MidiChannelOfInstrument(ImoInstrument* instr)
{
	int midiChannel = instr->get_num_sounds() > 0 && instr->get_sound_info(0)->get_midi_info() ?
		instr->get_sound_info(0)->get_midi_info()->get_midi_channel() + 1 : 0;

	return midiChannel;
}

void LomseScoreComponent::Cleanup()
{
	if (!m_presenter) return;

	ImoDocument* imoDoc = m_presenter->get_document_raw_ptr()->get_im_root();
	ImoScore* score = dynamic_cast<ImoScore*>(imoDoc->get_content_item(0));
	if (score)
	{
		// move all instruments back to score to ensure they are deleted with the score
		while (score->get_num_instruments() > 0)
		{
			score->get_instruments()->remove_child(score->get_instrument(0));
		}
		for (ImoInstrument* instr : m_instruments)
		{
			score->add_instrument(instr);
		}
	}

	m_presenter = nullptr; // this destroys the score object
}

void LomseScoreComponent::ApplySettings()
{
	if (m_scoreInstrumentNames != m_settings.scoreInstrumentNames ||
		m_scorePart != m_settings.scorePart ||
		m_scoreShowMidiChannel != m_settings.scoreShowMidiChannel)
	{
		UpdateInstruments(true);
	}
}

#endif
