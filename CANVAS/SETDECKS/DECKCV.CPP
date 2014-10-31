//************************************************************
// Canvas - ISetCanvas decks example.                         
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <icolor.hpp>
#include <ipoint.hpp>
#include <irect.hpp>
#include <istring.hpp>
#include "deckcv.hpp"
#include "setdecks.h"


DeckCanvas :: DeckCanvas ( unsigned long id,
                           IWindow* parentAndOwner,
                           IWindow* frameOrClient )
  : ISetCanvas( id, parentAndOwner, parentAndOwner ),
    cmdHandler( this ),
    childrenCreated( 0 )
{
  cmdHandler.handleEventsFor( frameOrClient );
  makeVertical();       // Set orientation and group box text.
}

DeckCanvas :: ~DeckCanvas ( )
{
  children.removeAll( &ChildDeleter );
}

unsigned long DeckCanvas :: childCount ( ) const
{
  return children.numberOfElements();
}

DeckCanvas& DeckCanvas :: setChildCount ( unsigned long count )
{
  while (childCount() < count)
  {                          // Need to add child windows.
     addAsLast();
  }
  while (childCount() > count)
  {                          // Need to remove child windows.
     removeLast();
  }
  return *this;
}

DeckCanvas& DeckCanvas :: addAsFirst ( )
{
  IStaticText* newChild =
          new IStaticText( childrenCreated + 1, this, this );
  setUpChild( newChild );
  children.addAsFirst( newChild );
  childrenCreated++;

#if 0
  if (IWindow::defaultOrdering() == IWindow::behindSiblings)
  {                          // Force to top
     newChild->positionOnSiblings();
  }
  else if (IWindow::defaultOrdering() == IWindow::onTopOfSiblings  &&
           areChildrenReversed())
  {                          // Add as last in compatibility mode
     newChild->positionBehindSiblings();
  }                          // Must put at end ourselves
#endif
  newChild->positionOnSiblings();  // Force to top.

  return *this;
}

DeckCanvas& DeckCanvas :: addAsLast ( )
{
  IStaticText* newChild =
          new IStaticText( childrenCreated + 1, this, this );
  setUpChild( newChild );
  children.addAsLast( newChild );
  childrenCreated++;

#if IC_MAJOR_VERSION < 201
  if (areChildrenReversed())
  {  // Children already reversed.
     // Must reverse this one ourselves.
     WinSetWindowPos( newChild->handle(),
                      HWND_BOTTOM, 0, 0, 0, 0, SWP_ZORDER );
  }
#else
#if 0
  if (IWindow::defaultOrdering() == IWindow::onTopOfSiblings  &&
      areChildrenReversed())
  {                          // In compatibility mode.
     newChild->positionBehindSiblings();
  }                          // Must put at end ourselves.
#endif
#endif

  return *this;
}

DeckCanvas& DeckCanvas :: removeFirst ( )
{
  if (! children.isEmpty())
  {                          // Child to delete.
     IStaticText* child = children.firstElement();
     delete child;
     children.removeFirst();
  }
  return *this;
}

DeckCanvas& DeckCanvas :: removeLast ( )
{
  if (! children.isEmpty())
  {                          // Child to delete.
     IStaticText* child = children.lastElement();
     delete child;
     children.removeLast();
  }
  return *this;
}

DeckCanvas& DeckCanvas :: setUpChild ( IStaticText* child )
{
  IColor bgColor( IColor::red );  // Assign color to child.
  switch (child->id() % 4)
  {                          // Alternate colors.
     case 1:
       bgColor = IColor::green;
       break;
     case 2:
       bgColor = IColor::blue;
       break;
     case 3:
       bgColor = IColor::yellow;
       break;
     case 0:                 // Use default color.
     default:
       break;
  } /* endswitch */

  (*child).setColor( IStaticText::fill, bgColor )
          .setColor( IStaticText::foreground, IColor::black )
          .setColor( IStaticText::background, IColor::white )
          .setAlignment( IStaticText::centerCenter)
          .setText( IString( child->id() ))
          .setMinimumSize( ISize( 80, 80 ) );

  return *this;
}

DeckCanvas& DeckCanvas :: makeHorizontal ( )
{
  (*this).setDeckOrientation( ISetCanvas::horizontal )
         .setText( "Horizontal decks" );
  return *this;
}

DeckCanvas& DeckCanvas :: makeVertical ( )
{
  (*this).setDeckOrientation( ISetCanvas::vertical )
         .setText( "Vertical decks" );
  return *this;
}

