//************************************************************
// Thread - Executing a Thread with _OptLink Linkage 
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#define INCL_DOSPROCESS
#include <os2.h>
#include <stdlib.h>
#include <ithread.hpp>
#include <iostream.h>

// Function:
//   o with optlink linkage,
//   o accepting void * argument, and
//   o returning void.
void _Optlink function( void *arg )
  {
  char
   *pMsg = (char*)arg;
  cerr << "Thread started using " << pMsg << endl;
  }

void main()
  {
  // Start function using _beginthread.
  _beginthread( function,
                0,
                8192,
                "_beginthread" );

  // Start function using IThread::start.
  IThread
    thread3;
  thread3.start( function, "IThread::start" );

  // Start function using an IThread constructor.
  IThread
    thread4( function, "IThread constructor" );

  // Wait a little, so all threads can run.
  DosSleep( 250 );
  }

