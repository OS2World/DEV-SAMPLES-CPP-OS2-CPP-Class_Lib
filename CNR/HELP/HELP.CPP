//************************************************************
// Container Control - Help in the Container
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iapp.hpp>
#include "devview.hpp"

void main()
{
  DeveloperView developers;
 
  developers
    .setFocus()
    .show();

  IApplication::current().run();
}
