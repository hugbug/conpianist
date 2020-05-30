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

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "Settings.h"
#include "PianoController.h"

//==============================================================================
/*
*/
class PrBaseComponent  : public Component,
                         public PianoController::Listener
{
public:
    PrBaseComponent(Settings& settings, PianoController& pianoController);
    ~PrBaseComponent() override;
    void paint (Graphics& g) override;
    void setBackgroundColor(Colour color) { backgroundColor = color; }

protected:
    Settings& settings;
    PianoController& pianoController;
    Colour backgroundColor;

    void drawSliderMark(Graphics& g, Slider* slider, int pos = -1);
   
private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PrBaseComponent)
};

