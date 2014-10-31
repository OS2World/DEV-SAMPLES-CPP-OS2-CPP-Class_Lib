/*************************************************************/
/* Basic help program.                                       */
/*                                                           */
/* Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.       */
/* All Rights Reserved.                                      */
/*************************************************************/
#include <iapp.hpp>
#include <iframe.hpp>
#include <ihelp.hpp>
#include <ilistbox.hpp>
#include <imcelcv.hpp>
#include <imenubar.hpp>
#include <istattxt.hpp>

#include "helpwin.hpp"
#include "childhlp.hpp"
#include "hcmdhdr.hpp"
#include "hkeyshdr.hpp"
#include "tutorhdr.hpp"
#include "helpwin.h"

static ChildHelpHandler childHelpHdr;
static KeysHelpHandler keysHelpHdr;
static TutorialHandler tutorialHdr;

void main ( )
{
  // Create a primary window with a list box.
  IFrameWindow primary( "Basic Help Sample", ID_PRIMARY );
  IMenuBar menubar( &primary );
  menubar.setMenu( ID_MENUBAR );
  HelpCommandHandler helpCommandHdr;
  helpCommandHdr.handleEventsFor( &primary );

  IMultiCellCanvas client( ID_CLIENT, &primary, &primary );
  primary.setClient( &client );

  IStaticText heading( ID_DUMMY, &client, &client );
  heading.setText( "Select a type of window to create." );
  IListBox list( ID_LISTBOX, &client, &client );
  list.addAsLast( "Primary" );
  list.addAsLast( "Secondary (modeless)" );
  list.addAsLast( "Secondary (modal)" );
  list.addAsLast( "Child (modeless)" );
  list.addAsLast( "Child (modal)" );
  list
   .select( 0 )
   .enableTabStop()
   .enableGroup();

  // Processing for an "open" event.
  ListBoxSelectHandler selHandler;
  selHandler
   .handleEventsFor( &client );

  client
   .addToCell( &heading, 2, 2 )
   .addToCell( &list,    2, 4 );
  client
   .setColumnWidth( 2, 1, true )
   .setColumnWidth( 3, IMultiCellCanvas::defaultCell().width() )
   .setRowHeight( 4, 1, true )
   .setRowHeight( 5, IMultiCellCanvas::defaultCell().height() );

  // Create the help window and associate it with the primary.
  IHelpWindow::Settings settings;
  settings
   .setTitle( "Basic Help Sample - Help" )
   .setLibraries( "HELPWIN.HLP" )
   .setHelpTable( ID_HELPTABLE )
   .setTutorial( "VIEW.EXE TUTORIAL.INF" );
  IHelpWindow help( settings, &primary );

  keysHelpHdr.handleEventsFor( &primary );
  tutorialHdr.handleEventsFor( &primary );

  primary
   .setFocus()
   .show();
  IApplication::current().run();
}

Boolean ListBoxSelectHandler :: enter ( IControlEvent& event )
{
  Boolean dontPassOn = false;
  if (event.controlId() == ID_LISTBOX)
  {
     long selection =
       ((IListBox*)event.controlWindow())->selection();
     switch (selection)
     {
       case 0:     // Another primary window.
       {
         PrimaryWindow* frame = new PrimaryWindow;
         frame->setAutoDeleteObject();
         IHelpWindow* help =
           IHelpWindow::helpWindow( event.window() );
         help->associateWindow( frame );
         keysHelpHdr.handleEventsFor( frame );
         tutorialHdr.handleEventsFor( frame );
         frame->show();
         break;
       }
       case 1:     // Modeless secondary window.
       {
         SecondaryWindow* frame =
            new SecondaryWindow( ID_SECONDARY_MODELESS,
                                 event.window() );
         frame->setAutoDeleteObject();
         IHelpWindow* help = IHelpWindow::helpWindow( frame );
         help->associateWindow( frame );
         keysHelpHdr.handleEventsFor( frame );
         tutorialHdr.handleEventsFor( frame );
         frame->show();
         break;
       }
       case 2:     // Modal secondary window.
       {
         SecondaryWindow frame( ID_SECONDARY_MODAL,
                                event.window() );
         IHelpWindow* help =
                        IHelpWindow::helpWindow( &frame );
         help->associateWindow( &frame );
         keysHelpHdr.handleEventsFor( &frame );
         tutorialHdr.handleEventsFor( &frame );
         frame.showModally();
         break;
       }
       case 3:     // Modeless child window.
       {
         ChildWindow* frame =
            new ChildWindow( ID_CHILD_MODELESS,
                             event.window(),
                             event.window() );
         frame->setAutoDeleteObject();
//       Help won't dismiss when child window is closed.
//       IHelpWindow* help =
//                      IHelpWindow::helpWindow( frame );
//       help->associateWindow( frame );  // no effect?
         childHelpHdr.handleEventsFor( frame );
         frame->show();
         break;
       }
       case 4:     // Modal child window.
       {
         ChildWindow frame( ID_CHILD_MODAL,
                            event.window(),
                            0 );
//       Help won't dismiss when child window is closed.
//       IHelpWindow* help =
//                      IHelpWindow::helpWindow( &frame );
//       help->associateWindow( &frame );  // no effect?
         childHelpHdr.handleEventsFor( &frame );
         frame.showModally();
         break;
       }
       default:
         break;
     }
     dontPassOn = true;
  }
  return dontPassOn;
}
