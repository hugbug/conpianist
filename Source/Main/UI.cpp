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

#include "UI.h"

void UI::ShowModalDialog(Component* comp, const String& title)
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

