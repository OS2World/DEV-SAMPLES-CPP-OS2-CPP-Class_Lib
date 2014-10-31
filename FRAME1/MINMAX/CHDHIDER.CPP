//************************************************************
// Frame Window Basics - Minimize/Maximize Handler Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************

#define INCL_WINWINDOWMGR    // WinShowWindow
#include <os2.h>
#include <iwindow.hpp>
#include "minmaxh.hpp"
#include "chdhider.hpp"

void ChildHider::showChildren ( IWindow *parent,
                                Boolean show )
{
  IWindow::ChildCursor
    cursor( *parent );
  for ( cursor.setToFirst();
        cursor.isValid();
        cursor.setToNext() )
  {
    IWindowHandle
      child = parent->childAt( cursor );
  
    // Show or hide the child
    // Note: We use WinShowWindow here to include
    //       non-IWindow windows   
    WinShowWindow( child, show );
  }
}

Boolean ChildHider::minimized ( IEvent &event )
{
  showChildren( event.window(), false );
  return false;
}

Boolean ChildHider::maximized ( IEvent &event )
{
  showChildren( event.window(), true );
  return false;
}

Boolean ChildHider::restored ( IEvent &event )
{
  showChildren( event.window(), true );
  return false;
}

