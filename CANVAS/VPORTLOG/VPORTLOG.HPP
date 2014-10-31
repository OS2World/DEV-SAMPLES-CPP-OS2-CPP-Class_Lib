#ifndef _VPORTLOG_
#define _VPORTLOG_
//************************************************************
// Canvas - IViewPort with Logically-sized View Window.
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************

#include <icanvas.hpp>
#include <ipainhdr.hpp>
#include <ivport.hpp>

#define PRE_CTM0006    1

// Align classes on four-byte boundaries.
#pragma pack(4)

//=================== LogicalSizeViewPort =====================

// Appear to scroll a large view window.
class LogicalSizeViewPort : public IViewPort {
public:
  LogicalSizeViewPort      ( unsigned long windowId,
                             IWindow* parentAndOwner,
                             unsigned long scale,
                             Boolean  specialScrolling );

#if PRE_CTM0005
virtual LogicalSizeViewPort
 &scrollViewVerticallyTo   ( unsigned long topOffset );
#endif

protected:
virtual LogicalSizeViewPort
 &layout                   ( ),
 &positionViewWindow       ( const IWindowHandle& viewWindow,
                             const IRectangle& viewRectangle );

private:
  LogicalSizeViewPort      ( const LogicalSizeViewPort& );
LogicalSizeViewPort
 &operator=                ( const LogicalSizeViewPort& );

  //===================== ViewPaintHdr ========================
  class ViewPaintHdr : public IPaintHandler {
  public:
    ViewPaintHdr ( LogicalSizeViewPort* viewport )
    {
      clViewPort = viewport;
    }
  protected:
  virtual Boolean
    paintWindow  ( IPaintEvent& event );
  private:
  LogicalSizeViewPort
   *clViewPort;
  };  // class LogicalSizeViewPort::ViewPaintHdr

#if PRE_CTM0006
  //==================== FocusKludgeHdr =======================
  class FocusKludgeHdr : public IHandler {
  protected:
  virtual Boolean
    dispatchHandlerEvent ( IEvent &event )
    {
      Boolean stopProcessing = false;
      if (event.eventId() == 0x000F  &&   // WM_SETFOCUS
          event.parameter2().number1())   //   gaining focus
      {
         stopProcessing = true;
      }
      return stopProcessing;
    }
  };  // class LogicalSizeViewPort::FocusKludgeHdr
#endif

ICanvas
  clViewWindow;
ViewPaintHdr
  clViewPaintHdr;
#if PRE_CTM0006
FocusKludgeHdr
  clFocusKludgeHdr;
#endif
unsigned long
  clVerticalLogicalRatio;
Boolean
  clCustomScrolling;
};  // class LogicalSizeViewPort

// Resume default compiler packing.
#pragma pack()

#endif // _VPORTLOG_
