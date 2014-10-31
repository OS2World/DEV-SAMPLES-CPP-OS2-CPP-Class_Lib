//************************************************************
// Using OS/2 Resources - Switching Resources Dynamically
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <iapp.hpp>
#include <istattxt.hpp>
#include "mytext.h"

void main()
{
   // Store the location of our resources from MYENG.DLL
   // in the application framework
   IApplication::current()
     .setUserResourceLibrary("myeng");

   // Create a frame and put the text field in the client
   IFrameWindow frame("Text from a Resource File");
   IStaticText text(100, &frame, &frame);

   // Align and add the text from a resource 
   text
     .setAlignment(IStaticText::centerCenter)
     .setText(MY_TEXT);

   // Put the text in the client and show the window
   frame
     .setClient(&text)
     .setFocus()
     .show();

   // Run the app
   IApplication::current().run();     
}
