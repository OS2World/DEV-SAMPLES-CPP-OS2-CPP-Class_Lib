#ifndef _DATECTRL_
#define _DATECTRL_
//************************************************************
// List Controls - Spin Button Date Control                 
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <imcelcv.hpp>
#include <idate.hpp>
#include <ipoint.hpp>

class IStaticText;
class ISpinButton;
class DateSpinHandler;

class DateControl : public IMultiCellCanvas
{
public:
  DateControl ( unsigned long id,
                IWindow*      parent,
                IWindow*      owner,
                const IDate&  = IDate::today(),
                const IRange& = IRange(1970,2000));
DateControl
 &setDate       ( const IDate& aDate),
 &setYearRange  ( const IRange& aRange);

IString
  dateAsString ( ) const;

ISpinButton
 &month  (  ),
 &day    (  ),
 &year   (  );

private:
ISpinButton
 *_month,
 *_day,
 *_year;
DateSpinHandler
 *_spinHandler;
DateControl ( const DateControl&);
DateControl& operator= ( const DateControl&);
};

#endif // _DATECTRL_
