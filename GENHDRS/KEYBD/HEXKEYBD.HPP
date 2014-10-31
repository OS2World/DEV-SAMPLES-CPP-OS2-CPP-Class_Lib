#ifndef _HEXKEYBD_
#define _HEXKEYBD_
//************************************************************
// Reusable Handlers - Keyboard Handler
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#define INCL_WINDIALOGS      // For WinAlarm.
#define INCL_WININPUT        // For KC_CHAR, VK_DELETE.
#include <os2.h>

#include <ikeyhdr.hpp>
#include <istring.hpp>
#include <iwindow.hpp>

// Keyboard handler example to restrict character input to
// hexadecimal digits (0-9, a-f, A-F).                    
class HexKeyboardHandler : public IKeyboardHandler {
protected:
virtual Boolean
  characterKeyPress ( IKeyboardEvent& event )
  {
    Boolean badKey = true;   // Assume an invalid key,
    Boolean dontPassOn = true;
    event.setResult(true);   // (Ignored if return false.)

    IString strChar = event.mixedCharacter();
    if (strChar.isSBCS())
    {                        // Single-byte input.
       if (strChar.isHexDigits())
       {                     // '0'-'9', 'A'-'F', 'a'-'f'.
          badKey = false;    // Valid hexadecimal digit.
          dontPassOn = false;  // Pass event to the window.
       }
       else if (strChar == " ")
       {                     // Space bar.
          badKey = false;    // Replace with Delete key.
          IEventParameter1
            param1( event.parameter1().number1() & ~KC_CHAR,
                    event.parameter1().char3(), 0 );
          (*event.window())
           .sendEvent(IWindow::character,
                      param1,
                      IEventParameter2( 0, VK_DELETE ));
               // (Throw out scan code and character data.)
       }
       // Throw away any other character key.
    }                        // End single-byte input.

    if (badKey)
    {
       WinAlarm( IWindow::desktopWindow()->handle(),
                 WA_WARNING );
    }
    return dontPassOn;
  }
};
#endif // _HEXKEYBD_
