#ifndef _UCKEYBD_
#define _UCKEYBD_
//************************************************************
// Reusable Handlers - Keyboard Handler
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <ikeyhdr.hpp>
#include <istring.hpp>
#include <iwindow.hpp>

// Keyboard handler example to convert lowercase characters
// to uppercase as the user types.                         
class UppercaseKeyboardHandler : public IKeyboardHandler {
protected:
virtual Boolean
  characterKeyPress ( IKeyboardEvent& event )
  {
    Boolean dontPassOn = false;
    IString strChar = event.mixedCharacter();
    if (strChar.isSBCS()  &&  strChar.isLowerCase())
    {                   // Single-byte 'a'-'z'.
       // Generate the uppercased character.
       IEventParameter2 param2( strChar.upperCase()[0],
                                event.parameter2().number2() );
                     // Only change the character to uppercase.
       event.window()->sendEvent( IWindow::character,
                                  event.parameter1(),
                                  param2);
       event.setResult( true );  // Mark key as processed.
       dontPassOn = true;    // Don't pass on original event.
    }
    return dontPassOn;
  }
};
#endif // _UCKEYBD_
