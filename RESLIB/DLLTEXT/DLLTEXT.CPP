//************************************************************
// Using OS/2 Resources - Building a Resource DLL
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iostream.h>
#include <istring.hpp>
#include <ireslib.hpp>
#include "mytext.h"

void main( )
{
  IDynamicLinkLibrary dllLib("myeng");
  IString str = dllLib.loadString(MY_TEXT);

  cout << "The resource text is [" << str << "]" << endl;
}


