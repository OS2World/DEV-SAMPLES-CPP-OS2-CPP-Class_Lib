#ifndef _TRBROWSE_
#define _TRBROWSE_
//************************************************************
// Problem Determination  - Trace Queue Browser
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <icnrctl.hpp>
#include <ithread.hpp>
#include <ihandler.hpp>
#include <ifont.hpp>
#include "querdr.hpp"

class TraceBrowser;

// Handler to process Queue requests.
class TraceBrowserHandler : public IHandler{
public:
  TraceBrowserHandler ( TraceBrowser& browser) 
       : browserWindow(browser) {}
protected:
virtual Boolean
  dispatchHandlerEvent ( IEvent &evt );
private:
TraceBrowser
 &browserWindow;
TraceBrowserHandler (const TraceBrowserHandler&);
TraceBrowserHandler operator= (const TraceBrowserHandler&);
};

class TraceBrowser : public IFrameWindow {
public:

 TraceBrowser   ( const char* applicationName );

IContainerControl
 &container     ( )       { return cnrWin;}
QueueReader
 &queueReader   ( )       { return reader;}
IThread
 &readerThread  ( )       { return thread; }

private:
TraceBrowserHandler
  handler;
IContainerControl
  cnrWin;
QueueReader
  reader;
IThread
  thread;
TraceBrowser (const TraceBrowser& );
TraceBrowser& operator= (const TraceBrowser& );
};
#endif  // _TRBROWSE_
