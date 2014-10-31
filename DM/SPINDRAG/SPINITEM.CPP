//************************************************************
// Direct Manipulation - Spin Button Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <ispinbt.hpp>
#include <itrace.hpp>
#include "spinitem.hpp"


// Construct IDMItem with type=any, operations=copyable...
SpinButtonItem::SpinButtonItem ( IDMSourceOperation *srcOp )
      : IDMItem( srcOp, IDM::any, IDMItem::copyable )
  {
  // Support intra-process drag/drop only...
  this -> addRMF( IDMItem::rmfFrom( IDM::rmLibrary, 
                                    IDMItem::rfForThisProcess() ) );
  // Set item contents to source spin button text...
  ISpinButton
    *pSpin = (ISpinButton*)( srcOp->sourceWindow()->parent() );
  ITRACE_DEVELOP( pSpin->text() );
  this->setContents( pSpin->text() );
  }


Boolean SpinButtonItem::generateSourceItems ( IDMSourceOperation *srcOp )
  {
  // Source item is object of this class...
  IDMItem::Handle
    item( new SpinButtonItem( srcOp ) );
  // Add it to the source operation...
  srcOp -> addItem( item );
  // Indicate an item is available to drag...
  return true;
  }

Boolean SpinButtonItem::targetDrop ( IDMTargetDropEvent &event )
  {
  // Add dropped text to the spin button...
  ISpinButton
   *pSpin = (ISpinButton*)( event.window()->parent() );
  ISpinButton::Cursor
    cursor( *pSpin );
  pSpin -> addAsLast( this->contents(), cursor );
  pSpin -> spinTo( cursor );
  return true;
  }

unsigned long SpinButtonItem::supportedOperationsFor ( const IString &selectedRMF ) const 
  {
  // Permit copying only...
  return IDMItem::copyable;
  }

