//************************************************************
// Advanced Frame - Dialog Window Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#define INCL_WIN
#include <os2.h>

#include "dlghndlr.hpp"

DialogInitEvent :: DialogInitEvent ( const IEvent &event )
  : IEvent( event )
  {
  }

IWindowHandle DialogInitEvent :: focusWindow ( ) const
  {
  return IWindowHandle( parameter1() );
  }

void *DialogInitEvent :: createParameters ( ) const
  {
  return parameter2();
  }

DialogInitEvent &DialogInitEvent :: focusChanged ( )
  {
  setResult( true );
  return *this;
  }

Boolean DialogHandler :: initialize ( DialogInitEvent &initEvent )
  {
  return false;
  }

Boolean DialogHandler :: dispatchHandlerEvent ( IEvent &event )
  {
  return false;
  }

