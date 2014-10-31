//************************************************************
// Frame Window Basics - Minimize/Maximize Handler Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************

#include "minmaxh.hpp"

#define INCL_WIN
#include <os2.h>

#include <iframe.hpp>

#include <iswp.hpp>

MinMaxHandler 
 &MinMaxHandler :: handleEventsFor ( IFrameWindow *frame )
  {
  this -> IHandler::handleEventsFor( frame );
  return *this;
  }

Boolean MinMaxHandler :: dispatchHandlerEvent ( IEvent &event )
  {
  Boolean
    result = false;
  switch ( event.eventId() )
    {
    case WM_ADJUSTFRAMEPOS:
      {
      ISWP
       *swp = (ISWP*)(char*)( event.parameter1() );
      if ( swp->flags() & SWP_MINIMIZE )
        result = this -> minimized( event );
      else if ( swp->flags() & SWP_MAXIMIZE )
        result = this -> maximized( event );
      else if ( swp->flags() & SWP_RESTORE )
        result = this -> restored( event );
      break;
      }
    default:
      break;
    }
  return result;
  }

Boolean MinMaxHandler :: minimized ( IEvent &event )
  {
  return false;
  }

Boolean MinMaxHandler :: maximized ( IEvent &event )
  {
  return false;
  }

Boolean MinMaxHandler :: restored ( IEvent &event )
  {
  return false;
  }

IHandler &MinMaxHandler :: handleEventsFor ( IWindow *p )
  {
  return Inherited::handleEventsFor( p );
  }

