#ifndef _DLGHNDLR_
#define _DLGHNDLR_
//************************************************************
// Advanced Frame - Dialog Window Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************

#include <ievent.hpp>
#include <ihandler.hpp>

class DialogInitEvent : public IEvent {
public:
  DialogInitEvent ( const IEvent &event );
IWindowHandle
  focusWindow ( ) const;
void
 *createParameters ( ) const;
DialogInitEvent
 &focusChanged ( );
};

class DialogHandler : public IHandler {
public:
virtual Boolean
  initialize ( DialogInitEvent &initEvent );
protected:
virtual Boolean
  dispatchHandlerEvent ( IEvent &event );
};

#endif // _DLGHNDLR_
