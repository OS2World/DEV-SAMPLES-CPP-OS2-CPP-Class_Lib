//************************************************************
// Canvas - ISplitCanvas with "problem" Child Windows 
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <icolor.hpp>
#include <iframe.hpp>
#include <iiconctl.hpp>
#include <imcelcv.hpp>
#include <imle.hpp>
#include <isplitcv.hpp>
#include <istring.hpp>

#define ADD_MULTICELLCANVAS  1   // Comment this out to experiment.

#ifndef ADD_MULTICELLCANVAS
  #define child2  client
  #define child3  client
  #define child4  client
#endif

void main ( )
{
  IFrameWindow frame( "Split canvas with \"problem\" children" );
  ISplitCanvas client( 0x8008, &frame, &frame );
  client.setColor( ISplitCanvas::splitBarMiddle,
                   IGUIColor( IGUIColor::activeFrameBorder ));
  frame.setClient( &client );

  // Create the first child of the split canvas.
  IMultiLineEdit mle( 1, &client, &client );
  mle.setText( "The frames and icon are \"problem\" "
                 + IString( "child windows" ));

  // Create the second child of the split canvas.
#ifdef ADD_MULTICELLCANVAS
  IMultiCellCanvas child2( 2, &client, &client );
#endif
  IFrameWindow frame1( 1, &child2, &child2, IRectangle(),
                       IFrameWindow::dialogBorder
                         | IWindow::visible );
  IStaticText st1( 0x8008, &frame1, &frame1 );
  st1.setText( "Child frame 1" )
     .setAlignment( IStaticText::centerCenter );
  frame1.setClient( &st1 );
#ifdef ADD_MULTICELLCANVAS
  frame1.setMinimumSize( ISize( 1, 1 ));
  child2.addToCell( &frame1, 1, 1 )
        .setRowHeight( 1, 0, true )
        .setColumnWidth( 1, 0, true );
#endif

  // Create the third child of the split canvas.
#ifdef ADD_MULTICELLCANVAS
  IMultiCellCanvas child3( 3, &client, &client );
#endif
  IFrameWindow frame2( 1, &child3, &child3, IRectangle(),
                       IFrameWindow::dialogBorder
                         | IWindow::visible );
  IStaticText st2( 0x8008, &frame2, &frame2 );
  st2.setText( "Child frame 2" )
     .setAlignment( IStaticText::centerCenter );
  frame2.setClient( &st2 );
#ifdef ADD_MULTICELLCANVAS
  frame2.setMinimumSize( ISize( 1, 1 ));
  child3.addToCell( &frame2, 1, 1 )
        .setRowHeight( 1, 0, true )
        .setColumnWidth( 1, 0, true );
#endif

  // Create the fourth child of the split canvas.
#ifdef ADD_MULTICELLCANVAS
  IMultiCellCanvas child4( 4, &client, &client );
#endif
  IIconControl icon( 1, &child4, &child4,
                     ISystemPointerHandle::question );
#ifdef ADD_MULTICELLCANVAS
  icon.setMinimumSize( ISize( 1, 1 ));
  child4.addToCell( &icon, 1, 1 )
        .setRowHeight( 1, 0, true )
        .setColumnWidth( 1, 0, true )
        .setColor( IColor::pink );
#endif

  // Size and show the window now.
  frame.setFocus()
       .show();
  IApplication::current().run();
}
