//************************************************************
// Using OS/2 Resources - Resources in the EXE
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iostream.h>
#include <istring.hpp>
#include <ireslib.hpp>
#include "mytext.h"

void main()
{
  IResourceLibrary reslib;
  IString str = reslib.loadString(MY_TEXT);

  cout << "The resource text is [" << str << "]" << endl;
}


