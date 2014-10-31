//************************************************************
// Container Control - Spreadsheet Behavior
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
extern "C"
{
  #include <os2.h>
}

#include <iapp.hpp>
#include <iframe.hpp>
#include <ipoint.hpp>
#include <icnrctl.hpp>
#include <icnrcol.hpp>
#include <icnrhdr.hpp>
#include <icnrehdr.hpp>
#include <new.h>
#include "table.hpp"
#include "sprdhdr.hpp"

void main()
{

IFrameWindow cnrFrame("Container SpreadSheet View");
cnrFrame.sizeTo(ISize(450,200));

IContainerControl cnr(0x101,        
                      &cnrFrame,    
                      &cnrFrame);

// Put container in client area
cnrFrame.setClient(&cnr);



// Create a bunch of Table Objects with columnCount fields
const unsigned long columnCount = 10;
int obj, col;
IString objectName;
for (obj=0; obj<50;obj++ ) {
  TableObject* pobject = new(columnCount)
                          TableObject(columnCount);
  cnr.addObject(pobject);
  for (col=0; col<columnCount; col++ ) {
     pobject->setFieldText(IString("Obj: ") + IString(obj) +
                IString(" Col: ") + IString(col),col);
     pobject->enableDataUpdate();
  } /* endfor */
} /* endfor */

// Create an IContainerColumn for each Field.
for (col=0; col<columnCount ; col++ ) {
   IContainerColumn* pcnrcol = new
       IContainerColumn(TableObject::fieldOffset(col));
   pcnrcol->enableDataUpdate();
   pcnrcol->setHeadingText(IString("Column ") + IString(col));
   cnr.addColumn(pcnrcol);
} /* endfor */

// Create Container EditHandler.
// Create a Default Handler for the Container Edit Field
// and energize it.
ICnrEditHandler* pcnrEdit = new ICnrEditHandler();
pcnrEdit->handleEventsFor(&cnr);

// Create the default ContainerHandler.
ICnrHandler* pcnrHandler = new ICnrHandler();
pcnrHandler->handleEventsFor(&cnr);

// Create Our Handler for Tabbing the Container.
CnrSpreadSheetHandler* psprdHandler= new CnrSpreadSheetHandler(cnr);
psprdHandler->handleEventsFor(&cnr);

// Show the details view.
cnr.showDetailsView();

cnrFrame.show();
cnrFrame.setFocus();

IApplication::current().run();
}
