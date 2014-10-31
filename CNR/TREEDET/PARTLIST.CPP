//************************************************************
// Container - Combined Tree and Details View
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
extern "C" {
   #define INCL_WINWINDOWMGR
   #define INCL_WINSTDCNR
   #define INCL_WINSYS
   #include <os2.h>
}

#include <iframe.hpp>
#include <icnrctl.hpp>
#include <icnrcol.hpp>
#include <isplitcv.hpp>
#include <imcelcv.hpp>
#include <istattxt.hpp>
#include <iscroll.hpp>
#include "partlist.hpp"
#include "partlist.h"
#include "partobj.hpp"
#include "treedetc.hpp"
#include "treedeth.hpp"




PartsList :: ~PartsList ( )
{
  // Note we rely on Auto Delete to clean up the
  // objects for windows contained herein.

  if (treeHandler)
     delete treeHandler;
  if (colorHandler)
     delete colorHandler;
}

PartsList :: PartsList ( )
                : IFrameWindow(EX_PARTLIST_FRAME ),
                  colorChanged(false)
{
  // Create a frame window with a split canvas client
  //            left  side = Multi-Cell Canvas
  //            right side = Multi-Cell Canvas
  // There is also a static text field on top
  // of the Tree view scroll Bar
  //
  //  --------------------------------------------
  //  |          |  ||   Empty Row for Pad       |
  //  |          |S ||---------------------------|
  //  |          |t ||                           |
  //  |          |a ||                           |
  //  |          |t ||                           |
  //  |  Tree    |i ||     Details               |
  //  |  Cnr     |c ||       Cnr                 |
  //  |          |  ||                           |
  //  |          |T ||                           |
  //  |          |e ||                           |
  //  |          |x ||                           |
  //  |          |t ||                           |
  //  --------------------------------------------
  //

  // Create a split canvas as a client
  canvas = new ISplitCanvas (EX_PARTLIST_CANVAS,
                              this, this);
  this->setClient(canvas);

  // Create a MultiCell canvas for both the left window (to
  // contain the tree) and the right (to contain the
  // details view)
  leftMCell  = new IMultiCellCanvas(EX_PARTLIST_LEFTCANVAS,
                              canvas, this);
  rightMCell = new IMultiCellCanvas(EX_PARTLIST_RIGHTCANVAS,
                              canvas, this);

  // Create the tree and a Static Text field for the
  // left canvas.  The static text is used to overlay
  // the tree view scroll bar (the container and
  // the static text field share a column)
  treeScrollHideWin = new IStaticText(EX_PARTLIST_TREESCROLLHIDE, 
                                         leftMCell, this);
  treeCnr        = new DetailsTreeContainer(EX_PARTLIST_TREE,
                                         leftMCell, this);

  // Add the cells to the left canvas
  (*leftMCell)
    .addToCell(treeCnr, 1, 1, 2, 2)
    .addToCell(treeScrollHideWin, 2, 1)
    .setColumnWidth(2, IScrollBar::systemScrollBarWidth())
    .setColumnWidth(1, 50, true)
    .setRowHeight(1, 10, true)
    .setRowHeight(2, IScrollBar::systemScrollBarWidth()); 


  // Create the details container and put it into row 2
  // with some pad for alignment,
  detailsCnr  = new IContainerControl(EX_PARTLIST_DETAILS,
                                      rightMCell, this);
  (*rightMCell)
    .addToCell(detailsCnr, 1, 2)
    .setRowHeight(1,6)
    .setRowHeight(2,30, true)
    .setColumnWidth(1, 10, true);

  // Wrapper the Tree view scroll bar, turn off updating for it,
  treeScroll = new IScrollBar(CID_VSCROLL, treeCnr);
  treeScroll->disableUpdate();


  // Notify the DetailsTreeContainer of it's details view
  treeCnr->setDetailsContainer(detailsCnr);

  // Set the appropriate views
  treeCnr->showTreeTextView();
  detailsCnr->showDetailsView();


  // We show an empty title to try and get the correct
  // alignment and add some line spacing in the details
  // view to line up with the default tree view spacing.
  treeCnr->showTitle();
  detailsCnr->setLineSpacing(10);

  // Create the handlers for syncing changes
  // Note: handleEventsFor is done in the constructor.
  // 1) Font
  treeHandler = new DetailsTreeHandler(treeCnr);

  // 2) Color
  colorHandler = new ColorChangeHandler(this);

  // Create some Columns for the details view
  IContainerColumn* pcol;

#ifdef IC_DEVELOP
// For testing, add the iconViewText column
  pcol = new IContainerColumn(IContainerColumn::isIconViewText);
  pcol->setHeadingText( "Test Column");
  pcol->showSeparators(IContainerColumn::horizontalSeparator);
  pcol->justifyData(IContainerColumn::bottom, IContainerColumn::left);
  detailsCnr->addColumn(pcol);
  detailsCnr->setDetailsViewSplit(pcol);
  detailsCnr->showSplitBar();
#endif

 
  pcol = new IContainerColumn(ExecutablePart::traceAbleOffset());
  (*pcol)
    .setHeadingText( EX_COLUMN_TRACEABLE)
    .showSeparators(IContainerColumn::horizontalSeparator)
    .enableDataUpdate();
  detailsCnr->addColumn(pcol);
    
  pcol = new IContainerColumn(ExecutablePart::enabledPartOffset( ));
  (*pcol)
    .setHeadingText(EX_COLUMN_ENABLED)
    .showSeparators(IContainerColumn::horizontalSeparator)
    .enableDataUpdate();
  detailsCnr->addColumn(pcol);

  pcol = new IContainerColumn(ExecutablePart::generatesTraceOffset());
  (*pcol)
    .setHeadingText(EX_COLUMN_GENTRACE)
    .showSeparators(IContainerColumn::horizontalSeparator)
    .enableDataUpdate();
  detailsCnr->addColumn(pcol);

  pcol = new IContainerColumn(ExecutablePart::containsTriggerOffset());
  (*pcol)
    .setHeadingText(EX_COLUMN_TRIGGER)
    .showSeparators(IContainerColumn::horizontalSeparator)
    .enableDataUpdate();
  detailsCnr->addColumn(pcol);

  // add some objects
  loadObjects ();

  // Auto Delete our objects when the PM Window gets destroyed
  this->setAutoDeleteObject();
  canvas->setAutoDeleteObject();
  treeCnr->setAutoDeleteObject();
  treeCnr->setDeleteObjectsOnClose();
  detailsCnr->setAutoDeleteObject();
  detailsCnr->setDeleteColumnsOnClose();
  detailsCnr->setDeleteObjectsOnClose();

detailsCnr->refresh();

}

