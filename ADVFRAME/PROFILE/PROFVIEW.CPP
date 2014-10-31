//************************************************************
// Advanced Frame - Profile Viewer Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include "profview.hpp"
#include "appview.hpp"
#include "keyview.hpp"
#include "enhprof.hpp"
#include "profview.h"

ProfileView :: ProfileView ( EnhancedProfile &profile )
  : profile( profile ),       
    frame( 0, 0, 0, 
           IFrameWindow::nextShellRect().scaleBy( 0.5, 1.0 ) ),
    title( &frame ),
    client( 0, &frame, &frame )
  {
  title.setObjectText( profile.name() );
  title.setViewText( "Tree View" );

  client.showTreeIconView();

  frame.setClient( &client );
  frame.setIcon( INI_ICON_ID );

  handler.handleEventsFor( &client );
  }

ProfileView &ProfileView :: open ( )
  {
  frame.setFocus();
  frame.show();
  populate();
  return *this;
  }

ProfileView &ProfileView :: populate ( )
  {
  IProfile::Cursor
    cursor( profile );
  for ( cursor.setToFirst(); 
        cursor.isValid(); 
        cursor.setToNext() )
    {
    IString        
      appName = profile.applicationOrKeyAt( cursor );
    ProfileAppObject
     *app = new ProfileAppObject( profile, 
                                  appName,
                                  &client );

    client.addObject( app );

    IProfile::Cursor
      cursor( profile, appName );
    for( cursor.setToFirst();
         cursor.isValid();
         cursor.setToNext() )
      {
      IString
        keyName = profile.applicationOrKeyAt( cursor );
      ProfileKeyObject
       *key = new ProfileKeyObject( app->application(), 
                                    keyName,
                                    &client );

      client.addObject( key, app );
      }
    }
  return *this;
  }
