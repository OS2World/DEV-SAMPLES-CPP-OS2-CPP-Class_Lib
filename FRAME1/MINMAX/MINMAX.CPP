//************************************************************
// Frame Window Basics - Minimize/Maximize Handler Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <istattxt.hpp>
#include "chdhider.hpp"

void main()
{
  // Create a frame window from a dialog.
  IFrameWindow frame(IC_DEFAULT_FRAME_ID);
  frame.setIcon(IC_DEFAULT_FRAME_ID);
    
  // Create and attach the Child Hider handler.
  // If you want to see the problem the handler
  // fixes, comment out the handleEventsFor function
  // and rebuild the program.  Then run the
  // program and minimize it to the "desktop."
  ChildHider hider;
  hider.handleEventsFor(&frame);

  // Set the focus and show the frame.
  frame
   .setFocus()
   .show();

  IApplication::current().run();
}

