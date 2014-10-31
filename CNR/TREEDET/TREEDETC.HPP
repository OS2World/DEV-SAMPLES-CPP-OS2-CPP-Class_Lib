#ifndef _TREEDETC_
#define _TREEDETC_
//************************************************************
// Container - Combined Tree and Details View
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <icnrctl.hpp>
#include <icnrobj.hpp>


class DetailsTreeContainer : public IContainerControl
{
typedef IContainerControl
  Inherited;

public:
  DetailsTreeContainer( unsigned long     id,
                      IWindow*          parent,
                      IWindow*          owner);

DetailsTreeContainer
 &setDetailsContainer (IContainerControl* container);

IContainerControl  
 &detailsContainer    ( );

virtual DetailsTreeContainer
 &setFont        (const IFont& fm );

virtual DetailsTreeContainer
 &addObject             ( const IContainerObject* newObject,
                                IContainerObject* parentObject = 0),
 &addObjectAfter        ( const IContainerObject* newObject,
                          const IContainerObject* afterObject,
                                IContainerObject* parentObject = 0),
  /* remove does not delete the object */
 &removeObject          ( IContainerObject* object,
                          Boolean fAllContainers = false),
 &removeObjectAt        ( IContainerControl::ObjectCursor& cursor),
 &removeObjectAt        ( IContainerControl::TextCursor& cursor),
 &removeSelectedObjects ( ),
 &removeAllObjects      ( );

protected:
DetailsTreeContainer
 &setScrollStarted      ( Boolean scrollBegun=true),
 &setCursorMoveStarted  ( Boolean cursorMoved=true),
 &setFontChangeStarted  ( Boolean changeStarted=true);

Boolean
 scrollStarted         ( ) const,
 cursorMoveStarted     ( ) const,
 fontChangeStarted     ( ) const;

private:
friend class DetailsTreeHandler;


IContainerControl
 *detailsCnr;
Boolean
  scrollBegun,
  cursorMoved,
  fontChanged;
DetailsTreeContainer( const DetailsTreeContainer&);
DetailsTreeContainer& operator=( const DetailsTreeContainer&);
};


inline DetailsTreeContainer& DetailsTreeContainer :: setDetailsContainer (
                                  IContainerControl* container)
{
  this->detailsCnr = container;
  return *this;
}

inline IContainerControl& DetailsTreeContainer :: detailsContainer ( )
{
  return *detailsCnr;
}

inline DetailsTreeContainer& DetailsTreeContainer :: setScrollStarted (Boolean scrollStarted)
{
  this->scrollBegun = scrollStarted;
  return *this;
}

inline Boolean DetailsTreeContainer :: scrollStarted ( ) const
{
  return this->scrollBegun;
}

inline DetailsTreeContainer& DetailsTreeContainer :: setCursorMoveStarted (Boolean cursorMoveStarted)
{
  this->cursorMoved = cursorMoveStarted;
  return *this;
}

inline Boolean DetailsTreeContainer :: cursorMoveStarted ( ) const
{
  return this->cursorMoved;
}

inline DetailsTreeContainer& DetailsTreeContainer :: setFontChangeStarted (Boolean fontChangeStarted)
{
  this->fontChanged = fontChangeStarted;
  return *this;
}

inline Boolean DetailsTreeContainer :: fontChangeStarted ( ) const
{
  return this->fontChanged;
}

#endif // _TREEDETC_
