#ifndef _TEMPVIEW_
#define _TEMPVIEW_
//************************************************************
// Slider - Slider Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <iedithdr.hpp>
#include <islider.hpp>
#include <istattxt.hpp>
#include <isplitcv.hpp>

//  Class for handling changes to the slider control.
class TemperatureHandler : public IEditHandler
{
public:
  TemperatureHandler ( IStaticText* text )
        : IEditHandler(), temperatureText(text) { }

Boolean
  edit       ( IControlEvent& event );

private:
IStaticText
 *temperatureText;
};     

//  The main view class.
class TemperatureView : public IFrameWindow
{
public:
 TemperatureView  ( const char* viewName );

IStaticText
 &text       ( ) { return tempText; }

ISlider
 &slider     ( ) { return farenheitSlider; }

private:
ISplitCanvas
  canvas;
IStaticText
  sliderTitle;
ISlider
  farenheitSlider;
IStaticText
  tempText;
TemperatureHandler
  tempHandler;
TemperatureView  (const TemperatureView& );
TemperatureView& operator=(const TemperatureView& );
};            

#endif // _TEMPVIEW_
