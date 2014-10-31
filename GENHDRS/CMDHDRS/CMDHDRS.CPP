//************************************************************
// Reusable Handlers - Simple Command Handler
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iapp.hpp>
#include <icnrctl.hpp>
#include <iframe.hpp>
#include "cmdhdr1.hpp"
#include "cmdhdr2.hpp"

void main ( )
{
  // Create the frame with a container client window.
  IFrameWindow frame( "Command Handlers" );
  IContainerControl client( 0x8008, &frame, &frame );
  frame.setClient( &client );

  // Set up the container.
  client
   .setTitle( "Use mouse button 2 to display a pop-up menu." )
   .showTitle()
   .showTitleSeparator();

  // Add this container menu handler to display the pop-up menu.
  PopupMenuHandler popupHandler;
  popupHandler.handleEventsFor( &client );

  // Attach command handlers.
  OneBeepCmdHandler oneBeepHandler;
  oneBeepHandler.handleEventsFor( &client );
  TwoBeepCmdHandler twoBeepHandler;
  twoBeepHandler.handleEventsFor( &frame );

  frame
   .setFocus()
   .show();
  IApplication::current().run();
}
