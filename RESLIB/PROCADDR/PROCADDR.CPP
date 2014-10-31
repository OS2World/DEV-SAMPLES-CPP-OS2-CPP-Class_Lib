/************************************************************
/ Using OS/2 Resources - Loading a Function Address
/
/ Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
/ All Rights Reserved.
************************************************************/
#include <iprocadr.hpp>
#include <stream.h>

typedef int (*IntReturningInt)( int );

void main( )
{
  IProcedureAddress<IntReturningInt> isValid( "isValid", "MYENG" );
  
  int checkIt=0;
  int valid=0;
  
  while(checkIt!=99)
  {
  
   cout << "Enter a number (99 to quit)" << "\n";
   cin >> checkIt;
   valid = isValid(checkIt );
   cout << "isValid() returned " << valid << "\n";
  }
}

