//************************************************************
// Direct Manipulation - List Box Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#define INCL_WIN
#define INCL_GPI
#include <os2.h>


#include <ilistbox.hpp>
#include <istring.hpp>
#include <ipoint.hpp>
#include <ifont.hpp>
#include <idmimage.hpp>
#include <idmevent.hpp>
#include <ihandle.hpp>
#include <itrace.hpp>

#include "lboxitem.hpp"
#include "operfix.hpp"

static const unsigned
  nil = 0xffffffffu;

ListBoxItem :: ListBoxItem ( IDMSourceOperation *srcOp,
                             IListBox           *srcLB,
                             unsigned            index )
  : IDMItem( srcOp,
             IDM::text,
             IDMItem:: moveable | IDMItem::copyable,
             none )
  {
  // Item contents is the list box item text.
  this -> setContents( srcLB->itemText( index ) );
  // Item object is the item index.
  this -> setObject( (void*)index );
  // Try to use rfText...
  IString
    name = this -> generateSourceName(),
    rfs   = rfForThisProcess();
  if ( name.length() )
    { // Text fits, use rfText.
    this -> setSourceName( name );
    rfs += IString( "," ) + IDM::rfText;
    }
  else
    { // Text doesn't fit, use rfSharedMem instead.
    rfs += IString( "," ) + IDM::rfSharedMem;
    this -> setRequiresPreparation();
    }
  // Set up RMFs; we support dropping on shredder, too.
  this -> setRMFs( rmfsFrom( IDM::rmLibrary, rfs ) );
  this -> addRMF( IDM::rmDiscard, IDM::rfUnknown );

  // Use text icon when dragged.
  ISystemPointerHandle
    icon( ISystemPointerHandle::text );
  IDMImage
    image( icon );
  this -> setImage( image );
  }  

ListBoxItem :: ListBoxItem ( const IDMItem::Handle &dragItem )
  : IDMItem( dragItem )
  {
  // We only support copy and move.
  this -> enableLink( false );
  }             

ListBoxItem :: ~ListBoxItem ( )
  {
  }

Boolean ListBoxItem :: generateSourceItems( IDMSourceOperation *srcOp )
  {
  Boolean
    result = false;
  IListBox
   *srcLB = (IListBox*)( srcOp->sourceWindow() );
  // Get index of dragged item:
  unsigned
    index = sourceIndex( srcLB, srcOp->position() );
  if ( index != nil )
    { // Not dragging from white space, add appropriate item:
    srcOp -> addItem( new ListBoxItem( srcOp, srcLB, index ) );
    srcOp -> setImageStyle( IDM::stack3AndFade );
    result = true;
    }
  return result;
  }

Boolean ListBoxItem :: targetDrop ( IDMTargetDropEvent &event )
  {
  IListBox
   *tgtLB = (IListBox*)( event.window() );

  // Turn off target emphasis:
  ListBoxItemProvider
   *provider = (ListBoxItemProvider*)( tgtLB->itemProvider() );
  provider -> drawEmphasis( tgtLB, TgtLocation( after, nil ) );

  // Calculate where dropped on:
  TgtLocation
    dropLoc = targetLocation( tgtLB, event.dropPosition() );
  // Add or replace, based on drop location:
  switch ( dropLoc.type )
    {
    case before:
      tgtLB -> add( dropLoc.index, contents() );
      break;
    case on:
      tgtLB -> setItemText( dropLoc.index, contents() );
      break;
    case after:
      tgtLB -> add( dropLoc.index + 1, contents() );
      break;
    }
  // If source and target are the same and item moved
  // forward, update source index.
  IDMTargetOperation::Handle
    tgtOp = IDMTargetOperation::targetOperation();
  if ( tgtOp->sourceWindow() == event.window()
       &&
       tgtOp->operation() == IDMOperation::move )
    {
    IDMItem::Handle
      srcItem = IDMItem::sourceItemFor( tgtOp->item( 1 ) );
    unsigned
      srcIndex = (unsigned)( srcItem->object() );
    if ( dropLoc.type != on 
         && 
         dropLoc.index < srcIndex )
      srcItem->setObject( (void*)( srcIndex + 1 ) );
    }

  return true;
  }

