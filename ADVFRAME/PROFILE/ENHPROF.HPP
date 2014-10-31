#ifndef _ENHPROF_
#define _ENHPROF_
//************************************************************
// Advanced Frame - Profile Viewer Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <istring.hpp>
#include <iprofile.hpp>

class ostream;

class EnhancedProfile : public IProfile {
public:
  EnhancedProfile ( const IString &name, 
                    Boolean createIfNotFound = false );
  EnhancedProfile ( const IProfile &profile );

virtual void
  displayOn ( ostream &aStream, 
              const IString &apps,
              const IString &keys ) const;

EnhancedProfile
 &open ( );

protected:
static IString
  validate ( const IString &name, 
             Boolean createIfNotFound );
};


class ProfileApplication : public IVBase {
public:
  ProfileApplication ( const IProfile &profile, 
                       const IString &name );
  ~ProfileApplication ( );

virtual IString
  name ( ) const;

virtual IProfile
  profile ( ) const;

virtual void
  displayOn ( ostream &aStream, 
              const IString &keys ) const;

private: 
IProfile
  prof;
IString
  nm;
};


class ProfileKey : public IVBase {
public:
  ProfileKey ( const ProfileApplication &profApp, 
               const IString &name );
  ~ProfileKey ( );

virtual IString
  name      ( ) const,
  value     ( ) const,
  formatted ( unsigned tabs = 0 ) const;

virtual ProfileApplication
  application ( ) const;

virtual void
  displayOn ( ostream &aStream ) const;

private: 
ProfileApplication
  app;
IString
  nm;
}; 

#endif // _ENHPROF_
