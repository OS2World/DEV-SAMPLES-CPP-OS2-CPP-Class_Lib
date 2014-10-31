#ifndef _PARTLIST_
#define _PARTLIST_
//************************************************************
// Container - Combined Tree and Details View
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <ivbase.hpp>
#include <ihandler.hpp>
#include <iframe.hpp>

class IContainerControl;
class ISplitCanvas;
class IMultiCellCanvas;
class ISetCanvas;
class DetailsTreeContainer;
class DetailsTreeHandler;
class ColorChangeHandler;
class IStaticText;
class IScrollBar;

class PartsList : protected IFrameWindow {
public:

  PartsList ( );
 ~PartsList ( );

PartsList
 &open               ( );

ISplitCanvas
 &splitCanvas        ( );

IMultiCellCanvas
 &leftMultiCell      ( ),
 &rightMultiCell     ( );

IStaticText
 &treeScrollHide     ( );


DetailsTreeContainer
 &treeContainer      ( );

IContainerControl
 &detailsContainer   ( ),
 &otherContainer     ( const IContainerControl& opposite);

PartsList
 &loadObjects        ( );

PartsList
 &setColorChangeStarted ( Boolean changeStarted=true);

Boolean
 colorChangeStarted    ( ) const;

private:

ISplitCanvas
 *canvas;
IMultiCellCanvas
 *leftMCell,
 *rightMCell;
IStaticText
 *treeScrollHideWin;
IScrollBar
 *treeScroll;
DetailsTreeContainer
 *treeCnr;
IContainerControl
 *detailsCnr;
DetailsTreeHandler
 *treeHandler;
ColorChangeHandler
 *colorHandler;

Boolean
  colorChanged;
PartsList ( const PartsList& );
PartsList& operator= ( const PartsList& );
};

class ColorChangeHandler : public IHandler
{
public:
  ColorChangeHandler  (PartsList* partsList );

protected:
virtual Boolean
  dispatchHandlerEvent ( IEvent &evt );

virtual Boolean
  backgroundColorChanged  ( IEvent&       event);
private:
PartsList
 *partsList;
};



inline ISplitCanvas& PartsList :: splitCanvas ( )
{
  return *canvas;
}

inline DetailsTreeContainer& PartsList :: treeContainer ( )
{
  return *treeCnr;
}

inline IContainerControl& PartsList :: detailsContainer ( )
{
  return *detailsCnr;
}

inline IStaticText& PartsList :: treeScrollHide ( )
{
  return *treeScrollHideWin;
}

inline IMultiCellCanvas& PartsList :: leftMultiCell ( )
{
  return *leftMCell;
}

inline IMultiCellCanvas& PartsList :: rightMultiCell ( )
{
  return *rightMCell;
}


inline PartsList& PartsList :: setColorChangeStarted (Boolean colorChangeStarted)
{
  this->colorChanged = colorChangeStarted;
  return *this;
}

inline Boolean PartsList :: colorChangeStarted ( ) const
{
  return this->colorChanged;
}

#endif // _PARTLIST_
