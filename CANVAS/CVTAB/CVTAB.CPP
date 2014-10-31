/*************************************************************/
/* Nested canvas tabbing example.                            */
/*                                                           */
/* Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.       */
/* All Rights Reserved.                                      */
/*************************************************************/
#include <icanvas.hpp>
#include <icolor.hpp>
#include <ientryfd.hpp>
#include <iframe.hpp>
#include <ipushbut.hpp>

void main ( )
{
  IFrameWindow frame( "Canvas Tabbing" );
  ICanvas client( 0x8008, &frame, &frame );
  frame.setClient( &client );

  // Create child windows of the client canvas.
  IEntryField ef1( 1, &client, &client,
                   IRectangle( IPoint( 40, 200 ),
                               ISize( 225, 25 )));
  ef1.setText( "Has tab stop" )
     .enableTabStop()
     .enableGroup();

  ICanvas childCanvas( 0, &client, &client,
                       IRectangle( IPoint( 15, 100 ),
                                   ISize( 275, 90 )));
  childCanvas.setColor( ICanvas::background, IColor::cyan );

  // Create child windows of the child canvas.
  IEntryField ef2( 2, &childCanvas, &childCanvas,
                   IRectangle( IPoint( 25, 55 ),
                               ISize( 225, 25 )));
  ef2.setText( "Has tab stop" )
     .enableTabStop()
     .enableGroup();

  IEntryField ef3( 3, &childCanvas, &childCanvas,
                   IRectangle( IPoint( 25, 10 ),
                               ISize( 225, 25 )));
  ef3.setText( "Has tab stop" )
     .enableTabStop()
     .enableGroup();

  // Create another child window of the client canvas.
  IEntryField ef4( 4, &client, &client,
                   IRectangle( IPoint( 40, 65 ),
                               ISize( 225, 25 )));
  ef4.setText( "Has tab stop" )
     .enableTabStop()
     .enableGroup();

  // Create a push button.
  IPushButton ok( 0x8004, &client, &client,
                  IRectangle( IPoint( 40, 10 ),
                              ISize( 100, 30 )));
  ok.enableSystemCommand()   // For SC_CLOSE.
    .enableDefault()
    .setText( "OK" )
    .enableTabStop()
    .enableGroup();

  // Size and show the window now.
  frame.sizeTo( ISize( 310, 280 ))
       .setFocus()
       .show();
  IApplication::current().run();
}
