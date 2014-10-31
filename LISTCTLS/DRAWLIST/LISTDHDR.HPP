#ifndef _LISTDHDR_
#define _LISTDHDR_
//************************************************************
// List Controls - List Box Custom Drawing           
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <ihandle.hpp>
#include <ilbdihdr.hpp>
#include <istring.hpp>

// The handler to draw the item.  The handler is
// preloaded with the amount to indent each
// item, and containes the bitmaps necessary
// to indicate whether an item is expanded or
// collapsed.  The handler processes all requests
// for drawing by routing them to the private
// function drawItem with an indication of whether
// selection needs to be drawn.
class DrawHandler : public IListBoxDrawItemHandler
{
public:
  DrawHandler (unsigned long indentBits=18)
     :   _indent   ( indentBits),
         _collapseIcon(ISystemBitmapHandle::collapsedTree),
         _expandIcon(ISystemBitmapHandle::expandedTree) {}

protected:
virtual Boolean
  setHeight(short& height)
  { height = 30; return true; }

virtual Boolean
  highlight(IListBoxDrawItemEvent& event),
  unhighlight(IListBoxDrawItemEvent& event),
  draw(IListBoxDrawItemEvent& event, DrawFlag& flag);

private:
unsigned long
  _indent;
ISystemBitmapHandle
  _expandIcon,
  _collapseIcon;
Boolean
  drawItem (IListBoxDrawItemEvent& event, Boolean selected);
};

#endif // _LISTDHDR_
