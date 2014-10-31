//************************************************************
// Controls - Constructor and color sample
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <icolor.hpp>
#include <icombobx.hpp>
#include <ientryfd.hpp>
#include <iframe.hpp>
#include <ilistbox.hpp>
#include <iscroll.hpp>
#include "controls.h"

void main ( )
{
  IFrameWindow frame( ID_DIALOG );

  // Construct objects for dialog controls.
  IComboBox combo( ID_COMBOBOX, &frame );
  combo.addAsFirst( "The child entry field" );
  combo.addAsLast ( "  should have a cyan background." );
  IListBox listBox( ID_LISTBOX, &frame );
  listBox.addAsFirst( "The child horizontal scroll bar" );
  listBox.addAsLast ( "  should have a cyan scroll box." );
  listBox.addAsLast ( "-- A long, long, long list box item\
 to enable the horizontal scroll bar --" );

  // Find the entry field child of the combo box.
  Boolean deleteEntryField = false;
  IEntryField* ef =
    (IEntryField*)IWindow::windowWithId( 0x029B, &combo );
         // Note: IWindow::windowFromId works because we
         // know the combo box owns the entry field.  If we
         // weren't sure about the ownership, but knew the
         // combination box was the parent of the entry
         // field, we would have had to include <os2.h>,
         // and call the following instead.
         //   IWindowHandle handle =
         //     WinWindowFromID( combo.handle(), 0x29B );
         //   IEntryField* ef = (IEntryField*)
         //     IWindow::windowWithHandle( handle );
  if (!ef)         // No existing window object.
  {                // Construct a new one.
     ef = new IEntryField( 0x29B, &combo );
     deleteEntryField = true;
  }                // Else use the existing window object.
  ef->setColor( IEntryField::background,
                IColor( IColor::cyan ));
                   // Manipulate the entry field.
  if (deleteEntryField)
  {                // Memory clean-up.
     delete ef;
  }

  // Find the horizontal scroll bar child of the list box.
  Boolean
    deleteScrollBar = false,
    done = false;
  IScrollBar* sb = 0;
  IWindow::ChildCursor cursor( listBox );
  for (cursor.setToFirst();
       !done  &&  cursor.isValid();
       cursor.setToNext())
  {
     IWindowHandle childHandle = listBox.childAt( cursor );
     sb = (IScrollBar*)
            IWindow::windowWithHandle( childHandle );
         // Note: Our code here assumes that the application
         // has not added any child windows to the list box
         // (which may not be scroll bars).
     if (!sb)      // No existing window object.
     {             // Construct a new one.
        sb = new IScrollBar( childHandle );
        deleteScrollBar = true;
     }             // Else use the existing window object.
     if (sb->isHorizontal())
     {             // We found it.
        done = true;
     }
     else if (deleteScrollBar)
     {             // Horizontal scroll bar.
        delete sb;
        deleteScrollBar = false;
     }
  }
  if (sb)          // Found the horizontal scroll bar.
  {                // Change its color.
     sb->setColor( IScrollBar::scrollBox,
                   IColor( IColor::cyan ));
                   // Manipulate the scroll bar.
     if (deleteScrollBar)
     {             // Memory clean-up.
        delete sb;
     }
  }

  // Show the window now.
  frame
   .setFocus()
   .show();

  // Display the window until the user closes it.
  IApplication::current().run();
}
