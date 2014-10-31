//************************************************************
// Frame Window Basics - Frame Window From a Dialog Template
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************

#include <iframe.hpp>
#include <imenubar.hpp>
#include <icmdhdr.hpp>
#include "dialog.h"

class MyCommandHandler : public ICommandHandler {
protected:
virtual Boolean
  command ( ICommandEvent& event );
};


void main()
{
  // Create a primary frame window.
  IFrameWindow
    primary("Primary Frame");

  // Create a menu and add a choice to open Hello.
  IMenuBar 
    menuBar(&primary);
  
  menuBar
   .addText( 10, "File")
   .addSubmenu( 10)
   .addText( DIALOG_ID, "Hello", 10);

  // Create our command handler.
  MyCommandHandler cmdHandler;
  cmdHandler.handleEventsFor (&primary);

  // Set the focus and show the frame 
  primary
   .setFocus()
   .show();

  IApplication::current().run();
}
 

Boolean MyCommandHandler :: command ( ICommandEvent &event )
{
  // Check for Hello... menu choice...
  if ( event.commandId() == DIALOG_ID )
    {
    IFrameWindow
     *secondary = new IFrameWindow( DIALOG_ID, event.window() );
    (*secondary)
      .setAutoDeleteObject()
      .setFocus()
      .show();
    }
  return false;
}

