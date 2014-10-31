#ifndef _PROFOBJ_
#define _PROFOBJ_
//************************************************************
// Advanced Frame - Profile Viewer Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <icnrctl.hpp>
#include <ititle.hpp>

class IString;
class ProfileObjectView;

class ProfileObject : public IContainerObject {
public:
  ProfileObject ( const IString     &name,
                  unsigned long      iconId,
                  IContainerControl *cnr );
virtual void
  handleOpen( IContainerControl *cnr );
virtual ProfileObjectView
 &view ( );
virtual ProfileObject
 &viewClosed ( );
virtual IContainerControl
 *container ( ) const;
protected:
virtual ProfileObjectView
 *newView ( ) = 0;
private:
IContainerControl
 *objCnr;
ProfileObjectView
 *objView;
};

class ProfileObjectView : protected IFrameWindow {
public:
virtual ProfileObjectView
 &open ( );
protected:
  ProfileObjectView ( IWindow       *client,
                      ProfileObject &object,
                      const IString &viewName );
  ~ProfileObjectView ( );
protected:
ProfileObject
 *object ( ) const;
private:
ITitle
  viewTitle;
ProfileObject
 *viewObj;
ProfileObjectView ( const ProfileObjectView&);
ProfileObjectView& operator=( const ProfileObjectView&);
};

#endif // _PROFOBJ_
