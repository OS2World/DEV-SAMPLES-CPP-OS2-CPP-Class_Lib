#ifndef _EXVIEWER_
#define _EXVIEWER_
//************************************************************
// Error Reporting - Exception Viewer Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <imle.hpp>    
#include <icmdhdr.hpp> 

// forward declaration
class ExceptionViewer;

class MenuHandler : public ICommandHandler
{
public:

 MenuHandler ( ExceptionViewer &excViewer )
                  : viewer(excViewer) {}

protected:
virtual Boolean
  command    ( ICommandEvent& event );

private:
ExceptionViewer
 &viewer;
MenuHandler ( const MenuHandler&);
MenuHandler& operator= ( const MenuHandler&);
};                    // MenuHandler

class ExceptionViewer : public IException::TraceFn,
                        public IWindow::ExceptionFn
{
public:

 ExceptionViewer  ( );

IFrameWindow
 &frame         ( )  { return frameWindow; }
IMultiLineEdit
 &mle           ( )  { return mleWindow; }

// callback functions from IException and IWindow
virtual void                                                                
  write ( const char* buffer );
virtual Boolean                                                              
  handleException (IException& exception, IEvent& event);

private:
IFrameWindow
  frameWindow;
IMultiLineEdit
  mleWindow;
MenuHandler
  menuHandler;
ExceptionViewer (const ExceptionViewer&);
ExceptionViewer& operator= (const ExceptionViewer&);
};                    // ExceptionViewer
                                                                             
#endif // _EXVIEWER_
