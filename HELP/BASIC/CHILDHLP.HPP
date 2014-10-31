#ifndef _CHILDHLP_
#define _CHILDHLP_
/*************************************************************/
/* Basic help program.                                       */
/*                                                           */
/* Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.       */
/* All Rights Reserved.                                      */
/*************************************************************/
#include <ihandler.hpp>

class IFrameWindow;

class ChildHelpHandler : public IHandler {
public:
virtual ChildHelpHandler
 &handleEventsFor       ( IFrameWindow* child ),
 &stopHandlingEventsFor ( IFrameWindow* child );
protected:
virtual Boolean
  dispatchHandlerEvent  ( IEvent& event );
ChildHelpHandler
 &setActiveWindow       ( IEvent& event,
                          Boolean active = true );
private:
virtual IHandler
 &handleEventsFor       ( IWindow* window  ),
 &stopHandlingEventsFor ( IWindow* window  );
};

#endif // _CHILDHLP_
