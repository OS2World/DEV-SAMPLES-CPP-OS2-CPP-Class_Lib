//************************************************************
// Menus - Using an IMenuBar          
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <iapp.hpp>
#include <imenubar.hpp>
#include "menubar.h"

void main()
{
// Create a frame window with a menubar from a resource
IFrameWindow
  frame ("IMenuBar Example");

// Add the Menubar from a resource file
IMenuBar
  menuBar(MAIN_MENU, &frame);

// Change the cascade to a conditional cascade
menuBar.setConditionalCascade(MI_CASCADE, MI_CASCADE1);


// Set the focus and show the app
frame
  .setFocus()
  .show();
IApplication::current().run();
}


