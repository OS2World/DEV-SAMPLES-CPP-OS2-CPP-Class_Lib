#ifndef _SAVHNDLR_
#define _SAVHNDLR_
//************************************************************
// Advanced Frame - Frame Save Handler
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <ihandler.hpp>
#include <istring.hpp>

class SaveHandler : public IHandler {
public:
  SaveHandler ( IFrameWindow  &frame,
                const IString &appName );

virtual Boolean
  saved( IEvent &event );

protected:
virtual Boolean
  dispatchHandlerEvent( IEvent &event );

virtual IHandler
 &handleEventsFor( IWindow *p );

private:
IString
  appName;
};

#endif  // SAVHNDLR_
