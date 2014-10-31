//************************************************************
// Extending the Library - Value Set Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <os2def.h>
#include <ipoint.hpp>
#include "vsetevt.hpp"

ValueSetEvent :: ValueSetEvent ( IEvent &event )
  : IControlEvent( event )
  {
  }

ValueSet *ValueSetEvent :: valueSet ( ) const
  {
  return (ValueSet*)controlWindow();
  }

unsigned long ValueSetEvent :: row ( ) const
  {
  return parameter2() & 0xffffU;
  }

unsigned long ValueSetEvent :: column ( ) const
  {
  return parameter2() >> 16;
  }

IPoint ValueSetEvent :: rowAndColumn ( ) const
  {
  return IPoint( column(), row() );
  }
