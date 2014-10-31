//************************************************************
// Canvas - Lunch dialog using an ISetCanvas                  
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#ifndef IC_MAJOR_VERSION
  #define INCL_WINSYS     // For WinQuerySysValue.
  #include <os2.h>
#endif

#include <icheckbx.hpp>
#include <ientryfd.hpp>
#include <iframe.hpp>
#include <iradiobt.hpp>
#include <isetcv.hpp>
#include <istattxt.hpp>

#include "pushbtns.hpp"      // For MyStandardPushButtons.
#include "setlunch.h"

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
  ISetCanvas client( 0x8008, &frame, &frame );  // FID_CLIENT.
  client.setDeckOrientation( ISetCanvas::vertical );

  // Heading text.
  IStaticText headingText( ID_LUNCH_TEXT, &client, &client );
  headingText.setText( "Select your lunch preferences:" );

  // Formatting canvases and food group box.
  ISetCanvas
    choices( 1, &client, &client ),
    columns( 2, &choices, &choices ),
    food   ( ID_FOOD, &columns, &columns );
  choices
   .setDeckOrientation( ISetCanvas::vertical )
   .setPackType       ( ISetCanvas::even );
  columns
   .setMargin  ( ISize() )
   .setPackType( ISetCanvas::expanded );
  food
   .setDeckOrientation( ISetCanvas::vertical )
   .setText           ( "Food" );

  // Food radio buttons.
  IRadioButton
    hamburger   ( ID_HAMBURGER,    &food, &food ),
    cheeseburger( ID_CHEESEBURGER, &food, &food ),
    hotdog      ( ID_HOTDOG,       &food, &food ),
    pizza       ( ID_PIZZA,        &food, &food );
  hamburger
   .setText      ( "~Hamburger" )
   .enableTabStop()
   .enableGroup  ();
  cheeseburger.setText( "~Cheeseburger" );
  hotdog.setText( "Hot ~dog" );
  pizza.setText( "~Pizza" );

  // Beverage group box and radio buttons.
  ISetCanvas beverage( ID_BEVERAGE, &columns, &columns );
  beverage
   .setDeckOrientation( ISetCanvas::vertical )
   .setText           ( "Beverage" );
  IRadioButton
    milk     ( ID_MILK,      &beverage, &beverage ),
    softDrink( ID_SOFTDRINK, &beverage, &beverage ),
    juice    ( ID_JUICE,     &beverage, &beverage ),
    water    ( ID_WATER,     &beverage, &beverage );
  milk
   .setText      ( "~Milk" )
   .enableTabStop()
   .enableGroup  ();
  softDrink.setText( "~Soft drink" );
  juice.setText( "~Juice" );
  water.setText( "~Water" );

  // Side orders group box and choices.
  ISetCanvas sideOrders( ID_SIDEORDERS, &choices, &choices );
  sideOrders
   .setDeckCount( 2 )
   .setAlignment( ISetCanvas::centerCenter )
   .setText     ( "Side orders" );
  ICheckBox
    salad( ID_SALAD, &sideOrders, &sideOrders ),
    fries( ID_FRIES, &sideOrders, &sideOrders );
  salad
   .setText      ( "Salad" )
   .enableTabStop()
   .enableGroup  ();
  fries
   .setText      ( "Fries" )
   .enableTabStop()
   .enableGroup  ();
  IStaticText
    requestPrompt( ID_REQUESTPROMPT, &sideOrders, &sideOrders, IRectangle(),
                   IStaticText::defaultStyle() | IStaticText::mnemonic );
  requestPrompt.setText( "~Other" );
  IEntryField request(ID_REQUEST, &sideOrders, &sideOrders );
  request
   .enableTabStop()
   .enableGroup();

  // Push buttons.
  MyStandardPushButtons pushButtons( 4, &client );

  // Select the default choices.
  hamburger.select();
  milk.select();

  // Size and position the frame window.
  frame.setClient( &client );
  IRectangle clientRect( IPoint( 30, 20 ),
                         client.minimumSize() );
#if IC_MAJOR_VERSION >= 201
  frame.moveSizeToClient( clientRect );
#else
  unsigned long borderWidth =
           WinQuerySysValue( IWindow::desktopWindow()->handle(),
                             SV_CXDLGFRAME );
  unsigned long borderHeight =
           WinQuerySysValue( IWindow::desktopWindow()->handle(),
                             SV_CYDLGFRAME );
  unsigned long titleHeight =
           WinQuerySysValue( IWindow::desktopWindow()->handle(),
                             SV_CYTITLEBAR );
  IRectangle frameRect( clientRect.bottomLeft() -
                          IPoint( borderWidth, borderHeight ),
                        ISize( clientRect.size().width() +
                                 borderWidth * 2,
                               clientRect.size().height() +
                                 borderHeight * 2 +
                                   titleHeight ));
  frame.moveSizeTo( frameRect );
#endif

  // Show the dialog now.
  frame
   .setFocus()
   .show();
  IApplication::current().run();
}
