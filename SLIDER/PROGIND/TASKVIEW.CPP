//************************************************************
// Slider - Progress Indicator Example                 
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <ithread.hpp>   
#include <irect.hpp>
#include <ipoint.hpp>
#include <icolor.hpp>
#include <ireslib.hpp>
#include "taskview.hpp"
#include "taskview.h"

//  Include os2.h for WM_TIMER 
#define INCL_WINTIMER  
#include <os2.h>

//  Status View definition
TaskStatusView :: TaskStatusView ( const char* viewName )
       : IFrameWindow(viewName),
         canvas(ID_CANVAS, this, this,
                IRectangle(),
                ISplitCanvas::horizontal  |
                ISplitCanvas::noSplitBars |
                IWindow::visible),
         timeHandler(),
         indicatorTitle(ID_IND_TITLE, &canvas, &canvas),
         taskIndicator(ID_INDICATOR, &canvas, &canvas,
                       IRectangle(), 101),
         drawHandler()
{
   //  Add the custom draw handler to the progress indicator.
   drawHandler.handleEventsFor(&indicator());

   //  Set the colors of the progress indicator ticks and text,
   //  background, and border
   indicator()
     .setColor(IProgressIndicator::foreground,
               IColor(IColor::darkBlue))
     .setColor(IProgressIndicator::background,
               IColor(IColor::cyan))
     .setColor(IProgressIndicator::border,
               IColor(IColor::darkBlue));


   //  Set the size of the progress indicator
   //  shaft and enable owner draw
   indicator()
     .setShaftBreadth(50)
     .enableDrawItem();

   //  Set the length and text for the indicator's ticks
   indicator()
     .setTickLength(0,10)
     .setTickText(0, IString(0) + "%");
   for ( int i=10; i<101; i+=10) {
      indicator()
        .setTickLength(i,10)
        .setTickLength(i-5,5)
        .setTickText(i, IString(i) + "%");
   }

   //  Set the colors, text, and alignment for the
   //  static text control
   indicatorTitle
     .setColor(IStaticText::fill,
               IColor(IColor::cyan))
     .setColor(IStaticText::background,
               IColor(IColor::cyan))
     .setColor(IStaticText::foreground,
               IColor(IColor::darkBlue))
     .setText("Percentage of Task Completed")
     .setAlignment(IStaticText::bottomCenter);
   
   //  Put the canvas in the client area 
   //  and set the pane percentages
   setClient(&canvas);
   canvas
     .setSplitWindowPercentage(&indicatorTitle, 30)
     .setSplitWindowPercentage(&indicator(), 70);

   //  add the time handler to the progress indicator
   timeHandler.handleEventsFor(&indicator());
}

//  Function for owner draw of the indicator ribbon strip
Boolean DrawHandler::drawRibbonStrip(IDrawItemEvent& event)
{
   RECTL rectl=event.itemRect().asRECTL();

   //  Draw the shaft using information from the draw item event
   WinFillRect((HPS)event.itemPresSpaceHandle(),
               &rectl,
               CLR_BLUE);
   return true;
}

//  Handler custom drawing of the progress indicator shaft.
Boolean DrawHandler::drawShaft(IDrawItemEvent& event)
{
   RECTL rectl=event.itemRect().asRECTL();

   //  Draw the shaft using information from the draw item event.
   WinFillRect((HPS)event.itemPresSpaceHandle(),
               &rectl,
               CLR_YELLOW);
   return true;
}
     
//  Override handleEventsFor to start the timer to simulate
//  the completed percentage of a task when the handler
//  is registered
IHandler& TimerHandler :: handleEventsFor( IWindow *window )
{
   WinStartTimer((HAB)IThread::current().anchorBlock(),
                 (HWND)window->handle(),
                 1,            // Timer ID
                 3000UL);      // Set to tick every 3 seconds
  return IHandler::handleEventsFor(window);
}

//  Override stopHandlingEventsFor to stop the timer.
IHandler& TimerHandler::stopHandlingEventsFor(IWindow *window)
{
   WinStopTimer((HAB)IThread::current().anchorBlock(),
                (HWND)window->handle(),
                1);            //Timer ID
   return IHandler::stopHandlingEventsFor(window);
} 

//  Move the indicator arm when WM_TIMER messages are received.
Boolean TimerHandler::dispatchHandlerEvent(IEvent& event)
{
   unsigned long ulOffset;
   if ((event.eventId() == WM_TIMER) &&
       (event.parameter1() == 1))  {
     ulOffset = ((IProgressIndicator*)event.window())->
                  armTickOffset();
     if (ulOffset < 100)
        ((IProgressIndicator*)event.window())->
          moveArmToTick(ulOffset+=10);
   }
   return false; 
} 
