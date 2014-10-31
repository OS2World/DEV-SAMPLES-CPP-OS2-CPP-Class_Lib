//************************************************************
// Getting Started - Simple Program Version 2
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iapp.hpp>
#include "start2w.hpp"

void main ( )
{
  // Create a primary window that contains an MLE.
  CodeWindow primary( "Getting Started - Version 2" );

  // Set the input focus, and show the window.
  primary
   .setFocus()
   .show();

  // Display the window until the user closes it.
  IApplication::current().run();
}
