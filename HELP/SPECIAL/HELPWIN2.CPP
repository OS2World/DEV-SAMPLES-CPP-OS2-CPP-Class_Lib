/*************************************************************/
/* Special-topic help program.                               */
/*                                                           */
/* Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.       */
/* All Rights Reserved.                                      */
/*************************************************************/
#define  INCL_WININPUT    // For WinQueryFocus.
#include <os2.h>

#include <iapp.hpp>
#include <icnrctl.hpp>
#include <icnrhdr.hpp>
#include <idmcnrit.hpp>
#include <idmsrch.hpp>
#include <idmevent.hpp>
#include <iframe.hpp>
#include <ihelp.hpp>

#include "helpwin2.hpp"
#include "childhlp.hpp"
#include "helpwin2.h"

static ChildHelpHandler childHelpHdr;

void main ( )
{
  // Create a primary window with a container.
  IFrameWindow primary( "Special-Topic Help Sample", ID_PRIMARY );
  IContainerControl client( ID_CLIENT, &primary, &primary );
  client
   .showIconView()
   .arrangeIconView()
   .setDeleteObjectsOnClose();
  primary.setClient( &client );

  // Get default processing for an "open" and "help" event.
  ICnrHandler cnrHandler;
  cnrHandler.handleEventsFor( &client );

  // Support drag and drop of container objects.
  IDMHandler::enableDragDropFor( &client );
  CnrDragHelpProvider provider;
  client.setItemProvider( &provider );

  ISystemPointerHandle icon( ISystemPointerHandle::information );
  CnrObject* cnrObject = new CnrObject();
  (*cnrObject)
   .setIcon( icon )
   .setIconText( "Object 1" );
  client.addObject( cnrObject );

  // Create the help window and associate it with the primary.
  IHelpWindow::Settings settings;
  settings
   .setTitle( "Special-Topic Help Sample - Help" )
   .setLibraries( "HELPWIN2.HLP" )
   .setHelpTable( ID_HELPTABLE );
  IHelpWindow help( settings, &primary );

  client.setFocus();
  primary.show();
  IApplication::current().run();
}

void CnrObject :: handleOpen ( IContainerControl* container )
{
  ObjectView* frame =
     new ObjectView( ID_SECONDARY, 0, container );
  frame->setAutoDeleteObject();
  IHelpWindow* help = IHelpWindow::helpWindow( frame );
  help->associateWindow( frame );
  frame->show();
}

unsigned long CnrObject :: helpId ( ) const
{
  return PANEL_CONTAINER;
}

Boolean CnrDragHelpProvider :: provideHelpFor
                                 ( IDMTargetHelpEvent& event )
{
  IHelpWindow* help =
     IHelpWindow::helpWindow( event.window() );
  help->show( IResourceId( PANEL_DROP ));
  return true;
}

Boolean NotebookTabHelpHdr :: help ( IPageHelpEvent& event )
{
  Boolean stopProcessingEvent = false;
  IPageHandle page = event.pageHandle();
  INotebook::PageSettings settings =
                  event.notebook()->pageSettings( page );
  unsigned long panel = settings.userData();
  if (panel)
  {
     event.helpWindow()->show( IResourceId( panel ));
     stopProcessingEvent = true;
  }
  return stopProcessingEvent;
}

Boolean
  DynamicPageHelpHdr :: handleError ( IHelpErrorEvent& event )
{
  Boolean stopProcessingEvent = false;
  if (event.error() == IHelpErrorEvent::invalidHelpWindow)
  {                // For PANEL_NONE case.
     IWindowHandle focus = WinQueryFocus( HWND_DESKTOP );
     IFrameWindow* frame = (IFrameWindow*)event.window();
     INotebook* notebook = (INotebook*)frame->client();
     IPageHandle page = notebook->topPage();
     IWindow* pageWindow = notebook->window( page );
     unsigned long id = pageWindow->id();
     unsigned long panel = 0;
     if (id == ID_PAGE1)
     {
        panel = PANEL_PAGE1;
     }
     else if (id == ID_PAGE2)
     {
        panel = PANEL_PAGE2;
     }
     if (panel)
     {
        IHelpWindow* help = IHelpWindow::helpWindow( frame );
        help->show( IResourceId( panel ));
        stopProcessingEvent = true;
     }
  }
  return stopProcessingEvent;
}

