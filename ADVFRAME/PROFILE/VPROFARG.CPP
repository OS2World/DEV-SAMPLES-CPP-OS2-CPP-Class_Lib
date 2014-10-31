//************************************************************
// Advanced Frame - Profile Viewer Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <istring.hpp>
#include <iostream.h>
#include "vprofarg.hpp"

#define SYNTAX "Syntax is: viewprof prffile[.ini] "\
               "[/?] [/s] [/u] [/a:app] [/k:key]" 
#define MSG1 "You can't provide a file name with /s or /u"
#define MSG2 "You can't use both /s and /u"

ViewProfileArgs :: ViewProfileArgs ( int argc, char *argv[] )
  : type( none ),
    app( "*" ),
    k( "*" )
  {
  for ( int i = argc; i > 1; i-- )
    {
    IString
      token = argv[i-1];
    if ( token[1] == '/' )
      switch ( token[2] )
        {
        case '?':
          {
          IString
            help( SYNTAX "\n"
                  "\tprffile - Profile to view\n"
                  "\t/?  - Displays help\n"
                  "\t/s  - View system profile\n"
                  "\t/u  - View user profile\n"
                  "\tapp - View application(s), default is *\n"
                  "\tkey - View key(s), default is *" );
          throw help;
          }
        case 's':
          if ( type == file )
            throw IString( MSG1 "\n" SYNTAX );
          if ( type == user )
            throw IString( MSG2 "\n" SYNTAX );
          type = system;
          break;
        case 'u':
          if ( type == file )
            throw IString( MSG1 "\n" SYNTAX );
          if ( type == system )
            throw IString( MSG2 "\n" SYNTAX );
          type = user;
          break;
        case 'a':
          if ( app == "*" )
            app = token.subString(4);
          break;
        case 'k':
          if ( k == "*" )
            k = token.subString(4);
          break;
        default:
          {
          IString
            msg = "Syntax error; invalid option: ";
          msg += token[2];
          msg += "\n" SYNTAX;
          throw msg;
          }
        }
    else
      {
      if ( type == user || type == system )
        throw IString( MSG1 "\n" SYNTAX );

      if ( name ==  "" )
        name = token;
      }
    }
  }

ViewProfileArgs :: ~ViewProfileArgs ()
  {
  }

ViewProfileArgs::ProfileType ViewProfileArgs :: profileType () const
  {
  return this->type;
  }

IString ViewProfileArgs :: applicationName ( ) const
  {
  return this->app;
  }

IString ViewProfileArgs :: key ( ) const
  {
  return this->k;
  }

IString ViewProfileArgs :: profileName ( ) const
  {
  return this->name;
  }
