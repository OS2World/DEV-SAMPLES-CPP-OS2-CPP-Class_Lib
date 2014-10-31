//************************************************************
// Advanced Frame - Frame Extension Drawing Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#define INCL_WINWINDOWMGR
#include <os2.h>
#include "myextns.hpp"

MyExtension::MyExtension( IWindow *control,
               IFrameWindow::Location loc,
               double size )
    : IFrameExtension( control, loc, size, IFrameWindow::none ),
      width( 5 ),
      color( 0 )
    {
    }

unsigned MyExtension:: separatorWidth ( ) const
  {
  return width;
  }
void MyExtension::drawSeparator ( const IPresSpaceHandle &hps ) const
  {
  IRectangle
    separator;
  if ( location() == IFrameWindow::aboveClient )
    // Separator goes beneath control:
    separator = control()->rect()
                  .moveBy( IPair( 0, -width ) );
  else
    // Separator goes above control:
    separator = control()->rect()
          .moveBy( IPair( 0, control()->size().height() ) );
  separator.sizeTo( separator.size().setHeight( width ) );
  WinFillRect( hps, PRECTL(&separator), color );
  }
MyExtension& MyExtension::setWidth ( unsigned width )
  {
  this->width = width;
  return *this;
  }

MyExtension& MyExtension::setColor ( long newColor )
{
  this->color = newColor;
  return *this;
}
