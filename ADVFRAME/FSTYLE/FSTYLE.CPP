//************************************************************
// Advanced Frame Window - Frame Style Test
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <istring.hpp>
#include <iframe.hpp>
#include <istattxt.hpp>
#include <iexcept.hpp>
#include <ifont.hpp>
#include <icmdhdr.hpp>

// Simple handler used to demonstrate 
// that short-cut keys are working...
class CmdHandler : public ICommandHandler {
public:
  CmdHandler ( IStaticText &txt )
    : text( txt )
    {
    }
virtual Boolean
  command ( ICommandEvent &event )
    {
    text.setText( IString( event.commandId() ) );
    return true;
    }
private:
IStaticText
 &text;
CmdHandler(const CmdHandler&);
CmdHandler& operator=(const CmdHandler&);
};

// Array of "option" mnemonics...
const char
 *options[] = 
    { "acc*", "*ico*", "*adj*", "ani*", "*db*", "bor*", 
    "def*", "d*l*g*", "hid*", "hor*", "*xb*", "max*", 
    "men*", "*nb*", "min*", "*own*", "*pos*", "siz*", 
    "sysmod*", "sys*", "tit*", "vert*", "win*" };

// Corresponding IFrameWindow::Styles...
IFrameWindow::Style
  styles[] = 
    { IFrameWindow::accelerator, IFrameWindow::minimizedIcon, 
      IFrameWindow::alignNoAdjust, IFrameWindow::animated,
      IFrameWindow::appDBCSStatus, IFrameWindow::border,
      IFrameWindow::classDefaultStyle, IFrameWindow::dialogBorder,
      IFrameWindow::hideButton, IFrameWindow::horizontalScroll,
      IFrameWindow::maximizeButton, IFrameWindow::maximized, 
      IFrameWindow::menuBar, IFrameWindow::minimizeButton,
      IFrameWindow::minimized, IFrameWindow::noMoveWithOwner,
      IFrameWindow::shellPosition, IFrameWindow::sizingBorder,
      IFrameWindow::systemModal, IFrameWindow::systemMenu,
      IFrameWindow::titleBar, IFrameWindow::verticalScroll,
      IFrameWindow::windowList };

void main( int argc, char *argv[] )
  {
  // Start with empty style...
  IFrameWindow::Style
    style = IWindow::noStyle;
  // Use default if no options specified...
  if ( argc == 1 )
    style = IFrameWindow::classDefaultStyle;
  else
    {
    int 
      n = sizeof options / sizeof options[0];
    // Examine each command line option...
    for ( int i = 1; i < argc; i++ )
      {
      // Get next option...
      IString
        opt( argv[ i ] );
      Boolean
        not = ( opt[1] == '~' );
      opt.stripLeading( '~' );
      // Check against array of mnemonics...
      for ( int j = 0; j < n; j++ )
        {
        // Turn corresponding style bit on or off...
        if ( opt.isLike( options[j] ) )
          {
          if ( not )
            style &= ~styles[ j ];
          else
            style |= styles[ j ];
          break;
          }
        }
      }
    }
  // Put style (in hex) on title bar...
  IString
    title( &style, sizeof style );
  title.c2x();
  // Construct frame with this style...
  IFrameWindow
    frame( title, IC_DEFAULT_FRAME_ID, style );
  // Set up handler/client...
  IStaticText
    text( 0, &frame, &frame );
  CmdHandler
    cmdHandler( text );
  cmdHandler.handleEventsFor( &frame );
  text
    .setAlignment( IStaticText::centerCenter )
    .setFont( IFont( "Times Roman", 72 ) );
  // Show the window...
  frame.setClient( &text ).showModally();
  }
