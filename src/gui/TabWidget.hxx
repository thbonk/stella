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

#ifndef TAB_WIDGET_HXX
#define TAB_WIDGET_HXX

#include "bspf.hxx"

#include "Command.hxx"
#include "Widget.hxx"

class TabWidget : public Widget, public CommandSender
{
  public:
    enum {
      kTabChangedCmd = 'TBCH'
    };

  public:
    TabWidget(GuiObject* boss, const GUI::Font& font, int x, int y, int w, int h);
    virtual ~TabWidget();

// use Dialog::releaseFocus() when changing to another tab

// Problem: how to add items to a tab?
// First off, widget should allow non-dialog bosses, (i.e. also other widgets)
// Could add a common base class for Widgets and Dialogs.
// Then you add tabs using the following method, which returns a unique ID
    int addTab(const string& title);
// Maybe we need to remove tabs again? Hm
    //void removeTab(int tabID);
// Setting the active tab:
    void setActiveTab(int tabID, bool show = false);
//    void disableTab(int tabID);
    void activateTabs();
    void cycleTab(int direction);
// setActiveTab changes the value of _firstWidget. This means Widgets added afterwards
// will be added to the active tab.
    void setParentWidget(int tabID, Widget* parent);

    int getTabWidth()  { return _tabWidth;  }
    int getTabHeight() { return _tabHeight; }
    int getActiveTab() { return _activeTab; }

    void loadConfig() override;

  protected:
    void handleMouseDown(int x, int y, MouseButton b, int clickCount) override;
    void handleMouseEntered() override;
    void handleMouseLeft() override;

    void handleCommand(CommandSender* sender, int cmd, int data, int id) override;
    bool handleEvent(Event::Type event) override;

    void drawWidget(bool hilite) override;
    Widget* findWidget(int x, int y) override;
    int getChildY() const override;

  private:
    struct Tab {
      string title;
      Widget* firstWidget;
      Widget* parentWidget;
      bool enabled;

      Tab(const string& t = "", Widget* first = nullptr, Widget* parent = nullptr,
          bool e = true)
        : title(t), firstWidget(first), parentWidget(parent), enabled(e) { }
    };
    using TabList = vector<Tab>;

    TabList _tabs;
    int     _tabWidth;
    int     _tabHeight;
    int     _activeTab;
    bool    _firstTime;

    enum {
#ifndef FLAT_UI
      kTabLeftOffset = 4,
      kTabSpacing = 2,
      kTabPadding = 3
#else
      kTabLeftOffset = 0,
      kTabSpacing = 1,
      kTabPadding = 4
#endif
    };

  private:
#ifndef FLAT_UI
    void box(int x, int y, int width, int height,
             uInt32 colorA, uInt32 colorB, bool omitBottom);
#endif
    void updateActiveTab();

  private:
    // Following constructors and assignment operators not supported
    TabWidget() = delete;
    TabWidget(const TabWidget&) = delete;
    TabWidget(TabWidget&&) = delete;
    TabWidget& operator=(const TabWidget&) = delete;
    TabWidget& operator=(TabWidget&&) = delete;
};

#endif
