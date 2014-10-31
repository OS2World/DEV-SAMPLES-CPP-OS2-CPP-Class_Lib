//************************************************************
// Button Controls  - Push Button Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <ipushbut.hpp>
#include <igraphbt.hpp>
#include <imcelcv.hpp>
#include <isetcv.hpp>
#include <iapp.hpp>
#include "pushbut.h"

#define INCL_WINFRAMEMGR  // For SC_CLOSE
#include <os2.h>  

void main()
{
IFrameWindow
  frame ("Push Button Example");
IMultiCellCanvas 
  client(0x8008, &frame, &frame);

// Push buttons on a set canvas
ISetCanvas 
  buttons(ID_BUTTONS, &client, &client);
IPushButton     
  ok(ID_OK, &buttons, &buttons),
  cancel(SC_CLOSE, &buttons, &buttons);
IGraphicPushButton
  bitmap(ID_BITMAPBUTTON, &buttons, &buttons, 
         ISystemBitmapHandle(ISystemBitmapHandle::program)),
  icon(ID_ICONBUTTON, &buttons, &buttons,
         ISystemPointerHandle(ISystemPointerHandle::folder));
IPushButton     
  help(ID_HELP, &buttons, &buttons, IRectangle(), 
       IPushButton::defaultStyle() | IPushButton::noPointerFocus);

bitmap.enableSizeToGraphic();

// Set default button to "OK" and make this
// button the first of the group
ok
  .enableDefault()
  .setText("OK")
  .enableTabStop()
  .enableGroup();

// Make the Cancel button a "Close" button
cancel
  .enableSystemCommand()
  .setText("Cancel");

// Make the help button a help button
help
  .enableHelp()
  .setText("Help");

// Add the controls to the set canvas
client
 .addToCell(&buttons, 2, 6, 3, 1);

// Allow for some growth in the canvas
client
 .setRowHeight   (1, 20, true);

// Put the canvas in the client and show the app
frame
  .setClient(&client)
  .setFocus()
  .show();
IApplication::current().run();

}
