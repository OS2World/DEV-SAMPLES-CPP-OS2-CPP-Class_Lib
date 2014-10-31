//************************************************************
// Extending the Library - Value Set Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#define INCL_WIN
#include <os2.h>

#include <iframe.hpp>
#include <icmdhdr.hpp>
#include <imenuhdr.hpp>
#include <ientryfd.hpp>
#include <istattxt.hpp>
#include <imenubar.hpp>
#include <isubmenu.hpp>
#include <ilistbox.hpp>

#include "valueset.hpp"
#include "vsethdr.hpp"
#include "testvset.h"

class CmdHandler : public ICommandHandler {
public:
  CmdHandler ( ValueSet &vset,
               IEntryField &input,
               IStaticText &output,
               IMenuBar    &menu,
               ValueSet    &palette )
    : ICommandHandler(),
      vset( vset ),
      in( input ),
      out( output ),
      menu( menu ),
      palette( palette )
    {
    this->handleEventsFor( &vset );
    }
protected:
virtual Boolean
  command ( ICommandEvent &cmd )
    {
    out.setText( "Ok" );
    switch ( cmd.commandId() )
      {
      case M_STYLE_BORDER:     // 101
        {
        vset.enableBorder( !vset.hasBorder() );
        vset.refresh();
        break;
        }
      case M_STYLE_ITEMBORDER: // 102
        {
        vset.enableItemBorder( !vset.hasItemBorder() );
        vset.refresh();
        break;
        }
      case M_STYLE_RTL:        // 103
        break;
      case M_STYLE_SCALE:      // 104
        {
        vset.enableBitmapScaling( !vset.willScaleBitmaps() );
        vset.refresh();
        break;
        }
      case M_STYLE_OWNERDRAW:  // 105
        {
        vset.enableDrawItem( !vset.isDrawItem() );
        vset.refresh();
        break;
        }

      case M_DIMENSIONS_QUERY:          // 201
        {
        ISize
          size = vset.dimensions();
        out.setText( "Value Set Size = " + size.asString() );
        break;
        }
      case M_DIMENSIONS_SET:            // 202
        {
        ISize
          size = ISize( in.text().word(1).asUnsigned(),
                        in.text().word(2).asUnsigned() );
        vset.setDimensions( size );
        break;
        }
      case M_DIMENSIONS_ITEMSIZE_QUERY: // 211
        {
        ISize
          size = vset.itemSize();
        out.setText( "Item Size = " + size.asString() );
        break;
        }
      case M_DIMENSIONS_ITEMSIZE_SET:   // 212
        {
        ISize
          size = ISize( in.text().word(1).asUnsigned(),
                        in.text().word(2).asUnsigned() );
        vset.setItemSize( size );
        break;
        }
      case M_DIMENSIONS_SPACING_QUERY:  // 221
        {
        ISize
          size = vset.itemSpacing();
        out.setText( "Item Spacing = " + size.asString() );
        break;
        }
      case M_DIMENSIONS_SPACING_SET:    // 222
        {
        ISize
          size = ISize( in.text().word(1).asUnsigned(),
                        in.text().word(2).asUnsigned() );
        vset.setItemSpacing( size );
        break;
        }
      case M_DIMENSIONS_MIN_QUERY:      // 231
        {
        ISize
          size = vset.minimumSize();
        out.setText( "Min Size = " + size.asString() );
        break;
        }
      case M_DIMENSIONS_MIN_SIZE:       // 232
        {
        IFrameWindow
         *frame = (IFrameWindow*)( vset.parent() );
        frame->moveSizeToClient( IRectangle( frame->position(),
                                             vset.minimumSize() ) );
        break;
        }

      case M_ITEMS_BITMAP: // 301
        {
        IPoint
          cell = vset.selection();
        static IBitmapHandle
          bmp = 0;
        if ( !bmp )
          bmp = IApplication::current().userResourceLibrary()
                  .loadBitmap( IC_DEFAULT_FRAME_ID );
        vset.setItemContents( cell.y(),
                              cell.x(),
                              bmp );
        break;
        }
      case M_ITEMS_COLOR:  // 302
        {
        IPoint
          cell = vset.selection();
        vset.setItemContents( cell.y(),
                              cell.x(),
                              palette.selectedItem().color() );
        break;
        }
      case M_ITEMS_ICON:   // 303
        {
        IPoint
          cell = vset.selection();
        static IPointerHandle
          ptr = 0;
        if ( !ptr )
          ptr = IApplication::current().userResourceLibrary()
                  .loadIcon( IC_DEFAULT_FRAME_ID );
        vset.setItemContents( cell.y(),
                              cell.x(),
                              ptr );
        break;
        }
      case M_ITEMS_TEXT:   // 304
        {
        IPoint
          cell = vset.selection();
        vset.setItemContents( cell.y(),
                              cell.x(),
                              in.text() );
        break;
        }
                        
      case M_ITEMSTYLE_SET:       // 401
        {
        IWindowHandle
          subHandle = menu.menuItem( M_ITEMSTYLE ).submenuHandle();
        ISubmenu
          subMenu( subHandle );
        ValueSet::ItemStyle
          style = ValueSet::noItemStyle;
        if ( subMenu.isItemChecked( M_ITEMSTYLE_DISABLED ) )
          style |= ValueSet::disabled;
        if ( subMenu.isItemChecked( M_ITEMSTYLE_DRAG ) )
          style |= ValueSet::dragSource;
        if ( subMenu.isItemChecked( M_ITEMSTYLE_DROP ) )
          style |= ValueSet::dropTarget;
        if ( subMenu.isItemChecked( M_ITEMSTYLE_OWNERDRAW ) )
          style |= ValueSet::itemOwnerDraw;
        IPoint
          cell = vset.selection();
        vset.setItemStyle( cell.y(),
                           cell.x(),
                           style );
        break;
        }
      case M_ITEMSTYLE_ENABLE:    // 402
        {
        IPoint
          cell = ISize( in.text().word(1).asUnsigned(),
                        in.text().word(2).asUnsigned() );
        vset.setItemStyle( cell.y(),
                           cell.x(),
                           vset.item( cell.y(), cell.x() ).style() 
                             & ~ValueSet::disabled );
        break;
        }
      case M_ITEMSTYLE_DISABLED:  // 403
      case M_ITEMSTYLE_DRAG:      // 404
      case M_ITEMSTYLE_DROP:      // 405
      case M_ITEMSTYLE_OWNERDRAW: // 406
        {
        IWindowHandle
          subHandle = menu.menuItem( M_ITEMSTYLE ).submenuHandle();
        ISubmenu
          subMenu( subHandle );
        subMenu
          .checkItem( cmd.commandId(),
                      !subMenu.isItemChecked( cmd.commandId() ) );
        break;
        }
      case M_COLORS_BACK:         // 501
        vset.setColor( ValueSet::background, 
                       palette.selectedItem().color() );
        break;
      case M_COLORS_BORDERS:      // 502
        vset.setColor( ValueSet::borders,
                       palette.selectedItem().color() );
        break;
      case M_COLORS_FORE:         // 503
        vset.setColor( ValueSet::foreground,
                       palette.selectedItem().color() );
        break;
      case M_COLORS_HILITE:       // 504
        vset.setColor( ValueSet::highlightBackground,
                       palette.selectedItem().color() );
        break;
      }
    return false;
    }
private:
ValueSet
 &vset;
IEntryField
 &in;
IStaticText
 &out;
IMenuBar
 &menu;
ValueSet
 &palette;
CmdHandler (const CmdHandler&);
CmdHandler& operator=(const CmdHandler&);
};

