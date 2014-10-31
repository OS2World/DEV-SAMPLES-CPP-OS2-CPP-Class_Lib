#define INCL_DOSPROCESS
#include <os2.h>

#include <iapp.hpp>         
#include <istattxt.hpp>     
#include <iframe.hpp>       
#include <os2.h>

void main()                             
{
  IFrameWindow frame("Main Window");
  IStaticText text(0x8008, &frame, &frame);

  text
    .setText("Hello, World!")
    .setAlignment(IStaticText::centerCenter);

  frame
   .setClient(&text)
   .setFocus()
   .show();

  // Close Down App - end of trace run
  DosExit(EXIT_PROCESS,0);

  // Since we exit, the message loop never starts.
  IApplication::current().run();
}


