//************************************************************
// Slider - Slider Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <ipoint.hpp>
#include <irect.hpp>
#include <istring.hpp>
#include "tempview.hpp"
#include "tempview.h"

//  primary application class definition
TemperatureView :: TemperatureView ( const char* viewName )
       : IFrameWindow(viewName),
         canvas(ID_CANVAS, this, this,
                IRectangle(),
                ISplitCanvas::horizontal  |
                ISplitCanvas::noSplitBars |
                IWindow::visible),
         sliderTitle(ID_SLD_TITLE, &canvas, &canvas),
         farenheitSlider(ID_SLIDER, &canvas, &canvas,
                         IRectangle(), 281),
         tempText(ID_TEMP, &canvas, &canvas),
         tempHandler(&text())
{
   //  Add the edit handler to the slider.
   tempHandler.handleEventsFor(&slider());

   //  Put the canvas in the client area 
   //  and set the pane percentages.
   setClient(&canvas);
   canvas
     .setSplitWindowPercentage(&sliderTitle, 20)
     .setSplitWindowPercentage(&slider(), 60)
     .setSplitWindowPercentage(&text(), 20);

   //  Set the alignment & text for the static text controls.
   sliderTitle
     .setAlignment(IStaticText::bottomCenter)
     .setText("Farenheit Temperature Slider");
   text()
     .setAlignment(IStaticText::centerCenter)
     .setText("Temperature is 0");

   //  Set the length and text for the slider's ticks.
   slider()
     .setTickLength(0,10)
     .setTickText(0, IString(-40));
   for ( int i=20; i<281; i+=20)  {
      slider()
        .setTickLength(i,10)
        .setTickLength(i-5,5)
        .setTickLength(i-10,5)
        .setTickLength(i-15,5)
        .setTickText(i, IString(i-40));
   }

   //  Get the pixel offset for pixel 0 to use as a base.
   IPoint base(slider().tickPosition(0));

   //  Get the pixel offsets for other ticks of interest.
   IPoint freeze(slider().tickPosition(72));
   IPoint boil(slider().tickPosition(252));

   //  Add detents for boiling and freezing temperatures
   //  using the previously obtained pixel offsets.
   slider().addDetent(freeze.x()-base.x());
   slider().addDetent(boil.x()-base.x());

   //  Move the slider arm to pixel 40, temperature 0.
   slider().moveArmToTick(40);
}

//  Handle changes to the slider control.
Boolean TemperatureHandler :: edit ( IControlEvent& event )
{
   long temp = (((ISlider*)event.controlWindow())->
                  armTickOffset()) - 40;
   temperatureText->setText(IString("Temperature is ") 
                                     + IString(temp));
   return true;
}

