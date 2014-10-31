//************************************************************
// Menus - Title Bar Bitmaps       
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <istattxt.hpp>
#include <iapp.hpp>
#include <imenu.hpp>
#include <icmdhdr.hpp>
#include "titlebmp.h"

#define INCL_WINFRAMEMGR  // For FID_MINMAX
#include <os2.h>

// Create a Class to represent the MinMaxMenu
//  (This is modeled after ISystemMenu)
class MinMaxMenu : public IMenu {
public:
   MinMaxMenu ( IFrameWindow& owner );

private:
MinMaxMenu ( const MinMaxMenu&);
MinMaxMenu& operator= ( const MinMaxMenu&);
};

MinMaxMenu :: MinMaxMenu(IFrameWindow&  owner)
{
   IWindowHandle hwndMinMaxMenu =
             handleWithId(FID_MINMAX,owner.handle());
   setAutoDestroyWindow(false);
   startHandlingEventsFor(hwndMinMaxMenu);
}
// Command handler to capture menu commands
class CommandHandler : public ICommandHandler
{
public:
  CommandHandler ( IStaticText& status)
            : _status(status) {}

protected:
virtual Boolean
  command              ( ICommandEvent& event );

private:
IStaticText
 &_status;
CommandHandler& operator=( const CommandHandler&);
};

void main()
{
IFrameWindow
  frame ("Title Bar Bitmap Example");

// Titlebar Bitmaps using Menus
MinMaxMenu minMaxMenu(frame);
IMenuItem 
  ringBefore(ID_RINGBEFORE),
  ringAfter(ID_RINGAFTER);

// Put the bitmaps first in the menu
ringBefore
  .setBitmap(ID_RINGBEFORE)
  .setIndex(0);
ringAfter
  .setBitmap(ID_RINGAFTER)
  .setIndex(0);

minMaxMenu
  .addItem(ringAfter, 0)
  .addItem(ringBefore, 0);

// Create a Status Area in the Client
// and a command handler to write in it
IStaticText statusArea(ID_STATUS, &frame, &frame);
CommandHandler commandHandler(statusArea);
commandHandler.handleEventsFor(&frame);

// Set the focus and show the app
frame
  .setClient(&statusArea)
  .setFocus()
  .show();
IApplication::current().run();

}


Boolean CommandHandler::command( ICommandEvent& event )
{
  switch(event.commandId())
  {
    case ID_RINGBEFORE :
    {
       _status.setText("Ring before button pressed");
       return true;
    }

    case ID_RINGAFTER :
    {
       _status.setText("Ring after button pressed");
       return true;
    }
  }
return false;
}


