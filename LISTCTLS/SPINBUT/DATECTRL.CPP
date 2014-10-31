//************************************************************
// List Controls - Spin Button Date Control                  
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <istring.hpp>
#include <ispinbt.hpp>
#include <istattxt.hpp>
#include <ispinhdr.hpp>
#include "datectrl.hpp"

class DateSpinHandler : public ISpinHandler
{
public:
  DateSpinHandler ( ISpinButton& month,
                ISpinButton& day,
                ISpinButton& year )
       : _month(&month), _day(&day), _year(&year) {}

ISpinButton
 &month  (  )   { return *_month;}
ISpinButton
 &day    (  )   { return *_day;}
ISpinButton
 &year    (  )  { return *_year;}

protected:
virtual Boolean
  arrowUp              ( IControlEvent& event ),
  arrowDown            ( IControlEvent& event ),
  dayChanged           ( Boolean        forward),
  monthChanged         ( Boolean        forward);

DateSpinHandler
 &updateMonth          ( Boolean forward);

unsigned long
  daysInMonth          ( ) const;
 
private:
ISpinButton
 *_month,
 *_day,
 *_year;
};

ISpinButton& DateControl::month(  )  
{ return *_month;}

ISpinButton& DateControl::day(  )
{ return *_day;}

ISpinButton& DateControl::year(  )  
{ return *_year;}


DateControl::DateControl ( unsigned long id,
                           IWindow*      parent,
                           IWindow*      owner,
                           const IDate& aDate,
                           const IRange& aYearRange)
      : IMultiCellCanvas(id, parent, owner),
        _month     ( new ISpinButton(id + 4, this, this,
                       IRectangle(),
                       ISpinButton::servant |
                       ISpinButton::rightAlign |
                       ISpinButton::allCharacters |
                       IWindow::visible)),
        _day       ( new ISpinButton(id + 5, this, this,
                       IRectangle(),
                       ISpinButton::servant |
                       ISpinButton::rightAlign |
                       ISpinButton::numericOnly |
                       IWindow::visible)),
        _year      ( new ISpinButton(id + 6, this, this,
                       IRectangle(),
                       ISpinButton::master |
                       ISpinButton::rightAlign |
                       ISpinButton::numericOnly |
                       IWindow::visible)),
        _spinHandler(new DateSpinHandler(*_month, *_day, *_year))
{


(*this)
  .addToCell( _month,      2, 2)
  .addToCell( _day,        4, 2)
  .addToCell( _year,       6, 2)
  .setColumnWidth(1, 1, true)
  .setColumnWidth(3, 2, false)
  .setColumnWidth(5, 2, false)
  .setColumnWidth(7, 1, true)
  .setRowHeight  (1, 1, true)
  .setRowHeight  (3, 1, true);

year()
  .setRange(aYearRange)
  .setLimit(4)
  .spinTo(aDate.year());



// Load the Month spin button
ISpinButton::Cursor cursor(month());
for (int i=1;
     i < 13;
     i++, cursor.setToNext())
{
   month().addAsLast(IDate::monthName((IDate::Month)i),cursor);
}
month()
  .refreshText()
  .setMaster(year())
  .setText(aDate.monthName())
  .setLimit(12);

day()
  .setMaster(year())
  .setRange(IRange(1,32))
  .setLimit(2)
  .spinTo(aDate.dayOfMonth());

// Start the spin handler on the canvas
(*_spinHandler)
  .handleEventsFor(this);
}


IString DateControl::dateAsString ( ) const
{
  IString str= _month->text()+" "+IString(_day->value())+", "+
               IString(_year->value());
  return str;
}


Boolean DateSpinHandler::arrowUp( IControlEvent& event )
{
   ISpinButton* spin = (ISpinButton*)(event.controlWindow());
   if (spin)
   {
      if  (spin->handle()==day().handle())
         return dayChanged(true);
      else if  (spin->handle()==month().handle())
         return monthChanged(true);
   }
   return false;
}

Boolean DateSpinHandler::arrowDown( IControlEvent& event )
{
   ISpinButton* spin = (ISpinButton*)(event.controlWindow());
   if (spin)
   {
      if  (spin->handle()==day().handle())
         return dayChanged(false);
      else if  (spin->handle()==month().handle())
         return monthChanged(false);
   }
  return false;
}

// Handle a Month change - update the year if necessary
Boolean DateSpinHandler::monthChanged( Boolean forward)
{
  IString contents = month().text();
  if (forward  &&
      contents == IDate::monthName(IDate::January))
  {
     year().setValue(year().value() + 1);
  }
  else if (!forward)
  {
     if(day().value() > daysInMonth())
       day().setValue(daysInMonth());
     if(contents == IDate::monthName(IDate::December))
       year().setValue(year().value() - 1);
  }
  return true;

}

// Handle a day change - update the month if necessary
Boolean DateSpinHandler::dayChanged( Boolean forward)
{
  unsigned long contents = day().value();
  if ( forward  && contents > daysInMonth())
  {
     updateMonth(true);
     day().setValue(1);
     return true;
  }
  else if ( !forward && 
            contents == day().range().upperBound())
  {
    updateMonth(false);
    day().setValue(daysInMonth());
    return true;
  }
  return false;
}

// Roll the spin buttons month forward one month or
// backward one month
DateSpinHandler& DateSpinHandler::updateMonth ( Boolean forward)
{
  unsigned newMonth;
  for (unsigned i=1; i<13; i++)
  {
    if (month().text() == IDate::monthName((IDate::Month)i))
    {
      if(forward)
         newMonth = (i<12)? i+1 : 1;
      else
         newMonth = (i>1)? i-1 : 12;
      month().setText(IDate::monthName(IDate::Month(newMonth)));
      if(forward && newMonth == 1)
        year().setValue(year().value() + 1);
      if(!forward && newMonth == 12)
        year().setValue(year().value() - 1);
 
      break;
    }
  }
  return *this;
}

// Compute the days in the Spin Buttons month
unsigned long DateSpinHandler::daysInMonth ( ) const
{
  for (int i=1; i<13; i++)
  {
    if (((DateSpinHandler*)this)->month().text() ==
                   IDate::monthName((IDate::Month)i))
    {
       return IDate::daysInMonth((IDate::Month)i,
                   ((DateSpinHandler*)this)->year().value());
    }
  }
  return 0;
}
