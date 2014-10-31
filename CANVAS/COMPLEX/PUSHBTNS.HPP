#ifndef _PUSHBTNS_
#define _PUSHBTNS_
//************************************************************
// Canvas - Complex Canvas Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <ipushbut.hpp>
#include <isetcv.hpp>

class MyStandardPushButtons : public ISetCanvas {
public:
  MyStandardPushButtons ( unsigned long id,
                          IWindow*      parentAndOwner )
    : ISetCanvas( id, parentAndOwner, parentAndOwner ),
      ok( 1, this, this ),
      cancel( 0x8004, this, this ),
      help( 10, this, this )
  {
    (*this)
     .setMargin( ISize() )
     .setPackType( ISetCanvas::expanded );
                        // Make all buttons the same size.
    ok
     .enableDefault()
     .setText( "OK" )
     .enableTabStop()
     .enableGroup();
    cancel
     .enableSystemCommand()  // For SC_CLOSE.
     .setText( "Cancel" );
    help
     .enableHelp()
     .disableMouseClickFocus()
     .setText( "Help" );
  }
private:
IPushButton
  ok,
  cancel,
  help;
};

#endif // _PUSHBTNS_
