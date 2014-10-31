//************************************************************
// Tour of the UICL - Shopping List Example Program
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#define INCL_WINSTDFILE   // For DID_xxx file dialog IDs.
#define INCL_WINFRAMEMGR  // For WM_TRANSLATEACCEL.
#include <os2.h>

#include <ifont.hpp>
#include <ilistbox.hpp>
#include <imsgbox.hpp>
#include <ireslib.hpp>
#include <isysmenu.hpp>
#include <ititle.hpp>

#include "puritem.hpp"
#include "puritemv.hpp"
#include "shopping.h"


//===================== PurchaseItemView ======================

PurchaseItemView :: PurchaseItemView
                         ( PurchaseItem& purchaseItem,
                           unsigned long windowId,
                           IWindow* owner )
  : IFrameWindow ( windowId, 0, owner, IRectangle(),
                   IFrameWindow::defaultStyle()
                    | IFrameWindow::dialogBackground ),
    clSaveHdr( this ),
    clPurchaseItem( purchaseItem ),
    clNotebook( ID_PURCHASEITEMBOOK, this, this ),
    clPage1( ID_PURCHASEITEMPAGE1, &clNotebook, &clNotebook ),
    clNamePrompt( ID_NAMEPROMPT, &clPage1, &clPage1 ),
    clName( ID_NAME, &clPage1, &clPage1 ),
    clQuantityPrompt( ID_QUANTITYPROMPT, &clPage1, &clPage1 ),
    clQuantity( ID_QUANTITY, &clPage1, &clPage1 ),
    clManufacturerPrompt( ID_MANUFACTURERPROMPT,
                          &clPage1, &clPage1 ),
    clManufacturer( ID_MANUFACTURER, &clPage1, &clPage1 ),
    clPricePrompt( ID_PRICEPROMPT, &clPage1, &clPage1 ),
    clPrice( ID_PRICE, &clPage1, &clPage1 ),
    clNotesPrompt( ID_NOTESPROMPT, &clPage1, &clPage1 ),
    clNotes( ID_NOTES, &clPage1, &clPage1, IRectangle(),
             IMultiLineEdit::classDefaultStyle
              | IMultiLineEdit::ignoreTab ),
    clPage2( ID_PURCHASEITEMPAGE2, &clNotebook, &clNotebook ),
    clSelectFileHdr( this )
{
  ITitle title( this, clPurchaseItem.name(),
                "Shopping List Settings View" );
  if (owner)
  {                     // Not a primary window.
     this->removeFromWindowList();  // Remove from switch list.
  }
  this->setClient( &clNotebook );

  IColor background =
    clNotebook.color( INotebook::notebookWindowBackground );
  clNotebook
   .setMinorTabSize( ISize( 0, 0 ) )
   .setBinding( INotebook::spiral )
   .setColor( INotebook::pageBackground, background )
   .setColor( INotebook::majorTabBackground, background );

  // Set up first page of the notebook.
  this->initializePage1();

  // Set up second page of the notebook.
  this->initializePage2();

  // Add the pages to the notebook.
  INotebook::PageSettings
    pageInfo( "1st", 0,
              INotebook::PageSettings::autoPageSize
               | INotebook::PageSettings::majorTab );
  clNotebook.addFirstPage( pageInfo, &clPage1 );
  pageInfo.setTabText( "2nd" );
  clNotebook.addLastPage( pageInfo, &clPage2 );

  // Size the frame window.
  IRectangle rectFrame =
    this->frameRectFor( IRectangle( IPoint( 0, 0 ),
                                    clNotebook.minimumSize() ));
  this->sizeTo( rectFrame.size() );
}

PurchaseItemView :: ~PurchaseItemView ( )
{
  delete clFileDlg;
}

PurchaseItemView& PurchaseItemView :: initializePage1 ( )
{
  // Locate controls on the multi-cell canvas.
  clPage1
   .addToCell( &clNamePrompt,         2, 2 )
   .addToCell( &clName,               4, 2 )
   .addToCell( &clQuantityPrompt,     2, 4 )
   .addToCell( &clQuantity,           4, 4 )
   .addToCell( &clManufacturerPrompt, 2, 6 )
   .addToCell( &clManufacturer,       4, 6 )
   .addToCell( &clPricePrompt,        2, 8 )
   .addToCell( &clPrice,              4, 8 )
   .addToCell( &clNotesPrompt,        2, 10 )
   .addToCell( &clNotes,              4, 10, 1, 2 );

  // Allow MLE control to expand vertically with the window.
  clPage1.setRowHeight( 11, 0, true );
  // Allow MLE and entry fields to expand horizontally.
  clPage1.setColumnWidth( 4, 0, true );
  // Create bottom and right margins.
  ISize defaultCell = IMultiCellCanvas::defaultCell();
  clPage1
   .setRowHeight( 12, defaultCell.height() )
   .setColumnWidth( 5, defaultCell.width() );

  // Set-up the child controls.
  clNamePrompt.setText( "Name" );
  clName
   .setText( clPurchaseItem.name() )
   .enableTabStop()
   .enableGroup();
  clQuantityPrompt.setText( "Quantity" );
  clQuantity
   .setText( clPurchaseItem.quantity() )
   .enableTabStop()
   .enableGroup();
  clManufacturerPrompt.setText( "Manufacturer" );
  clManufacturer
   .setText( clPurchaseItem.manufacturer() )
   .enableTabStop()
   .enableGroup();
  clPricePrompt.setText( "Price" );
  clPrice
   .setText( IString( clPurchaseItem.price() ))
   .enableTabStop()
   .enableGroup();
  clNotesPrompt.setText( "Notes" );
  clNotes
   .setText( clPurchaseItem.notes() )
   .enableTabStop()
   .enableGroup();
  ISize maxSize = IFont( &clNotes ).maxSize();
  clNotes.setMinimumSize( maxSize * 2 );

  // Establish the size of the notebook page window.
  clPage1.setLayoutDistorted( IWindow::immediateUpdate, 0 );
  clPage1.sizeTo( clPage1.minimumSize() );

  return *this;
}

