#ifndef _DIALOG_
#define _DIALOG_
//************************************************************
// Advanced Frame - Dialog Window Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <ireslib.hpp>

class DialogHandler;

class DialogWindow : public IFrameWindow {
public:
// Use this to construct a dialog using 
// your own dialog procedure:
  DialogWindow( const IResourceId &resId,
                IWindow           *owner,
                IWinProc          *dlgProc = 0,
                void              *pCreateParms = 0 );

// Use this to construct a dialog using 
// your own dialog handler:
  DialogWindow( const IResourceId &resId,
                IWindow           *owner,
                DialogHandler     &dlgHandler,
                void              *pCreateParms = 0 );
protected:
void
  loadDialog ( const IResourceId &resId,
               IWindow           *owner,
               IWinProc          *dlgProc,
               void              *pCreateParms );
private:
DialogWindow (const DialogWindow&);
DialogWindow& operator= (const DialogWindow&);
}; // class DialogWindow

#endif // _DIALOG_
