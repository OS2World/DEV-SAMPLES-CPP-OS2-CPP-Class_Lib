//************************************************************
// Menus - Dynamic Submenu Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <imle.hpp>
#include <iapp.hpp>
#include <isubmenu.hpp>
#include <imenuhdr.hpp>
#include <icmdhdr.hpp>
#include "dynsubmn.h"

// Menu handler to capture pop-up menu requests
class MenuHandler : public IMenuHandler
{
public:
  MenuHandler (IMultiLineEdit& editWindow)
    : _editWindow(editWindow) {}
protected:  
virtual Boolean
  menuShowing   ( IMenuEvent& menuEvent,
                  ISubmenu&   submenuAboutToShow );
private:
IMultiLineEdit
 &_editWindow;
MenuHandler& operator=(const MenuHandler&);
};

// Command handler to capture menu commands
class CommandHandler : public ICommandHandler
{
public:
  CommandHandler ( IMultiLineEdit& status)
            : _status(status) {}

protected:
virtual Boolean
  command              ( ICommandEvent& event );

private:
IMultiLineEdit
 &_status;
CommandHandler& operator=(const CommandHandler&);
};

void main()
{
// Create a frame window with a menubar and an
// accelerator table from a resource file
IFrameWindow
  frame ("Dynamic Submenu Example", MAIN_MENU, 
         IFrameWindow::defaultStyle()
                | IFrameWindow::menuBar
                | IFrameWindow::accelerator);


// Create a Status Area in the Client
// and a command handler to write in it.  Add
// the command handler to the text field so that
// we get any command messages it sends.
IMultiLineEdit
  editArea(ID_EDIT, &frame, &frame);

CommandHandler 
  commandHandler(editArea);
commandHandler
  .handleEventsFor(&frame)
  .handleEventsFor(&editArea);

// Add a menu handler to dynamically alter the menu
MenuHandler
  editMenuHandler(editArea);
editMenuHandler.handleEventsFor(&editArea);

// Set the focus and show the app
editArea.setFocus();
frame
  .setClient(&editArea)
  .show();
IApplication::current().run();

}

Boolean MenuHandler::menuShowing   ( IMenuEvent& event,
                                     ISubmenu&   submenu )
{
  // Enable and disable the appropriate "Edit flags"
  if(submenu.id() == MI_EDIT)
  {
     if(!_editWindow.hasSelectedText())
     {
        submenu.disableItem(MI_COPY);
        submenu.disableItem(MI_CUT);
     }
     else if (_editWindow.isReadOnly())
     {
        submenu.disableItem(MI_CUT);
        submenu.disableItem(MI_PASTE);
     }
     if(!_editWindow.clipboardHasTextFormat())
        submenu.disableItem(MI_PASTE);
  }
  return true;
}


Boolean CommandHandler::command( ICommandEvent& event )
{
  switch(event.commandId())
  {
    case MI_CUT           :     
    {
      _status.cut();
      return true;
    }

    case MI_COPY          :     
    {
      _status.copy();
      return true;
    }

    case MI_PASTE         :     
    {
      _status.paste();
      return true;
    }

    case MI_READONLY   :
    {
      _status.disableDataUpdate();
      return true;
    }

    case MI_READWRITE   :
    {
      _status.enableDataUpdate();
      return true;
    }

    case MI_FILE          :     
    case MI_NEW           :     
    case MI_OPEN          :     
    case MI_SAVE          :     
    case MI_SAVEAS        :     
    case MI_EDIT          :     
    case MI_UNDO          :     
    case MI_EXAMPLE       :     
    case MI_BITMAP        :     
    case MI_HELP          :     
    case MI_GENERAL_HELP  :     
    case MI_CASCADE1      :
    case MI_CASCADE2      :
    case MI_CASCADE3      :
    {
       _status.setText(event.commandId());
       return true;
    }
  }
return false;
}

