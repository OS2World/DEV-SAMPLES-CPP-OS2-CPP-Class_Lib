#ifndef _VPORTBMP_
#define _VPORTBMP_
//************************************************************
// Canvas - IViewPort that Scrolls a Bitmap.
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************

#include <ibmpctl.hpp>
#include <icmdhdr.hpp>
#include <iexcept.hpp>
#include <ivport.hpp>
#include "vportbmp.h"

// Align classes on four-byte boundaries.
#pragma pack(4)

//================== ScrollViewCmdHandler =====================

// Process command to scroll a view port.
class ScrollViewCmdHandler : public ICommandHandler {
public:
  ScrollViewCmdHandler ( IViewPort* viewPort )
    : clViewPort( viewPort )
  {
     IASSERTPARM( viewPort != 0);
  }
protected:
virtual Boolean
  command              ( ICommandEvent& event )
  {
     Boolean dontPassOn = false;
     switch ( event.commandId() )
     {
        case ID_SCROLL_TO_TOP:
        {
           clViewPort->scrollViewVerticallyTo(0);
           dontPassOn = true;
           break;
        }
        case ID_SCROLL_TO_VERT_MIDDLE:
        {
           IRectangle
             viewWindow( IPoint(),
                         clViewPort->viewWindowSize() ),
             visibleView( clViewPort
                            ->viewWindowDrawRectangle() );
           visibleView.centerAt( viewWindow.center() );
           clViewPort
             ->scrollViewVerticallyTo( visibleView.bottom() );
           dontPassOn = true;
           break;
        }
        case ID_SCROLL_TO_BOTTOM:
        {
           unsigned long
             viewHeight = clViewPort->viewWindowSize().height(),
             visible = clViewPort->viewWindowDrawRectangle()
                                  .height();
           clViewPort
             ->scrollViewVerticallyTo( viewHeight - visible );
           dontPassOn = true;
           break;
        }
        case ID_SCROLL_TO_LEFT:
        {
           clViewPort->scrollViewHorizontallyTo( 0 );
           dontPassOn = true;
           break;
        }
        case ID_SCROLL_TO_MIDDLE:
        {
           IRectangle
             viewWindow( IPoint(),
                         clViewPort->viewWindowSize() ),
             visibleView( clViewPort
                            ->viewWindowDrawRectangle() );
           visibleView.centerAt( viewWindow.center() );
           clViewPort
             ->scrollViewHorizontallyTo( visibleView.left() );
           dontPassOn = true;
           break;
        }
        case ID_SCROLL_TO_RIGHT:
        {
           unsigned long
             viewWidth = clViewPort->viewWindowSize().width(),
             visible = clViewPort->viewWindowDrawRectangle()
                                 .width();
           clViewPort
             ->scrollViewHorizontallyTo( viewWidth - visible );
           dontPassOn = true;
           break;
        }
        default:
           break;
     }
     return dontPassOn;
  }
private:
IViewPort
 *clViewPort;
};  // class ScrollViewCmdHandler

//================== SizeBitmapCmdHandler =====================

// Process command to resize a bit-map control.
class SizeBitmapCmdHandler : public ICommandHandler {
public:
  SizeBitmapCmdHandler ( IBitmapControl* bitmap,
                         IViewPort*      viewPort = 0 )
    : clBitmap( bitmap ),
      clViewPort( viewPort )
  {
     IASSERTPARM( bitmap != 0);
  }
protected:
virtual Boolean
  command              ( ICommandEvent& event )
  {
     Boolean dontPassOn = false;
     unsigned long mult = 1,
                   div = 1;
     switch ( event.commandId() )
     {
        case ID_DOUBLE_SIZE:
          mult = 2;
          break;
        case ID_HALVE_SIZE:
          div = 2;
          break;
        default:
          break;
     }
     if ( mult != 1  ||  div != 1)
     {
        clBitmap->sizeTo( clBitmap->size() * mult / div );
        if ( clViewPort )
        {
           (*clViewPort)
             .setLayoutDistorted( IWindow::layoutChanged, 0 )
             .refresh();
        }
        dontPassOn = false;
     }
     return dontPassOn;
  }
private:
IBitmapControl
 *clBitmap;
IViewPort
 *clViewPort;
};  // SizeBitmapCmdHandler

//=================== NewBitmapCmdHandler =====================

// Process command to show a new bit map.
class NewBitmapCmdHandler : public ICommandHandler {
public:
  NewBitmapCmdHandler ( IBitmapControl* bitmap )
    : clBitmap( bitmap )
  {
     IASSERTPARM( bitmap != 0);
  }
protected:
virtual Boolean
  command             ( ICommandEvent& event )
  {
     Boolean dontPassOn = false;
     switch ( event.commandId() )
     {
        case ID_FLAMINGO:
        case ID_BUTTERFLIES:
        case ID_SHELLS:
        case ID_ORCHIDS:
        case ID_OS2LOGO:
#if IC_MAJOR_VERSION >= 201
          clBitmap->setBitmap( event.commandId() );
#else
          clBitmap->setBitmap( IResourceId( event.commandId() ));
#endif
          dontPassOn = true;
          break;
        default:
          break;
     }
     return dontPassOn;
  }
private:
IBitmapControl
 *clBitmap;
};  // NewBitmapCmdHandler

// Resume default compiler packing.
#pragma pack()

#endif // _VPORTBMP_
