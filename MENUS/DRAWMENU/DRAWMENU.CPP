//************************************************************
// Menus - Custom Drawing Example 
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <istattxt.hpp>
#include <iapp.hpp>
#include <ifont.hpp>
#include <imenubar.hpp>
#include <imndihdr.hpp>
#include <icmdhdr.hpp>
#include <irect.hpp>
#include <istring.hpp>
#include "drawmenu.h"

#define INCL_WINWINDOWMGR    // for WinDrawText
extern "C" {
   #include <os2.h>
}
// Menu handler to capture Draw Item requests
class MenuDrawHandler : public IMenuDrawItemHandler
{
public:
  MenuDrawHandler () 
      : font("Tms Rmn", 24) {}
 
protected:  
virtual Boolean
  setSize       ( IMenuDrawItemEvent& event,
                  ISize&              newSize),
  draw          ( IMenuDrawItemEvent& event,
                  DrawFlag&           flag),
  highlight     ( IMenuDrawItemEvent& event),
  unhighlight   ( IMenuDrawItemEvent& event),
  drawText      ( IMenuDrawItemEvent& event,
                  Boolean             highlight);

private:
IFont
  font;
};

// Command handler to capture menu commands
class CommandHandler : public ICommandHandler
{
public:
  CommandHandler ( IStaticText& status)
            : _status(status)  {}

protected:
virtual Boolean
  command    ( ICommandEvent& event );

private:
IStaticText
 &_status;
CommandHandler& operator=(const CommandHandler&);
};

void main()
{
IFrameWindow
  frame ("Custom Menu Drawing Example");

// Add the Menubar from a resource file
IMenuBar 
  menuBar(MAIN_MENU, &frame);

// Change a menu item to the drawItem style
IMenuItem drawItem = menuBar.menuItem(MI_DRAWITEM);
drawItem.setDrawItem();
menuBar.setItem(drawItem);

// Create a Status Area in the Client
// and a command handler to write in it.  Add
// the command handler to the text field so that
// we get command messages it sends.
IStaticText 
  statusArea(ID_STATUS, &frame, &frame);
CommandHandler 
  commandHandler(statusArea);
commandHandler
  .handleEventsFor(&frame)
  .handleEventsFor(&statusArea);

// Add a MenuDrawHandler to the frame
MenuDrawHandler
  drawHandler;
drawHandler
  .handleEventsFor(&frame);

// Set the focus and show the app
frame
  .setClient(&statusArea)
  .setFocus()
  .show();
IApplication::current().run();
}


Boolean MenuDrawHandler :: setSize(IMenuDrawItemEvent& event,
                                   ISize& newSize)
{
  newSize.setWidth(160).setHeight(font.maxCharHeight()+5);
  return true;
}

Boolean MenuDrawHandler :: highlight(IMenuDrawItemEvent& event)
{
   if (event.itemId() != 0)
      return drawText(event, true);
   return false;
}

Boolean MenuDrawHandler :: unhighlight(IMenuDrawItemEvent& event)
{
   if (event.itemId() != 0)
      return drawText(event, false);
   return false;
}

Boolean MenuDrawHandler :: draw(IMenuDrawItemEvent& event, DrawFlag& flag)
{
   if (event.itemId() != 0)
      return drawText(event, false);
   return false;
}

Boolean MenuDrawHandler :: drawText(IMenuDrawItemEvent& event,
                                    Boolean highlight)
{
  // This routine assumes that all drawing is for text items whose
  // text is contained in a STRINGTABLE resource with an id the
  // same as the item id.
  IString str = IApplication::current().userResourceLibrary()
                   .loadString(event.itemId());
  str = " "+str;
  font.beginUsingFont(event.itemPresSpaceHandle());
  unsigned long color = CLR_RED;
  unsigned long style = DT_LEFT | DT_VCENTER;
  if(!highlight)
    style |= DT_TEXTATTRS;

  RECTL rectl = event.itemRect().asRECTL();
  WinDrawText( event.itemPresSpaceHandle(), -1,
               str, &rectl,
               color, 0,
               style);
  font.endUsingFont(event.itemPresSpaceHandle());
  return true;
}


Boolean CommandHandler::command( ICommandEvent& event )
{
  switch(event.commandId())
  {
    default:
    {
      try {
       _status.setText(event.commandId());
      } catch (...) {}
      return true;
    }
  }
return false;
}

