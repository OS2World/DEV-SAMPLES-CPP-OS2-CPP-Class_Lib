//************************************************************
// Canvas - ISplitCanvas with Static Text Child Windows
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <ibmpctl.hpp>
#include <iframe.hpp>
#include <isplitcv.hpp>
#include <istattxt.hpp>

void main ( )
{
  IFrameWindow frame( "Split canvas example" );
  ISplitCanvas client( 0x8008, &frame, &frame );
  frame.setClient( &client );

  // Create five child windows.
  IStaticText st1( 1, &client, &client ),
              st2( 2, &client, &client );
  IBitmapControl bmp( 3, &client, &client,
                      ISystemBitmapHandle::systemMenu );
  IStaticText st4( 4, &client, &client ),
              st5( 5, &client, &client );
  st1.setText( "First" )
     .setAlignment( IStaticText::centerCenter );
  st2.setText( "Second" )
     .setAlignment( IStaticText::centerCenter );
  st4.setText( "Fourth" )
     .setAlignment( IStaticText::centerCenter );
  st5.setText( "Fifth" )
     .setAlignment( IStaticText::centerCenter );

  // Size and show the window now.
  frame.setFocus()
       .show();
  IApplication::current().run();
}
