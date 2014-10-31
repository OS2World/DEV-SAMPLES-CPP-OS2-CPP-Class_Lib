//************************************************************
// Canvas - ISetCanvas Desks Example                          
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include "packcv.hpp"
#include "packcv.h"

PackCanvas :: PackCanvas ( unsigned long id,
                           IWindow* parentAndOwner,
                           ISetCanvas::PackType pack )
  : ISetCanvas( id, parentAndOwner, parentAndOwner ),
    first(  1, this, this),
    second( 2, this, this),
    third(  3, this, this),
    fourth( 4, this, this),
    fifth(  5, this, this),
    sixth(  6, this, this)
{
  (*this).setPackType( pack )
         .setDeckCount( 2 );
  switch ( pack )
  {
    case ISetCanvas::tight:
       this->setText( "Pack tight" );
       break;
    case ISetCanvas::even:
       this->setText( "Pack even" );
       break;
    case ISetCanvas::expanded:
    default:
       this->setText( "Pack expanded" );
       break;
  }
  first.setMinimumSize ( ISize( 30, 25 ));
  second.setMinimumSize( ISize( 15, 40 ));
  third.setMinimumSize ( ISize( 35, 65 ));
  fourth.setMinimumSize( ISize( 40, 35 ));
  fifth.setMinimumSize ( ISize( 30, 20 ));
  sixth.setMinimumSize ( ISize( 20, 60 ));
}

PackAlignTest :: PackAlignTest ( )
  : IFrameWindow( "ISetCanvas pack options" ),
    packClient( 0x8008, this, this ),
    tight( 1, &packClient, ISetCanvas::tight ),
    even( 2, &packClient, ISetCanvas::even ),
    expanded( 3, &packClient, ISetCanvas::expanded ),
    cmdHdr( this ),
    buttons( 0, this, this ),
    topLeft( ID_TOP_LEFT, &buttons, &buttons,
             ID_TOP_LEFT ),
    topCenter( ID_TOP_CENTER, &buttons, &buttons,
               ID_TOP_CENTER ),
    topRight( ID_TOP_RIGHT, &buttons, &buttons,
              ID_TOP_RIGHT ),
    centerLeft( ID_CENTER_LEFT, &buttons, &buttons,
                ID_CENTER_LEFT ),
    centerCenter( ID_CENTER_CENTER, &buttons, &buttons,
                  ID_CENTER_CENTER ),
    centerRight( ID_CENTER_RIGHT, &buttons, &buttons,
                 ID_CENTER_RIGHT ),
    bottomLeft( ID_BOTTOM_LEFT, &buttons, &buttons,
                ID_BOTTOM_LEFT ),
    bottomCenter( ID_BOTTOM_CENTER, &buttons, &buttons,
                  ID_BOTTOM_CENTER ),
    bottomRight( ID_BOTTOM_RIGHT, &buttons, &buttons,
                 ID_BOTTOM_RIGHT )
{
  setClient( &packClient );
  packClient.setDeckOrientation( ISetCanvas::horizontal );
  cmdHdr.handleEventsFor( this );
  buttons
   .setMargin( ISize( 1, 1 ))
   .setPad( ISize( 1, 1 ));
  ISize buttonSize( 25, 25 );
  topLeft.setMinimumSize( buttonSize );
  topCenter.setMinimumSize( buttonSize );
  topRight.setMinimumSize( buttonSize );
  centerLeft.setMinimumSize( buttonSize );
  centerCenter.setMinimumSize( buttonSize );
  centerRight.setMinimumSize( buttonSize );
  bottomLeft.setMinimumSize( buttonSize );
  bottomCenter.setMinimumSize( buttonSize );
  bottomRight.setMinimumSize( buttonSize );
  sizHdr
   .handleEventsFor( &topLeft )
   .handleEventsFor( &topCenter )
   .handleEventsFor( &topRight )
   .handleEventsFor( &centerLeft )
   .handleEventsFor( &centerCenter )
   .handleEventsFor( &centerRight )
   .handleEventsFor( &bottomLeft )
   .handleEventsFor( &bottomCenter )
   .handleEventsFor( &bottomRight );

  // Add the buttons above the client.
  addExtension( &buttons,
                IFrameWindow::aboveClient,
                (unsigned long)buttons.minimumSize()
                 .height() );

  // Show the window now.
  ISize clientSize = packClient.minimumSize();
  IPoint clientPos = IFrameWindow::nextShellRect().topLeft()
                           - IPoint( 0, clientSize.height() );
  (*this)
   .moveSizeToClient( IRectangle( clientPos, clientSize ))
   .setFocus()
   .show();
}

PackAlignTest& PackAlignTest :: alignGrandChildren
                                 ( ISetCanvas::Alignment align )
{
  tight.setAlignment( align );
  even.setAlignment( align );
  expanded.setAlignment( align );
  return *this;
}

Boolean PackAlignTest::CmdHandler :: command
                                        ( ICommandEvent& event )
{
  Boolean dontPassOn = false;
  ISetCanvas::Alignment align = ISetCanvas::bottomRight;
  switch ( event.commandId() )
  {
     case ID_TOP_LEFT:
       align = ISetCanvas::topLeft;
       dontPassOn = true;
       break;
     case ID_TOP_CENTER:
       align = ISetCanvas::topCenter;
       dontPassOn = true;
       break;
     case ID_TOP_RIGHT:
       align = ISetCanvas::topRight;
       dontPassOn = true;
       break;
     case ID_CENTER_LEFT:
       align = ISetCanvas::centerLeft;
       dontPassOn = true;
       break;
     case ID_CENTER_CENTER:
       align = ISetCanvas::centerCenter;
       dontPassOn = true;
       break;
     case ID_CENTER_RIGHT:
       align = ISetCanvas::centerRight;
       dontPassOn = true;
       break;
     case ID_BOTTOM_LEFT:
       align = ISetCanvas::bottomLeft;
       dontPassOn = true;
       break;
     case ID_BOTTOM_CENTER:
       align = ISetCanvas::bottomCenter;
       dontPassOn = true;
       break;
     case ID_BOTTOM_RIGHT:
     default:
       dontPassOn = true;
       break;
  }
  if (dontPassOn)
  {
     clWindow->alignGrandChildren( align );
  }
  return dontPassOn;
}

Boolean PackAlignTest::GraphicSizer :: windowResize
                                         ( IResizeEvent& event )
{
  IIconControl* graphic =
     &(((IGraphicPushButton*)event.window())->graphicWindow());
  graphic->moveSizeTo( IRectangle( IPoint( 2, 2 ),
                                   ISize( event.newSize()
                                            - ISize( 4, 4 ))));
  return true;
}
