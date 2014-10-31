#ifndef _MYEXTNS_
#define _MYEXTNS_
//************************************************************
// Advanced Frame - Frame Extension Drawing Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iframext.hpp>
#include <icolor.hpp>
#include <irect.hpp>

class MyExtension : public IFrameExtension {
public:
  MyExtension( IWindow *control,
               IFrameWindow::Location loc,
               double size );
virtual unsigned
  separatorWidth ( ) const;

virtual void
  drawSeparator ( const IPresSpaceHandle &hps ) const;

virtual MyExtension
 &setWidth ( unsigned width ),
 &setColor ( long newColor );

private:
unsigned
  width;
long
  color;
};

#endif // _MYEXTNS_
