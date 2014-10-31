//************************************************************
// Getting Started - Simple Program Version 1
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iapp.hpp>
#include <iframe.hpp>
#include <imle.hpp>

void main ( )
{
  // Create a primary window that contains a read-only MLE.
  IFrameWindow primary( "Getting Started - Version 1" );
  IMultiLineEdit mle( 0x8008, &primary, &primary,
                      IRectangle(),
                      IMultiLineEdit::verticalScroll
                       | IMultiLineEdit::horizontalScroll
                       | IMultiLineEdit::readOnly );
  primary.setClient( &mle );

  // Read this source file into the MLE, and scroll to
  // the top of the file.
  mle.importFromFile( __FILE__ );
  mle.setCursorAtLine( 0 );

  // Set the input focus, and show the window.
  primary.setFocus();
  primary.show();

  // Display the window until the user closes it.
  IApplication::current().run();
}
