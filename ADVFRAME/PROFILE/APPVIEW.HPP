#ifndef _APPVIEW_
#define _APPVIEW_
//************************************************************
// Advanced Frame - Profile Viewer Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <icnrhdr.hpp>
#include "profobj.hpp"
#include "enhprof.hpp"

class ProfileAppObject : public ProfileObject {
public:
  ProfileAppObject ( EnhancedProfile   &profile,
                     const IString     &appName,
                     IContainerControl *cnr );
virtual ProfileObjectView
 *newView ( );
virtual ProfileApplication
 &application ( );
private:
ProfileApplication
  app;
};

class ApplicationView : public ProfileObjectView {
public:
  ApplicationView ( ProfileAppObject &appObj );
protected:
virtual ApplicationView
 &populate ( );
static IContainerControl
 *clientWindow ( );
private:
ICnrHandler
  handler;
ProfileAppObject
 &appObj;
ApplicationView(const ApplicationView&);
ApplicationView operator=(const ApplicationView&);
};

#endif // _APPVIEW_
