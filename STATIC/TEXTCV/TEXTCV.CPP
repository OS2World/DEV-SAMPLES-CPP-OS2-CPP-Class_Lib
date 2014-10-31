//************************************************************
// Canvas - Static Text on a Canvas
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <ifont.hpp>
#include <iframe.hpp>
#include <imcelcv.hpp>
#include <iradiobt.hpp>
#include <iselhdr.hpp>
#include <istattxt.hpp>
#include <istring.hpp>

class MultiLineStaticText : public IStaticText {
public:
  MultiLineStaticText ( unsigned long id,
                        IWindow* parent,
                        IWindow* owner,
                        IStaticText::Style style =
                          IStaticText::defaultStyle() )
    : IStaticText( id, parent, owner, IRectangle(), style )
  { this->setAlignment( IStaticText::topLeftWrapped ); }
virtual MultiLineStaticText
 &setFraction         ( double fraction )
  {
    parentFraction = (fraction > 1) ? 1 : fraction;
    return *this;
  }
virtual double
  fraction            ( ) const
  { return parentFraction; }
protected:
virtual ISize
  calcMinimumSize     ( ) const
  {
    unsigned long recommendedWidth =
              (unsigned long)(this->parent()->size().width() * this->fraction());
    IFont font( this ); // Get current font information.

    if (recommendedWidth == 0)
    {                   // Parent has no size information.
       recommendedWidth = font.minTextWidth( this->text() );
       recommendedWidth += font.charWidth( ' ' );
                        // Work-around for IFont bug $HT!
    }                   // Base it off the text.
    unsigned long lines =
       font.textLines( this->text(), recommendedWidth );

    return ISize( recommendedWidth,
                  lines * font.maxCharHeight() );
  }
private:
double
  parentFraction;
MultiLineStaticText ( const MultiLineStaticText&);
MultiLineStaticText& operator= ( const MultiLineStaticText&);
};

class HumptyDumptySelectHandler : public ISelectHandler {
public:
  HumptyDumptySelectHandler ( IStaticText* outputArea )
  { output = outputArea; }
protected:
virtual Boolean
  selected      ( IControlEvent& event )
  {
    char* text = " ";
    switch ( event.controlWindow()->id() )
    {
       case 1:
         text = "Humpty Dumpty sat on a wall.";
         break;
       case 2:
         text = "Humpty Dumpty had a great fall.";
         break;
       case 3:
         text = "All the king's horses and all the king's men,";
         break;
       case 4:
         text = "Couldn't put Humpty together again.";
         break;
       default:
         break;
    }
    if (output)
    {
       output->setText( text );
    }
    return false;
  }
private:
IStaticText
 *output;
};

void main ( )
{
  IFrameWindow frame( "Static Text and Canvas Example" );
  IMultiCellCanvas client( 0x8008, &frame, &frame );
  frame.setClient( &client );

  // Create child windows.
  IStaticText
    output   ( 10, &client, &client ),
    separator( 11, &client, &client );
  output.setLimit( 45 );
  separator
   .setColor( IStaticText::fill, IColor::black )
   .setMinimumSize( ISize( 10, 2 ) );

  MultiLineStaticText
    heading1( 12, &client, &client ),
    heading2( 13, &client, &client );
  heading1
   .setFraction( 0.4 )
   .setText( "Select a radio button from the group below." );
  heading2
   .setFraction( 0.4 )
   .setText( "This text consists of several words, and may"
               + IString( " wrap across several lines." ));

  IRadioButton
    none  ( 0, &client, &client ),
    first ( 1, &client, &client ),
    second( 2, &client, &client ),
    third ( 3, &client, &client ),
    fourth( 4, &client, &client );
  none
   .setText( "None" )
   .enableTabStop()
   .enableGroup();
  first.setText( "First" );
  second.setText( "Second" );
  third.setText( "Third" );
  fourth.setText( "Fourth" );

  client
   .addToCell( &heading1,  2, 2 )
   .addToCell( &heading2,  4, 2 )
   .addToCell( &none,      2, 4 )
   .addToCell( &first,     2, 6 )
   .addToCell( &second,    2, 8 )
   .addToCell( &third,     2, 10 )
   .addToCell( &fourth,    2, 12 )
   .addToCell( &separator, 2, 14, 3 )
   .addToCell( &output,    2, 15, 3 );
  client
   .setColumnWidth( 2, 0, true )
   .setColumnWidth( 4, 0, true )
   .setColumnWidth( 5,
                    IMultiCellCanvas::defaultCell().width() );

  unsigned long defaultHeight =
                  IMultiCellCanvas::defaultCell().height();
  client
   .setRowHeight( 1,  defaultHeight, true )
   .setRowHeight( 3,  defaultHeight, true )
   .setRowHeight( 13, defaultHeight, true )
   .setRowHeight( 16, defaultHeight, true );

  HumptyDumptySelectHandler selHdr( &output );
  selHdr.handleEventsFor( &client );

  // Size and show the window now.
  frame
   .moveSizeToClient( IRectangle( IPoint( 50, 50 ),
                                  client.minimumSize() ))
   .setFocus()
   .show();

  IApplication::current().run();
}
