//************************************************************
// Container - Combined Tree and Details View
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <icnrobj.hpp>
#include  "treedetc.hpp"

DetailsTreeContainer ::  DetailsTreeContainer( unsigned long id,
                      IWindow*  parent,
                      IWindow*  owner)
    : IContainerControl (id, parent, owner),
      scrollBegun(false)
{
}


DetailsTreeContainer&  DetailsTreeContainer::setFont ( const IFont& fm )
{
   // If fontChangeStarted is true. we are being called because a
   // font has been dropped on the details view.  In this case we
   // just pass the setFont up the chain for processing

   if(!fontChangeStarted()) {
     if(isVisible())
       disableUpdate();
     if(detailsContainer().isVisible())
       detailsContainer().disableUpdate();
   }

   // Set the font of this window
   Inherited::setFont(fm);

   if(!fontChangeStarted()) {
     // Set the font of the details window
     detailsContainer().setFont(fm);
  
     // Turn visibility back on and refresh
     if(detailsContainer().isVisible()) {
       detailsContainer().enableUpdate();
       // Refresh the canvas
       detailsContainer().parent()->refresh();
     }

     if(isVisible()) {
       enableUpdate();
       parent()->refresh();
     }
   }
   return *this;
}

DetailsTreeContainer& DetailsTreeContainer :: addObject( 
                          const IContainerObject* newObject,
                          IContainerObject* parentObject)
{
  // Pass tree view request to the base class
  Inherited::addObject(newObject,  parentObject);

  // Handle the details view
  // If no parent add as last
  if(!parentObject) {
     detailsContainer().addObject(newObject);
     detailsContainer().expand((IContainerObject*)newObject);
  }
  else if (isExpanded(parentObject)){
     // We will defer an add request until the parent is expanded
     // If the parent is expanded, add after the last child of the parent
     IContainerControl::ObjectCursor childCursor(*this, parentObject);
     childCursor.setToLast();
     if (childCursor.isValid())
          detailsContainer().addObjectAfter(newObject,
                     detailsContainer().objectAt(childCursor));
     else
          detailsContainer().addObjectAfter(newObject, parentObject);
  }

  return *this;
}

DetailsTreeContainer& DetailsTreeContainer :: addObjectAfter( 
                          const IContainerObject* newObject,
                          const IContainerObject* afterObject,
                                IContainerObject* parentObject)
{
  Boolean addedToDetails = true;

  if(!parentObject)
    detailsContainer().addObjectAfter(newObject, afterObject);
  else if(isExpanded(parentObject))
    detailsContainer().addObjectAfter(newObject, afterObject);
  else
     addedToDetails = false;

  Inherited::addObjectAfter(newObject, afterObject, parentObject);
  return *this;
}

DetailsTreeContainer& DetailsTreeContainer :: removeObject( 
                          IContainerObject* object,
                          Boolean fAllContainers)
{
  Inherited::removeObject(object, fAllContainers);
  if(!fAllContainers && 
     detailsContainer().containsObject(object))
       detailsContainer().removeObject(object);
  return *this;
}

DetailsTreeContainer& DetailsTreeContainer :: removeObjectAt ( 
                        IContainerControl::ObjectCursor& cursor)
{
  Inherited::removeObjectAt(cursor);
  if (detailsContainer().containsObject(cursor.current()))
    detailsContainer().removeObjectAt(cursor);
  return *this;
}

DetailsTreeContainer& DetailsTreeContainer :: removeObjectAt ( 
                        IContainerControl::TextCursor& cursor)
{
  Inherited::removeObjectAt(cursor);
  if (detailsContainer().containsObject(cursor.current()))
    detailsContainer().removeObjectAt(cursor);
  return *this;
}

DetailsTreeContainer& DetailsTreeContainer :: removeSelectedObjects ( )
{
  // Note: we are Assuming that we are ONLY a tree view where just a
  // single object can be selected. 
  IContainerControl::ObjectCursor cursor(*this,
                                   IContainerObject::selected);
  // It is assumed that a selected object has been added to the details
  // view container.
  cursor.setToFirst();
  if(cursor.isValid()) {
    IContainerObject* pobj = objectAt(cursor);
    Inherited::removeSelectedObjects();
    detailsContainer().removeObject(pobj);
  }
  return *this;
}

DetailsTreeContainer& DetailsTreeContainer :: removeAllObjects ( )
{
  Inherited::removeAllObjects();
  detailsContainer().removeAllObjects();
  return *this;
}