Boolean ListBoxItem :: sourceEnd ( IDMSourceEndEvent &event )
  {
  // If move completed OK (and not to shredder),
  // delete source item.
  if ( event.wasTargetSuccessful()
       &&
       (unsigned long)( object() ) != nil
       &&
       OperFix::dropOperation( event ) != IDMOperation::copy )
    {
    unsigned
      index = (unsigned)( this->object() );
    ( (IListBox*)( event.window() ) ) -> remove( index );
    }
  return true;
  }

Boolean ListBoxItem :: sourceDiscard ( IDMSourceDiscardEvent &event )
  {
  IListBox
   *srcLB = (IListBox*)( event.window() );

  // Get index of dragged item back out.
  unsigned
    index = (unsigned)( this->object() );

  // Delete that item.
  srcLB->remove( index );

  // Mark deleted so sourceEnd doesn't delete it again.
  setObject( (void*)nil );

  return true;
  }

unsigned ListBoxItem :: sourceIndex ( IListBox *pLB, 
                                      const IPoint &pt ) 
  {
  // If there are no items, indicate no match.
  if ( pLB->isEmpty() )
    return nil;

  // Calculate index of dragged item:
  unsigned
    dy = pLB->rect().height() - pt.y(),
    i  = itemHeight(pLB),
    row = dy / i,
    index = pLB->top() + row;

  // If off end, indicate that.
  if ( index >= pLB->count() )
    index = nil;

  return index;
  }

ListBoxItem::TgtLocation
  ListBoxItem :: targetLocation ( IListBox *pLB, const IPoint &pt )
  {
  // Target position is in desktiop coordinates.
  // We must map this to listbox window coordinates.
  IPoint
    lbPt = IWindow::mapPoint( pt,
                              IWindow::desktopWindow()->handle(),
                              pLB->handle() );
  // Get index of target item:
  unsigned
    index = sourceIndex( pLB, lbPt );
  LocType
    type = on;
  if ( index != nil )
    { // Drop at item, see if before or after:
    unsigned
      dy  = pLB->rect().height() - lbPt.y(),
      i   = itemHeight(pLB),
      rem = dy % i;
    if ( rem < i/4 )
      type = before;
    else if ( rem > 3*i/4 )
      type = after;
    }
  else
    { // Drop off end.
    type = after;
    index = pLB->count() - 1;
    }
  return TgtLocation( type, index );
  }

unsigned ListBoxItem :: itemHeight( IListBox *pLB )
  {
  // Get item height presuming standard usage
  // based on current font.  Note that this is 
  // may be wrong if the listbox is owner-draw
  // or somebody has called setHeight().
  IFont
    font( pLB );
  unsigned 
    result = font.maxCharHeight() + font.externalLeading();
  // Don't return 0 since that would cause divide-by-zero error.
  if ( !result )
    result++;
  return result;
  }

ListBoxItem::TgtLocation :: TgtLocation ( LocType type, 
                                          unsigned index )
  : type( type ),
    index( index )
  {
  }

Boolean ListBoxItem::TgtLocation :: 
  operator == ( const TgtLocation &loc ) const
  {
  if ( index == loc.index )
    return type == loc.type;
  else if ( index == loc.index-1 )
    return ( type == after && loc.type == before );
  else if ( index == loc.index+1 )
    return ( type == before && loc.type == after );
  else
    return false;
  }

ListBoxItemProvider :: ListBoxItemProvider ( IListBox *listBox )
  {
  if ( listBox )
    this -> provideItemsFor( listBox );
  }

ListBoxItemProvider 
 &ListBoxItemProvider :: provideItemsFor( IListBox *listBox )
  {
  listBox -> setItemProvider( this );
  return *this;
  }      

typedef ListBoxItem::TgtLocation TgtLocation;

static TgtLocation
  lastTarget( ListBoxItem::after, nil );

