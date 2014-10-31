//************************************************************
// Advanced Frame - Dialog Window Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#define INCL_WIN
#include <os2.h>

#include "dialog.hpp"
#include "dlghndlr.hpp"

#include <ithread.hpp>

DialogWindow :: DialogWindow( const IResourceId &resId,
                              IWindow           *owner,
                              IWinProc          *dlgProc,
                              void              *pCreateParms )
  : IFrameWindow( deferCreation )
  {
  this->loadDialog( resId, owner, dlgProc, pCreateParms );
  }

struct DialogParms {
  DialogHandler
   &dlgHandler;
  void
   *pCreateParms;
};

static void * _System dialogProc( unsigned long  hwnd,
                                  unsigned long  eventId,
                                  void          *parm1,
                                  void          *parm2 )
  {
  if ( eventId == WM_INITDLG )
    {
    DialogParms
     *p = (DialogParms*)parm2;
    DialogInitEvent
      initEvent( IEvent( hwnd,
                         eventId,
                         parm1,
                         p->pCreateParms ) );
    // Dispatch handler and check result:
    if ( p->dlgHandler.initialize( initEvent ) )
      // Don't pass along; result is in event.
      return initEvent.result();
    else
      // Pass to default dialog procedure.
      return WinDefDlgProc( hwnd,
                            eventId,
                            parm1,
                            p->pCreateParms );
    }
  else
    return WinDefDlgProc( hwnd, eventId, parm1, parm2 );
  }

DialogWindow :: DialogWindow( const IResourceId &resId,
                              IWindow           *owner,
                              DialogHandler     &dlgHandler,
                              void              *pCreateParms )
  : IFrameWindow( deferCreation )
  {
  DialogParms
    parms = { dlgHandler, pCreateParms };
  this->loadDialog( resId, owner, dialogProc, &parms );
  this->addHandler( &dlgHandler );
  }

void DialogWindow :: loadDialog ( const IResourceId &resId,
                                  IWindow  *owner,
                                  IWinProc *dlgProc,
                                  void     *pCreateParms )
  {
  IThread::current().initializePM();

  const IResourceLibrary
   &resLib = resId.resourceLibrary();
  IWindowHandle
    dlg = resLib.loadDialog( resId.id(),
                             0,
                             owner,
                             dlgProc,
                             pCreateParms );
  start( dlg );
  }

