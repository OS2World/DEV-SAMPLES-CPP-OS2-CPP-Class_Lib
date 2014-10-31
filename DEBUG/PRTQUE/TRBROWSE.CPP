//************************************************************
// Problem Determination  - Trace Queue Browser
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include "trbrowse.hpp"
#include "trbrowse.h"

TraceBrowser::TraceBrowser ( const char* applicationName )
       : IFrameWindow(applicationName),
         cnrWin(0x8008, this, this),
         reader("\\QUEUES\\PRINTF32", this->handle()),
         thread(),
         handler(*this) 
{
  // Attach handler to our frame
  handler.handleEventsFor(this);

  // Change the font & show text view with extended selection
  IFont font("Courier", 8);
  container()
    .showTextView()
    .setExtendedSelection()
    .setFont(font);

  // Put the container in the client and
  // and start the queue
  (*this)
    .setClient(&container())
    .postEvent(START_QUEUE);
}

Boolean  TraceBrowserHandler::dispatchHandlerEvent ( IEvent & evt )
{
  switch (evt.eventId())
  {
     case ADD_OBJECT:
     {
       browserWindow.container()
         .addObject((IContainerObject*)(void*)evt.parameter1());
       return true;
     }
     case START_QUEUE:
     {
       // Start Reader in a separate Thread
       browserWindow.readerThread()
          .start(new IThreadMemberFn<QueueReader>
                 (browserWindow.queueReader(), 
                  QueueReader::run));
       return true;
     }
     default:
        break;
  } /* endswitch */
  return false;
}
