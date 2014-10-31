//************************************************************
// Container Control - Help in the Container                    
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <ifont.hpp>
#include "devview.hpp"
#include "devview.h"
#include "devmodel.hpp"


DeveloperView::DeveloperView ( )
                   : IFrameWindow("Developers - Details View", ID_DETAILS_FRAME),
                     cnrWin(ID_DETAILS_CNR, this, this),
                     nameColumn(IContainerColumn::isIconViewText),
                     addressColumn(Developer::addressOffset()),
                     ageColumn(Developer::ageOffset()),
                     cnrHandler(),
                     cnrEditHandler(),
                     helpWindow(HELP_TABLE, this)
{
  // Put data in columns add to container.
  // "Name"
  nameColumn.setHeadingText("Developer Name");
  cnrWin.addColumn(&nameColumn);
  
  // "CompuServe Id"
  addressColumn.setHeadingText("CompuServe Id");
  cnrWin.addColumn(&addressColumn);
  
  // "Age"
  ageColumn.setHeadingText("Age");
  cnrWin.addColumn(&ageColumn);
  
  // Create objects & add to cnr.
  Developer* developer1;
  Developer* developer2;
  developer1 = new Developer("John Smith",
                            "222222,3333",
                            38);
  cnrWin.addObject(developer1);
  
  developer2 = new Developer("Bob Jones",
                            "33333,4444",
                            40);
  cnrWin.addObject(developer2);
  
  // Add Help for objects and columns.
  nameColumn.setHelpId(HELPFOR_NAME);
  addressColumn.setHelpId(HELPFOR_ADDRESS);
  ageColumn.setHelpId(HELPFOR_AGE);
  developer1->setHelpId(HELPFOR_DEVELOPER);
  developer2->setHelpId(HELPFOR_DEVELOPER);
  
  // Set the Help Title and indicate the 
  // help libraries.
  helpWindow.setTitle("Help for Developer Details");
  helpWindow.addLibraries(IApplication::current().userResourceLibrary().
                             loadString(HELP_LIBRARIES));
  
  // Enable editing in objects and columns.
  nameColumn.enableDataUpdate();
  addressColumn.enableDataUpdate(); 
  ageColumn.enableDataUpdate(); 
  developer1->enableDataUpdate();
  developer2->enableDataUpdate();
  
  // Attach the handlers.
  cnrHandler.handleEventsFor(&cnrWin);
  cnrEditHandler.handleEventsFor(&cnrWin);
  
  // Switch to the Details view.
  cnrWin.showDetailsView();
  
  // Put container in client area.
  setClient(&cnrWin);
}

