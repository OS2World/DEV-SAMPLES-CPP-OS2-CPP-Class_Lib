//************************************************************
// Frame Window Basics - Frame Extension Sampler
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <istattxt.hpp>
#include <imenubar.hpp>

void main()
  {
  IFrameWindow
    frame( "Title Bar" );
  IMenuBar
    menu(&frame );

  menu
    .addText(10, "~File")
    .addText(11, "~Edit")
    .addText(12, "~View");
    
  IStaticText
    text1( 0, &frame, &frame ),
    text2( 0, &frame, &frame ),
    text3( 0, &frame, &frame ),
    text4( 0, &frame, &frame ),
    text5( 0, &frame, &frame ),
    text6( 0, &frame, &frame ),
    text7( 0, &frame, &frame ),
    text8( 0, &frame, &frame );

  IStaticText::Alignment
    alignment = IStaticText::centerCenter;
  text1.setAlignment( alignment ).setText( "leftOfTitleBar" );
  text2.setAlignment( alignment ).setText( "rightOfTitleBar" );
  text3.setAlignment( alignment ).setText( "leftOfMenuBar" );
  text4.setAlignment( alignment ).setText( "rightOfMenuBar" );
  text5.setAlignment( alignment ).setText( "aboveClient" );
  text6.setAlignment( alignment ).setText( "belowClient" );
  text7.setAlignment( alignment ).setText( "leftOfClient" );
  text8.setAlignment( alignment ).setText( "rightOfClient" );

  const unsigned long
    fixed = 150;
  const IFrameWindow::SeparatorType
    none = IFrameWindow::none,
    thin = IFrameWindow::thinLine,
    thick = IFrameWindow::thickLine;

  frame
    .addExtension( &text1, IFrameWindow::leftOfTitleBar,
                   fixed, thick )
    .addExtension( &text2, IFrameWindow::rightOfTitleBar,
                   fixed, thin )
    .addExtension( &text3, IFrameWindow::leftOfMenuBar,
                   fixed, thick )
    .addExtension( &text4, IFrameWindow::rightOfMenuBar,
                   fixed, none )
    .addExtension( &text5, IFrameWindow::aboveClient,
                   33, thick )
    .addExtension( &text6, IFrameWindow::belowClient,
                   33, thick )
    .addExtension( &text7, IFrameWindow::leftOfClient,
                   fixed, thin )
    .addExtension( &text8, IFrameWindow::rightOfClient,
                   fixed, thin )
    .setFocus ( );

  frame
    .showModally();
  }

