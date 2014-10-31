//************************************************************
// Profile - Profile Viewer Example              
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iostream.h>
#include <fstream.h>
#include <ctype.h>
#include "enhprof.hpp"

EnhancedProfile :: EnhancedProfile ( const IString &name,
                                     Boolean createIfNotFound )
  : IProfile( validate( name, createIfNotFound ) )
  {
  }

EnhancedProfile :: EnhancedProfile ( const IProfile &profile )
  : IProfile( profile )
  {
  }

void EnhancedProfile :: displayOn ( ostream &aStream,
                                    const IString &apps,
                                    const IString &keys ) const
  {
  aStream << "Profile: " << this->name() << endl;
  IProfile
    self( *this );
  IProfile::Cursor
    cursor( self );
  for ( cursor.setToFirst(); 
        cursor.isValid(); 
        cursor.setToNext() )
    {
    IString
      app = self.applicationOrKeyAt( cursor );

    if ( app.isLike( apps ) )
      {
      ProfileApplication
        nextApp( self, app );
      nextApp.displayOn( aStream, keys );
      }
    }
  }

IString EnhancedProfile :: validate ( const IString &name,
                                      Boolean createIfNotFound )
  {
  int
    option = createIfNotFound ? 0 : ios::nocreate;
  IString
    outName( name );
  ifstream
    test( outName, option );
  if ( !test )
    {
    outName += ".ini";
    ifstream
      test( outName, option );
    if ( !test )
      {
      IString
        msg( "Unable to open profile " );
      msg += outName;
      throw msg;
      }
    }
  return outName;
  }

ProfileApplication :: ProfileApplication ( const IProfile &profile,
                                           const IString  &name )
  : prof( profile ),
    nm( name )
  {
  }

ProfileApplication :: ~ProfileApplication ( )
  {
  }

IString ProfileApplication :: name ( ) const
  {
  return this->nm;
  }

IProfile ProfileApplication :: profile ( ) const
  {
  return this->prof;
  }

void ProfileApplication :: displayOn ( ostream &aStream, 
                                       const IString &keys ) const
  {
  aStream << "Application: " << this->name() << endl;
  IProfile
    profile( this->profile() );
  IProfile::Cursor
    cursor( profile, this->name() );
  for ( cursor.setToFirst(); 
        cursor.isValid(); 
        cursor.setToNext() )
    {
    IString
      key = profile.applicationOrKeyAt( cursor );

    if ( key.isLike( keys ) )
      {
      ProfileKey
        nextKey( *this, key );
      nextKey.displayOn( aStream );
      }
    }
  }

ProfileKey :: ProfileKey ( const ProfileApplication &application,
                           const IString  &name )
  : app( application ),
    nm( name )
  {
  }

ProfileKey :: ~ProfileKey ( )
  {
  }

IString ProfileKey :: name ( ) const
  {
  return this->nm;
  }

IString ProfileKey :: value ( ) const
  {
  IProfile
    profile( this->application().profile() );
  IString
    data( profile.elementWithKey( this->name(), 
                                  this->application().name() ) );
  return data;
  }

IString ProfileKey :: formatted ( unsigned tabs ) const
  {
  IString
    data = this->value(),
    tab  = IString( '\t' ).copy( tabs ),
    result;
  unsigned
    pos = 1;
  while ( pos <= data.length() )
    {
    unsigned
      bytes = data.length() - pos + 1;
    if ( bytes > 16 )
      bytes = 16;
    result += tab;
    for ( int i = 0; i < bytes; i++ )
      {
      if ( isprint( data[ pos + i ] ) )
        result += data[ pos + i ];
      else
        result += '.';
      }
    result += IString( 0, 17 - bytes );
    IString
      hex( data.subString( pos, bytes ) );
    hex.c2x().leftJustify( 32, ' ' );
    hex.insert( ' ', 8 );
    hex.insert( ' ', 17 );
    hex.insert( ' ', 26 );
    cout << hex << endl;
    result += hex + IString( '\n' );
    pos += bytes;
    }
  return result;
  }

ProfileApplication ProfileKey :: application ( ) const
  {
  return this->app;
  }

void ProfileKey :: displayOn ( ostream &aStream ) const
  {
  aStream << "\tKey: " << this->name() << endl << this->formatted(2);
  }