static void draw ( IPresSpaceHandle hps,
                   IListBox *lb, 
                   const TgtLocation &target )
  {
  if ( target.index != nil )
    {
    // First, get offset from top of listbox:
    unsigned
      offset = target.index - lb->top() + 1,
      height = ListBoxItem::itemHeight( lb );
    // Next, adjust if before this item:
    if ( target.type == ListBoxItem::before )
      offset--;
    // Calculate that item's rectangle's bottom:
    unsigned
      bottom = lb->rect().height() - height * offset;
    // Lower 2 pels 'cause it looks better!
    bottom -= 2;
    // Draw line or box:
    IPoint
      origin( 0, bottom );
    if ( target.type == ListBoxItem::on )
      {
      IPoint
        topRight( lb->rect().width(), bottom + height );
      origin += 1;
      topRight -= IPoint( WinQuerySysValue( HWND_DESKTOP,
                                            SV_CXVSCROLL ) + 1, 1 );
      GpiMove( hps, PPOINTL( &origin ) );
      GpiBox( hps, DRO_OUTLINE, PPOINTL( &topRight ), 0, 0 );
      }
    else
      {
      IPoint
        end( lb->rect().width(), bottom );
      GpiMove( hps, PPOINTL( &origin ) );
      GpiLine( hps, PPOINTL( &end ) );
      }
    }
  }

ListBoxItemProvider 
 &ListBoxItemProvider :: drawEmphasis ( IListBox *listBox, 
                                        const TgtLocation &target ) 
  {
  // If same target, then it's already drawn.
  if ( target == lastTarget )
    return *this;

  // Get presentation space and make it mode INVERT.
  IPresSpaceHandle
    hps = DrgGetPS( listBox->handle() );
  GpiSetMix( hps, FM_INVERT );

  // "Undraw" current target emphasis:
  draw( hps, listBox, lastTarget );

  // Set new target and draw it.
  lastTarget = target;
  draw( hps, listBox, lastTarget );

  DrgReleasePS( hps );
  return *this;
  }

Boolean ListBoxItemProvider ::
  provideLeaveSupport ( IDMTargetLeaveEvent &event )
  {
  IListBox
   *listBox = (IListBox*)( event.window() );
  this -> drawEmphasis( listBox, 
                        TgtLocation( ListBoxItem::after, nil ) );
  return false;
  }

Boolean ListBoxItemProvider :: 
  provideEnterSupport ( IDMTargetEnterEvent &event )
  {
  // Get default dragover result:
  Inherited::provideEnterSupport( event );

  IDMTargetOperation::Handle
    tgtOp = IDMTargetOperation::targetOperation();

  IListBox
   *lb = (IListBox*)( event.window() );

  ListBoxItem::TgtLocation
    tgtLocation 
      = ListBoxItem::targetLocation( lb, event.position() );

  if ( event.dropIndicator() == IDM::ok 
       &&
       tgtOp->sourceWindow() == event.window() )
    { // Source==target, prohibit dropping on same item.
    IDMItem::Handle
      srcItem = IDMItem::sourceItemFor( tgtOp->item( 1 ) );
    unsigned
      srcIndex = (unsigned)( srcItem->object() );

    // Disable conflicting drop on source window:
    unsigned long
      op = tgtOp->operation();
    if ( op == IDMOperation::drag )
      op = IDMOperation::move; // Default;
    if ( op == IDMOperation::copy )
      { // Can't copy to self.
      if ( srcIndex == tgtLocation.index
           &&
           tgtLocation.type == ListBoxItem::on )
        event.setDropIndicator( IDM::notOk );
      }
    else if ( op == IDMOperation::move )
      { // No sense moving to same place.
      if ( srcIndex == tgtLocation.index 
           ||
           ( tgtLocation.type == ListBoxItem::before
             &&
             srcIndex == tgtLocation.index - 1 )
           ||
           ( tgtLocation.type == ListBoxItem::after
             &&
             srcIndex == tgtLocation.index + 1 ) )
        event.setDropIndicator( IDM::notOk );
      }
    }

  // Draw target emphasis:
  drawEmphasis( lb, tgtLocation );

  return true;
  }

ListBoxItemProvider *ListBoxItemProvider :: operator & ()
  {
  return this;
  }
