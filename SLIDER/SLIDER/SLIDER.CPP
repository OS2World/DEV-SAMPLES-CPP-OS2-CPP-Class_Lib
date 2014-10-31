//************************************************************
// Slider - Slider Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iapp.hpp>
#include "tempview.hpp"

void main()
{
   // Create the temperature view window.
   TemperatureView mainWindow("ISlider Example");

   //  Give the window the focus and show it.
   mainWindow
     .setFocus()
     .show();

   IApplication::current().run();
} 
