#ifndef _DEVELOPR_
#define _DEVELOPR_
//************************************************************
// Container Control - Dates and Times as IDate/ITime        
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <icnrctl.hpp>
#include <icnrcol.hpp>
#include <icnrobj.hpp>
#include <idate.hpp>
#include <itime.hpp>


class Developer : public IContainerObject
{
  public:
  Developer   ( IString       name,
                unsigned long iconId,
                IString       compuServeId = IString("?"),
                IString       age = IString("?"),
                const IDate&  birthDate =IDate(),
                const ITime&  quittingTime=ITime())
     : IContainerObject(name, iconId),
       strCompuServeId(compuServeId),
       strAge(age),
       date(birthDate.asString()),
       time(quittingTime.asString())
 {}

// offset functions
static unsigned long
  compuServeOffset ( )
{ return offsetof(Developer, strCompuServeId); }

static unsigned long
  ageOffset        ( )
{   return offsetof(Developer, strAge); }

static unsigned long
  dateOffset        ( )
{   return offsetof(Developer, date); }

static unsigned long
  timeOffset        ( )
{   return offsetof(Developer, time); }

private:

IString
  strCompuServeId;
IString
  strAge;
IString
  date;
IString
  time;

};


class DeveloperList : public IFrameWindow {
public:

  DeveloperList ( const char* title);

IContainerControl
 &container        ( );

private:
IContainerControl
  cnrctl;
DeveloperList& operator=(const DeveloperList&);
DeveloperList(const DeveloperList&);
};

#endif // _DEVELOPR_