class MenuHandler : public IMenuHandler {
public:
  MenuHandler ( ValueSet &vset,
                IEntryField &input,
                ValueSet    &palette )
    : IMenuHandler(),
      vset( vset ),
      in( input ),
      palette( palette )
    {
    this->handleEventsFor( &vset );
    }
protected:
virtual Boolean
  menuShowing ( IMenuEvent &event,
                ISubmenu   &subMenu )
    {
    switch ( subMenu.id() )
      {
      case M_STYLE:     // 100
        {
        subMenu.checkItem( M_STYLE_BORDER, vset.hasBorder() );
        subMenu.checkItem( M_STYLE_ITEMBORDER, vset.hasItemBorder() );
        subMenu.checkItem( M_STYLE_RTL, vset.isRightToLeft() );
        subMenu.checkItem( M_STYLE_SCALE, vset.willScaleBitmaps() );
        subMenu.checkItem( M_STYLE_OWNERDRAW, vset.isDrawItem() );
        break;
        }
      case M_ITEMS:     // 300
        {
        Boolean
          active = vset.hasSelection();
        subMenu
          .enableItem( M_ITEMS_BITMAP, active )
          .checkItem ( M_ITEMS_BITMAP, false )
          .enableItem( M_ITEMS_COLOR, active )
          .checkItem ( M_ITEMS_COLOR, false )
          .enableItem( M_ITEMS_ICON, active )
          .checkItem ( M_ITEMS_ICON, false )
          .enableItem( M_ITEMS_TEXT, active )
          .checkItem ( M_ITEMS_TEXT, false );
        if ( active )
          {
          if ( vset.selectedItem().containsBitmap() 
               && 
               vset.selectedItem().bitmap() )
            subMenu
              .checkItem( M_ITEMS_BITMAP )
              .disableItem( M_ITEMS_BITMAP );
          else if ( vset.selectedItem().containsColor() )
            subMenu.checkItem( M_ITEMS_COLOR );
          else if ( vset.selectedItem().containsIcon() )
            subMenu
              .checkItem( M_ITEMS_ICON )
              .disableItem( M_ITEMS_ICON );
          else if ( vset.selectedItem().containsText() )
            subMenu.checkItem( M_ITEMS_TEXT );
          if ( !palette.hasSelection() )
            subMenu.disableItem( M_ITEMS_COLOR );
          }
        break;
        }
      case M_ITEMSTYLE: // 400
        {
        subMenu
          .disableItem( M_ITEMSTYLE_SET )
          .disableItem( M_ITEMSTYLE_ENABLE )
          .disableItem( M_ITEMSTYLE_DISABLED )
          .disableItem( M_ITEMSTYLE_DRAG )
          .disableItem( M_ITEMSTYLE_DROP )
          .disableItem( M_ITEMSTYLE_OWNERDRAW );
        if ( vset.hasSelection() )
          {
          ValueSet::Item
            item = vset.selectedItem();
          subMenu
            .enableItem( M_ITEMSTYLE_SET )
            .enableItem( M_ITEMSTYLE_DISABLED )
            .checkItem( M_ITEMSTYLE_DISABLED, false )
            .enableItem( M_ITEMSTYLE_DRAG )
            .checkItem( M_ITEMSTYLE_DRAG, item.canBeDragged() )
            .enableItem( M_ITEMSTYLE_DROP )
            .checkItem( M_ITEMSTYLE_DROP, item.canBeDroppedOn() )
            .enableItem( M_ITEMSTYLE_OWNERDRAW )
            .checkItem( M_ITEMSTYLE_OWNERDRAW, item.isOwnerDraw() );
          }
        IPoint
          cell = ISize( in.text().word(1).asUnsigned(),
                        in.text().word(2).asUnsigned() );
        if ( cell > IPoint()
             && 
             cell <= vset.dimensions()
             &&
             vset.item( cell.y(), cell.x() ).isDisabled() )
          subMenu.enableItem( M_ITEMSTYLE_ENABLE );
        break;
        }
      case M_COLORS: // 500
        {
        Boolean
          flag = palette.hasSelection();
        subMenu
          .enableItem( M_COLORS_BACK, flag )
          .enableItem( M_COLORS_BORDERS, flag )
          .enableItem( M_COLORS_FORE, flag )
          .enableItem( M_COLORS_HILITE, flag );
        break;
        }
      default:
        break;
      }
    return false;
    }
private:
ValueSet
 &vset;
IEntryField
 &in;
ValueSet
 &palette;
MenuHandler (const MenuHandler&);
MenuHandler& operator= (const MenuHandler&);
};

