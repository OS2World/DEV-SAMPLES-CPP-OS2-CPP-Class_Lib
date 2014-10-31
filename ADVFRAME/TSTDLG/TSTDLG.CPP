//************************************************************
// Advanced Frame - Dialog Window Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#define INCL_WIN
#include <os2.h>

#include <istattxt.hpp>
#include <ithread.hpp>

#include "dialog.hpp"
#include "dlghndlr.hpp"

class MyDialogHandler : public DialogHandler {
public:
virtual Boolean
  initialize( DialogInitEvent &initEvent )
    {
    IStaticText
      text( WinWindowFromID( initEvent.handle(), 1 ) );
    text.setText( (char*)( initEvent.createParameters() ) );
    return false;
    }
};

static void * _System myDlgProc( unsigned long  hwnd,
                                 unsigned long  eventId,
                                 void          *parm1,
                                 void          *parm2 )
  {
  if ( eventId == WM_INITDLG )
    {
    IStaticText
      text( WinWindowFromID( hwnd, 1 ) );
    text.setText( (char*)parm2 );
    }
  return WinDefDlgProc( hwnd, eventId, parm1, parm2 );
  }

void main()
  {
  MyDialogHandler
    myHandler;
  DialogWindow
   dlg1( IC_DEFAULT_FRAME_ID,
         IWindow::desktopWindow(),
         myHandler,
         "myHandler" );
  DialogWindow
    dlg2( IC_DEFAULT_FRAME_ID,
          IWindow::desktopWindow(),
          myDlgProc,
          "myDlgProc" );
  dlg1.show();
  dlg2.show().setFocus();
  IThread::current().processMsgs();
  }

