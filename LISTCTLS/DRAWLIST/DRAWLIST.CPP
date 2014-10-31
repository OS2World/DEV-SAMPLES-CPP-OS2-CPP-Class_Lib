//************************************************************
// List Controls - List Box Custom Drawing           
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <iapp.hpp>
#include <ilistbox.hpp>
#include <istring.hpp>
#include "listdhdr.hpp"
#include "listitem.hpp"

void main()
{
  IFrameWindow frame("List box Custom Drawing");
  DrawHandler listHandler;

  // Attach to the list box owner so that we get the
  // setSize events (WM_MEASUREITEM is sent during the
  // creation of the list box).
  listHandler.handleEventsFor(&frame);

  // Create a client area list box.
  IListBox list(0x8008, &frame, &frame, IRectangle(),
                IListBox::defaultStyle() | IWindow::saveBits);

  list
    .enableMultipleSelect()
    .enableDrawItem();

  // Dummy up the data for each class in the
  // heirarchy.
  ListItem items[] 
     =  {ListItem("IBase",            0,true, false),
        ListItem("IVBase",            1,true, false),
        ListItem("IWindow",           2,true, false),
        ListItem("IControl",          3,true, false),
        ListItem("ICanvas",           4,true, true),
        ListItem("IContainerControl", 4,false,false),
        ListItem("IListBox",          4,false, false),
        ListItem("INotebook",         4,false, false),
        ListItem("IScrollBar",        4,false, false),
        ListItem("ISpinButton",       4,false, false),
        ListItem("ITextControl",      4,true, false),
        ListItem("IButton",           5,true, false),
        ListItem("IPushButton",       6,true, false),
        ListItem("IGraphicPushButton",7,false, false),
        ListItem("ISettingButton",    6,true, false),
        ListItem("I3StateCheckBox",   7,false, false),
        ListItem("ICheckBox",         7,false, false),
        ListItem("IRadioButton",      7,false, false),
        ListItem("IEntryField",       5,true, false),
        ListItem("IComboBox",         6,false, false),
        ListItem("IGroupBox",         5,false, false),
        ListItem("IMultiLineEdit",    5,false, false),
        ListItem("IStaticText",       5,true, false),
        ListItem("IBitmapControl",    6,false, true),
        ListItem("IInfoArea",         6,false, false),
        ListItem("ITitle",            5,false, false),
        ListItem("IFrameWindow",      3,true, false),
        ListItem("IFileDialog",       4,false, false),
        ListItem("IFontDialog",       4,false, false),
        ListItem("IHelpWindow",       3,false, false),
        ListItem("IMenu",             3,true, false),
        ListItem("IMenuBar",          4,false, false),
        ListItem("IPopUpMenu",        4,false, false),
        ListItem("ISubmenu",          4,false, false),
        ListItem("ISystemMenu",       4,false, false),
        ListItem("IObjectWindow",     3,false, false)};

  // Add the items to the list box by creating an
  // IString from the item data address.
  for(int i=0; i< sizeof(items)/sizeof(ListItem); i++)
  {
    list.add(i, IString((unsigned long)&items[i]));
  }
 
  // Put the list box in the client and show the app.
  frame
    .setClient(&list)
    .setFocus()
    .show();

  IApplication::current().run();
}

