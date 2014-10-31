//************************************************************
// Lunch dialog - Dialog template implementation.             
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <iradiobt.hpp>
#include "lunch.h"

void main ( )
{
  IFrameWindow lunch( ID_LUNCH_DIALOG );

  // Initialize the dialog controls.
  IRadioButton hamburger( ID_HAMBURGER, &lunch );
  hamburger
   .select()
   .setFocus();
  IRadioButton milk( ID_MILK, &lunch );
  milk.select();

  lunch.show();
  IApplication::current().run();
}
