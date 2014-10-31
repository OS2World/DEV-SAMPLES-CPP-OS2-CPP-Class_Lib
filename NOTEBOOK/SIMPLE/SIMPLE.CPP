//************************************************************
// Notebook Control - Simple Notebook Example                 
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <inotebk.hpp>
#include <iframe.hpp>

void main()
{
  IFrameWindow frame ("Default Notebook");
  INotebook notebook (0x8008, &frame, &frame);

  frame
    .setClient(&notebook)
    .setFocus()
    .show();
  IApplication::current().run();
}