PartsList& PartsList :: open ( )
{
  if ( isMinimized() )
    restore();
  setFocus();
  show();
  return *this;
}



// Load Some Executable Parts into the container
PartsList& PartsList :: loadObjects ( )
{
  ExecutablePart *partExe, *partObj, *partFunc;

  partExe = new ExecutablePart("DDE4MUI.DLL");
  treeContainer().addObject(partExe);
    partObj = new ExecutablePart("IWINDOW.OBJ");
    treeContainer().addObject(partObj, partExe);
      partFunc = new ExecutablePart("IWindow::show");
      treeContainer().addObject(partFunc, partObj);
      partFunc = new ExecutablePart("IWindow::hide");
      treeContainer().addObject(partFunc, partObj);
      partFunc = new ExecutablePart("IWindow::enableUpdate");
      treeContainer().addObject(partFunc, partObj);
    partObj = new ExecutablePart("ICNROBJ.OBJ");
    treeContainer().addObject(partObj, partExe);
      partFunc = new ExecutablePart("IContainerObject::enableDataUpdate");
      treeContainer().addObject(partFunc, partObj);
      partFunc = new ExecutablePart("IContainerObject::setIcon");
      treeContainer().addObject(partFunc, partObj);
      partFunc = new ExecutablePart("IContainerObject::setIconText");
      treeContainer().addObject(partFunc, partObj);
  partExe = new ExecutablePart("DDE4MBS.DLL");
  treeContainer().addObject(partExe);
    partObj = new ExecutablePart("MALLOC.OBJ");
    treeContainer().addObject(partObj, partExe);
      partFunc = new ExecutablePart("_have_freed");
      treeContainer().addObject(partFunc, partObj);
      partFunc = new ExecutablePart("__malloc");
      treeContainer().addObject(partFunc, partObj);
  partExe = new ExecutablePart("DDE4CC.DLL");
  treeContainer().addObject(partExe);
    partObj = new ExecutablePart("IEXCBASE.OBJ");
    treeContainer().addObject(partObj, partExe);
      partFunc = new ExecutablePart("IOutOfWindowResource()");
      treeContainer().addObject(partFunc, partObj);
      partFunc = new ExecutablePart("IException::terminate");
      treeContainer().addObject(partFunc, partObj);
    partObj = new ExecutablePart("IMSGTEXT.OBJ");
    treeContainer().addObject(partObj, partExe);
      partFunc = new ExecutablePart("IMessageText::setDefaultText");
      treeContainer().addObject(partFunc, partObj);
 
  return *this;
}

