//************************************************************
// Direct Manipulation - List Box Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <ilistbox.hpp>
#include <ientryfd.hpp>
#include <idmhndlr.hpp>
#include <idmprov.hpp>

#include "lboxitem.hpp"

void main()
  {
  IFrameWindow
    frame( "List Box Drag Drop Sample" );

  IListBox
    client( 0, &frame, &frame );
  ListBoxItemProvider
    provider( &client );
  IDMHandler::enableDragDropFor( &client );
  client.addAsLast( "Drag an item as text" );
  client.addAsLast( "Drag to shredder to delete" );
  client.addAsLast( "Drop on item to replace text" );
  client.addAsLast( "Drop off end to add item" );

  IEntryField
    ef( 0xef, &frame, &frame );
  IDMHandler::enableDragDropFor( &ef );
  ef.setLimit( 1024 );
  ef.setText( "Drag text from here to list box" );

  frame.setClient( &client );
  frame.addExtension( &ef, frame.belowClient, 30 );
  frame.setFocus();
  frame.moveSizeTo( frame.rect().scaleBy( 0.5, 1.0 ) );
  frame.showModally();
  }
