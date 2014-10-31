//************************************************************
// Advanced Frame - Profile Viewer Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <istring.hpp>
#include <iexcept.hpp>
#include <imsgbox.hpp>
#include <ithread.hpp>
#include <iwindow.hpp>

#include "vprofarg.hpp"
#include "profview.hpp"
#include "enhprof.hpp"

int main ( int argc, char *argv[] )
  {
  // Explicitly start PM so that we can display a message box when
  // incorrect input is received.
  IThread::current().initializePM();
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
    // Open view of selected profile...
    ProfileView
      view( *profile );
    view.open();
    IThread::current().processMsgs();
    delete profile;
    }
  catch ( const IString &msg )
    {
    // Display error message...
    IMessageBox
      msgBox( IWindow::objectWindow() );
    msgBox.show( msg, msgBox.cancelButton );
    rc = 1;
    }
  catch ( const IException &exception )
    {
    // Display report of system-type error...
    IMessageBox
      msgBox( IWindow::objectWindow() );
    msgBox.show( exception );
    rc = 2;
    }
  return rc;
  }
