//============================================================================
//
//   SSSS    tt          lll  lll
//  SS  SS   tt           ll   ll
//  SS     tttttt  eeee   ll   ll   aaaa
//   SSSS    tt   ee  ee  ll   ll      aa
//      SS   tt   eeeeee  ll   ll   aaaaa  --  "An Atari 2600 VCS Emulator"
//  SS  SS   tt   ee      ll   ll  aa  aa
//   SSSS     ttt  eeeee llll llll  aaaaa
//
// Copyright (c) 1995-2018 by Bradford W. Mott, Stephen Anthony
// and the Stella Team
//
// See the file "License.txt" for information on usage and redistribution of
// this file, and for a DISCLAIMER OF ALL WARRANTIES.
//============================================================================

#ifndef BOOSTER_WIDGET_HXX
#define BOOSTER_WIDGET_HXX

#include "Control.hxx"
#include "ControllerWidget.hxx"

class BoosterWidget : public ControllerWidget
{
  public:
    BoosterWidget(GuiObject* boss, const GUI::Font& font, int x, int y,
                   Controller& controller);
    virtual ~BoosterWidget() = default;

  private:
    enum { kJUp = 0, kJDown, kJLeft, kJRight, kJFire, kJBooster, kJTrigger };

    CheckboxWidget* myPins[7];
    static Controller::DigitalPin ourPinNo[5];

  private:
    void loadConfig() override;
    void handleCommand(CommandSender* sender, int cmd, int data, int id) override;

    // Following constructors and assignment operators not supported
    BoosterWidget() = delete;
    BoosterWidget(const BoosterWidget&) = delete;
    BoosterWidget(BoosterWidget&&) = delete;
    BoosterWidget& operator=(const BoosterWidget&) = delete;
    BoosterWidget& operator=(BoosterWidget&&) = delete;
};

#endif
