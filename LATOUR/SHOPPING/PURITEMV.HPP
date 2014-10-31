#ifndef _PURITEMV_
#define _PURITEMV_
//************************************************************
// Tour of the UIL - Shopping List Example Program
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <icmdhdr.hpp>
#include <ientryfd.hpp>
#include <ifiledlg.hpp>
#include <ifilehdr.hpp>
#include <iframe.hpp>
#include <ikeyhdr.hpp>
#include <imcelcv.hpp>
#include <imle.hpp>
#include <inotebk.hpp>
#include <iselhdr.hpp>
#include <istattxt.hpp>
#include <istring.hpp>
#include <ivport.hpp>
#include "puritem.hpp"
#include "shopping.h"

// Align classes on four-byte boundaries.
#pragma pack(4)

//==================== PurchaseItemView =======================
// Settings view for a PurchaseItem object.
class PurchaseItemView : public IFrameWindow {
public:
  PurchaseItemView ( PurchaseItem& purchaseItem,
                     unsigned long windowId,
                     IWindow* owner = 0 );
 ~PurchaseItemView ( );

Boolean
  validated        ( );

PurchaseItemView
 &updateDataObject ( ),
 &updateIcon       ( const IString& fileName );

protected:
PurchaseItemView
 &initializePage1  ( ),
 &initializePage2  ( );

private:
  PurchaseItemView ( const PurchaseItemView& );
PurchaseItemView
 &operator=        ( const PurchaseItemView& );

  //======================== SaveHdr ==========================
  // Process command actions for a PurchaseItem.
  class SaveHdr : public ICommandHandler {
  public:
    SaveHdr       ( PurchaseItemView* view );
  protected:
  virtual Boolean
    systemCommand ( ICommandEvent& event );
  };  // class PurchaseItemView::SaveHdr

  //=================== IgnoreEscEnterHdr =====================
  // Prevent Esc and Enter from closing the file dialog.
  class IgnoreEscEnterHdr : public IKeyboardHandler {
  protected:
  virtual Boolean
    virtualKeyPress ( IKeyboardEvent& event );
  };  // class PurchaseItemView::IgnoreEscEnterHdr

  //=================== DeferAccelerators =====================
  // Prevent Alt+F4 from closing the file dialog.
  class DeferAccelerators : public IHandler {
  protected:
  virtual Boolean
    dispatchHandlerEvent ( IEvent& event );
  };  // class PurchaseItemView::DeferAccelerators

  //===================== SelectFileHdr =======================
  // Get notified each time user selects a file.
  class SelectFileHdr : public ISelectHandler {
  public:
    SelectFileHdr ( PurchaseItemView* view );
  protected:
  virtual Boolean
    selected      ( IControlEvent& event ),
    enter         ( IControlEvent& event );
  private:
  PurchaseItemView
   *clView;
  };  // class PurchaseItemView::SelectFileHdr

PurchaseItem
 &clPurchaseItem;
SaveHdr
  clSaveHdr;
IgnoreEscEnterHdr
  clIgnoreEscEnterHdr;
DeferAccelerators
  clDeferAccelerators;
SelectFileHdr
  clSelectFileHdr;

INotebook
  clNotebook;
IMultiCellCanvas
  clPage1;
IStaticText
  clNamePrompt;
IEntryField
  clName;
IStaticText
  clQuantityPrompt;
IEntryField
  clQuantity;
IStaticText
  clManufacturerPrompt;
IEntryField
  clManufacturer;
IStaticText
  clPricePrompt;
IEntryField
  clPrice;
IStaticText
  clNotesPrompt;
IMultiLineEdit
  clNotes;
IViewPort
  clPage2;
IFileDialog
 *clFileDlg;
};  // class PurchaseItemView

// Resume default compiler packing.
#pragma pack()

#endif // _PURITEMV_
