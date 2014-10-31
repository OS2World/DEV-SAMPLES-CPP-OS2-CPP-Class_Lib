#ifndef _CMDHDR1_
#define _CMDHDR1_
//************************************************************
// Reusable Handlers - Simple Command Handler
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <os2.h>        // For DosBeep.
#include <icmdhdr.hpp>
#include "cmdhdrs.h"

class OneBeepCmdHandler : public ICommandHandler {
protected:
virtual Boolean
  command ( ICommandEvent& event )
  {
     Boolean dontPassOn = false;
     if (event.commandId() == ID_ONE_BEEP_CMD)
     {
        DosBeep( 100, 100 );
        dontPassOn = true;
     }
     return dontPassOn;
  }
};
#endif // _CMDHDR1_
