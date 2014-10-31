#ifndef _PARTOBJ_
#define _PARTOBJ_
//************************************************************
// Container - Combined Tree and Details View
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <icnrobj.hpp>
#include <istring.hpp>

class ExecutablePart : public IContainerObject
{
public:
  ExecutablePart   ( IString  partName,
                     Boolean  isTraceAble = true,
                     Boolean  isEnabledPart = false,
                     Boolean  willGenerateTrace = true,
                     Boolean  hasTrigger = false);

ExecutablePart
 &setTraceAble     ( Boolean traceAble      = true),
 &setEnabledPart   ( Boolean enabled        = true),
 &setGenerateTrace ( Boolean generateTrace  = true),
 &setTrigger       ( Boolean triggerOn      = true);

Boolean
 isTraceAble       ( ) const,
 isEnabledPart     ( ) const,
 willGenerateTrace ( ) const,
 hasTrigger        ( ) const;

// offset functions
static unsigned long
  traceAbleOffset       ( ),
  enabledPartOffset     ( ),
  generatesTraceOffset  ( ),
  containsTriggerOffset ( );

private:

IString
  strTraceAble,
  strEnabledPart,
  strGeneratesTrace,
  strContainsTrigger;
};

// INLINE Functions 

inline unsigned long ExecutablePart ::  traceAbleOffset ( ) 
{ return offsetof(ExecutablePart, strTraceAble); }

inline unsigned long ExecutablePart ::  enabledPartOffset ( ) 
{ return offsetof(ExecutablePart, strEnabledPart); }

inline unsigned long ExecutablePart ::  generatesTraceOffset ( ) 
{ return offsetof(ExecutablePart, strGeneratesTrace); }

inline unsigned long ExecutablePart ::  containsTriggerOffset ( ) 
{ return offsetof(ExecutablePart, strContainsTrigger); }

#endif // _PARTOBJ_
