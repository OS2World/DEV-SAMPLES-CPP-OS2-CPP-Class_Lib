//************************************************************
// Reusable Handlers - Keyboard Handler
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <icombobx.hpp>
#include <ientryfd.hpp>
#include <iframe.hpp>
#include <imle.hpp>

#include "hexkeybd.hpp"
#include "uckeybd.hpp"
#include "keybd.h"

//=========================== Main ============================

void main ( )
{
  IFrameWindow frame( ID_KEYBD_DIALOG );

  // Wrapper the relevant dialog controls.
  IEntryField anyEntry( ID_ANY_ENTRY, &frame );
  IEntryField upperEntry( ID_UPPERCASE_ENTRY, &frame );
  IEntryField hexEntry( ID_HEX_ENTRY, &frame );
  IEntryField upperHexEntry( ID_UPPERCASE_HEX_ENTRY, &frame );
  IComboBox upperHexCombo( ID_UPPERCASE_HEX_COMBO, &frame );
  IEntryField comboEntry( 0x029B, &upperHexCombo );
                   // CBID_EDIT entry field child window.
  IMultiLineEdit upperHexMLE( ID_UPPERCASE_HEX_MLE, &frame );

  // Construct and attach the keyboard handlers.
  UppercaseKeyboardHandler upperKeyboardHandler;
  upperKeyboardHandler
   .handleEventsFor( &upperEntry )
   .handleEventsFor( &upperHexEntry )
   .handleEventsFor( &comboEntry )
   .handleEventsFor( &upperHexMLE );

  HexKeyboardHandler hexKeyboardHandler;
  hexKeyboardHandler
   .handleEventsFor( &hexEntry )
   .handleEventsFor( &upperHexEntry )
   .handleEventsFor( &comboEntry )
   .handleEventsFor( &upperHexMLE );

  // Show the window now.
  anyEntry.setFocus();
  frame.show();
  IApplication::current().run();
}  // main()
