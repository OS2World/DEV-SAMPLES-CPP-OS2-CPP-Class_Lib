//************************************************************
// Problem Determination - Termination Signal Handler 
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <signal.h>
#include <string.h>
#include <stdio.h>
#include <new.h>
 
void TrapOnTerm(int signal)
{
  // Cause a trap
  char* psz=0;
  strcpy(psz, "junk");
}
 
void main( )
 {
   signal(SIGABRT, (_SigFunc)TrapOnTerm);
 
   // Now cause a memory overlay for a termination
   char* pszBuffer = new char(10);
   strcpy(pszBuffer, "Memory overlay Memory overlay");

#ifdef __DEBUG_ALLOC__
   // And run the heap check to detect it with -Tm
   _heap_check();
#endif
 }
 
 


