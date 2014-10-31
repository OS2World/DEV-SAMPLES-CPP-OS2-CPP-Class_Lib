/*************************************************************/
/* Basic help program.                                       */
/*                                                           */
/* Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.       */
/* All Rights Reserved.                                      */
/*************************************************************/
#define INCL_DOSPROCESS   // For DosExecPgm.
#define INCL_DOSERRORS    // For NO_ERROR.
#include <os2.h>

#include <ihelphdr.hpp>
#include <imsgbox.hpp>
#include "tutorhdr.hpp"
#include "helpwin.h"

Boolean
  TutorialHandler :: showTutorial ( IHelpTutorialEvent& event )
{
  char buffer[260];
  IString args( (char*)event.tutorialName(),
                event.tutorialName().length() + 2,
                0x00 );   // Ensure ends with two nulls.
  args.space( 1, 0x00 );  // Assume a token is an argument.
  RESULTCODES result;

  unsigned long rc =
     DosExecPgm( buffer, sizeof(buffer), EXEC_ASYNC,
                 (char*)args, 0, &result, (char*)args );

  if (rc != NO_ERROR)
  {
     IMessageBox msg( event.window() );
     msg
      .setTitle( "Tutorial - Error" )
      .show( "Error starting " + event.tutorialName()
              + ".  Return code = " + IString(rc) + ".",
             IMessageBox::errorIcon | IMessageBox::moveable,
             PANEL_TUTORIAL_ERROR );
  }

  return true;
}
