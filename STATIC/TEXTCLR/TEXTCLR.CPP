//************************************************************
// Text Controls - Static Text Color Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <icolor.hpp>
#include <iframe.hpp>
#include <istattxt.hpp>

void main ( )
{
  IFrameWindow frame( "Static Text Color Example" );
  IStaticText client( 0x8008, &frame, &frame );
  frame.setClient( &client );
  client.setColor( IStaticText::fill, IColor::green );

  // Cyan block on the left.
  IStaticText left( 1, &frame, &frame );
  frame.addExtension( &left,
                      IFrameWindow::leftOfClient, 100 );
  left.setColor( IStaticText::background, IColor::cyan );

  // Text on top.
  IStaticText top( 2, &frame, &frame );
  frame.addExtension( &top,
                      IFrameWindow::aboveClient, 30 );
  top.setColor( IStaticText::foreground, IColor::blue )
     .setColor( IStaticText::background, IColor::white )
     .setColor( IStaticText::fill,       IColor::yellow )
     .setText( "This is blue on white text." )
     .setAlignment( IStaticText::centerCenter );

  // Red horizontal separators.
  ISize screen( IWindow::desktopWindow()->size() ),
        separatorSize( screen.width(), 4 );
  IStaticText thinSeparator( 3, &client, &client );
  thinSeparator.setColor( IStaticText::fill, IColor::red )
               .moveSizeTo( IRectangle( IPoint( 0, 10 ),
                                        separatorSize ));

  IStaticText medSeparator( 4, &client, &client );
  separatorSize.scaleBy( 1, 2 );  // Double the thickness.
  medSeparator.setColor( IStaticText::fill, IColor::red )
              .moveSizeTo( IRectangle( IPoint( 0, 50 ),
                                       separatorSize ));

  IStaticText thickSeparator( 5, &client, &client );
  separatorSize.scaleBy( 1, 3 );  // Now triple the thickness.
  thickSeparator.setColor( IStaticText::fill, IColor::red )
                .moveSizeTo( IRectangle( IPoint( 0, 110 ),
                                         separatorSize ));

  // Size and show the window now.
  frame.setFocus()
       .show();
  IApplication::current().run();
}
