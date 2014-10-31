//************************************************************
// Canvas - IViewPort with Logically-sized View Window.
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#define INCL_WINWINDOWMGR   // WinFillRect
#include <os2.h>

#include <icolor.hpp>
#include <ifont.hpp>
#include <iframe.hpp>
#include <ipoint.hpp>
#include <iscroll.hpp>
#include <istring.hpp>
#include "vportlog.hpp"

#define NUMBER_COLORS  8
static IColor::Color colorEnums[ NUMBER_COLORS ] =
  { IColor::blue, IColor::darkGreen, IColor::red,
    IColor::darkCyan, IColor::pink, IColor::darkRed,
    IColor::brown, IColor::black };

//=================== LogicalSizeViewPort =====================

LogicalSizeViewPort :: LogicalSizeViewPort
                        ( unsigned long windowId,
                          IWindow* parentAndOwner,
                          unsigned long scale,
                          Boolean  specialScrolling )
  : IViewPort( windowId, parentAndOwner,
               parentAndOwner, IRectangle(),
               IViewPort::classDefaultStyle
                 | IViewPort::noViewWindowFill ),
    clViewWindow( windowId, this, this ),
    clViewPaintHdr( this ),
    clVerticalLogicalRatio( 1 ),
    clCustomScrolling( specialScrolling )
{
  // Physically size the view window to the size of the
  // screen, and leave it positioned at (0, 0).
  ISize desktopSize = IWindow::desktopWindow()->size();
  this->clViewWindow.sizeTo(desktopSize);

  // Logically size the view window using the scaling factor.
  ISize logicalSize( 0x4000 * scale, 0x8000 * scale );
  if (scale == 0)
  {                     // <32K logical sizes.
     logicalSize = ISize( 0x4000, 0x7FFF );
  }
  (*this).setViewWindowSize( logicalSize );

  this->clViewPaintHdr.handleEventsFor( &clViewWindow );
#if PRE_CTM0006
  this->clFocusKludgeHdr.handleEventsFor( &clViewWindow );
#endif

  if (clCustomScrolling)
  {                     // Modify scroll bars if necessary.
     IScrollBar* horz = this->horizontalScrollBar();
     horz->setMinScrollIncrement
             ( horz->minScrollIncrement() * 4 );
     IScrollBar* vert = this->verticalScrollBar();
     vert->setMinScrollIncrement
             ( vert->minScrollIncrement() * 4 );
  }
}  // LogicalSizeViewPort ctor

#if PRE_CTM0005
LogicalSizeViewPort&
  LogicalSizeViewPort :: scrollViewVerticallyTo
                           ( unsigned long topOffset )
{
  if (this->viewWindowSize().height() >
        this->viewWindowDrawRectangle().height())
  {      // It's ok to scroll (application may have called us).
     // Adjust scroll amount if too large.
     unsigned long new0basedOffset =
                      this->viewWindowSize().height();
     if (topOffset < new0basedOffset)
     {
        new0basedOffset = topOffset;
     }

     // Set new top left point.
     unsigned long topPos =
                   this->viewWindowSize().height() - topOffset;
     this->setTopLeftViewPoint( (*this).topLeftViewPoint()
                                       .setY(topPos) );

     // Move the scroll box.
//   this->verticalScrollBar()
//       ->moveScrollBoxTo(new0basedOffset + 1);
  }

  refresh();  // Force a repaint.

  return *this;
}  // LogicalSizeViewPort::scrollViewVerticallyTo
#endif

LogicalSizeViewPort& LogicalSizeViewPort :: layout ( )
{
  IViewPort::layout();

  if (clCustomScrolling)
  {                     // Modify scroll bars if necessary.
     IScrollBar* horz = this->horizontalScrollBar();
     horz->setPageScrollIncrement
             ( horz->pageScrollIncrement() / 2 );
     IScrollBar* vert = this->verticalScrollBar();
     vert->setPageScrollIncrement
             ( vert->pageScrollIncrement() / 2 );
  }

  return *this;
}  // LogicalSizeViewPort::layout

LogicalSizeViewPort& LogicalSizeViewPort :: positionViewWindow
                            ( const IWindowHandle& viewWindow,
                              const IRectangle& viewRectangle )
{
#if 0
  // Only honor horizontal changes to keep the view window
  // visible.
  IPoint viewPos = this->clViewWindow.position()
                       .setX(0 - this->topLeftViewPoint().x());
  this->clViewWindow.moveTo(viewPos);
#endif

  // Force repaint to allow painting updates.
  this->clViewWindow.refresh();

  return *this;
}  // LogicalSizeViewPort::positionViewWindow

//============ LogicalSizeViewPort::ViewPaintHdr ==============

