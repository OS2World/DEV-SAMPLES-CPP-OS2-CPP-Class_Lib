//************************************************************
// Container Control - Dates and Times as CDATE/CTIME         
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <ictlevt.hpp>
#include "developr.h"
#include "developr.hpp"

DeveloperList :: DeveloperList ( const char* title)
                   : IFrameWindow (title, DEVELOPER_WINDOW),
                     cnrctl( DEVELOPER_CONTAINER, this, this)
 
{

// Put container in client area
setClient(&container());

// Create and add the columns
IContainerColumn* pcolumn;

// "Name"
pcolumn = new IContainerColumn(IContainerColumn::isIconViewText);
pcolumn->setHeadingText("Name");
pcolumn->enableDataUpdate();
container().addColumn(pcolumn);
container().setDetailsViewSplit(pcolumn, 125);

// "Role" - icon
pcolumn = new IContainerColumn(IContainerColumn::isIcon);
pcolumn->setHeadingText("Role");
container().addColumn(pcolumn);

// "CompuServe Id" 
pcolumn = new IContainerColumn( Developer::compuServeOffset());
pcolumn->setHeadingText("CompuServe Id");
pcolumn->enableDataUpdate();
container().addColumn(pcolumn);

// "Age"
pcolumn = new IContainerColumn( Developer::ageOffset());
pcolumn->setHeadingText("Age");
pcolumn->enableDataUpdate();
container().addColumn(pcolumn);

// CDATE
pcolumn = new IContainerColumn(Developer::dateOffset(),
                               IContainerColumn::defaultHeadingStyle(),
                               IContainerColumn::date);
pcolumn->setHeadingText("Birth Date");
container().addColumn(pcolumn);

// CTIME
pcolumn = new IContainerColumn( Developer::timeOffset(),
                                IContainerColumn::defaultHeadingStyle(),
                                IContainerColumn::time);
pcolumn->setHeadingText("Quiting Time");
container().addColumn(pcolumn);

// Create and add the objects
Developer* developer;
CDATE bDate(27,6,1953);
CTIME qTime(3);

developer = new Developer("Joe Programmer",
                          ID_DEVELOPER,
                          "12345,6789",
                          "38");
container().addObject(developer);
container().enableDataUpdate(developer);

container().setDeleteColumnsOnClose();
container().setDeleteObjectsOnClose();
container().showSplitBar();
}

IContainerControl& DeveloperList :: container( ) { 
  return cnrctl;
}

