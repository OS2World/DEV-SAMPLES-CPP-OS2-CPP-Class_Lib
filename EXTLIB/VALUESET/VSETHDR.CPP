//************************************************************
// Extending the Library - Value Set Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#define INCL_WIN
#include <os2.h>

#include "vsethdr.hpp"
#include "valueset.hpp"

ValueSetHandler :: ValueSetHandler ( ValueSet &vset )
  : IHandler()
  {
  handleEventsFor( &vset );
  }

ValueSetHandler :: ValueSetHandler ( )
  : IHandler()
  {
  }

ValueSetHandler :: ~ValueSetHandler ( )
  {
  }
 
ValueSetHandler &ValueSetHandler :: handleEventsFor( ValueSet *vset )
  {
  IHandler::handleEventsFor( vset );
  return *this;
  }

Boolean ValueSetHandler :: enter ( ValueSetEvent &vsetEvent )
  {
  return false;
  }

Boolean ValueSetHandler :: selected  ( ValueSetEvent &vsetEvent )
  {
  return false;
  }

Boolean ValueSetHandler :: gotFocus ( ValueSetEvent &vsetEvent )
  {
  return false;
  }

Boolean ValueSetHandler :: lostFocus ( ValueSetEvent &vsetEvent )
  {
  return false;
  }

Boolean ValueSetHandler :: help ( ValueSetEvent &vsetEvent )
  {
  return false;
  }

Boolean ValueSetHandler :: dispatchHandlerEvent ( IEvent &event )
  {
  Boolean
    result = false;
  if ( event.eventId() == WM_CONTROL )
    {
    ValueSetEvent
      vsetEvent( event );
    unsigned long
      msg = event.parameter1().number2();
    switch ( msg )
      {
      case VN_ENTER:
        result = enter( vsetEvent );
        break;
      case VN_SELECT:
        result = selected( vsetEvent );
        break;
      case VN_KILLFOCUS:
        result = lostFocus( vsetEvent );
        break;
      case VN_SETFOCUS:
        result = gotFocus( vsetEvent );
        break;
      case VN_HELP:
        result = help( vsetEvent );
        break;
      }
    event.setResult( vsetEvent.result() );
    }
  return result;
  }

ValueSetHandler &ValueSetHandler :: handleEventsFor( IWindow * )
  {
  return *this;
  }
