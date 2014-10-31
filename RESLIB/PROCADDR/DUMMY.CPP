/************************************************************
/ Using OS/2 Resources - Loading a Function Address
/
/ Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
/ All Rights Reserved.
************************************************************/
extern "C" {

void ADummyFunction()
{
}

#pragma export(isValid, "isValid", 1)

// The following is added to test procaddr
int isValid( int number)
{

  if (number<10) 
     return 1;
  else
     return 0;
}

}
