//************************************************************
// Button Controls - Title Bar Bitmap Example                 
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iapp.hpp>
#include <iframe.hpp>
#include <igraphbt.hpp>
#include <istattxt.hpp>
#include <isizehdr.hpp>
#include <iiconctl.hpp>
#include <icmdhdr.hpp>
#include "titlebut.h"


// Command handler to capture button commands
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
CommandHandler& operator=(const CommandHandler&);
};

// Create a Resize Handler for the Graphic Push Button
class GraphicResizeHandler : public IResizeHandler {

protected:
virtual Boolean
  windowResize         ( IResizeEvent& event );
}; 


void main()
{
IFrameWindow
  frame ("Title Bar Bitmap Example");

// Titlebar Bitmaps using Buttons
IGraphicPushButton
  ringBefore(ID_RINGBEFORE, &frame, &frame, ID_RINGBEFORE),
  ringAfter(ID_RINGAFTER, &frame, &frame, ID_RINGAFTER);

// Create the resize handler and energize
// it for both bitmap buttons
GraphicResizeHandler resizeHandler;
resizeHandler
  .handleEventsFor(&ringBefore)
  .handleEventsFor(&ringAfter);

// Add the buttons as frame extensions
frame
  .addExtension(&ringAfter,  IFrameWindow::rightOfTitleBar, 22)
  .addExtension(&ringBefore, IFrameWindow::rightOfTitleBar, 22);

// Create a Status Area and
// a command handler to write in it
IStaticText statusArea(ID_STATUS, &frame, &frame);
CommandHandler commandHandler(statusArea);
commandHandler.handleEventsFor(&frame);

// Put the status area in the client, 
// set the focus, and show the app
frame
  .setClient(&statusArea)
  .setFocus()
  .show();
IApplication::current().run();

}

// A Command handler just to be sure the buttons work
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

// Resize the IIconControl child of the IGraphicPushButton 
// - this is needed because too much padding is around the 
// IIconControl by default
Boolean GraphicResizeHandler :: windowResize( IResizeEvent& evt )
{
  IGraphicPushButton* button = (IGraphicPushButton*)evt.window();
  if (evt.oldSize() != evt.newSize() &&
             !(button->isSizeToGraphic()))
  {
     button->graphicWindow().moveSizeTo(IRectangle(2,2,22,22));
  }
  return true;
}
