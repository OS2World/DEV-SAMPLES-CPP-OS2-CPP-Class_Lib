//************************************************************
// Problem Determination  - Trace Queue Browser
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <ithread.hpp>
#include "trbrowse.hpp"

const unsigned PMQUEUE_SIZE = 2000;  

void main( )
{
   // Note that we increase the size of the PM
   // message queue to try to avoid filling
   // it up.
   IThread::current().initializePM(PMQUEUE_SIZE);
 
   // Create the trace browser window
   TraceBrowser traceWindow("Trace Browser");

  // Give the window the focus and show it.
  // focus (try to be non-intrusive).
  traceWindow
    .setFocus()
    .show();

   IThread::current().processMsgs();
   IThread::current().terminatePM();
}
