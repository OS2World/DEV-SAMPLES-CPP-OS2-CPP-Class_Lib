#ifndef _VSETEVT_
#define _VSETEVT_
//************************************************************
// Extending the Library - Value Set Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************

#ifndef _ICTLEVT_
  #include <ictlevt.hpp>
#endif

class IPoint;
class ValueSet;

class ValueSetEvent : public IControlEvent {
typedef IEvent
  Inherited;
/*******************************************************************************
* Objects of this class represent value set control notification events.       *
* IN addition to the inherited behavior of generic events, ValueSetEvent       *
* objects also return the appropriate row/column positions to which the        *
* event relates.                                                               *
*******************************************************************************/
public:
/*------------------------------- Constructor ----------------------------------
| These events are constructed from generic IEvents.                           |
------------------------------------------------------------------------------*/
  ValueSetEvent ( IEvent &event );

/*-------------------------------- Parameters ----------------------------------
| These functions return the various event paraemters.                         |
------------------------------------------------------------------------------*/
ValueSet
 *valueSet ( ) const;

unsigned long
  row    ( ) const,
  column ( ) const;

IPoint
  rowAndColumn ( ) const;

}; // class ValueSetEvent

#endif // _VSETEVT_
