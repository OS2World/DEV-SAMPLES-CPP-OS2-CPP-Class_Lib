//************************************************************
// Menus  - Creating Pop-up Menus Dynamically 
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <istattxt.hpp>
#include <iapp.hpp>
#include <imenubar.hpp>
#include <ipopmenu.hpp>
#include <imenuhdr.hpp>
#include <icmdhdr.hpp>
#include "dynpopup.h"

#define INCL_WINFRAMEMGR  // For SC_CLOSE
#include <os2.h>

// Menu handler to capture pop-up menu requests
class MenuHandler : public IMenuHandler
{
protected:  
virtual Boolean
  makePopUpMenu(IMenuEvent& menuEvent);  
};

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
CommandHandler& operator= ( const CommandHandler&);
};

void main()
{
IFrameWindow
  frame ("Pop-Up Menu Example");

// Add the Menubar from a resource file
IMenuBar 
  menuBar(MAIN_MENU, &frame);

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

// Add a PopUp menu to the client status area
MenuHandler
  textPopUpHandler;
textPopUpHandler.handleEventsFor(&statusArea);

// Set the focus and show the app
frame
  .setClient(&statusArea)
  .setFocus()
  .show();
IApplication::current().run();

}

Boolean MenuHandler :: makePopUpMenu(IMenuEvent& event)
{
  // Create the pop-up menu
  IPopUpMenu * popUp;                 
  popUp=new IPopUpMenu(event.window(), POPUP_MENU);

  // Create menu items for "Close" and "Help"
  IMenuItem close(SC_CLOSE, IMenuItem::postSystemCommand);
  close.setText(SC_CLOSE);
  IMenuItem help(MI_HELP, IMenuItem::postHelp);
  help.setText(MI_HELP);

  // Add the menu items to the pop-up menu
  (*popUp)
    .addText(MI_EDIT,   MI_EDIT)
    .addSubmenu(MI_EDIT)
      .addText(MI_UNDO,  MI_UNDO, MI_EDIT)
      .addSeparator(MI_EDIT)
      .addText(MI_CUT,   MI_CUT,   MI_EDIT)
      .addText(MI_COPY,  MI_COPY,  MI_EDIT)
      .addText(MI_PASTE, MI_PASTE, MI_EDIT)
    .addText(MI_EXAMPLE, MI_EXAMPLE)
    .addSubmenu(MI_EXAMPLE)
      .addBitmap(MI_BITMAP, MI_BITMAP, MI_EXAMPLE)
      .addSeparator(MI_EXAMPLE)
      .addItem(close, MI_EXAMPLE)
      .addItem(help, MI_EXAMPLE)
    .setAutoDeleteObject();

  // Show the pop-up menu
  (*popUp)
    .show(event.mousePosition());
  return true;                         
}


Boolean CommandHandler::command( ICommandEvent& event )
{
  switch(event.commandId())
  {
    case MI_FILE          :     
    case MI_NEW           :     
    case MI_OPEN          :     
    case MI_SAVE          :     
    case MI_SAVEAS        :     
    case MI_EDIT          :     
    case MI_UNDO          :     
    case MI_CUT           :     
    case MI_COPY          :     
    case MI_PASTE         :     
    case MI_EXAMPLE       :     
    case MI_BITMAP        :     
    case MI_HELP          :     
    case MI_GENERAL_HELP  :     
    {
       _status.setText(event.commandId());
       return true;
    }

  }
return false;
}


