//************************************************************
// Container - Combined Tree and Details View
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include "partobj.hpp"

const IString strNoYes[2] = {"Yes", "No"};


ExecutablePart ::  ExecutablePart   ( IString       name,
                                      Boolean  isTraceAble,
                                      Boolean  isEnabledPart,
                                      Boolean  willGenerateTrace,
                                      Boolean  hasTrigger)
                         : IContainerObject(name),
                           strTraceAble(""),
                           strEnabledPart(""),
                           strGeneratesTrace(""),
                           strContainsTrigger("")
 
{
setTraceAble(isTraceAble);
setEnabledPart(isEnabledPart);
setGenerateTrace(willGenerateTrace);
setTrigger(hasTrigger);
enableDataUpdate();
}

ExecutablePart& ExecutablePart :: setTraceAble     ( Boolean traceAble )
{
   this->strTraceAble = strNoYes[traceAble];
   return *this;
}

ExecutablePart& ExecutablePart :: setEnabledPart   ( Boolean enabledPart )
{
   this->strEnabledPart = strNoYes[enabledPart];
   return *this;
}

ExecutablePart& ExecutablePart :: setGenerateTrace ( Boolean generateTrace )
{
   this->strGeneratesTrace = strNoYes[generateTrace];
   return *this;
}

ExecutablePart& ExecutablePart :: setTrigger       ( Boolean containsTrigger)
{
   this->strContainsTrigger = strNoYes[containsTrigger];
   return *this;
}

Boolean ExecutablePart :: isTraceAble ( ) const
{
  if (this->strTraceAble == strNoYes[true])
     return true;
  else
     return false;
}

Boolean ExecutablePart :: isEnabledPart ( ) const
{
  if (this->strEnabledPart == strNoYes[true])
     return true;
  else
     return false;
}

Boolean ExecutablePart :: willGenerateTrace ( ) const
{
  if (this->strGeneratesTrace == strNoYes[true])
     return true;
  else
     return false;
}

Boolean ExecutablePart :: hasTrigger ( ) const
{
  if (this->strContainsTrigger == strNoYes[true])
     return true;
  else
     return false;
}

