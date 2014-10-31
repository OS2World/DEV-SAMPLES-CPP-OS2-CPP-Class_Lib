//************************************************************
// Tour of the UICL - Shopping List Example Program
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iapp.hpp>
#include <icnrctl.hpp>
#include <icnrhdr.hpp>
#include <idmsrch.hpp>
#include <idmtgth.hpp>
#include <iframe.hpp>
#include <isplitcv.hpp>

#include "puritem.hpp"
#include "shopping.h"


//=========================== Main ============================

void main ( )
{
  // Create the primary window with the two container views.
  IFrameWindow primary( "Shopping List", ID_SHOPPINGLIST );
  ISplitCanvas containers( ID_LISTCLIENT, &primary, &primary );
  containers.setOrientation( ISplitCanvas::horizontalSplit );
  primary.setClient( &containers );

  IContainerControl
    buyList( ID_BUYLIST, &containers, &containers ),
    dontBuyList( ID_DONTBUYLIST, &containers, &containers );

  // Set up the two containers.
  buyList
   .setTitle( "Items to buy" )
   .showTitle()
   .showTitleSeparator()
   .showIconView()
   .arrangeIconView()
   .setDeleteObjectsOnClose();
  dontBuyList
   .setTitle( "Unneeded items" )
   .showTitle()
   .showTitleSeparator()
   .showIconView()
   .arrangeIconView()
   .setDeleteObjectsOnClose();

  // Get default processing for an "open" event.
  ICnrHandler cnrHandler;
  cnrHandler
   .handleEventsFor( &buyList )
   .handleEventsFor( &dontBuyList );

  // Support drag and drop of purchase items.
  IDMHandler::enableDragDropFor( &buyList );
  IDMHandler::enableDragDropFor( &dontBuyList );

  // Create some PurchaseItems.
  PurchaseItem* p1 = new PurchaseItem( "Apple juice" );
  p1->setNotes( "Kids won't drink anything else." );
  PurchaseItem* p2 = new PurchaseItem( "Diskettes" );
  (*p2)
   .setQuantity( "1 box of 10 diskettes" )
   .addNotes( "3.5 inch, double-sided, high-density." )
   .addNotes( "Prefer pre-formatted." );
  PurchaseItem* p3 =
      new PurchaseItem( "Milk", "2 gallons", "Any", 0.0,
                        "Skim" );
  PurchaseItem* p4 = new PurchaseItem( "Fruit snacks" );
  p4->setNotes( "These are for the kids." );
  PurchaseItem* p5 =
      new PurchaseItem( "Eggs", "1 dozen", 0, 0.0,
                        "Extra large size." );
  p5->addNotes( "Be sure none are cracked." );
  PurchaseItem* p6 =
      new PurchaseItem( "C Set ++", "10", "IBM", 0.0,
                        "Version 2.1" );
  (*p6)
   .addNotes( "Love the User Interface Library!" )
   .addNotes( "Need CSD CTM0008." )
   .setIcon( ID_CSETPLUSPLUSICON );

  // Fill the containers.
  dontBuyList
   .addObject( p1 )
   .addObject( p2 )
   .addObject( p3 )
   .addObject( p4 )
   .addObject( p5 );
  buyList.addObject( p6 );

  buyList.setFocus();  // Give input focus to first container.
  primary.show();      // Show the window.

  // Display the window until the user closes it.
  IApplication::current().run();
}
