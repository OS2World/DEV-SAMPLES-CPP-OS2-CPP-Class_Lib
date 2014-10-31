//************************************************************
// Canvas - IViewPort that Scrolls a Bitmap.
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iapp.hpp>
#include <iframe.hpp>
#include <iscroll.hpp>
#include "vportbmp.hpp"

void main ( )
{
  // Create the frame window and its client view port.
  IFrameWindow frame( IFrameWindow::classDefaultStyle
                        | IFrameWindow::menuBar );
  IViewPort vport( 0x8008, &frame, &frame, IRectangle(),
                   IViewPort::classDefaultStyle
                     & ~IViewPort::asNeededHorizontalScrollBar
                     & ~IViewPort::asNeededVerticalScrollBar
                     | IViewPort::alwaysHorizontalScrollBar
                     | IViewPort::alwaysVerticalScrollBar
#if IC_MAJOR_VERSION >= 201
                     | IViewPort::noViewWindowFill );
#else
                     );
#endif
  unsigned long scrollIncrement =
           vport.verticalScrollBar()->minScrollIncrement() * 2;
  (*(vport.verticalScrollBar()))
    .setMinScrollIncrement( scrollIncrement )
    .sizeTo( ISize( IScrollBar::systemScrollBarWidth(true)
                                                 * 3 / 2, 0 ));
  (*(vport.horizontalScrollBar()))
    .setMinScrollIncrement( scrollIncrement )
    .sizeTo( ISize( 0,
                    IScrollBar::systemScrollBarWidth(false)
                                                    * 3 / 2 ));

#if IC_MAJOR_VERSION >= 201
  IBitmapControl bmp( 1, &vport, &vport, ID_DEFAULTBMP,
#else
  IBitmapControl bmp( 1, &vport, &vport,
                      IResourceId(ID_DEFAULTBMP),
#endif
                      IWindow::desktopWindow()->size() / 2 );

  NewBitmapCmdHandler cmdHdr1( &bmp );
  cmdHdr1.handleEventsFor( &vport );
  SizeBitmapCmdHandler cmdHdr2( &bmp, &vport );
  cmdHdr2.handleEventsFor( &vport );
  ScrollViewCmdHandler cmdHdr3( &vport );
  cmdHdr3.handleEventsFor( &vport );

  // Show it all now.
  frame.setFocus().show();
  IApplication::current().run();
}  // main()
