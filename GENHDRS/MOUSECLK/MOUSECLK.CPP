//************************************************************
// Resuable Handlers - Mouse Handler Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <icolor.hpp>
#include <ientryfd.hpp>
#include <ifont.hpp>
#include <iframe.hpp>
#include <igroupbx.hpp>
#include <ilistbox.hpp>
#include <imchdr.hpp>
#include <imcelcv.hpp>
#include <ipoint.hpp>
#include <iradiobt.hpp>
#include <isetcv.hpp>
#include <istattxt.hpp>
#include <istring.hpp>

#define ID_CLIENT            0x8008    // FID_CLIENT
#define ID_HEADING           1
#define ID_LIST_BOX          2
#define ID_CANVAS            3
#define ID_STATIC_TEXT       4
#define ID_RADIO_BUTTON      5
#define ID_GROUP_BOX         6
#define ID_ENTRY_FIELD       7

class MouseClickWindow : public IVBase {
public:
  MouseClickWindow ( );
MouseClickWindow
 &showClickInfo    ( const IWindow* eventWindow,
                     const IWindowHandle& clicked,
                     IString button,
                     IString stateChange,
                     const IPoint& mousePosition );
protected:
IString
  nameForId        ( unsigned long id );
private:
IFrameWindow
  frame;
IMultiCellCanvas
  clientWindow;
IStaticText
  heading;
IListBox
  listBox;
ISetCanvas
  canvas;
IStaticText
  staticText;
IRadioButton
  radioButton;
IGroupBox
  groupBox;
IEntryField
  entryField;
unsigned long
  clickEntries,
  maxClickEntries;
class MouseClickHandler : public IMouseClickHandler {
  public:
  MouseClickHandler ( MouseClickWindow* window )
    : clickWindow( window )
    { }
  protected:
  virtual Boolean
    mouseClicked    ( IMouseClickEvent& event );
  private:
  IString
    textForButton   ( IMouseClickEvent::MouseNumber button );
  IString
    textForAction   ( IMouseClickEvent::MouseAction action );
  MouseClickWindow
   *clickWindow;
  };
MouseClickHandler
  mouseHdr;
MouseClickWindow (const MouseClickWindow&);
MouseClickWindow& operator=(const MouseClickWindow&);
};

void main ( )
{
  MouseClickWindow window;
  IApplication::current().run();
}

MouseClickWindow :: MouseClickWindow ( )
  : frame( "Mouse-Click Example" ),
    clientWindow( ID_CLIENT, &frame, &frame ),
    heading( ID_HEADING, &clientWindow, &clientWindow ),
    listBox( ID_LIST_BOX, &clientWindow, &clientWindow ),
    canvas( ID_CANVAS, &clientWindow, &clientWindow ),
    staticText( ID_STATIC_TEXT, &canvas, &canvas ),
    radioButton( ID_RADIO_BUTTON, &canvas, &canvas ),
    groupBox( ID_GROUP_BOX, &canvas, &canvas ),
    entryField( ID_ENTRY_FIELD, &canvas, &canvas ),
    clickEntries( 0 ),
    maxClickEntries( 100 ),
    mouseHdr( this )
{
  heading
   .setText( "      window()      handleOnTop()"
               + IString( "  mouseNumber() mouseAction()" )
               + IString( " mousePosition()" ));

  staticText
   .setColor( IStaticText::foreground, IColor::red )
   .setColor( IStaticText::background, IColor::yellow )
   .setText( "Static Text" );

  radioButton
   .setColor( IButton::foreground, IColor::darkGreen )
   .setColor( IButton::background, IColor::yellow )
   .setText( "Radio Button" );

  groupBox.setText( "Group Box  " );  // Adjust for calcMinimumSize.

  entryField
   .setLimit( 16 )
   .setText( "Entry Field" );

  clientWindow
   .addToCell( &heading, 2, 2 )
   .addToCell( &listBox, 2, 3 )
   .addToCell( &canvas, 2, 5 )
   .setColumnWidth( 2, 0, true )
   .setColumnWidth( 3, IMultiCellCanvas::defaultCell().width() )
   .setRowHeight( 3, 0, true )
   .setRowHeight( 6, IMultiCellCanvas::defaultCell().height() );

  IFont fixedFont( "Courier", 8 );  // For alignment.
  clientWindow.setFont( fixedFont );

  canvas.setColor( ISetCanvas::background, IColor::green );

  mouseHdr              // Attach to all windows.
   .handleEventsFor( &frame )
   .handleEventsFor( &clientWindow )
   .handleEventsFor( &heading )
   .handleEventsFor( &listBox )
   .handleEventsFor( &canvas )
   .handleEventsFor( &staticText )
   .handleEventsFor( &radioButton )
   .handleEventsFor( &groupBox )
   .handleEventsFor( &entryField );

  frame
   .setClient( &clientWindow )
   .setFocus()
   .show();
}

