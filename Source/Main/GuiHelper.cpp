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

#include "GuiHelper.h"

std::unique_ptr<FileChooser> GuiHelper::m_fileChooser;

class AsyncDialogWindow : public DialogWindow
{
public:
	AsyncDialogWindow(Component* content, const String& title)
		: DialogWindow(title, Colours::lightgrey, true, true)
	{
		bool usingNativeTitleBar = (SystemStats::getOperatingSystemType() & SystemStats::Windows) ||
			(SystemStats::getOperatingSystemType() & SystemStats::MacOSX);
		setUsingNativeTitleBar(usingNativeTitleBar);
		setContentOwned(content, true);
		centreAroundComponent(nullptr, getWidth(), getHeight());
		setResizable(false, false);
	}

	~AsyncDialogWindow()
	{
		FadeOut();
	}

	void closeButtonPressed() override
	{
		setVisible (false);
	}

	void Launch()
	{
		FadeIn();
		enterModalState(true, nullptr, true);
	}

	void FadeIn()
	{
		m_topWindow = TopLevelWindow::getActiveTopLevelWindow();
		m_topWindow->getChildren()[0]->setAlpha(0.3);
	}

	void FadeOut()
	{
		if (m_topWindow)
		{
			m_topWindow->getChildren()[0]->setAlpha(1.0);
		}
	}

private:
	TopLevelWindow* m_topWindow = nullptr;
};

void GuiHelper::Final()
{
	m_fileChooser.reset();
}

void GuiHelper::ShowDialogAsync(Component* content, const String& title)
{
	AsyncDialogWindow* dialog = new AsyncDialogWindow(content, title);
	dialog->Launch();
}

void GuiHelper::ShowFileOpenDialogAsync(const String& title, const String& initialLocation,
	const String& patterns, std::function<void(const URL&)> callback)
{
	File location(initialLocation);
	m_fileChooser = std::make_unique<FileChooser>(title, location, patterns);

	m_fileChooser->launchAsync(FileBrowserComponent::openMode | FileBrowserComponent::canSelectFiles,
		[callback](const FileChooser& ch)
		{
			const URL url = ch.getURLResult();
			if (!url.isEmpty())
			{
				callback(url);
			}
		});
}

void GuiHelper::ShowFileSaveDialogAsync(const String& title, const String& initialLocation,
	const String& patterns, std::function<void(const URL&)> callback)
{
	File location(initialLocation);
	m_fileChooser = std::make_unique<FileChooser>(title, location, patterns);

	m_fileChooser->launchAsync(FileBrowserComponent::saveMode | FileBrowserComponent::canSelectFiles,
		[callback](const FileChooser& ch)
		{
			const URL url = ch.getURLResult();
			if (!url.isEmpty())
			{
				callback(url);
			}
		});
}

void GuiHelper::ShowMenuAsync(PopupMenu& menu, Component* comp,
	std::function<void(int)> callback)
{
	menu.showMenuAsync(PopupMenu::Options()
		.withTargetComponent(comp)
		.withStandardItemHeight(35),
		callback);
}
