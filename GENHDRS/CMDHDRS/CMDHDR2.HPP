#ifndef _CMDHDR2_
#define _CMDHDR2_
//************************************************************
// Reusable Handlers - Simple Command Handler
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#define INCL_WINWINDOWMGR  // For CMDSRC_OTHER.
#include <os2.h>           // For DosBeep.

#include <icmdhdr.hpp>
#include <icnrmhdr.hpp>
#include <ipopmenu.hpp>
#include "cmdhdrs.h"

class TwoBeepCmdHandler : public ICommandHandler {
protected:
virtual Boolean
  command ( ICommandEvent& event )
  {
     Boolean dontPassOn = false;
     if (event.commandId() == ID_TWO_BEEP_CMD)
     {
        DosBeep( 200, 100 );
        event.window()
         ->sendEvent( IWindow::command,
                      IEventParameter1( ID_ONE_BEEP_CMD ),
                      IEventParameter2( CMDSRC_OTHER, false ) );
        dontPassOn = true;
     }
     return dontPassOn;
  }
};

class PopupMenuHandler : public ICnrMenuHandler {
protected:
virtual Boolean
  makePopUpMenu ( IMenuEvent& event )
  {
     IPopUpMenu* popUp =
                   new IPopUpMenu( ID_POPUP, event.window() );
     popUp->setAutoDeleteObject();
     popUp->show( event.mousePosition() );
     return true;
  }
};

#endif // _CMDHDR2_