IContainerControl& PartsList :: otherContainer (
                  const IContainerControl& opposite)
{
  if (&opposite == treeCnr)
     return *detailsCnr;
  else
     return *treeCnr;
}


ColorChangeHandler :: ColorChangeHandler ( PartsList* partsList)
{
  this->partsList = partsList;
  handleEventsFor(&partsList->leftMultiCell());
  handleEventsFor(&partsList->rightMultiCell());
  handleEventsFor(&partsList->treeScrollHide());
  handleEventsFor(&partsList->treeContainer());
  handleEventsFor(&partsList->detailsContainer());
}


Boolean ColorChangeHandler :: dispatchHandlerEvent ( IEvent& evt)
{
   if(evt.eventId() == WM_PRESPARAMCHANGED)
   {
      if(evt.parameter1() == PP_BACKGROUNDCOLOR )
         return backgroundColorChanged(evt);
   }


  return false;
}

Boolean ColorChangeHandler :: backgroundColorChanged(IEvent& evt)
{
  // We need to keep track of the top level entry to this
  // function so that we avoid a ping-pong affect that could 
  // occur when the notification is received more then once. 
  Boolean fNested = partsList->colorChangeStarted();
  partsList->setColorChangeStarted(true);


  if(!fNested) {
       IWindow* receiver=evt.window();
       // The following will change with new color scheme
       IColor color(IColor::white);

       // Determine the color of the changed window.
       if (receiver==&partsList->leftMultiCell() 
           || receiver == &partsList->rightMultiCell())
          color = ((IMultiCellCanvas*)receiver)->color();
       else if (receiver==&partsList->treeContainer()
           || receiver==&partsList->detailsContainer())
          color = ((IContainerControl*)receiver)->color(IContainerControl::background);
       else if (receiver==&partsList->treeScrollHide())
          color = partsList->treeScrollHide().color(IStaticText::background);

       // Apply the new color to the other windows in the SplitCanvas
          partsList->rightMultiCell().setColor(color);
       if(receiver!=&partsList->rightMultiCell())
          partsList->rightMultiCell().setColor(color);
       if(receiver!=&partsList->leftMultiCell())
          partsList->leftMultiCell().setColor(color);
       if(receiver!=&partsList->splitCanvas())
          partsList->splitCanvas().setColor(ISplitCanvas::splitBarMiddle, color);
       if(receiver!=&partsList->treeContainer())
          partsList->treeContainer().setColor(IContainerControl::background, color);
       if(receiver!=&partsList->detailsContainer())
          partsList->detailsContainer().setColor(IContainerControl::background, color);
       if(receiver!=&partsList->treeScrollHide())
          partsList->treeScrollHide().setColor(IStaticText::background, color);
       partsList->setColorChangeStarted(false);
  }

  return false;
}

