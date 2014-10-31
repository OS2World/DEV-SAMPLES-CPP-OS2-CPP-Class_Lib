//************************************************************
// Notebook Control - Default Notebook Example                 
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <inotebk.hpp>
#include <iframe.hpp>

void main()
{
  IFrameWindow frame ("Default Notebook");
  frame.sizeTo(ISize(400, 250));

  INotebook    notebook (0x0101, &frame, &frame);

  INotebook::PageSettings::Attribute attribute1 =
                      INotebook::PageSettings::majorTab;
  INotebook::PageSettings::Attribute attribute2 =
                      INotebook::PageSettings::minorTab;
  INotebook::PageSettings page1Layout("Major Tab", "Page 1 of 2", attribute1);
  INotebook::PageSettings page2Layout("Minor Tab", "Page 2 of 2", attribute2);

  // Set the tab sizes.
  notebook
    .setMajorTabSize(ISize(110,26))
    .setMinorTabSize(ISize(110,26));
 
  // Add the pages.
  notebook.addFirstPage(page1Layout);
  notebook.addLastPage(page2Layout);

  // Give the notebook the focus.
  notebook.setFocus();

  // Put the notebook in the client and show the window.
  frame
    .setClient(&notebook)
    .show();

  IApplication::current().run();
}

