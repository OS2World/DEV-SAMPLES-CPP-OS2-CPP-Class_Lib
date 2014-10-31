//************************************************************
// Advanced Frame - Profile Viewer Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include "appview.hpp"
#include "keyview.hpp"
#include "profview.h"

ProfileAppObject :: ProfileAppObject ( EnhancedProfile   &profile,
                                       const IString     &appName,
                                       IContainerControl *cnr )
  : ProfileObject( appName, APP_ICON_ID, cnr ),
    app( profile, appName )
  {
  }

ProfileObjectView *ProfileAppObject :: newView ( )
  {
  return new ApplicationView( *this );
  }

ProfileApplication &ProfileAppObject :: application ( )
  {
  return app;
  }

ApplicationView :: ApplicationView ( ProfileAppObject &appObj )
  : ProfileObjectView( clientWindow(),
                       appObj,
                       "Icon View" ),
    appObj( appObj )
  {
  handler.handleEventsFor( (IContainerControl*)( this->client() ) );
  populate();
  }

ApplicationView &ApplicationView :: populate ( )
  {
  IContainerControl
   *cnr = (IContainerControl*)( client() );
  IContainerControl::ObjectCursor
    cursor( *(appObj.container()), &appObj );
  for ( cursor.setToFirst();
        cursor.isValid();
        cursor.setToNext() )
    {
    ProfileKeyObject
     *next = (ProfileKeyObject*)( appObj.container()->objectAt( cursor ) );
    cnr -> addObject( next );
    }
  cnr -> arrangeIconView();
  return *this;
  }

IContainerControl *ApplicationView :: clientWindow ( )
  {
  IContainerControl
   *p = new IContainerControl( 0, 
                               IWindow::objectWindow(),
                               IWindow::objectWindow() );
  p -> showIconView();
  p -> setAutoDeleteObject( true );
  return p;
  }