#if IC_MAJOR_VERSION < 201
DeckCanvas& DeckCanvas :: setLayoutDistorted( unsigned long flagsOn,
                                              unsigned long flagsOff )
/*******************************************************************/
/* Fix problem in IViewRectangle.                                  */
/*******************************************************************/
{
  ISetCanvas::setLayoutDistorted(flagsOn, flagsOff);
  if (flagsOn & minimumSizeChanged)
  {                               // change to child window size
     parent()->parent()->setLayoutDistorted(childMinimumSizeChanged, 0);
  }
  return *this;
}
#endif

DeckCanvas::DeckCommandHandler :: DeckCommandHandler
                                        ( DeckCanvas* canvas )
  : deckCanvas( canvas )
{ }

Boolean DeckCanvas::DeckCommandHandler :: command
                                        ( ICommandEvent& event )
{
  Boolean dontPassOn = false;
  switch ( event.commandId() )
  {
     case ID_DECK_HORZ:
     {
        deckCanvas->makeHorizontal();
        dontPassOn = true;
        break;
     }
     case ID_DECK_VERT:
     {
        deckCanvas->makeVertical();
        dontPassOn = true;
        break;
     }
     case ID_DECK_COUNT_1:
     case ID_DECK_COUNT_2:
     case ID_DECK_COUNT_3:
     case ID_DECK_COUNT_4:
     case ID_DECK_COUNT_5:
     case ID_DECK_COUNT_6:
     case ID_DECK_COUNT_7:
     case ID_DECK_COUNT_8:
     case ID_DECK_COUNT_9:
     {
        deckCanvas->setDeckCount( event.commandId()
                                    - ID_DECK_COUNT_1 + 1 );
        dontPassOn = true;
        break;
     }
     case ID_MARGIN_11:
     {
        deckCanvas->setMargin( ISize( 1, 1 ));
        dontPassOn = true;
        break;
     }
     case ID_MARGIN_88:
     {
        deckCanvas->setMargin( ISize( 8, 8 ));
        dontPassOn = true;
        break;
     }
     case ID_MARGIN_XX2:
     {
        deckCanvas->setMargin( deckCanvas->margin()
                                 * ISize( 2, 1 ));
        dontPassOn = true;
        break;
     }
     case ID_MARGIN_XD2:
     {
        deckCanvas->setMargin( deckCanvas->margin()
                                 / ISize( 2, 1 ));
        dontPassOn = true;
        break;
     }
     case ID_MARGIN_YX2:
     {
        deckCanvas->setMargin( deckCanvas->margin()
                                 * ISize( 1, 2 ));
        dontPassOn = true;
        break;
     }
     case ID_MARGIN_YD2:
     {
        deckCanvas->setMargin( deckCanvas->margin()
                                 / ISize( 1, 2 ));
        dontPassOn = true;
        break;
     }
     case ID_PAD_11:
     {
        deckCanvas->setPad( ISize( 1, 1 ));
        dontPassOn = true;
        break;
     }
     case ID_PAD_88:
     {
        deckCanvas->setPad( ISize( 8, 8 ));
        dontPassOn = true;
        break;
     }
     case ID_PAD_XX2:
     {
        deckCanvas->setPad( deckCanvas->pad() * ISize( 2, 1 ));
        dontPassOn = true;
        break;
     }
     case ID_PAD_XD2:
     {
        deckCanvas->setPad( deckCanvas->pad() / ISize( 2, 1 ));
        dontPassOn = true;
        break;
     }
     case ID_PAD_YX2:
     {
        deckCanvas->setPad( deckCanvas->pad() * ISize( 1, 2 ));
        dontPassOn = true;
        break;
     }
     case ID_PAD_YD2:
     {
        deckCanvas->setPad( deckCanvas->pad() / ISize( 1, 2 ));
        dontPassOn = true;
        break;
     }
     case ID_ADD_FIRST:
     {
        deckCanvas->addAsFirst();
        dontPassOn = true;
        break;
     }
     case ID_ADD_LAST:
     {
        deckCanvas->addAsLast();
        dontPassOn = true;
        break;
     }
     case ID_DELETE_FIRST:
     {
        deckCanvas->removeFirst();
        dontPassOn = true;
        break;
     }
     case ID_DELETE_LAST:
     {
        deckCanvas->removeLast();
        dontPassOn = true;
        break;
     }
     default:
        break;
  }

  return dontPassOn;
}
