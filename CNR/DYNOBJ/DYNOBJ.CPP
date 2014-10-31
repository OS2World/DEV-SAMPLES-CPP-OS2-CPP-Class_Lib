//************************************************************
// Container Control - Dynamic Creation Of Objects            
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************

#include <iapp.hpp>
#include <iframe.hpp>
#include <icnrctl.hpp>
#include <icnrcol.hpp>
#include "table.hpp"

void main( )
{

IFrameWindow cnrFrame("Container Details View");

IContainerControl cnr(0x101,        
                      &cnrFrame,    
                      &cnrFrame);

// Size the frame & put container in client area
cnrFrame
  .setClient(&cnr)
  .sizeTo(ISize(450,200));


// Create a TableObject with 3 fields
const unsigned long columnCount = 3;
TableObject* pobject = new(columnCount)
                          TableObject(columnCount);
pobject->setFieldText("John Doe", 0);
pobject->setFieldText("Anywhere USA", 1);
pobject->setFieldText("Hacker", 2);
cnr.addObject(pobject);


// Create an IContainerColumn for the 1st field
IContainerColumn* pcnrcol = new
    IContainerColumn(TableObject::fieldOffset(0));
pcnrcol->setHeadingText("Name");
cnr.addColumn(pcnrcol);

// Create an IContainerColumn for the 2nd field
pcnrcol = new
    IContainerColumn(TableObject::fieldOffset(1));
pcnrcol->setHeadingText("Address");
cnr.addColumn(pcnrcol);

// Create an IContainerColumn for the 3rd field
pcnrcol = new
    IContainerColumn(TableObject::fieldOffset(2));
pcnrcol->setHeadingText("Occupation");
cnr.addColumn(pcnrcol);

// Details view
cnr.showDetailsView();

// Set the focus and show the window
cnrFrame
 .setFocus()
 .show();

IApplication::current().run();
}


