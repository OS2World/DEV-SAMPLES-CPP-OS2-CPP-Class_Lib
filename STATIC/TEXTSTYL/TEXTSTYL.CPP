//************************************************************
// Static Text Controls - Style Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iapp.hpp>
#include <ifont.hpp>
#include <iframe.hpp>
#include <istattxt.hpp>
#include <istring.hpp>

void main ( )
{
  IFrameWindow frame( "Static Text Style Example" );

  // Illustrate the different alignment styles.
  IStaticText
     topLeftAndClient( 0x8008, &frame, &frame ),
     topCenter       (2, &frame, &frame),
     topRight        (3, &frame, &frame),
     centerLeft      (4, &frame, &frame),
     centered        (5, &frame, &frame),
     centerRight     (6, &frame, &frame),
     bottomLeft      (7, &frame, &frame),
     bottomCenter    (8, &frame, &frame),
     bottomRight     (9, &frame, &frame);
  
  IFont font( &topLeftAndClient );     
  unsigned long lineHeight = font.maxCharHeight();
  unsigned long alignmentHeight = (lineHeight*3)/2;

  // Use a smaller font for the alignment styles.
  font
    .setName("Times New Roman")
    .setPointSize(9);

  // Set the alignment, text, and new font size.
  topLeftAndClient
    .setAlignment(IStaticText::topLeft)
    .setText("Top-left")
    .setFont(font);
  topCenter
    .setAlignment(IStaticText::topCenter)
    .setText("Top-center")
    .setFont(font);
  topRight 
    .setAlignment(IStaticText::topRight)
    .setText("Top-right")
    .setFont(font);
  centerLeft     
    .setAlignment(IStaticText::centerLeft)
    .setText("Center-left")
    .setFont(font);
  centered 
    .setAlignment(IStaticText::centerCenter)
    .setText("Centered")
    .setFont(font);
  centerRight
    .setAlignment(IStaticText::centerRight)
    .setText("Center-right")
    .setFont(font);
  bottomLeft 
    .setAlignment(IStaticText::bottomLeft)
    .setText("Bottom-left")
    .setFont(font);
  bottomCenter 
    .setAlignment(IStaticText::bottomCenter)
    .setText("Bottom-center")
    .setFont(font);
  bottomRight   
    .setAlignment(IStaticText::bottomRight)
    .setText("Bottom-right")
    .setFont(font);

  // Illustrate the different drawing styles.
  IStaticText multiStyle( 11, &frame, &frame );
  multiStyle
   .enableStrikeout()
   .enableUnderscore()
   .enableHalftone()
   .setAlignment( IStaticText::topLeftWrapped )
   .setText( "Strike-out + underscore + half-tone"
               + IString( " + top-left-wrapped" ));

  IStaticText halftone( 12, &frame, &frame );
  halftone
   .enableHalftone()
   .setText( "Half-tone style" );

  IStaticText underscore( 13, &frame, &frame );
  underscore
   .enableUnderscore()
   .setText( "Underscore style" );

  IStaticText strikeout( 14, &frame, &frame );
  strikeout
   .enableStrikeout()
   .setText( "Strike-out style" );

  IStaticText mnemonic( 15, &frame, &frame, IRectangle(),
                        IStaticText::classDefaultStyle
                          | IStaticText::mnemonic );
  mnemonic.setText( "~Mnemonic style" );

  // Position the static text controls.
  frame
   .setClient( &topLeftAndClient )
   .addExtension( &multiStyle,
                  IFrameWindow::belowClient,
                  2 * lineHeight )
   .addExtension( &halftone,
                  IFrameWindow::belowClient,
                  lineHeight )
   .addExtension( &underscore,
                  IFrameWindow::belowClient,
                  lineHeight )
   .addExtension( &strikeout,
                  IFrameWindow::belowClient,
                  lineHeight )
   .addExtension( &mnemonic,
                  IFrameWindow::belowClient,
                  lineHeight )
   .addExtension( &bottomRight,
                  IFrameWindow::belowClient,
                  alignmentHeight )
   .addExtension( &bottomCenter,
                  IFrameWindow::belowClient,
                  alignmentHeight )
   .addExtension( &bottomLeft,
                  IFrameWindow::belowClient,
                  alignmentHeight )
   .addExtension( &centerRight,
                  IFrameWindow::belowClient,
                  alignmentHeight )
   .addExtension( &centered,
                  IFrameWindow::belowClient,
                  alignmentHeight )
   .addExtension( &centerLeft,
                  IFrameWindow::belowClient,
                  alignmentHeight )
   .addExtension( &topRight,
                  IFrameWindow::belowClient,
                  alignmentHeight )
   .addExtension( &topCenter,
                  IFrameWindow::belowClient,
                  alignmentHeight );

  // Size and show the window now (needed for proper
  // alignment of the below strings).
  frame
   .sizeTo( ISize( 450, 472 ))
   .moveTo( IPoint( 10, 10 ))
   .setFocus()
   .show();

  IApplication::current().run();
}
