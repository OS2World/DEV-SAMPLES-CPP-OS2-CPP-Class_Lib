#ifndef _HKEYSHDR_
#define _HKEYSHDR_
/*************************************************************/
/* Basic help program.                                       */
/*                                                           */
/* Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.       */
/* All Rights Reserved.                                      */
/*************************************************************/
#include <ihelphdr.hpp>
#include "helpwin.h"    // For PANEL_KEYS_HELP.

class KeysHelpHandler : public IHelpHandler {
protected:
virtual Boolean
  keysHelpId ( IEvent& event )
  {
    event.setResult( PANEL_KEYS_HELP );
    return true;
  }
};

#endif // _HKEYSHDR_
