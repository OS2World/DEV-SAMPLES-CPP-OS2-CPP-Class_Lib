//************************************************************
// Canvas - ISetCanvas decks example.                         
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iapp.hpp>
#include <iframe.hpp>
#include <ivport.hpp>

#include "deckcv.hpp"
#include "setdecks.h"

void main ( )
{
  IFrameWindow frame( ID_DECKS_FRAME,
                      IFrameWindow::classDefaultStyle
                        | IFrameWindow::accelerator
                        | IFrameWindow::menuBar );

  // Create the IViewPort client area.
  IViewPort client( ID_CLIENT, &frame, &frame );
  frame.setClient( &client );

  // Create the scrollable ISetCanvas.
  DeckCanvas deckCanvas( ID_DECK_CANVAS, &client, &client );
  deckCanvas.setDeckCount( 2 );
  deckCanvas.setChildCount( 5 );

  // Show the window now.
  frame.setFocus()
       .show();
  IApplication::current().run();
}

