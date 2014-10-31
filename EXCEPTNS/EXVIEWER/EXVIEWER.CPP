//************************************************************
// Error Reporting - Exception Viewer Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iapp.hpp>
#include <imsgbox.hpp>
#include "exviewer.hpp"
#include "exviewer.h"

ExceptionViewer::ExceptionViewer ( )
       : frameWindow(IFrameWindow::defaultStyle() | 
                     IFrameWindow::menuBar,
                     WND_MAIN),
         mleWindow(0x8008, &frameWindow, &frameWindow),
         menuHandler(*this)
{
   IException::setTraceFunction(*this);
   IWindow::setExceptionFunction(this);
   mle().disableDataUpdate();
   menuHandler.handleEventsFor(&frame());

   frame()
    .setClient(&mle())
    .setFocus()
    .show();
}

Boolean MenuHandler::command(ICommandEvent& event)
{
  switch (event.commandId()) {
     case THROW_EXCEPTION:
        IException exc("\nException thrown from menu selection.  \n",
                       0, IException::recoverable);
        ITHROW(exc);
  }                                 
  return false;                      
} 

void ExceptionViewer::write ( const char* buffer )
{
   mle().addAsLast((char*)buffer);
}

Boolean ExceptionViewer::handleException (IException& exc, IEvent& event)
{
   IMessageBox msgBox(&frame());
   msgBox.setTitle("Exception caught in dispatch routine");
   IMessageBox::Response response =
      msgBox.show(exc.text(),
                  IMessageBox::retryCancelButton |
                  IMessageBox::errorIcon         |
                  IMessageBox::moveable );
   if (response == IMessageBox::retry) {
      mle().addAsLast("Exception caught in dispatch.  User decided to retry.\n",
                       0, IMultiLineEdit::noTran );
      return true;
   }
   else {
      exc.setText("Exception caught and re-thrown in dispatch.  User decided to cancel.");
      IRETHROW(exc);
   }
}

void main()
{
   ExceptionViewer mainWindow;
   try {                                        
      IApplication::current().run();
   }
   catch ( IException& exc) {  
      IMessageBox msgBox(&mainWindow.frame());
      msgBox.setTitle("Exception caught in Main routine");
      msgBox.show(exc.text(),
                  IMessageBox::okButton    |
                  IMessageBox::errorIcon   |
                  IMessageBox::moveable );
   }
} 

