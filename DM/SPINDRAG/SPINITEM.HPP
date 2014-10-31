#ifndef _SPINITEM_
#define _SPINITEM_
//************************************************************
// Direct Manipulation - Spin Button Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************

#include <idmitem.hpp>
#include <idmevent.hpp>
#include <idmoper.hpp>

class SpinButtonItem : public IDMItem {
public:
  SpinButtonItem ( const IDMItem::Handle &item )
    // Simply "inherit" IDMItem constructor...
    : IDMItem( item ) { }
  SpinButtonItem ( IDMSourceOperation *srcOp );

static Boolean
  generateSourceItems ( IDMSourceOperation *srcOp );

virtual Boolean
  targetDrop ( IDMTargetDropEvent &event );

virtual unsigned long
  supportedOperationsFor ( const IString &selectedRMF ) const;

};

#endif // _SPINITEM_