Boolean DynamicPageHelpHdr :: subitemNotFound
                         ( IHelpSubitemNotFoundEvent& event )
{
  Boolean stopProcessingEvent = false;
  if (event.isWindow())
  {
     unsigned long panel = 0;
     if (event.topicId() == ID_PAGE1  &&
         event.subtopicId() == ID_ENTRY3)
     {
        panel = PANEL_ENTRY3;
     }
     else if (event.topicId() == ID_PAGE2  &&
              event.subtopicId() == ID_ENTRYC)
     {
        panel = PANEL_ENTRYC;
     }

     if (panel)
     {
        IFrameWindow* frame = (IFrameWindow*)event.window();
        IHelpWindow* help = IHelpWindow::helpWindow( frame );
        help->show( IResourceId( panel ));
        event.setResult(true);
        stopProcessingEvent = true;
     }
  }
  return stopProcessingEvent;
}

ObjectView :: ObjectView ( unsigned long id,
                           IWindow* parent,
                           IWindow* owner )
  : IFrameWindow ( id, parent, owner, IRectangle(),
                   IFrameWindow::defaultStyle()
                    | IFrameWindow::dialogBackground ),
    notebook ( ID_CLIENT, this, this ),
    page1 ( ID_PAGE1, &notebook, &notebook ),
    heading1 ( ID_DUMMY, &page1, &page1 ),
    prompt1  ( ID_DUMMY, &page1, &page1 ),
    prompt2  ( ID_DUMMY, &page1, &page1 ),
    prompt3  ( ID_DUMMY, &page1, &page1 ),
    entry1 ( ID_ENTRY1, &page1, &page1 ),
    entry2 ( ID_ENTRY2, &page1, &page1 ),
    entry3 ( ID_ENTRY3, &page1, &page1 ),
    page2 ( ID_PAGE2, &notebook, &notebook ),
    headingA ( ID_DUMMY, &page2, &page2 ),
    promptA  ( ID_DUMMY, &page2, &page2 ),
    promptB  ( ID_DUMMY, &page2, &page2 ),
    promptC  ( ID_DUMMY, &page2, &page2 ),
    entryA ( ID_ENTRYA, &page2, &page2 ),
    entryB ( ID_ENTRYB, &page2, &page2 ),
    entryC ( ID_ENTRYC, &page2, &page2 ),
    page3 ( ID_PAGE3, &notebook, &notebook, IRectangle(),
            IFrameWindow::dialogBackground ),
    page3a ( ID_CLIENT, &page3, &page3 ),
    headingX ( ID_DUMMY, &page3a, &page3a ),
    promptX  ( ID_DUMMY, &page3a, &page3a ),
    promptY  ( ID_DUMMY, &page3a, &page3a ),
    entryX ( ID_ENTRYX, &page3a, &page3a ),
    entryY ( ID_ENTRYY, &page3a, &page3a ),
    dialog ( ID_DIALOG, &notebook, &notebook )
{
  ITitle title( this, "Object1 - View" );
  this->setClient( &notebook );

  // Set-up the first page.
  heading1.setText( "This is a canvas page window." );
  prompt1.setText( "Has contextual help" );
  prompt2.setText( "No contextual help" );
  prompt3.setText( "Dynamic contextual help" );
  entry1
   .enableTabStop()
   .enableGroup();
  entry2.enableTabStop();
  entry3.enableTabStop();
  page1
   .addToCell( &heading1, 2, 2, 3 )
   .addToCell( &prompt1,  2, 4 )
   .addToCell( &prompt2,  2, 6 )
   .addToCell( &prompt3,  2, 8 )
   .addToCell( &entry1,   4, 4 )
   .addToCell( &entry2,   4, 6 )
   .addToCell( &entry3,   4, 8 );
  page1
   .setColumnWidth( 4, 1, true )
   .setColumnWidth( 7, IMultiCellCanvas::defaultCell().width() )
   .setRowHeight( 1, 20, true )
   .setRowHeight( 3, 20, true )
   .setRowHeight( 5, 20, true )
   .setRowHeight( 7, 20, true )
   .setRowHeight( 9, 20, true )
   .sizeTo( page1.minimumSize() );

  // Set-up the second page.
  headingA.setText( "This is another canvas page window." );
  promptA.setText( "Has contextual help" );
  promptB.setText( "No contextual help" );
  promptC.setText( "Dynamic contextual help" );
  entryA
   .enableTabStop()
   .enableGroup();
  entryB.enableTabStop();
  entryC.enableTabStop();
  page2
   .addToCell( &headingA, 2, 2, 3 )
   .addToCell( &promptA,  2, 4 )
   .addToCell( &promptB,  2, 6 )
   .addToCell( &promptC,  2, 8 )
   .addToCell( &entryA,   4, 4 )
   .addToCell( &entryB,   4, 6 )
   .addToCell( &entryC,   4, 8 );
  page2
   .setColumnWidth( 4, 1, true )
   .setColumnWidth( 7, IMultiCellCanvas::defaultCell().width() )
   .setRowHeight( 1, 20, true )
   .setRowHeight( 3, 20, true )
   .setRowHeight( 5, 20, true )
   .setRowHeight( 7, 20, true )
   .setRowHeight( 9, 20, true )
   .sizeTo( page2.minimumSize() );

  // Set-up the third page.
  childHelpHdr.handleEventsFor( &page3 );
  headingX.setText( "This is another canvas in a frame page window." );
  promptX.setText( "Has contextual help" );
  promptY.setText( "No contextual help" );
  entryX
   .enableTabStop()
   .enableGroup();
  entryY.enableTabStop();
  page3a
   .addToCell( &headingX, 2, 2, 3 )
   .addToCell( &promptX,  2, 4 )
   .addToCell( &promptY,  2, 6 )
   .addToCell( &entryX,   4, 4 )
   .addToCell( &entryY,   4, 6 );
  page3a
   .setColumnWidth( 4, 1, true )
   .setColumnWidth( 7, IMultiCellCanvas::defaultCell().width() )
   .setRowHeight( 1, 20, true )
   .setRowHeight( 3, 20, true )
   .setRowHeight( 5, 20, true )
   .setRowHeight( 7, 20, true )
   .sizeTo( page3a.minimumSize() );
  page3.setClient( &page3a );
  page3.setMinimumSize( page3.frameRectFor( page3a.rect() ).size() );

  // Set-up the fourth page.
  childHelpHdr.handleEventsFor( &dialog );

  IColor background =
    notebook.color( INotebook::notebookWindowBackground );
  notebook
   .setMinorTabSize( ISize( ) )
   .setBinding( INotebook::spiral )
   .setColor( INotebook::pageBackground, background )
   .setColor( INotebook::majorTabBackground, background );
  tabHelpHdr.handleEventsFor( &notebook );
  dynamicPageHelpHdr.handleEventsFor( this );

  // Add the pages to the notebook.
  INotebook::PageSettings
    pageInfo( "1st", 0,
              INotebook::PageSettings::autoPageSize
               | INotebook::PageSettings::majorTab );
  pageInfo.setUserData( PANEL_PAGE1_TAB );
  notebook.addFirstPage( pageInfo, &page1 );
  pageInfo
   .setTabText( "2nd" )
   .setUserData( PANEL_PAGE2_TAB );
  notebook.addLastPage( pageInfo, &page2 );
  pageInfo
   .setTabText( "3rd" )
   .setUserData( PANEL_PAGE3_TAB );
  notebook.addLastPage( pageInfo, &page3 );
  pageInfo
   .setTabText( "4rth" )
   .setUserData( PANEL_DIALOG_TAB );
  notebook.addLastPage( pageInfo, &dialog );

  IPoint nextShellPoint =
           IFrameWindow::nextShellRect().bottomLeft();

  this->moveSizeToClient(
           IRectangle( nextShellPoint,
                       (ISize)notebook.minimumSize() ));
  notebook.setFocus();
}
