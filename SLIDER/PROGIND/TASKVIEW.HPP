#ifndef _TASKVIEW_
#define _TASKVIEW_
//************************************************************
// Slider - Progress Indicator Example                 
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <islidhdr.hpp>
#include <islider.hpp>
#include <istattxt.hpp>
#include <isplitcv.hpp>
#include <ihandle.hpp>

//  Handle custom drawing of progress indicator.
class DrawHandler : public ISliderDrawHandler
{
public:
virtual Boolean
  drawRibbonStrip ( IDrawItemEvent& event ),
  drawShaft       ( IDrawItemEvent& event );
};     

//  Class to simulate the progression of a task
class TimerHandler : public IHandler 
{
public:
virtual IHandler
 &handleEventsFor      ( IWindow *window ),
 &stopHandlingEventsFor( IWindow *window );

protected:
virtual Boolean
  dispatchHandlerEvent(IEvent& evt);
};     

//  The main application class
class TaskStatusView : public IFrameWindow
{
public:
 TaskStatusView ( const char* viewName);

IProgressIndicator
 &indicator  ( ) { return taskIndicator; }

private:
ISplitCanvas
  canvas;
TimerHandler
  timeHandler;
IStaticText
  indicatorTitle;
IProgressIndicator
  taskIndicator;
DrawHandler
  drawHandler;

TaskStatusView (const TaskStatusView& );
TaskStatusView& operator= (const TaskStatusView& );
};     

#endif // _TASKVIEW_
