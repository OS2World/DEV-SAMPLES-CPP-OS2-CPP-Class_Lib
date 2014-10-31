//************************************************************
// Direct Manipulation - Menu Drag Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#define INCL_WINMENUS
#define INCL_WINWINDOWMGR
#define INCL_WININPUT
#include <os2.h>

#include <istring.hpp>
#include <idmitem.hpp>
#include <idmprov.hpp>
#include <idmimage.hpp>
#include <isubmenu.hpp>
#include <ipushbut.hpp>
#include <istattxt.hpp>
#include <itrace.hpp>
#include <irect.hpp>
#include <idmsrch.hpp>
#include "cmditem.hpp"



// Construct IDMItem with type=any, operations=copyable...
CommandItem::CommandItem ( IDMSourceOperation *srcOp )
    : IDMItem( srcOp, IDM::any, IDMItem::linkable ),
      noDismiss(false)
   {
    IFUNCTRACE_DEVELOP();
    // Support only special "menu" rmf...
    this -> addRMF( IDMItem::rmfFrom( IDM::rmLibrary,
                                      IDMItem::rfForThisProcess() ) );
    // Locate source menu item...
    IWindow
     *p = srcOp->sourceWindow();
    ISubmenu
      sub( p->handle() );
    ITRACE_DEVELOP( "submenu->" + IString( (unsigned long)p ) );
    ISubmenu::Cursor
      cursor( sub );
    IPoint
      pos = srcOp->position();
    ITRACE_DEVELOP( "Looking for item for " + pos.asString() );
    for( cursor.setToFirst(); cursor.isValid(); cursor.setToNext() )
      {
      IMenuItem
        item = sub.elementAt( cursor );
      IRectangle itemRect = sub.itemRect( item.id() );

      ITRACE_DEVELOP( "testing item->" + IString( item.id() ) );
      ITRACE_DEVELOP( "rectangle->" + itemRect.asString() );
      if ( itemRect.contains( srcOp->position() ) )
        {
        // Set object() pointer to menu id...
        ITRACE_DEVELOP( "Match!" );
        this -> setObject( (void*) item.id() );
        this -> setContents( item.text() );

        // Do not allow the menu to be dismissed.
        // Much thanks to Mark Benge for this fix to work
        // around the fact that PM really doesn't support
        // dragging from menu items.
        if (!item.isNoDismiss())
          {
          ITRACE_DEVELOP( "Setting no dismiss");
          item.setNoDismiss();
          sub.setItem( item );
          this->noDismiss = true;
          }
        sub.selectItem( item.id() );

        break;
        }
      }
    }

Boolean CommandItem::generateSourceItems ( IDMSourceOperation *srcOp )
    {
    IFUNCTRACE_DEVELOP();
    // Source item is object of this class...
    IDMItem::Handle
      item( new CommandItem( srcOp ) );
    // Set image...
    IDMImage
      image( IResourceId( IC_DEFAULT_FRAME_ID ) );
    item -> setImage( image );
    // Add it to the source operation...
    srcOp -> addItem( item );
    srcOp -> setImageStyle( IDM::allStacked );
    srcOp -> setOperation( IDMOperation::link );
    // Indicate an item is available to drag...
    return true;
    }

// Called by the source handler to allow the menu to be dismissed after the  
// target has indicated that the drop  processing has completed.             
Boolean CommandItem::sourceEnd ( IDMSourceEndEvent & )
{
  IFUNCTRACE_DEVELOP();
  IWindow *pWin = sourceOperation()->sourceWindow();
  ISubmenu sub( pWin->handle() );
  IMenuItem item = sub.menuItem( (unsigned long)object() );

  if (this->noDismiss)
  {
    ITRACE_DEVELOP( "Resetting no dismiss");
    item.setNoDismiss( false );
    sub.setItem( item );
    this->noDismiss = false;
  }

  pWin->sendEvent( MM_SELECTITEM,
                   IEventData((unsigned short)item.id(), true),
                   IEventData(0, true) );

  return( true );
}

Boolean CommandItem::targetDrop ( IDMTargetDropEvent &event )
    {
    IFUNCTRACE_DEVELOP();
    IPushButton
     *pb = (IPushButton*)( event.window() );
    WinSetWindowUShort( pb->handle(),
                        QWS_ID,
                        (unsigned short)(unsigned long)( this->object() ) );
    pb -> setText( this->contents() );
    pb -> enable();
    return true;
    }


unsigned long CommandItem::supportedOperationsFor( const IString &selectedRMF ) const
    {
    return IDMItem::linkable;
    }

Boolean CmdHandler::command ( ICommandEvent &event )
    {
    text.setText( IString( event.commandId() ) );
    return true;
    }
