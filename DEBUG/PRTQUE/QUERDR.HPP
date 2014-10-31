#ifndef _QUERDR_
#define _QUERDR_
//************************************************************
// Problem Determination  - Trace Queue Browser
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <ihandle.hpp>

class QueueReader
{
public:
QueueReader  ( const char*          queueName,
               const IWindowHandle& receiver);
~QueueReader ( );

void 
  run           ( );
unsigned long
 queueHandle    ( ) const { return qHandle;}
IWindowHandle
 targetHandle   ( ) const { return target;}

private:
IWindowHandle
  target;
unsigned long
  qHandle;
};
#endif  // _QUERDR_
