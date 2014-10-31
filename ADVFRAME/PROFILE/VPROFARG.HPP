#ifndef _VPROFARG_
#define _VPROFARG_
//************************************************************
// Advanced Frame - Profile Viewer Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <ivbase.hpp>
#include <istring.hpp>

class ostream;

class ViewProfileArgs : public IVBase {
typedef IVBase
  Inherited;
public:
  ViewProfileArgs ( int argc, char *argv[] );
  ~ViewProfileArgs ( );

enum 
  ProfileType { none, system, user, file };

virtual ProfileType
  profileType ( ) const;

virtual IString
  applicationName ( ) const,
  key             ( ) const,
  profileName     ( ) const;

private: 
ProfileType
  type;
IString
  app,
  k,
  name;
}; // class ViewProfileArgs

#endif // _VPROFARG_
