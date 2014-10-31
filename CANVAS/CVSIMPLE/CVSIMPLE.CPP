//************************************************************
// Canvas  - Simple ICanvas Example                           
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <icanvas.hpp>
#include <icolor.hpp>
#include <iframe.hpp>
#include <ipushbut.hpp>

#define MARGIN         30
#define BUTTON_PAD     15
#define BUTTON_HEIGHT  35
#define COLOR_SIZE     100
#define COLOR_OVERLAP  25
#define COLOR_START_Y  (MARGIN + BUTTON_HEIGHT + BUTTON_PAD)

void main ( )
{
  IFrameWindow frame( "Base Canvas Example" );
  ICanvas client( 0x8008, &frame, &frame );
  frame.setClient( &client );

  // Create three color squares.
  ICanvas red  ( 1, &client, &client,
                 IRectangle( IPoint( MARGIN,
                                     COLOR_START_Y + COLOR_SIZE
                                            - COLOR_OVERLAP ),
                             ISize( COLOR_SIZE, COLOR_SIZE )));
  red.setColor( ICanvas::background, IColor::red );

  ICanvas green( 2, &client, &client,
                 IRectangle( IPoint( MARGIN + COLOR_SIZE
                                            - COLOR_OVERLAP,
                                     COLOR_START_Y ),
                             ISize( COLOR_SIZE, COLOR_SIZE )));
  green.setColor( ICanvas::background, IColor::green );

  ICanvas blue ( 3, &client, &client,
                 IRectangle( IPoint( MARGIN + 2 * COLOR_SIZE
                                            - 2 * COLOR_OVERLAP,
                                     COLOR_START_Y + COLOR_SIZE
                                            - COLOR_OVERLAP ),
                             ISize( COLOR_SIZE, COLOR_SIZE )));
  blue.setColor( ICanvas::background, IColor::blue );

  // Create a push button.
  IPushButton ok( 0x8004, &client, &client,
                  IRectangle( IPoint( MARGIN, MARGIN ),
                              ISize( 3 * COLOR_SIZE
                                       - 2 * COLOR_OVERLAP,
                                     BUTTON_HEIGHT )));
  ok
   .enableSystemCommand()    // For SC_CLOSE.
   .enableDefault()
   .setText( "OK" )
   .enableTabStop()
   .enableGroup();

  // Size and show the window now.
  ISize clientSize( client.minimumSize()
                      + ISize( MARGIN, MARGIN ));
  frame
   .moveSizeToClient( IRectangle( IPoint( 100, 100 ),
                                  clientSize ))
   .setFocus()
   .show();
  IApplication::current().run();
}
