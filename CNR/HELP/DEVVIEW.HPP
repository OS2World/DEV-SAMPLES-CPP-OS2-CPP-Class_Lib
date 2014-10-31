#ifndef _DEVVIEW_
#define _DEVVIEW_
//************************************************************
// Container Control - Help in the Container                    
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <icnrctl.hpp>
#include <icnrcol.hpp>
#include <icnrhdr.hpp>
#include <icnrehdr.hpp>
#include <istring.hpp>
#include <ihelp.hpp>

// Forward Declarations
class Developer;

class DeveloperView : public IFrameWindow
{
public:
   DeveloperView ( );

private:
IContainerControl
 cnrWin;
IContainerColumn
  nameColumn,
  addressColumn,
  ageColumn;

ICnrHandler
  cnrHandler;
ICnrEditHandler
  cnrEditHandler;
IHelpWindow
 helpWindow;
DeveloperView (const DeveloperView& );
DeveloperView& operator=(const DeveloperView& );
};

#endif // _DEVVIEW_