class MyVSetHandler : public ValueSetHandler {
public:
  MyVSetHandler ( ValueSet &vset,
                  IListBox &out )
    : ValueSetHandler( vset ),
      out( out )
    {
    }
protected:
virtual Boolean
  enter ( ValueSetEvent &event )
    {
    out.addAsLast( id(event) + ": enter "
                   + 
                   IPoint( event.column(),
                           event.row() ).asString() );
    return true;
    }
virtual Boolean
  selected ( ValueSetEvent &event )
    {
    out.addAsLast( id(event) + ": selected "
                   + 
                   IPoint( event.column(),
                           event.row() ).asString() );
    return true;
    }
virtual Boolean
  gotFocus ( ValueSetEvent &event )
    {
    out.addAsLast( id(event) + ": gotFocus" );
    return true;
    }
virtual Boolean
  lostFocus ( ValueSetEvent &event )
    {
    out.addAsLast( id(event) + ": lostFocus" );
    return true;
    }
virtual Boolean
  help ( ValueSetEvent &event )
    {
    out.addAsLast( id(event) + ": help "
                   + 
                   IPoint( event.column(),
                           event.row() ).asString() );
    return true;
    }
private:
IListBox
 &out;
IString
  id ( ValueSetEvent &event ) const
  {
  return ( event.valueSet()->id() != ID_PALETTE ) ?
             "Client"
           :
             "Colors";
  }
MyVSetHandler (const MyVSetHandler&);
MyVSetHandler& operator= (const MyVSetHandler&);
};

