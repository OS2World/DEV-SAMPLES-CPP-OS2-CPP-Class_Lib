//************************************************************
// Getting Started - Simple Program Version 2
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include "start2ch.hpp"
#include "start2w.hpp"
#include "start2.h"

Boolean CutCopyPasteHandler :: command ( ICommandEvent& event )
{
  Boolean stopProcessingEvent = false;
  CodeWindow* frame = (CodeWindow*)event.window();
  switch ( event.commandId() )
  {
    case CMD_CUT:
      frame->cut();
      stopProcessingEvent = true;
      break;
    case CMD_COPY:
      frame->copy();
      stopProcessingEvent = true;
      break;
    case CMD_PASTE:
      frame->paste();
      stopProcessingEvent = true;
      break;
    default:
      break;
  }
  return stopProcessingEvent;
}
