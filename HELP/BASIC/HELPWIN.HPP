#ifndef _HELPWIN_
#define _HELPWIN_
/*************************************************************/
/* Basic help program.                                       */
/*                                                           */
/* Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.       */
/* All Rights Reserved.                                      */
/*************************************************************/
#include <ientryfd.hpp>
#include <iframe.hpp>
#include <iselhdr.hpp>
#include <istattxt.hpp>
#include <istring.hpp>
#include <ititle.hpp>

#include "helpwin.h"

class ListBoxSelectHandler : public ISelectHandler {
protected:
virtual Boolean
  enter ( IControlEvent& event );
};

class TestWindow : public IFrameWindow {
public:
  TestWindow ( unsigned long id,
               IWindow* parent = 0,
               IWindow* owner = 0 )
    : IFrameWindow ( id, parent, owner ),
      prompt1 ( ID_DUMMY, this, this ),
      prompt2 ( ID_DUMMY, this, this ),
      entry1 ( ID_ENTRY1, this, this ),
      entry2 ( ID_ENTRY2, this, this )
  {
    prompt1
     .setText( "Has contextual help" )
     .moveSizeTo( IRectangle( IPoint( 20, 120), ISize( 180, 30 )));
    prompt2
     .setText( "No contextual help" )
     .moveSizeTo( IRectangle( IPoint( 20, 50), ISize( 180, 30 )));
    entry1
     .enableTabStop()
     .enableGroup()
     .moveSizeTo( IRectangle( IPoint( 200, 120), ISize( 180, 30 )));
    entry2
     .enableTabStop()
     .moveSizeTo( IRectangle( IPoint( 200, 50), ISize( 180, 30 )));

    this->sizeTo( ISize( 400, 220 ));
    entry1.setFocus();
  }
private:
IStaticText
  prompt1,
  prompt2;
IEntryField
  entry1,
  entry2;
};

class PrimaryWindow : public TestWindow {
public:
  PrimaryWindow ( )
    : TestWindow ( ID_PRIMARY2 )
  {
    ITitle( this, "Another Primary Window" );
  }
};

class SecondaryWindow : public TestWindow {
public:
  SecondaryWindow ( unsigned long id,
                    IWindow* owner )
    : TestWindow ( id, 0, owner )
  {
    IString title( id == ID_SECONDARY_MODELESS ?
                      "Modeless" : "Modal" );
    ITitle( this, title + " Secondary Window" );
  }
};

class ChildWindow : public TestWindow {
public:
  ChildWindow ( unsigned long id,
                IWindow* parent,
                IWindow* owner )
    : TestWindow ( id, parent, owner )
  {
    IString title( id == ID_CHILD_MODELESS ?
                      "Modeless" : "Modal" );
    ITitle( this, title + " Child Window" );
  }
};
#endif // _HELPWIN_