void main()
  {
  IFrameWindow
    frame;
  IMenuBar
    menu( IC_DEFAULT_FRAME_ID, &frame );
  IListBox
    lb( 0, &frame, &frame );
  ValueSet
    vsetClient( 0,
                &frame,
                &frame,
                ISize( 3, 4 ) );
  ValueSet
    palette( ID_PALETTE,
             &frame,
             &frame,
             ISize( 8, 2 ) );
  IColor
    colors[16] = { IColor::white, IColor::black, 
                   IColor::blue, IColor::red, 
                   IColor::pink, IColor::green, 
                   IColor::cyan, IColor::yellow, 
                   IColor::darkGray, IColor::darkBlue, 
                   IColor::darkRed, IColor::darkPink, 
                   IColor::darkGreen, IColor::darkCyan, 
                   IColor::brown, IColor::paleGray };
  for ( int i = 0; i < 16; i++ )
    {
    int
      row = ( i / 8 ) + 1,
      col = ( i % 8 ) + 1;
    palette.setItemContents( row, col, colors[i] );
    }
  IEntryField
    input( 0, &frame, &frame );
  IStaticText
    output( 0, &frame, &frame );
  CmdHandler
    cmdHandler( vsetClient, input, output, menu, palette );
  MenuHandler
    menuHandler( vsetClient, input, palette );
  MyVSetHandler
    vsetHandler( vsetClient, lb );
  vsetHandler.handleEventsFor( &palette );
  frame
    .addExtension( &palette, frame.aboveClient, 100 )
    .addExtension( &input, frame.aboveClient, 30 )
    .addExtension( &output, frame.belowClient, 30 )
    .addExtension( &lb, frame.rightOfClient, 250 )
    .setIcon( IC_DEFAULT_FRAME_ID )

    .setClient( &vsetClient )
    .setFocus(); 
  frame.showModally();
  }
