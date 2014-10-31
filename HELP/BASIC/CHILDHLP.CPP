/*************************************************************/
/* Simple help program.                                      */
/*                                                           */
/* Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.       */
/* All Rights Reserved.                                      */
/*************************************************************/
#define INCL_WINMESSAGEMGR
#include <os2.h>

#include <iexcept.hpp>
#include <ihelp.hpp>
#include "childhlp.hpp"

Boolean
  ChildHelpHandler :: dispatchHandlerEvent ( IEvent& event )
{
  unsigned long activeWindow = true;
  switch ( event.eventId() )
  {
     case WM_ACTIVATE:
        // Frame is gaining or losing activation.
        activeWindow = event.parameter1().number1();
        // Fall into the WM_HELP case.
     case WM_HELP:
        // In case help is initialized only after this
        // frame window is activated.
        this->setActiveWindow( event, activeWindow );
        break;
     default:
        break;
  }
  return false;
}

ChildHelpHandler&
  ChildHelpHandler :: setActiveWindow ( IEvent& event,
                                        Boolean active )
{
  IHelpWindow* help = IHelpWindow::helpWindow( event.window() );
  if (help)
  {
     IFrameWindow* frame = 0;
     if (active)
     {
        frame = (IFrameWindow*)event.window();
     }
     help->setActiveWindow( frame, frame );
  }
  return *this;
}

ChildHelpHandler&
  ChildHelpHandler :: handleEventsFor ( IFrameWindow* child )
{             // Overloaded version for better type safety.
  IASSERTPARM( child != 0 );
  IHandler::handleEventsFor( child );
  return *this;
}

ChildHelpHandler&
  ChildHelpHandler :: stopHandlingEventsFor
                                      ( IFrameWindow* child )
{             // Overloaded version for better type safety.
  IASSERTPARM( child != 0 );
  IHandler::stopHandlingEventsFor( child );
  return *this;
}

IHandler&
  ChildHelpHandler :: handleEventsFor ( IWindow* window  )
{             // Private to hide version in IHandler.
  ITHROWLIBRARYERROR( IC_MEMBER_ACCESS_ERROR,
                      IErrorInfo::invalidRequest,
                      IException::recoverable );
  return *this;
}

IHandler&
  ChildHelpHandler :: stopHandlingEventsFor ( IWindow* window  )
{             // Private to hide version in IHandler.
  ITHROWLIBRARYERROR( IC_MEMBER_ACCESS_ERROR,
                      IErrorInfo::invalidRequest,
                      IException::recoverable );
  return *this;
}
