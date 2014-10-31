#ifndef _HELPWIN2_
#define _HELPWIN2_
/*************************************************************/
/* Special-topic help program.                               */
/*                                                           */
/* Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.       */
/* All Rights Reserved.                                      */
/*************************************************************/
#include <icnrobj.hpp>
#include <idmprov.hpp>
#include <ientryfd.hpp>
#include <iframe.hpp>
#include <ihelphdr.hpp>
#include <imcelcv.hpp>
#include <inotebk.hpp>
#include <ipagehdr.hpp>
#include <ititle.hpp>
#include <istattxt.hpp>
#include "helpwin2.h"

class CnrObject : public IContainerObject {
public:
virtual void
  handleOpen ( IContainerControl* container );
virtual unsigned long
  helpId     ( ) const;
};

class CnrDragHelpProvider
        : public IDMItemProviderFor< IDMCnrItem > {
public:
virtual Boolean
  provideHelpFor ( IDMTargetHelpEvent& event );
};

class NotebookTabHelpHdr : public IPageHandler {
protected:
virtual Boolean
  help ( IPageHelpEvent& event );
};

class DynamicPageHelpHdr : public IHelpHandler {
protected:
virtual Boolean
  handleError     ( IHelpErrorEvent& event ),
  subitemNotFound ( IHelpSubitemNotFoundEvent& event );
};

class ObjectView : public IFrameWindow {
public:
  ObjectView ( unsigned long id,
               IWindow* parent = 0,
               IWindow* owner = 0 );
private:
// Disallow copy and assignment.
ObjectView ( const ObjectView& );
ObjectView& operator= ( const ObjectView& );

INotebook
  notebook;
NotebookTabHelpHdr
  tabHelpHdr;
DynamicPageHelpHdr
  dynamicPageHelpHdr;
IMultiCellCanvas
  page1;
IStaticText
  heading1,
  prompt1,
  prompt2,
  prompt3;
IEntryField
  entry1,
  entry2,
  entry3;
IMultiCellCanvas
  page2;
IStaticText
  headingA,
  promptA,
  promptB,
  promptC;
IEntryField
  entryA,
  entryB,
  entryC;
IFrameWindow
  page3;
IMultiCellCanvas
  page3a;
IStaticText
  headingX,
  promptX,
  promptY;
IEntryField
  entryX,
  entryY;
IFrameWindow
  dialog;
};

#endif // _HELPWIN2_
