//************************************************************
// Container - Combined Tree and Details View
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
extern "C" {
   #define INCL_WINWINDOWMGR
   #define INCL_WINSYS
   #define INCL_WINSTDCNR
   #define INCL_WINMENUS
   #include <os2.h>
}

#include <ifont.hpp>
#include <itrace.hpp>
#include <icolor.hpp>
#include <icnrolst.hpp>
#include "treedetc.hpp"
#include "treedeth.hpp"


DetailsTreeHandler :: DetailsTreeHandler ( DetailsTreeContainer* tree)
                           : treeCnr(tree)
{
  handleEventsFor(tree);
  handleEventsFor(&(tree->detailsContainer()));
 
}



Boolean DetailsTreeHandler :: dispatchHandlerEvent ( IEvent& evt)
{
  if(evt.eventId() == WM_PRESPARAMCHANGED)
  {
     if(evt.parameter1() == PP_FONTNAMESIZE ||
        evt.parameter1() == PP_FONTHANDLE)
        return fontChanged(evt);
  }
  return Inherited::dispatchHandlerEvent(evt);
}


Boolean DetailsTreeHandler :: treeCollapsed(IContainerObject* collapsedObject, IContainerControl* container)
{
  // On collapse, remove the coresponding objects in the
  // details view (we'd really like to hide the objects in
  // the details view, but hiding or filtering objects in the
  // details view, resets the container to the top).
  IContainerObject* pobj =0 ;
  ICnrObjectSet childObjects = container->descendentsOf(collapsedObject);
  if(childObjects.numberOfElements() > 0)
  {
    treeCnr->detailsContainer().disableUpdate();

    ICnrObjectSet::Cursor cursor(childObjects);
    for(cursor.setToFirst(); cursor.isValid(); cursor.setToNext()) {
       pobj = childObjects.elementAt(cursor);
       if(treeCnr->detailsContainer().containsObject(pobj))
         treeCnr->detailsContainer().removeObject(pobj);
    }
    treeCnr->detailsContainer().enableUpdate();
    collapsedObject->refresh(&(treeCnr->detailsContainer()));
  } 
  return true;
}

Boolean DetailsTreeHandler :: treeExpanded(IContainerObject* expandedObject, 
                                           IContainerControl* )
{
  IFUNCTRACE_DEVELOP();
  IContainerObject* lastObject = expandedObject;
  IContainerObject* currentObject;
  Boolean needsRefresh = false;

  // On expand, add the coresponding objects to the
  // details view (or show them if already there)

  IContainerControl::ObjectCursor cursor(*treeCnr, expandedObject, true);
  cursor.setToFirst();
  if (cursor.isValid()) {
     treeCnr->detailsContainer().disableUpdate();
     needsRefresh = true;
  } 

  for(; cursor.isValid(); cursor.setToNext()) {
     currentObject = treeCnr->objectAt(cursor);
     if(treeCnr->isExpanded(treeCnr->parentObject(currentObject))) {
       if(treeCnr->detailsContainer().containsObject(currentObject))
          treeCnr->detailsContainer().showObject(currentObject);
       else {
         treeCnr->detailsContainer().addObjectAfter(currentObject, lastObject);
       }
       lastObject = currentObject;
     }
  }
  if (needsRefresh) {
     treeCnr->detailsContainer().enableUpdate();
     expandedObject->refresh(&(treeCnr->detailsContainer()));
  }
  return true;

}


Boolean DetailsTreeHandler :: inuseChanged(ICnrEmphasisEvent& evt)
{
  IFUNCTRACE_DEVELOP();
  // Not currently implemented
  return true;
}

Boolean DetailsTreeHandler :: cursoredChanged(ICnrEmphasisEvent& evt)
{
  IFUNCTRACE_DEVELOP();
  IContainerControl* thisContainer = (IContainerControl*)evt.controlWindow();
  IContainerControl* otherContainer;

  if(thisContainer==treeCnr)
    otherContainer = &(treeCnr->detailsContainer());
  else
    otherContainer = treeCnr;

 
  Boolean fAcquired;
  try {
     fAcquired = thisContainer->isCursored(evt.object());
     if(fAcquired) {
       if (!treeCnr->cursorMoveStarted()) {
         treeCnr->setCursorMoveStarted();
         try {
           otherContainer->setCursor(evt.object());
         } catch (IException&) {}
       }
       else
         treeCnr->setCursorMoveStarted(false);
     }
  } 
  catch(IException&) {}

  return true;
}


Boolean DetailsTreeHandler :: windowScrolled(ICnrScrollEvent& evt)
{
  IFUNCTRACE_DEVELOP();
  IContainerControl* thisContainer = (IContainerControl*)evt.controlWindow();
  IContainerControl* otherContainer;

  if(thisContainer==treeCnr) {
    ITRACE_DEVELOP("Tree scrolled");
    otherContainer = &(treeCnr->detailsContainer());
  }
  else {
    ITRACE_DEVELOP("Details scrolled");
    otherContainer = treeCnr;
  }

  // Only worry about Vertical Scroll - scroll the Tree View the
  // same amount.
  if(evt.isVertical()) {
     if (!treeCnr->scrollStarted()) {
       treeCnr->setScrollStarted(true);
       otherContainer->scrollVertically(evt.amount());
       ITRACE_DEVELOP(IString("Scrolled  vertically(")+IString(evt.amount()));
     }
     else
       treeCnr->setScrollStarted(false);
  }
  return true;
}

Boolean DetailsTreeHandler :: fontChanged(IEvent& evt)
{
  IFUNCTRACE_DEVELOP();
  IContainerControl* thisContainer = (IContainerControl*)evt.window();
  IContainerControl* otherContainer;

  if(thisContainer==treeCnr) {
    otherContainer = &(treeCnr->detailsContainer());
  }
  else {
    otherContainer = treeCnr;
  }


  // We need to keep track of the top level entry to this    
  // function so that we avoid a ping-pong affect that could 
  // occur between the two containers on font a change. This 
  // works since the font change notification is WinSent.    
  Boolean fNested = treeCnr->fontChangeStarted();
  treeCnr->setFontChangeStarted(true);


  if(!fNested) {
       IFont newFont(thisContainer);
       otherContainer->setFont(newFont);
       treeCnr->setFontChangeStarted(false);
  }
  return false;
}


