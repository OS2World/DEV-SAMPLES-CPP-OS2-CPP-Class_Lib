#ifndef _APPSTAT_
#define _APPSTAT_
//************************************************************
// Packaging and Performance - Using Static Object Functions 
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************

#include <ireslib.hpp>

class AppStatics
{
public:
// Destructor for cleanup
  ~AppStatics ();

// DLL Accessor function
static IDynamicLinkLibrary
 &englishDLL();

private:
static IDynamicLinkLibrary
 *engDLL;
};

#endif // _APPSTAT_
