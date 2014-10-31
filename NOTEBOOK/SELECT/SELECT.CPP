//************************************************************
// Notebook Control - Delayed Page Loading                    
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <inotebk.hpp>
#include <ipagehdr.hpp>
#include <iframe.hpp>
#include <ihandle.hpp>
#include <ifont.hpp>
#include <ipoint.hpp>
#include <icolor.hpp>
#include "select.h"

// Page Handler for capturing page select
// events(used to delay dialog creation).
class PageSelectHandler : public IPageHandler
{
protected:
virtual Boolean
  select  ( IPageSelectEvent  &event );
};

void main()
{
  // Create the frame and the notebook
  IFrameWindow frame ("Delayed Addition of Pages");
  INotebook    notebook (ID_NOTEBOOK, &frame, &frame);

  // Set the color of the page parts to that of a dialog
  notebook
    .setColor(INotebook::pageBackground,
              IGUIColor(IGUIColor::dialogBgnd))
    .setColor(INotebook::majorTabBackground,
              IGUIColor(IGUIColor::dialogBgnd));
 
  // Declare a page settings.
  INotebook::PageSettings pageData(
           INotebook::PageSettings::statusTextOn |
           INotebook::PageSettings::majorTab |
           INotebook::PageSettings::autoPageSize);
 
  
  // Setup Page1 with text, a major tab, & a dialog.
  // User data is 0 because we load the dialog here.
  pageData
    .setTabText("Page 1")
    .setStatusText("Page 1")
    .setUserData(0);         

  // Create the Dialog for the top page.
  // and add the page to the notebook
  IFrameWindow dialog1(ID_DIALOG1, &notebook, &notebook);
  notebook.addLastPage( pageData, &dialog1);
   
  // Setup Page2 with text, a major tab, & a dialog.
  // We will store the dialog id in user data and use it
  // later to load the id.
  pageData
    .setTabText("Page 2")
    .setStatusText("Page 2 - no window yet")
    .setUserData(ID_DIALOG2);  

  // Add page two to the notebook without a dialog.
  notebook.addLastPage( pageData);
   
  // Repeat the above for page3.
  pageData
    .setTabText("Page 3")
    .setStatusText("Page 3 - no window yet")
    .setUserData(ID_DIALOG3); 
  notebook.addLastPage( pageData);

  // Make sure the tabs are big enough.
  IFont noteFont(&notebook);
  ISize tabSize(ISize(noteFont.minTextWidth("no_window Page_3"),
                noteFont.maxCharHeight()) + ISize(6,6));
  notebook
    .setMajorTabSize(tabSize)
    .setMinorTabSize(tabSize);

  // Create and energize a page handler to capture "select"
  // events so we can add the missing dialogs.
  PageSelectHandler pageHandler;
  pageHandler.handleEventsFor(&frame);
 
  // Put the notebook in the client and show the frame.
  frame 
    .setClient(&notebook)
    .show();
  dialog1.setFocus();

  // Run the application.
  IApplication::current().run();
}


Boolean PageSelectHandler::select  ( IPageSelectEvent  &event )
{
  IPageHandle selectedPage = event.pageHandle();
  INotebook* notebook = event.notebook();
  INotebook::PageSettings pageData =
                event.notebook()->pageSettings(selectedPage);
  unsigned long dialogId = pageData.userData();

  // If we have a dialog id in user data, the frame needs to
  // be created
  if (dialogId != 0) {
    IFrameWindow* dialog = new IFrameWindow(
                                    dialogId,
                                    notebook,
                                    notebook);

    // Size the dialog to the size of the page
    (*dialog).sizeTo((*notebook).pageSize());

    // Put the page on the notebook and set user data to
    // zero to indicate that we've added the page window.
    IString statusText 
              = pageData.tabText() + " has been added";
    (*notebook)
       .setWindow( selectedPage, dialog)
       .setUserData(selectedPage, 0)
       .setStatusText(selectedPage, statusText);

 
  }
  return false;
}

