#ifndef _HCMDHDR_
#define _HCMDHDR_
/*************************************************************/
/* Basic help program.                                       */
/*                                                           */
/* Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.       */
/* All Rights Reserved.                                      */
/*************************************************************/
#define INCL_WINHELP    // For HM_TUTORIAL.
#include <os2.h>

#include <icmdhdr.hpp>
#include <ihelp.hpp>
#include <imsgbox.hpp>
#include <istring.hpp>
#include "helpwin.h"

class HelpCommandHandler : public ICommandHandler {
protected:
virtual Boolean
  command  ( ICommandEvent& event )
  {
    Boolean dontPassOn = false;
    switch (event.commandId())
    {
       case ID_USINGHELP:
       {           // For "Using help" choice.
         IHelpWindow* help =
            IHelpWindow::helpWindow( event.window() );
         help->show( IHelpWindow::using );
         dontPassOn = true;
         break;
       }
       case ID_TUTORIAL:
       {           // For "Tutorial" choice.
         event.window()
          ->sendEvent( HM_TUTORIAL,
                   IEventParameter1( "VIEW.EXE TUTORIAL.INF" ));
         dontPassOn = true;
         break;
       }
       case ID_PRODUCTINFO:
       {           // For "Product information" choice.
         IMessageBox msg( event.window() );
         msg
          .setTitle( "Product Information" )
          .show( "Basic help sample program.\n"
                  + IString( "Copyright (C) 1994, " )
                  + IString( "Law, Leong, Love, " )
                  + IString( "Olson, Tsuji." ),
                 IMessageBox::noIcon | IMessageBox::moveable,
                 PANEL_PRODUCT_INFO_MSG );
         dontPassOn = true;
         break;
       }
       default:
         break;
    }
    return dontPassOn;
  }
};
#endif // _HCMDHDR_
