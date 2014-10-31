//************************************************************
// Container - Combined Tree and Details View
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iapp.hpp>
#include "partlist.hpp"

void main ()
{
  // Create the view of EXE parts and 
  // open it.
  PartsList partsView;
  partsView
   .open();

  IApplication::current().run();
}

