#ifndef _XCANVAS_
#define _XCANVAS_
//************************************************************
// Canvas - Complex Canvas Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************

#include <ibmpctl.hpp>
#include <icheckbx.hpp>
#include <ientryfd.hpp>
#include <iframe.hpp>
#include <igraphbt.hpp>
#include <ilistbox.hpp>
#include <imcelcv.hpp>
#include <isetcv.hpp>
#include <isizehdr.hpp>
#include <isplitcv.hpp>
#include <istattxt.hpp>
#include <ivport.hpp>

#include "pushbtns.hpp"

//======================= ColorButtons ========================
class ColorButtons : public ISetCanvas {
public:
  ColorButtons    ( unsigned long id,
                    IWindow* parentAndOwner );
private:      // Problem with buttons pushed to bottom.  $HT!
IGraphicPushButton
  red,
  green,
  blue,
  cyan,
  pink;
class ResizeHandler : public IResizeHandler {
protected:
  Boolean windowResize ( IResizeEvent& event )
  {
    event.window()->setLayoutDistorted( IWindow::layoutChanged, 0 );
    return false;
  }
};
ResizeHandler
  sizHdr;
};

//=========== SizeHandlerForViewPortWithMultiCell =============
class SizeHandlerForViewPortWithMultiCell : public IResizeHandler {
public:
virtual SizeHandlerForViewPortWithMultiCell
 &handleEventsFor       ( IViewPort* viewport ),
 &stopHandlingEventsFor ( IViewPort* viewport );

protected:
virtual Boolean
  windowResize          ( IResizeEvent& event );

private:
virtual IHandler
 &handleEventsFor       ( IWindow* window  ),
 &stopHandlingEventsFor ( IWindow* window  );
};

//==================== ComplexCanvasWindow =====================
class ComplexCanvasWindow : public IVBase {
public:
  ComplexCanvasWindow ( );
private:
IFrameWindow
  frame;
IMultiCellCanvas
  clientCanvas;
IStaticText
  headingText,
  topSeparator;
IMultiCellCanvas
  level1;
ISplitCanvas
  horizSplit,
  vertSplit;
IBitmapControl
  sizedBmp1,
  sizedBmp2;
IViewPort
  bmpScroller;
IBitmapControl
  actualSizeBmp;
IStaticText
  centerSeparator;
IViewPort
  dlgScroller;
IMultiCellCanvas
  level2;
IStaticText
  prompt;
IEntryField
  entry;
ICheckBox
  choice1,
  choice2;
IStaticText
  listHeading;
IListBox
  list;
IStaticText
  rightSeparator;
ColorButtons
  colorButtons;
MyStandardPushButtons
  pushButtons;
SizeHandlerForViewPortWithMultiCell
  viewPortSizeHdr;
};  // ComplexClient

#endif  // _XCANVAS_
