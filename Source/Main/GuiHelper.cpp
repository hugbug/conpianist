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

void GuiHelper::Final()
{
	m_fileChooser.reset();
}

void GuiHelper::ShowModalDialog(Component* comp, const String& title)
{
	DialogWindow::LaunchOptions dialog;
	dialog.content.setOwned(comp);
	dialog.dialogTitle = title;
	dialog.useNativeTitleBar = (SystemStats::getOperatingSystemType() & SystemStats::Windows) ||
		(SystemStats::getOperatingSystemType() & SystemStats::MacOSX);
	dialog.resizable = false;

	TopLevelWindow* win = TopLevelWindow::getActiveTopLevelWindow();
	win->getChildren()[0]->setAlpha(0.3);

#if JUCE_MODAL_LOOPS_PERMITTED
	dialog.runModal();
#else
	//TODO: Async mode for dialogs
#endif

	win->getChildren()[0]->setAlpha(1.0);
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
