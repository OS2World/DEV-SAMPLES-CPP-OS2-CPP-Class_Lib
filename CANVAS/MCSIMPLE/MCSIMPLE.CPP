//************************************************************
// Canvas Simple IMultiCellCanvas example.                    
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <icolor.hpp>
#include <iframe.hpp>
#include <imcelcv.hpp>
#include <ipushbut.hpp>

#define MARGIN         10
#define BUTTON_PAD     15
#define COLOR_OVERLAP  25

void main ( )
{
  IFrameWindow frame( "Multi-cell Canvas Example" );
  IMultiCellCanvas client( 0x8008, &frame, &frame );
  frame.setClient( &client );

  // Create three color squares.
  ICanvas
    red  ( 1, &client, &client ),
    green( 2, &client, &client ),
    blue ( 3, &client, &client );
  red.setColor  ( ICanvas::background, IColor::red );
  green.setColor( ICanvas::background, IColor::green );
  blue.setColor ( ICanvas::background, IColor::blue );

  // Create a push button.
  IPushButton ok( 0x8004, &client, &client );
  ok
   .enableSystemCommand()    // For SC_CLOSE.
   .enableDefault()
   .setText( "OK" )
   .enableTabStop()
   .enableGroup();

  // Position child windows in the canvas.
  ISize defaultCell = IMultiCellCanvas::defaultCell();
  client
  .addToCell( &red,   2, 2, 3, 2 )
  .addToCell( &green, 4, 3, 3, 2 )
  .addToCell( &blue,  6, 2, 3, 2 )
  .addToCell( &ok,    2, 6, 7 );
 client
  .setColumnWidth( 1, MARGIN )
  .setColumnWidth( 2, COLOR_OVERLAP )
  .setColumnWidth( 3, defaultCell.width(), true )
  .setColumnWidth( 4, COLOR_OVERLAP )
  .setColumnWidth( 5, defaultCell.width(), true )
  .setColumnWidth( 6, COLOR_OVERLAP )
  .setColumnWidth( 7, defaultCell.width(), true )
  .setColumnWidth( 8, COLOR_OVERLAP )
  .setColumnWidth( 9, MARGIN )
  .setRowHeight( 1, MARGIN )
  .setRowHeight( 2, defaultCell.height(), true )
  .setRowHeight( 3, COLOR_OVERLAP )
  .setRowHeight( 4, defaultCell.height(), true )
  .setRowHeight( 5, BUTTON_PAD )
  .setRowHeight( 7, MARGIN );

  // Size and show the window now.
  frame
   .moveSizeToClient( IRectangle( IPoint( 100, 100 ),
                                  client.minimumSize() ))
   .setFocus()
   .show();
  IApplication::current().run();
}
