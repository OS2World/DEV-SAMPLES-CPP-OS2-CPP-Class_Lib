//************************************************************
// Container Control - Pop Up Menu Example 
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <icnrctl.hpp>
#include <icnrcol.hpp>
#include <icnrobj.hpp>
#include <icnrmhdr.hpp>
#include <ipopmenu.hpp>
#include <ictlevt.hpp>
#include <iapp.hpp>
#include <itrace.hpp>
#include "popup.h"

class Developer : public IContainerObject
{
  public:
  Developer   ( IString       name,
                unsigned long iconId,
                IString       compuServeId,
                unsigned long age)
     : IContainerObject(name, iconId),
       strCompuServeId(compuServeId),
       ulAge(age)
 
 {}

static unsigned long
  compuServeOffset ( )
{ return offsetof(Developer, strCompuServeId); }

static unsigned long
  ageOffset        ( )
{   return offsetof(Developer, ulAge); }

private:

IString
  strCompuServeId;
unsigned long
  ulAge;
};


class DeveloperMenuHandler : public ICnrMenuHandler
{

protected:

virtual Boolean
 makePopUpMenu(IMenuEvent& mnEvt);

};

void main ()
{

IFrameWindow cnrFrame("Container Details View");
cnrFrame.sizeTo(ISize(300,350));

IContainerControl cnr(0x101,        
                      &cnrFrame,    
                      &cnrFrame);

// Put container in client area
cnrFrame.setClient(&cnr);

// Create and add the columns
// "Name"
IContainerColumn name(IContainerColumn::isIconViewText);
name.setHeadingText("Name");
cnr.addColumn(&name);

// "Role" - icon
IContainerColumn icon(IContainerColumn::isIcon);
icon.setHeadingText("Role");
cnr.addColumn(&icon);


// "CompuServe Id" 
IContainerColumn compuServeId(
                    Developer::compuServeOffset());
compuServeId.setHeadingText("CompuServe Id");
cnr.addColumn(&compuServeId);

// "Age"
IContainerColumn age(Developer::ageOffset(),
                    IContainerColumn::defaultHeadingStyle(),
                    IContainerColumn::number
                    | IContainerColumn::centeredVertically
                    | IContainerColumn::alignRight);
age.setHeadingText("Age");
cnr.addColumn(&age);

// Create and add the objects
Developer* developer;
developer = new Developer("Joe South", 
                          ICON_FOLDER,  
                          "12345,6789",
                          38);
cnr.addObject(developer);
developer = new Developer("Silly Sally",
                          ICON_FOLDER,  
                          "98765,4321",
                          40);
cnr.addObject(developer);


//Create a container MenuHandler and add it to the list
DeveloperMenuHandler* pmenu = new DeveloperMenuHandler();
pmenu->handleEventsFor(&cnr);

// Details view
cnr.showDetailsView();

cnrFrame.show();
cnrFrame.setFocus();

IApplication::current().run();
}

Boolean DeveloperMenuHandler :: makePopUpMenu(IMenuEvent& mnEvt)
{
  // If on an object, create a menu for the object
  // Support should be added to have a container window
  // Menu if we aren't over an object

  // Note that evt.window in version 2.0 pointed to the owner
  // of the container since the makePopUpMenu() called was the
  // result of a WM_CONTROL event.  In version 2.1, makePopUpMenu
  // is being called as a result of WM_CONTEXTMENU so evt.window
  // is correctly the container window().

  IContainerControl* pcnr;
  if(IBase::version().major == 1 && IBase::version().minor == 0) {
    IControlEvent ctlevt(mnEvt);
    pcnr = (IContainerControl*)(ctlevt.controlWindow());
  }
  else
     pcnr = (IContainerControl*)(mnEvt.window());

  if(popupMenuObject()) {
    IPopUpMenu* ppumn = new IPopUpMenu(POPUP_MENU, pcnr);
    ppumn->setAutoDeleteObject();
    ppumn->show(mnEvt.mousePosition());
    return true;
  }
  return false;
}
