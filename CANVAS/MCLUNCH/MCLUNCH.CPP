//************************************************************
// Canvas  - IMultiCellCanvas Implementation of Lunch Dialog
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <icheckbx.hpp>
#include <ientryfd.hpp>
#include <iframe.hpp>
#include <igroupbx.hpp>
#include <imcelcv.hpp>
#include <iradiobt.hpp>
#include <istattxt.hpp>

#include "pushbtns.hpp"      // For MyStandardPushButtons.
#include "lunch.h"

void main ( )
{
  IFrameWindow frame( "Lunch",
                      ID_LUNCH_DIALOG,
                      IFrameWindow::classDefaultStyle
                        & ~IFrameWindow::maximizeButton
                        & ~IFrameWindow::minimizeButton
#if IC_MAJOR_VERSION >= 201
                        | IFrameWindow::dialogBackground );
#else
                      );
#endif

  // Create the client window.
  IMultiCellCanvas client( 0x8008, &frame, &frame );

  // Heading text.
  IStaticText headingText( ID_LUNCH_TEXT, &client, &client );
  headingText.setText( "Select your lunch preferences:" );

  // Food group box and radio buttons.
  IGroupBox food( ID_FOOD, &client, &client );
  food.setText( "Food" );
  IRadioButton
    hamburger   ( ID_HAMBURGER,    &client, &client ),
    cheeseburger( ID_CHEESEBURGER, &client, &client ),
    hotdog      ( ID_HOTDOG,       &client, &client ),
    pizza       ( ID_PIZZA,        &client, &client );
  hamburger
   .setText      ( "Hamburger" )
   .enableTabStop()
   .enableGroup  ();
  cheeseburger.setText( "Cheeseburger" );
  hotdog.setText( "Hot dog" );
  pizza.setText( "Pizza" );

  // Beverage group box and radio buttons.
  IGroupBox beverage( ID_BEVERAGE, &client, &client );
  beverage.setText( "Beverage" );
  IRadioButton
    milk     ( ID_MILK,      &client, &client ),
    softDrink( ID_SOFTDRINK, &client, &client ),
    juice    ( ID_JUICE,     &client, &client ),
    water    ( ID_WATER,     &client, &client );
  milk
   .setText      ( "Milk" )
   .enableTabStop()
   .enableGroup  ();
  softDrink.setText( "Soft drink" );
  juice.setText( "Juice" );
  water.setText( "Water" );

  // Side orders group box and choices.
  IGroupBox sideOrders( ID_SIDEORDERS, &client, &client );
  sideOrders.setText( "Side orders" );
  IMultiCellCanvas
    checkBoxes ( 1, &client, &client ),
    requestPair( 2, &client, &client );
  ICheckBox
    salad( ID_SALAD, &checkBoxes, &checkBoxes ),
    fries( ID_FRIES, &checkBoxes, &checkBoxes );
  salad
   .setText      ( "Salad" )
   .enableTabStop()
   .enableGroup  ();
  fries
   .setText      ( "Fries" )
   .enableTabStop()
   .enableGroup  ();
  IStaticText
    requestPrompt( ID_REQUESTPROMPT,
                   &requestPair, &requestPair );
  requestPrompt
   .setAlignment( IStaticText::centerLeft )
   .setText( "Other" );
  IEntryField request(ID_REQUEST, &requestPair, &requestPair );
  request
   .setLimit(15)
   .enableTabStop()
   .enableGroup();

  // Push buttons.
  MyStandardPushButtons pushButtons( 4, &client );

  // Assign child windows to cells.
  ISize defaultCell = IMultiCellCanvas::defaultCell();
  client
   .addToCell( &headingText,   2,  2,  14 )
   .addToCell( &food,          3,  5,  5,  11 )
   .addToCell( &hamburger,     5,  7 )
   .addToCell( &cheeseburger,  5,  9 )
   .addToCell( &hotdog,        5,  11 )
   .addToCell( &pizza,         5,  13 )
   .addToCell( &beverage,      9,  5,  6,  11 )
   .addToCell( &milk,          11, 7 )
   .addToCell( &softDrink,     11, 9 )
   .addToCell( &juice,         11, 11 )
   .addToCell( &water,         11, 13 )
   .addToCell( &sideOrders,    3,  17, 12, 7 )
   .addToCell( &checkBoxes,    5,  19, 8 )
   .addToCell( &requestPair,   5,  21, 8 )
   .addToCell( &pushButtons,   2,  25, 14 );
  client
   .setColumnWidth( 6,  defaultCell.width(), true )
   .setColumnWidth( 12, defaultCell.width(), true )
   .setColumnWidth( 16, defaultCell.width() )
   .setRowHeight  ( 1,  defaultCell.height(), true )
   .setRowHeight  ( 3,  defaultCell.height(), true )
   .setRowHeight  ( 16, defaultCell.height(), true )
   .setRowHeight  ( 24, defaultCell.height(), true )
   .setRowHeight  ( 26, defaultCell.height(), true );

  checkBoxes
   .addToCell( &salad,         1,  1 )
   .addToCell( &fries,         3,  1 );
  checkBoxes
   .setColumnWidth( 2, defaultCell.width(), true )
   .setColumnWidth( 4, defaultCell.width(), true );

  requestPair
   .addToCell( &requestPrompt, 1,  1 )
   .addToCell( &request,       3,  1 );
  requestPair
   .setColumnWidth( 3, 0, true );

  // Select the default choices.
  hamburger.select();
  milk.select();

  // Size and position the frame window.
  frame.setClient( &client );
  IRectangle clientRect( IPoint( 30, 20 ),
                         client.minimumSize() );
  frame.moveSizeToClient( clientRect );

  // Show the dialog now.
  frame
   .setFocus()
   .show();
  IApplication::current().run();
}
