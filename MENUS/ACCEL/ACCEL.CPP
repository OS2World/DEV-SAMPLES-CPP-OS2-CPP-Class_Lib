//************************************************************
// Menus  - Using an Accelerator Table Resource 
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <istattxt.hpp>
#include <iapp.hpp>
#include <iaccel.hpp>
#include <icmdhdr.hpp>
#include "accel.h"


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
CommandHandler ( const CommandHandler&);
CommandHandler& operator= ( const CommandHandler&);
};

void main()
{
// Create a frame window with a menubar 
IFrameWindow
  frame ("Accelerator Example", MAIN_MENU,
         IFrameWindow::defaultStyle()
                | IFrameWindow::menuBar);

// Load an Accelerator table from the resource
// file and associate it with our frame window
IAccelerator accelTable(MAIN_MENU, &frame);

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