//************************************************************
// Frame Window Basics - Modal Frame Window
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************

#include <iframe.hpp>

void main() 
{
  IFrameWindow
    mainWindow("Modal Frame");

  // Give frame focus.
  mainWindow.setFocus(); 

  // Process events 
  mainWindow.showModally();
}

