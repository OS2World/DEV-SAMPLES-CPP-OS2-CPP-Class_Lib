//************************************************************
// Menus - Using a Menu Cursor     
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <icnr.hpp>
#include <icnrobj.hpp>
#include <iapp.hpp>
#include <imenubar.hpp>
#include "cursor.h"

void main()
{
IFrameWindow
  frame ("Menu Cursor Example");

// Add the Menubar from a resource file
IMenuBar 
  menuBar(MAIN_MENU, &frame);

// Create a Container Status Area in the Client
IContainerControl
  statusArea(ID_STATUS, &frame, &frame);
statusArea
  .showTreeTextView()
  .setDeleteObjectsOnClose();

// Create menu cursors to display the menu bar contents
// in the client area
IMenu::Cursor level1Cursor(menuBar);
for (level1Cursor.setToFirst();
     level1Cursor.isValid();
     level1Cursor.setToNext())
{
  IContainerObject* level1Object;
  IMenuItem level1Item = 
             menuBar.elementAt(level1Cursor);

  if (level1Item.text().length()!=0)
    level1Object = new IContainerObject(level1Item.text());
  else if (level1Item.bitmap())
    level1Object = new IContainerObject("Bitmap");
  else if (level1Item.isSeparator())
    level1Object = new IContainerObject("Separator");
  else 
    level1Object = new IContainerObject("Unknown");
  statusArea.addObject(level1Object);

  if(level1Item.submenuHandle())
  {
    IMenu::Cursor level2Cursor(menuBar, level1Item.id());
    for (level2Cursor.setToFirst();
         level2Cursor.isValid();
         level2Cursor.setToNext())
    {
      IContainerObject* level2Object;
      IMenuItem level2Item = 
                     menuBar.elementAt(level2Cursor);
      if (level2Item.text().length()!=0)
        level2Object = new IContainerObject(level2Item.text());
      else if (level2Item.bitmap())
        level2Object = new IContainerObject("Bitmap");
      else if (level2Item.isSeparator())
        level2Object = new IContainerObject("Separator");
      else 
        level2Object = new IContainerObject("Unknown");
      statusArea.addObject(level2Object, level1Object);
    }
  }
}

// Set the focus and show the app
frame
  .setClient(&statusArea)
  .setFocus()
  .show();
IApplication::current().run();
}

