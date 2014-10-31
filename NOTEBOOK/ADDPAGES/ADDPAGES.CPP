//************************************************************
// Notebook Control - Adding Dialog Pages                     
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <inotebk.hpp>
#include <iframe.hpp>
#include <ihandle.hpp>
#include <ifont.hpp>
#include <ipoint.hpp>
#include "addpages.h"

void main()
{
  IFrameWindow frame ("Adding Notebook Pages");
  INotebook    notebook (0x08008, &frame, &frame);

  // Dialog1 & Dialog3
  IFrameWindow 
    dialog1(ID_DIALOG1, &notebook, &notebook),
    dialog3(ID_DIALOG3, &notebook, &notebook);

  // Use one of the system bitmaps for the tab.
  ISystemBitmapHandle page1Bitmap(ISystemBitmapHandle::drive);
  
  // Declare a page settings.
  INotebook::PageSettings pageData;
  
  // Page 1 with bitmap, major tab, & dialog1
  pageData = INotebook::PageSettings ( 
                         page1Bitmap,
                         "Page 1",
                         INotebook::PageSettings::statusTextOn |
                         INotebook::PageSettings::majorTab);
  notebook.addLastPage( pageData, &dialog1);
   
  // Page 2 with text, major tab, & no window
  pageData = INotebook::PageSettings ( 
                         "no window",
                         "Page 2",
                         INotebook::PageSettings::statusTextOn |
                         INotebook::PageSettings::majorTab);
  notebook.addLastPage( pageData);
   
  // Page 3 with text, minor tab, & dialog3
  pageData = INotebook::PageSettings ( 
                         "dialog3",
                         "Page 3",
                         INotebook::PageSettings::statusTextOn |
                         INotebook::PageSettings::minorTab);
  notebook.addLastPage( pageData, &dialog3);


  // Make sure the tabs are big enough.
  IFont noteFont(&notebook);
  ISize tabSize(ISize(noteFont.minTextWidth("no_window Page_3"),
                noteFont.maxCharHeight()) + ISize(6,6));
  notebook
    .setMajorTabSize(tabSize)
    .setMinorTabSize(tabSize);

  frame
    .setClient(&notebook)
    .show();
  IApplication::current().run();
}