PurchaseItemView& PurchaseItemView :: initializePage2 ( )
{
  // Set-up the file dialog as a child of the view port.
  IFileDialog::Settings settings;
  settings.setDialogTemplate( IResourceId( ID_FILEDIALOG ) );
  if (clPurchaseItem.iconFile() != IString())
  {
     settings.setFileName( clPurchaseItem.iconFile() );
  }
  clFileDlg =
     new IFileDialog( &clPage2, &clPage2, 0,
                      IFileDialog::modeless, settings );
  clIgnoreEscEnterHdr.handleEventsFor( clFileDlg );
  clDeferAccelerators.handleEventsFor( clFileDlg );
  clSelectFileHdr.handleEventsFor( clFileDlg );

  // Establish the size of the notebook page window.
  clPage2.sizeTo( clFileDlg->size() );

  return *this;
}

Boolean PurchaseItemView :: validated ( )
{
  Boolean valid = true;
  if (clName.text().strip() == IString())
  {
     IPageHandle page = clNotebook.firstPage();
     clNotebook.turnToPage( page );
     clName.setFocus();
     IMessageBox msg( this );
     msg.show( "You must specify a name.",
               IMessageBox::okButton
                | IMessageBox::errorIcon
                | IMessageBox::moveable );
     valid = false;
  }
  return valid;
}

PurchaseItemView& PurchaseItemView :: updateDataObject ( )
{
  clPurchaseItem
   .setName( clName.text().strip() )
   .setQuantity( clQuantity.text().strip() )
   .setManufacturer( clManufacturer.text().strip() )
   .setPrice( clPrice.text().asDouble() )
   .setNotes( clNotes.text().strip() )
   .setClosed();
  return *this;
}

PurchaseItemView&
  PurchaseItemView :: updateIcon ( const IString& fileName )
{
  if (fileName != IString())
  {
     clPurchaseItem.setIconFile( fileName );
  }
  return *this;
}

//================ PurchaseItemView::SaveHdr ==================

PurchaseItemView::SaveHdr :: SaveHdr ( PurchaseItemView* view )
{
  handleEventsFor( view );
}

Boolean PurchaseItemView::SaveHdr :: systemCommand
                                       ( ICommandEvent& event )
{
  Boolean stopProcessing = false;
  PurchaseItemView* view = (PurchaseItemView*)(event.window());
  if (event.commandId() == ISystemMenu::idClose)  // SC_CLOSE
  {                // View is being closed.
     if (view->validated())
     {             // Save any changes.
        view->updateDataObject();
     }
     else
     {             // Error, don't close the window.
        stopProcessing = true;
     }
  }
  return stopProcessing;
}

//=========== PurchaseItemView::IgnoreEscEnterHdr =============

Boolean PurchaseItemView::IgnoreEscEnterHdr :: virtualKeyPress
                                      ( IKeyboardEvent& event )
{
  Boolean dontPassOn = false;
  if (!(event.isAltDown()  ||  event.isCtrlDown()  ||
        event.isShiftDown())  &&
      (event.virtualKey() == IKeyboardEvent::esc ||
       event.virtualKey() == IKeyboardEvent::enter ||
       event.virtualKey() == IKeyboardEvent::newLine))
  {                // Esc or Enter key pressed.
     event.setResult( true );
     dontPassOn = true;  // Don't let the file dialog get it.
  }
  return dontPassOn;
}

//=========== PurchaseItemView::DeferAccelerators =============

Boolean
  PurchaseItemView::DeferAccelerators :: dispatchHandlerEvent
                                              ( IEvent& event )
{
  Boolean dontPassOn = false;
  if (event.eventId() == WM_TRANSLATEACCEL)
  {           // Emulate notebook's handling for page windows.
     IWindow* parent = event.window()->parent();
     if (parent)
     {                  // Forward event to parent (view port).
        IEventResult result = parent->sendEvent( event );
        event.setResult( result );
     }
     dontPassOn = true;  // Don't let the file dialog get it.
  }
  return dontPassOn;
}

//============= PurchaseItemView::SelectFileHdr ===============

PurchaseItemView::SelectFileHdr :: SelectFileHdr
                                     ( PurchaseItemView* view )
  : clView( view )
{ }

Boolean PurchaseItemView::SelectFileHdr :: selected
                                       ( IControlEvent& event )
{
  if (event.controlId() == DID_FILES_LB)
  {                // New file selected.
     IListBox files( event.controlId(), event.window() );
     long selectedRow = files.selection();
     if (selectedRow != -1)  // Something is selected.
     {             // Concatenate path + file.
        IFileDialog* fileDlg = (IFileDialog*)(event.window());
        clView->updateIcon( fileDlg->fileName()
                             + files.itemText( selectedRow ));
     }
  }
  return false;
}

Boolean PurchaseItemView::SelectFileHdr :: enter
                                       ( IControlEvent& event )
{
  Boolean dontPassOn = false;
  if (event.controlId() == DID_FILES_LB)
  {             // Don't let the file dialog get a double-click
     dontPassOn = true;      // or Enter on the list box.
  }
  return dontPassOn;
}
