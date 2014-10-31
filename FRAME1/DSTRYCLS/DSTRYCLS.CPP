//************************************************************
// Frame Window Basics - Defer Destroy on Close
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************

#define INCL_WIN
#include <os2.h>
#include <iframe.hpp>
#include <icmdhdr.hpp>
#include <istattxt.hpp>
#include <ipushbut.hpp>
#include <istring.hpp>

class CmdHandler : public ICommandHandler {
public:
  CmdHandler ( IFrameWindow &frame )
    : frame( frame )
    {
    handleEventsFor( &frame );
    }

virtual Boolean
  command ( ICommandEvent &cmd )
    {
    frame.dismiss( cmd.commandId() );
    return false;
    }

private:
IFrameWindow
 &frame;
CmdHandler &operator=(const CmdHandler&);
};

void main()
  {
  IFrameWindow
    dialog( "Hello" );
  CmdHandler
    handler( dialog );
  IStaticText
    text( 0, &dialog, &dialog );
  IPushButton
    againButton( DID_OK, &dialog, &dialog );

  againButton.setText( "Again" );
  dialog.setDestroyOnClose( false );
  dialog.setClient( &text );
  dialog.addExtension( &againButton,
                       IFrameWindow::belowClient, 
                       100 );

  dialog.setResult( DID_OK );
  for ( int i = 1; dialog.result() == DID_OK; i++ )
    {
    text.setText( "Display Number " + IString( i ) );
    dialog.setFocus();
    dialog.showModally();
    }
  }