MouseClickWindow&
  MouseClickWindow :: showClickInfo ( const IWindow* eventWindow,
                                      const IWindowHandle& clicked,
                                      IString button,
                                      IString stateChange,
                                      const IPoint& mousePosition )
{
  if (listBox.count() > maxClickEntries)
  {                     // Don't let the list box grow too big.
     listBox.remove( 0 );  // Remove top entry.
  }

  IString handlerWindow = nameForId( eventWindow->id() );
  IWindow* window = IWindow::windowWithHandle( clicked );
  IString clickedWindow =
             nameForId( window ? window->id() : 0 );
  IString match( (eventWindow == window) ? "*" : " " );

  listBox.addAsLast( IString( ++clickEntries ) + ": "
                       + match + handlerWindow + "  "
                       + clickedWindow + "  "
                       + button + "   "
                       + stateChange + "  "
                       + mousePosition.asString() );
  listBox.setTop( listBox.count() );

  return *this;
}

IString MouseClickWindow :: nameForId ( unsigned long id )
{
  IString name;
  switch (id)
  {
     case IC_DEFAULT_FRAME_ID:
        name = "Frame window ";
        break;
     case ID_CLIENT:
        name = "Client window";
        break;
     case ID_HEADING:
        name = "Heading text ";
        break;
     case ID_LIST_BOX:
        name = "List Box     ";
        break;
     case ID_CANVAS:
        name = "Green canvas ";
        break;
     case ID_STATIC_TEXT:
        name = "Static Text  ";
        break;
     case ID_RADIO_BUTTON:
        name = "Radio Button ";
        break;
     case ID_GROUP_BOX:
        name = "Group Box    ";
        break;
     case ID_ENTRY_FIELD:
        name = "Entry Field  ";
        break;
     default:
        name = "Other        ";
        break;
  } /* endswitch */

  return name;
}

Boolean MouseClickWindow::MouseClickHandler :: mouseClicked
                                 ( IMouseClickEvent& event )
{
  IString button = this->textForButton( event.mouseNumber() );
  IString action = this->textForAction( event.mouseAction() );
  clickWindow->showClickInfo( event.window(),
                              event.handleOnTop(),
                              button, action,
                              event.mousePosition() );
  return false;         // Allow someone else to also process.
}

IString MouseClickWindow::MouseClickHandler :: textForButton
                        ( IMouseClickEvent::MouseNumber button )
{
  IString buttonText;
  switch (button)
  {
     case (IMouseClickEvent::button1):
        buttonText = "Button 1   ";
        break;
     case (IMouseClickEvent::button2):
        buttonText = "Button 2   ";
        break;
     case (IMouseClickEvent::button3):
        buttonText = "Button 3   ";
        break;
     case (IMouseClickEvent::button12):
        buttonText = "Buttons 1&2";
        break;
     default:
        buttonText = "Unknown    ";
        break;
  }
  return buttonText;
}

IString MouseClickWindow::MouseClickHandler :: textForAction
                        ( IMouseClickEvent::MouseAction action )
{
  IString actionText;
  switch (action)
  {
     case (IMouseClickEvent::click):
        actionText = "Single click";
        break;
     case (IMouseClickEvent::doubleClick):
        actionText = "Double click";
        break;
     case (IMouseClickEvent::down):
        actionText = "Down        ";
        break;
     case (IMouseClickEvent::up):
        actionText = "Up          ";
        break;
     default:
        actionText = "Unknown     ";
        break;
  }
  return actionText;
}
