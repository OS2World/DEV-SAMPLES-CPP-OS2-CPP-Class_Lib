//************************************************************
// Error Handling - New Exception Class
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iexcbase.hpp>
#include "custexcp.hpp"

void main()
{
  CustomException exc("Hey dude!  Bet you thought this was a real program!",
                      -1);
  ITHROW(exc);
}
