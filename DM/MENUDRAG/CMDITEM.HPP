#ifndef _CMDITEM_
#define _CMDITEM_
//************************************************************
// Direct Manipulation - Menu Drag Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************

#include <icmdhdr.hpp>
#include <idmitem.hpp>
#include <idmevent.hpp>
#include <istattxt.hpp>
#include <idmsrch.hpp>

class IString;

class CommandItem : public IDMItem {
public:
  CommandItem ( const IDMItem::Handle &item )
    : IDMItem( item ),
      noDismiss(false)
    {
    }
  // Construct IDMItem with type=any, operations=linkable...
  CommandItem ( IDMSourceOperation *srcOp );

static Boolean
  generateSourceItems ( IDMSourceOperation *srcOp );

virtual Boolean
  targetDrop ( IDMTargetDropEvent &event ),
  sourceEnd        ( IDMSourceEndEvent & );

virtual unsigned long
  supportedOperationsFor( const IString &selectedRMF ) const;
private:
Boolean
 noDismiss;
};

class CmdHandler : public ICommandHandler {
public:
  CmdHandler ( IStaticText &txt )
    : text( txt ) { }

virtual Boolean
  command ( ICommandEvent &event );

private:
IStaticText
 &text;
Boolean
 noDismiss;
CmdHandler (const CmdHandler&);
CmdHandler operator=(const CmdHandler&);
};
#endif // _CMDITEM_
