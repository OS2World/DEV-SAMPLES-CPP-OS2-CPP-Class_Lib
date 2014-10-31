//************************************************************
// Menus  - Defining a Menu Resource
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <iapp.hpp>
#include "menures.h"

void main()
{
// Create a frame window with a menubar from a resource
IFrameWindow
  frame ("Menu Resource Example", MAIN_MENU,
         IFrameWindow::defaultStyle() | IFrameWindow::menuBar);

// Set the focus and show the app
frame
  .setFocus()
  .show();
IApplication::current().run();
}

