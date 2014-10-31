//************************************************************
// Problem Determination - Simple Trace Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <itrace.hpp>
#include <istring.hpp>

int foo(unsigned long count);

void main()
{
   IMODTRACE_DEVELOP("main");
   foo(10);
}

int foo(unsigned long count)
{
  IFUNCTRACE_DEVELOP();
  ITRACE_DEVELOP(IString("The count is ")+IString(count).d2x());
  return 0;
}
