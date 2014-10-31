#ifndef _VSETHDR_
#define _VSETHDR_
//************************************************************
// Extending the Library - Value Set Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************

#ifndef _IHANDLER_
  #include <ihandler.hpp>
#endif

#ifndef _VSETEVT_
  #include "vsetevt.hpp"
#endif

class ValueSet;

class ValueSetHandler : public IHandler {
typedef IHandler
  Inherited;
/*******************************************************************************
* This class provides a base from which you can derive your own special        *
* handlers to be attached to value set controls.                               *
*******************************************************************************/
public:
/*------------------------------- Constructor ----------------------------------
| The constructor accepts an optional ValueSet control object.  If             |
| provided, then the new handler is automatically attached.                    |
------------------------------------------------------------------------------*/
  ValueSetHandler ( ValueSet &vset );
  ValueSetHandler ( );

virtual
  ~ValueSetHandler ( );
 
/*-------------------------------- Attaching -----------------------------------
| You can only attach these handlers to ValueSet controls.                     |
------------------------------------------------------------------------------*/
virtual ValueSetHandler
 &handleEventsFor( ValueSet *vset );

protected:
/*------------------------------ Event Handling --------------------------------
| These functions should be overridden to add your event handling.             |
------------------------------------------------------------------------------*/
virtual Boolean
  enter     ( ValueSetEvent &vsetEvent ),
  selected  ( ValueSetEvent &vsetEvent ),
  gotFocus  ( ValueSetEvent &vsetEvent ),
  lostFocus ( ValueSetEvent &vsetEvent ),
  help      ( ValueSetEvent &vsetEvent );

/*------------------------------ Implementation --------------------------------
| These functions provide utility services used to implement this class.       |
------------------------------------------------------------------------------*/
virtual Boolean
  dispatchHandlerEvent ( IEvent &event );

private:
virtual ValueSetHandler
 &handleEventsFor( IWindow * );

  ValueSetHandler ( const ValueSetHandler & );
  operator = ( const ValueSetHandler & );
}; // class ValueSetHandler

#endif // _VSETHDR_
