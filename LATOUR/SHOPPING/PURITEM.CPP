//************************************************************
// Tour of the UICL - Shopping List Example Program
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#define INCL_WINWORKPLACE   // For WinLoadFileIcon, WinFreeFileIcon.
#include <os2.h>

#include <icnrctl.hpp>
#include <iexcept.hpp>
#include <ihandle.hpp>

#include "puritem.hpp"
#include "puritemv.hpp"
#include "shopping.h"


//======================= PurchaseItem ========================

PurchaseItem :: PurchaseItem ( const IString& name,
                               const IString& quantity,
                               const IString& manufacturer,
                               double price,
                               const IString& notes )
  : IContainerObject( name,
                      ISystemPointerHandle
                        ( ISystemPointerHandle::question )),
    clManufacturer( manufacturer ),
    clNotes( notes ),
    clQuantity( quantity ),
    clPrice( price )
{
  IASSERTPARM( name != IString() );
}

PurchaseItem :: PurchaseItem ( const PurchaseItem& purchaseItem )
  : IContainerObject( (const IContainerObject&)purchaseItem ),
    clManufacturer( purchaseItem.manufacturer() ),
    clNotes( purchaseItem.notes() ),
    clQuantity( purchaseItem.quantity() ),
    clPrice( purchaseItem.price() )
{        // Copy constructor for drag and drop.
}

PurchaseItem :: ~PurchaseItem ( )
{
  if (clIconFile != IString())
  {                          // Previous icon file.
     WinFreeFileIcon( icon() );
  }
}

PurchaseItem& PurchaseItem :: setName ( const IString& name )
{
  IASSERTPARM( name != IString() );
  setIconText( name );
  return *this;
}

PurchaseItem&
  PurchaseItem :: addNotes ( const IString& moreNotes )
{
  if (clNotes.length())
  {
     clNotes += "\r\n";
  }
  clNotes += moreNotes;
  return *this;
}

PurchaseItem&
  PurchaseItem :: setIconFile ( const IString& fileName )
{
  if (clIconFile != IString())
  {                          // Previous icon file.
     WinFreeFileIcon( icon() );
       // Should overload setIcon to do this also, since
       // this pointer handle may not from WinLoadFileIcon.
  }

  IPointerHandle icon;
  clIconFile = fileName;
  if (fileName != IString())
  {                          // Use specified file.
     icon = WinLoadFileIcon( fileName, false );
     if (!icon)              // No icon found.
     {                       // Reset to default icon.
        icon =
          ISystemPointerHandle( ISystemPointerHandle::question );
        clIconFile = IString();
     }
     this->setIcon( icon );
  }
  return *this;
}

PurchaseItem&
  PurchaseItem :: setManufacturer
                     ( const IString& manufacturer )
{
  clManufacturer = manufacturer;
  return *this;
}

PurchaseItem&
  PurchaseItem :: setQuantity ( const IString& quantity )
{
  clQuantity = quantity;
  return *this;
}

PurchaseItem& PurchaseItem :: setPrice ( double price )
{
  clPrice = price;
  return *this;
}

PurchaseItem& PurchaseItem :: setNotes ( const IString& notes )
{
  clNotes = notes;
  return *this;
}

IString PurchaseItem :: name ( ) const
{
  return this->iconText();
}

IString PurchaseItem :: manufacturer ( ) const
{
  return clManufacturer;
}

IString PurchaseItem :: quantity ( ) const
{
  return clQuantity;
}

IString PurchaseItem :: notes ( ) const
{
  return clNotes;
}

IString PurchaseItem :: iconFile ( ) const
{
  return clIconFile;
}

double PurchaseItem :: price ( ) const
{
  return clPrice;
}

void
  PurchaseItem :: handleOpen ( IContainerControl* container )
{
  // User has opened a PurchaseItem object.
  // Create a secondary window with a settings view.
  PurchaseItemView* secondary =
    new PurchaseItemView( *this,
                          ID_PURCHASEITEMVIEW,
                          container->parent() );
  secondary->setAutoDeleteObject();
  (*secondary)
   .setFocus()
   .show();
  this->IContainerObject::handleOpen( container );
}

IContainerObject* PurchaseItem :: objectCopy ( )
{
  // Copy the object, for copy via drag and drop.
  PurchaseItem *copy = new PurchaseItem( *this );
  return (IContainerObject *)copy;
}
