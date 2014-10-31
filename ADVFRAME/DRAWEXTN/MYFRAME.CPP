//************************************************************
// Advanced Frame - Frame Extension Drawing Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#define INCL_WIN
#include <os2.h>

#include <iframe.hpp>
#include <iframext.hpp>
#include <icmdhdr.hpp>
#include <istring.hpp>
#include <ilistbox.hpp>
#include <ientryfd.hpp>
#include <ipushbut.hpp>
#include <itrace.hpp>


#include "myframe.hpp"
#include "myextns.hpp"

static IString
  colorText( "white black background blue red pink green "
             "cyan yellow neutral darkgray darkblue darkred "
             "darkpink darkgreen darkcyan brown palegray" );

ColorList::ColorList ( IWindow *owner )
    : IListBox( 0, owner, owner )
  {
  for ( int i = 1; i <= 18; i++ )
     addAsLast( colorText.word( i ) );
  }

long ColorList:: color ( )
  {
  IString
    selected( itemText( selection() ) );
  return (long)( colorText.wordIndexOfPhrase( selected ) ) - 3;
  }

MyFrame::MyFrame ( )
    : IFrameWindow( "Extended Extension Test" ),
      colorList( this ),
      extSize( 0, this, this ),
      drawButton( 0, this, this ),
      handler( *this )
  {
  drawButton.setText( "Redraw" );
  extSize.setText( "5" );
  colorList.select( 0 );
  addMyExtension( new MyExtension( &colorList,
                                 aboveClient, 0.5 ) );
  addMyExtension( new MyExtension( &extSize,
                                 aboveClient, 0.5 ) );
  addMyExtension( new MyExtension( &drawButton,
                                 belowClient, 0.5 ) );
  }

IFrameWindow& MyFrame::update ( )
  {
  IFrameExtensions
   *exts = extensions();
  unsigned
    newWidth = extSize.text().asUnsigned();
  long
    newColor = colorList.color();
  for ( int i = 1; exts && i <= exts->numberOfElements(); i++ )
    {
    MyExtension
     *p = (MyExtension*)( exts->elementAtPosition(i) );
    p -> setWidth( newWidth );
    p -> setColor( newColor );
    }
  return IFrameWindow::update();
  }

MyFrame&  MyFrame::addMyExtension( MyExtension *pExt )
  {
  // Get frame extensions...
  IFrameExtensions
   *exts = this->extensions();

  // If none previously, allocate collection...
  if ( !exts )
    this->setExtensions( exts = new IFrameExtensions );

  // Add argument extension to collection...
  exts -> addAsLast( pExt );

  // Update the frame.
  update();
  return *this;
  }

MyHandler :: MyHandler ( MyFrame &frame )
  : frame( frame )
  {
  handleEventsFor( &frame );
  }

Boolean MyHandler :: command ( ICommandEvent &cmd )
  {
  frame.update().refresh();
  return true;
  }


