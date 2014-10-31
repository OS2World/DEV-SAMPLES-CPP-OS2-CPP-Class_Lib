//************************************************************
// Container Control - Dates and Times as CDATE/CTIME        
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include "developr.hpp"


void main ()
{

DeveloperList developers("Developer List");

// Details view
developers.container()
  .showDetailsView()
  .setFocus();

developers
  .show();

IApplication::current().run();
}
