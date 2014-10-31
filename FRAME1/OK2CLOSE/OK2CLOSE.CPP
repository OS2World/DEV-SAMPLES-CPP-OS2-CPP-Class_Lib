//************************************************************
// Frame Window Closing - Confirm Frame Closing
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#define INCL_WIN
#include <os2.h>

#include <iframe.hpp>
#include <imsgbox.hpp>
#include <icmdhdr.hpp>
#include <istring.hpp>
#include <ithread.hpp>

class CloseHandler : public ICommandHandler {
public:
// Use this function to attach this handler to your frame:
virtual CloseHandler
 &handleClosingOf( IFrameWindow &frame )
    {
    ICommandHandler::handleEventsFor( &frame );
    return *this;
    }
// Override this function to insert your own "close" logic:
virtual Boolean
  systemCommand ( ICommandEvent &event )
    {
    Boolean
      result = false;
    if ( event.commandId() == SC_CLOSE )
      {
      IFrameWindow
       *frame = (IFrameWindow*)( event.window() );
      IMessageBox
        prompt( frame );
      IString
        title( 0, WinQueryWindowTextLength( frame->handle() ) );
      WinQueryWindowText( frame->handle(),
                          title.length()+1,
                          title );
      prompt.setTitle( title );
      const char* text = 
      "Press Cancel to keep window open; Press OK to let close";
      IMessageBox::Response
        rc = prompt.show( text,
                          IMessageBox::okCancelButton );
      if ( rc == IMessageBox::cancel )
        result = true;
      }
    return result;
    }
private:
virtual IHandler
 &handleEventsFor( IWindow *p )
    {
    return ICommandHandler::handleEventsFor( p );
    }
};

void main()
  {
  IFrameWindow
    frame( "Confirm on Close" );
  CloseHandler
    closer;
  closer.handleClosingOf( frame );
  frame.setFocus().show();
  IThread::current().processMsgs();
  }

