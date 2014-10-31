//************************************************************
// Slider - Progress Indicator Example                 
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iapp.hpp>
#include "taskview.hpp"

void main()
{
   // Create the status view window.
   TaskStatusView mainWindow("Progress Indicator Custom Drawing");          
   
   // Give the window the focus and show it.
   mainWindow
     .setFocus()
     .show();

   IApplication::current().run();  
} 
