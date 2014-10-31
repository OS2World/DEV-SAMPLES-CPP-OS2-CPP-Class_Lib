//************************************************************
// Thread - Executing a Thread with _System Linkage
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#define INCL_DOSPROCESS
#include <os2.h>

#include <ithread.hpp>
#include <iostream.h>

// Function:
//   o with system linkage,
//   o accepting unsigned long argument, and
//   o returning void.
void _System function( unsigned long arg )
  {
  char
   *pMsg = (char*)arg;
  cerr << "Thread started using " << pMsg << endl;
  }
void main()
  {
  // Start function using DosCreateThread.
  TID
    tid;
  DosCreateThread( &tid,
                   function,
                   (unsigned long)"DosCreateThread",
                   0,
                   4096 );

  // Start function using IThread::start.
  IThread
    thread3;
  thread3.start( function, (unsigned long)"IThread::start" );

  // Start function using an IThread constructor.
  IThread
    thread4( function, (unsigned long)"IThread constructor" );

  // Wait a little, so all threads can run.
  DosSleep( 250 );
  }

