//************************************************************
// Profile - Profile Viewer Example             
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <istring.hpp>
#include <iexcept.hpp>
#include <iostream.h>
#include "vprofarg.hpp"
#include "enhprof.hpp"


int main ( int argc, char *argv[] )
  {
  int
    rc = 0;
  try
    {
    // Get arguments...
    ViewProfileArgs
      args( argc, argv );
    // Open specified profile...
    EnhancedProfile
      *profile = 0;
    switch ( args.profileType() )
      {
      case ViewProfileArgs::system:
        profile = 
          new EnhancedProfile( IProfile::systemProfile() );
        break;
      case ViewProfileArgs::user:
        profile = 
          new EnhancedProfile( IProfile::userProfile() );
        break;
      default:
        profile = 
          new EnhancedProfile( args.profileName(), false );
      }
    // Dump selected app/key data to standard output...
    profile -> displayOn( cout, 
                          args.applicationName(), 
                          args.key() );
    }
  catch ( const IString &msg )
    {
    // Display error message...
    cout << msg << endl;
    rc = 1;
    }
  catch ( const IException &exception )
    {
    // Display report of system-type error...
    cout << "Error: " << exception.text() << endl;
    rc = 2;
    }
  return rc;
  }
