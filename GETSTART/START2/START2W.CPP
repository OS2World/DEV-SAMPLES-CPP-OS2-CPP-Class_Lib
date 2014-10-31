//************************************************************
// Getting Started - Simple Program Version 2
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <imenubar.hpp>
#include "start2w.hpp"
#include "start2.h"

CodeWindow :: CodeWindow ( const char* title,
                           unsigned long id )
  : IFrameWindow ( title, id ),
    mle( ID_CLIENT, this, this,
         IRectangle(),
         IMultiLineEdit::verticalScroll
          | IMultiLineEdit::horizontalScroll )
{
  // Make the MLE the client window.
  this->setClient( &mle );

  // Read this source file into the MLE, and scroll to
  // the top of the file.
  mle.importFromFile( __FILE__ );
  mle.setCursorAtLine( 0 );

  // Add a menu bar and attach the command handler
  // that will process selections from it.
  IMenuBar menuBar( ID_MENUBAR, this );
  menuBar.setAutoDestroyWindow( false );
  cmdHandler.handleEventsFor( this );
}

Boolean CodeWindow :: cut ( )
{
  Boolean didCut = false;
  if (mle.hasSelectedText())
  {           // Cut selected text to the clipboard.
     mle.cut();
     didCut = true;
  }
  return didCut;
}

Boolean CodeWindow :: copy ( )
{
  Boolean didCopy = false;
  if (mle.hasSelectedText())
  {           // Copy selected text to the clipboard.
     mle.copy();
     didCopy = true;
  }
  return didCopy;
}

Boolean CodeWindow :: paste ( )
{
  Boolean didPaste = false;
  if (mle.clipboardHasTextFormat())
  {           // Paste selected text from the clipboard.
     mle.paste();
     didPaste = true;
  }
  return didPaste;
}
