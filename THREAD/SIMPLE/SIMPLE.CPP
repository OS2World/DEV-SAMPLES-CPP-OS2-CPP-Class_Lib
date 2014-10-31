//************************************************************
// Thread - Simple Thread Example        
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <istattxt.hpp>
#include <ipushbut.hpp>
#include <icmdhdr.hpp>
#include <ithread.hpp>

enum { cmdThreaded, cmdNotThreaded, cmdDone };

static const char
 *prompt = "Press a button to perform action.";

class Action {
public:
  Action ( IFrameWindow &frame )
    : frame( frame )
    {
    }
virtual void
  performAction ( )
    {
    // Sleep for 15 seconds.
    IThread::current().sleep( 15000 );
    // Tell frame the action is "done."
    frame.postEvent( IWindow::command, cmdDone );
    }
private:
IFrameWindow
 &frame;
Action (const Action&);
Action& operator= (const Action&);
};

class CmdHandler : public ICommandHandler {
public:
  // Handler attaches to frame + text.
  CmdHandler ( IFrameWindow &frame,
               IStaticText  &text )
    : action( frame ),
      frame( frame ),
      text( text )
    {
    handleEventsFor( &frame );
    }
protected:
virtual Boolean
  command ( ICommandEvent &event )
    {
    switch ( event.commandId() )
      {
      case cmdThreaded:
        {
        frame.disable();
        text.setText( "Performing action on separate thread." );
        IThread
          thread( new IThreadMemberFn<Action>
                        ( action, Action::performAction ) );
        break;
        }
      case cmdNotThreaded:
        frame.disable();
        text.setText( "Performing action on current thread" );
        action.performAction();
        break;
      case cmdDone:
        frame.enable();
        text.setText( prompt );
        break;
      }
    return true;
    }
private:
Action
  action;
IFrameWindow
 &frame;
IStaticText
 &text;
CmdHandler ( const CmdHandler& );
CmdHandler& operator= ( const CmdHandler& );
};

void main()
  {
  IFrameWindow
    frame( "PM Multi-Thread Demo" );
  IStaticText
    client( 0, &frame, &frame );
  CmdHandler
    handler( frame, client );
  client.setAlignment( IStaticText::centerCenter );
  client.setText( "Press button to try logon" );
  IPushButton
    button1( cmdThreaded, &frame, &frame ),
    button2( cmdNotThreaded, &frame, &frame );
  button1.setText( "On another thread" );
  button2.setText( "On current thread" );
  frame
    .addExtension( &button1, IFrameWindow::belowClient, 30 )
    .addExtension( &button2, IFrameWindow::belowClient, 30 )
    .setClient( &client )
    .setFocus()
    .show();

  IThread::current().processMsgs();
  }

