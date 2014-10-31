//************************************************************
// List Controls - List Box Custom Drawing           
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <ilistbox.hpp>
#include <irect.hpp>
#include <ifont.hpp>
#include <istring.hpp>
#include "listdhdr.hpp"
#include "listitem.hpp"

// os2.h needing for drawing primitives
#define INCL_WINWINDOWMGR
#define INCL_WINSYS
extern "C" {
  #include <os2.h>
}

Boolean DrawHandler::highlight(IListBoxDrawItemEvent& event)
{ 
  // Draw Selection
  return drawItem(event, true); 
}

Boolean DrawHandler::unhighlight(IListBoxDrawItemEvent& event)
{ 
  //Draw without selection
  return drawItem(event, false); 
}

Boolean DrawHandler::draw(IListBoxDrawItemEvent& event, DrawFlag& flag)
{
  if(event.isSelected())
  {
    flag = drewSelected;
    return drawItem(event, true);
  }
    else
      return drawItem(event, false);
}

// Handle the drawing of the list box items.
Boolean DrawHandler::drawItem( IListBoxDrawItemEvent& event,
                               Boolean selected)
{
  IListBox* list = (IListBox*)event.controlWindow();
  IRectangle rect = event.itemRect();
  RECTL rectl = rect.asRECTL();

  // Fill the background. 
  WinFillRect(event.itemPresSpaceHandle(), &rectl,
              selected?CLR_BLACK:SYSCLR_ENTRYFIELD);

  // Convert the item data from the list box item text
  ListItem* data = 
     (ListItem*)(list->itemText(event.itemId()).asUnsigned());

  // Determine the indent for the class based on the
  // number of inherited classes.
  if (data->inheritedClasses() != 0)
  {
     ISize indentSize = ISize(
                data->inheritedClasses() * (_indent+1), 0);
     rect.moveBy(indentSize);
  }

  // Draw a bitmap based on the collapsed flag
  // if the class is not a leaf.
  if(data->children())
  {
    // Make the bitmap a square the size of an item
    IRectangle rectBitmap(rect.bottomLeft(),
                        ISize(rect.height(),
                              rect.height()));
    rectl = rectBitmap.asRECTL();
    WinDrawBitmap(event.itemPresSpaceHandle(),
                data->collapsed()? _collapseIcon:_expandIcon,
                0, 
                (PPOINTL)&rectl,
                selected?CLR_WHITE:CLR_BLACK,
                selected?CLR_BLACK:SYSCLR_ENTRYFIELD,
                DBM_STRETCH );
  }

  // Calculate the rectangle for the text based
  // on the current font of the listbox.
  IFont font(list);
  rect
    .moveBy(ISize(rect.height(),0))
    .sizeTo(ISize(font.textWidth(data->text())+3,
            rect.size().height()));
  rectl = rect.asRECTL();
                          
  // Draw the text.
  unsigned long style =  DT_VCENTER | DT_LEFT;
  WinDrawText(event.itemPresSpaceHandle(), 
              -1,
              data->text(),
              &rectl, 
              selected?CLR_WHITE:CLR_BLACK,
              selected?CLR_BLACK:SYSCLR_ENTRYFIELD,
              style);
  return true;
}
