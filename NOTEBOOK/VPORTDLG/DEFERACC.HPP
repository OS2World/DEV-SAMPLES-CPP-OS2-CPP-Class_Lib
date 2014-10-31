//************************************************************
// Notebook Control - Adding Notebook Windows to a Viewport
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <ihandler.hpp>
#include <iwindow.hpp>

// Prevent Alt+F4 from closing the dialog.
class DeferAccelerators : public IHandler {
protected:
virtual Boolean
  dispatchHandlerEvent ( IEvent& event )
  {
    Boolean dontPassOn = false;
    // Don't let the dialog/frame window process
    // accelerator keys.  These should instead be passed
    // up to the notebook's frame window for processing.
    // The notebook does this for frame page windows.
    // This handler lets us do it for frames that are
    // children of page windows.
    if (event.eventId() == 0x004B)  // WM_TRANSLATEACCEL.
    {         // Emulate notebook's handling for page windows.
       IWindow* parent = event.window()->parent();
       if (parent)
       {                // Forward event to parent (view port).
          IEventResult result = parent->sendEvent( event );
          event.setResult( result );
       }
       dontPassOn = true;  // Don't let the frame get it.
    }
    return dontPassOn;
  }
};
