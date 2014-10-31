//************************************************************
// Advanced Frame - Frame Save Handler
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include "savhndlr.hpp"

void main()
  {
  IFrameWindow
    frame( "Position Save Test" );
  SaveHandler
    handler( frame, "savhndlr.exe" );
  frame.setFocus();
  frame.showModally();
  }
