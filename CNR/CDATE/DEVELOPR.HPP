#ifndef _DEVELOPR_
#define _DEVELOPR_
//************************************************************
// Container Control - Dates and Times as CDATE/CTIME         
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <icnrctl.hpp>
#include <icnrcol.hpp>
#include <icnrobj.hpp>


#pragma pack(4)
struct CDATE    
{
   CDATE(unsigned char  aDay = 10,
         unsigned char  aMonth =1,
         unsigned short aYear  =1950)
      : day(aDay),
        month(aMonth),
        year(aYear) {}

   unsigned char   day;   
   unsigned char   month; 
   unsigned short  year;  
};

struct CTIME
{
   CTIME(unsigned char anHour = 17,
         unsigned char aMinute = 0,
         unsigned char aSecond = 0)
      : hours(anHour),
        minutes(aMinute),
        seconds(aSecond) {}

   unsigned char   hours; 
   unsigned char   minutes; 
   unsigned char   seconds; 
   unsigned char   ucReserved;  
};
#pragma pack()

class Developer : public IContainerObject
{
  public:
  Developer   ( IString       name,
                unsigned long iconId,
                IString       compuServeId = IString("?"),
                IString       age = IString("?"),
                const CDATE&  birthDate =CDATE(),
                const CTIME&  quittingTime=CTIME())
     : IContainerObject(name, iconId),
       strCompuServeId(compuServeId),
       strAge(age),
       date(birthDate),
       time(quittingTime)
 
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
CDATE
  date;
CTIME
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