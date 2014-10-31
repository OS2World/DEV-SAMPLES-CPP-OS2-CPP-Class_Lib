//************************************************************
// Advanced Frame - Profile Viewer Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include "profobj.hpp"

ProfileObject :: ProfileObject ( const IString     &name,
                                 unsigned long      iconId,
                                 IContainerControl *cnr )
  : IContainerObject( name, iconId ),
    objCnr( cnr )
  {
  }

void ProfileObject :: handleOpen ( IContainerControl * )
  {
  this->view().open();
  }

ProfileObjectView &ProfileObject :: view ( )
  {
  if ( !objView )
    {
    objView = this -> newView();
    setInUse( true );
    }
  return *objView;
  }

ProfileObject &ProfileObject :: viewClosed ( )
  {
  this->objView = 0;
  setInUse( false );
  return *this;
  }

IContainerControl *ProfileObject :: container ( ) const
  {
  return objCnr;
  }

ProfileObjectView &ProfileObjectView :: open ( )
  {
  if ( isMinimized() )
    restore();
  setFocus();
  show();
  return *this;
  }

ProfileObjectView :: ProfileObjectView ( IWindow *client,
                                         ProfileObject &object,
                                         const IString &viewName )
  : IFrameWindow( 0, 0, object.container()->parent(),
                  nextShellRect().scaleBy( 0.5, 0.5 ),
                  classDefaultStyle | noMoveWithOwner ),
    viewTitle( this ),
    viewObj( &object )
  {
  viewTitle.setObjectText( object.iconText() );
  viewTitle.setViewText( viewName );
  setIcon( object.icon() );
  setClient( client );
  client->setOwner( this );
  setAutoDeleteObject( true );
  }

ProfileObjectView :: ~ProfileObjectView ( )
  {
  if ( viewObj )
    viewObj -> viewClosed();
  }

ProfileObject *ProfileObjectView :: object ( ) const
  {
  return viewObj;
  }
