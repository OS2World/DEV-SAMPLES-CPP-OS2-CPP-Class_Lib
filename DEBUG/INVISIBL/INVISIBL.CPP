//************************************************************
// Problem Determination - Finding an Invisible Window 
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <iapp.hpp>
#include <istattxt.hpp>

void main( )
{
  IFrameWindow frame(100);
  IStaticText text(101, &frame, &frame, IRectangle(50,50,50,50));

  text
    .setText("Initial Text");
  frame
   .setFocus()
   .show();

  IApplication::current().run();
}