Boolean LogicalSizeViewPort::ViewPaintHdr :: paintWindow
                                         ( IPaintEvent& event )
{
  ICanvas* canvas = (ICanvas*)event.window();

  // Compensate for effects of CS_PARENTCLIP.
  IRectangle rectWindow = canvas->rect().moveTo( IPoint() );
  IRectangle rectInvalid = event.rect() & rectWindow;

  if (rectInvalid.size() > ISize())
  {                     // Something needs painting.
     // Initialize drawing variables.
     unsigned long blockWidth  = 0x0100,  // 256
                   blockHeight = 0x0080;  // 128
     IRectangle drawRect =
                  clViewPort->viewWindowDrawRectangle();
     IColor fgColor( IColor::yellow );

     // Width-dependent painting: Paint colors and offsets.
     // Figure out where we are.
     long x = drawRect.left();
     unsigned long xIndex = x / blockWidth;

     while (x < drawRect.right())
     {                  // Paint visible background.
       // Paint a color block.
       IColor bgColor( colorEnums[ xIndex % NUMBER_COLORS ] );
       unsigned long x2 = (xIndex + 1) * blockWidth;
       Boolean rightEdge = true;
       if (x2 > drawRect.right())
       {                // For last visible block.
          x2 = drawRect.right() + 1;
          rightEdge = false;
       }
       x2--;
//     event.clearBackground(rectInvalid, bgColor);
       IRectangle paintRect( IPoint( x, rectInvalid.bottom() ),
                             IPoint( x2, rectInvalid.top() ));
       paintRect.moveBy( IPoint( 0 - drawRect.left(), 0 ));
       RECTL rcl = paintRect.asRECTL();
       WinFillRect( event.presSpaceHandle(),
                    &rcl, bgColor.index() );

       if (rightEdge)
       {                // Right edge is visible.
          // Draw thin divider at right edge of color block.
          IRectangle divider( IPoint( x2,
                                      rectInvalid.bottom() ),
                              IPoint( x2 + 1,
                                      rectInvalid.top() ));
          divider.moveBy( IPoint(0 - drawRect.left(), 0) );
          rcl = divider.asRECTL();
          WinFillRect( event.presSpaceHandle(),
                       &rcl, fgColor.index() );
       }

       // Write offset at left edge of color block.
       if (!(x % blockWidth))
       {                // Left edge of color block is showing.
          IString offset( xIndex * blockWidth );
          event.drawText( offset.d2x(),
                          IPoint( x - drawRect.left(), 0 ),
                          fgColor );
       }

       x = x2 + 1;
       xIndex++;
     }

     // Height-dependent painting: Draw offsets of logical rows.
     // Figure out where we are.
     unsigned long fontHeight =
                     IFont( event.window() ).maxCharHeight();
     long y = clViewPort->viewWindowSize().height() -
                                          drawRect.top();
     long viewBottom = y + drawRect.height();
     unsigned long yIndex = y / blockHeight;
          // Bottom of a row, relative to logical view window.

     while (y < viewBottom)
     {                  // Draw visible rows.
       unsigned long y2 = (yIndex + 1) * blockHeight;
       if (y2 - fontHeight < viewBottom)
       {                // This row number is visible.
          IString lineNumber( IString(y2).d2x() );
          event.drawText( lineNumber,
                          IPoint( 20, viewBottom - y2 ),
                          fgColor );
       }

       y = y2 + 1;
       yIndex++;
     }

  }  // End something needs painting.

  return true;          // All painting performed
}  // LogicalSizeViewPort::ViewPaintHdr::paintWindow()

//========================== Main =============================

void main( int argc, char *argv[] )
{
  long scale = 1;
  Boolean specialScrolling = false;

  // This .exe take two optional command line arguments.
  // The first is a "scale" value, which specifies the
  // multiples of 0x4000 for width and 0x8000 for height that
  // the view port should logically size its view window.  A
  // value of zero means to use (0x4000, 0x7FFF).
  // A second argument means that the default scroll amounts
  // should not be used.
  if (argc > 1)
  {                     // First argument is scale.
     scale = IString( argv[1] ).asInt();
     if (scale < 0)
     {                  // Valid values are 0 or greater.
        scale = 1;      // 1 is default.
     }
     if (argc > 2)
     {                  // Second command line argument.
        specialScrolling = true;
     }
  }

  // Create the frame window and its client view port.
  IFrameWindow frame
               ( "View port with logically-sized view window" );
  LogicalSizeViewPort vport( 0x8008, &frame,
                             scale, specialScrolling );

  // Show it all now.
  frame.setFocus().show();
  IApplication::current().run();
}  // main()
