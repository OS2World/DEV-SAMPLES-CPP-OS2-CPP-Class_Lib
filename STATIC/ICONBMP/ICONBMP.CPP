//************************************************************
// Text Controls - Canvas - Icon and Bitmap Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <ibmpctl.hpp>
#include <iframe.hpp>
#include <iiconctl.hpp>
#include <imcelcv.hpp>
#include <istattxt.hpp>

#include "iconbmp.h"

void main ( )
{
  IFrameWindow frame( "Icon and Bitmap Example" );

  // Put the icons and bitmaps on an expandable canvas.
  IMultiCellCanvas client( 0x8008, &frame, &frame );
  frame.setClient( &client );

  // Create background bitmap.
  IBitmapControl bmp1( 1, &client, &client, ID_CPPBITMAP );

  // Text labels.
  IStaticText
    bmpHeading   ( 0, &client, &client ),
    iconHeading  ( 0, &client, &client );
  bmpHeading
   .setText( "Bitmap - Sized By Canvas" )
   .setAlignment( IStaticText::centerCenter )
   .disableFillBackground();
  iconHeading
   .setText( "Icon - Actual Size" )
   .setAlignment( IStaticText::centerCenter )
   .disableFillBackground();

  // Create an icon.
  IIconControl icon1( 1, &client, &client,
                      ID_CPPICON, IRectangle(),
                      IIconControl::classDefaultStyle
                        | IIconControl::sizeToIcon );

  // Assign the child windows to cells.
  client
   .addToCell( &bmp1,        1, 1, 5, 7 )
   .addToCell( &bmpHeading,  1, 2, 5 )
   .addToCell( &iconHeading, 2, 5, 3 )
   .addToCell( &icon1,       3, 4 );

  // Assign expandable columns and rows.
  client
   .setColumnWidth( 2, 1, true )
   .setColumnWidth( 4, 1, true )
   .setColumnWidth( 5, 3, true )
   .setRowHeight( 3, 4, true )
   .setRowHeight( 6, 1, true );

  // Show the window now.
  frame.setFocus()
       .show();
  IApplication::current().run();
}
