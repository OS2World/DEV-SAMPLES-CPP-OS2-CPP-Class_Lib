//************************************************************
// Extending the Library - Value Set Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#define INCL_WIN
#define INCL_GPI
#include <os2.h>

#include "valueset.hpp"

#include <iexcept.hpp>
#include <ireslib.hpp>

// Static Data Member Definitions

const ValueSet::Style
  ValueSet::border            = VS_BORDER,
  ValueSet::itemBorder        = VS_ITEMBORDER,
  ValueSet::rightToLeft       = VS_RIGHTTOLEFT,
  ValueSet::scaleBitmaps      = VS_SCALEBITMAPS,
  ValueSet::drawItem          = VS_OWNERDRAW,
  ValueSet::classDefaultStyle = WS_VISIBLE;

ValueSet::Style
  ValueSet::dfltStyle = WS_VISIBLE;

const ValueSet::ItemStyle
  ValueSet::noItemStyle   = 0,
  ValueSet::disabled      = VIA_DISABLED,
  ValueSet::dragSource    = VIA_DRAGGABLE,
  ValueSet::dropTarget    = VIA_DROPONABLE,
  ValueSet::itemOwnerDraw = VIA_OWNERDRAW;

ValueSet::ItemStyle
  ValueSet::Item::dfltStyle = ValueSet::noItemStyle;

// ValueSet

ValueSet :: ValueSet ( const IWindowHandle &hwnd )
  : IControl()
  {
  this -> initialize( hwnd );
  }

ValueSet :: ValueSet ( IWindow *parent,
                       unsigned long id )
  : IControl()
  {
  this -> initialize( WinWindowFromID( parent->handle(), id ) );
  }

ValueSet :: ValueSet ( unsigned long     id,
                       IWindow          *parent,
                       IWindow          *owner,
                       const IRectangle &initial,
                       const Style      &style )
  : IControl()
  {
  this -> initialize ( ISize(0,0),
                       id,
                       parent,
                       owner,
                       initial,
                       style );
  }

ValueSet :: ValueSet ( unsigned long     id,
                       IWindow          *parent,
                       IWindow          *owner,
                       const ISize      &rowsAndColumns,
                       const IRectangle &initial,
                       const Style      &style )
  : IControl()
  {
  this -> initialize( rowsAndColumns,
                      id, 
                      parent, 
                      owner, 
                      initial,
                      style );
  }

ValueSet :: ~ValueSet ()
  {
  }

ValueSet::Style ValueSet :: defaultStyle ( )
  {
  return ValueSet::dfltStyle;
  }

void ValueSet :: setDefaultStyle ( const Style &style ) 
  {
  ValueSet::dfltStyle = style;
  }

Boolean ValueSet :: hasBorder ( ) const
  {
  return this->style() & VS_BORDER;
  }

Boolean ValueSet :: hasItemBorder ( ) const
  {
  return this->style() & VS_ITEMBORDER;
  }

Boolean ValueSet :: isRightToLeft ( ) const
  {
  return this->style() & VS_RIGHTTOLEFT;
  }

Boolean ValueSet :: willScaleBitmaps ( ) const
  {
  return this->style() & VS_SCALEBITMAPS;
  }

Boolean ValueSet :: isDrawItem ( ) const
  {
  return this->style() & VS_OWNERDRAW;
  }

ValueSet &ValueSet :: enableBorder ( Boolean flag )
  {
  if ( flag )
    this->setStyle( this->style() | VS_BORDER );
  else
    this->setStyle( this->style() & ~VS_BORDER );
  return *this;
  }

ValueSet &ValueSet :: disableBorder ( )
  {
  return this->enableBorder( false );
  }

ValueSet &ValueSet :: enableItemBorder ( Boolean flag )
  {
  if ( flag )
    this->setStyle( this->style() | VS_ITEMBORDER );
  else
    this->setStyle( this->style() & ~VS_ITEMBORDER );
  return *this;
  }

ValueSet &ValueSet :: disableItemBorder ( )
  {
  return this->enableItemBorder( false );
  }

ValueSet &ValueSet :: enableBitmapScaling ( Boolean flag )
  {
  if ( flag )
    this->setStyle( this->style() | VS_SCALEBITMAPS );
  else
    this->setStyle( this->style() & ~VS_SCALEBITMAPS );
  return *this;
  }

ValueSet &ValueSet :: disableBitmapScaling ( )
  {
  return this->enableBitmapScaling( false );
  }

ValueSet &ValueSet :: enableDrawItem ( Boolean flag )
  {
  if ( flag )
    this->setStyle( this->style() | VS_OWNERDRAW );
  else
    this->setStyle( this->style() & ~VS_OWNERDRAW );
  return *this;
  }

ValueSet &ValueSet :: disableDrawItem ( )
  {
  return this->enableDrawItem( false );
  }

ISize ValueSet :: dimensions ( ) const
  {
  ISize
    result;
  IString
    ctlData = ValueSet::controlData( ISize( 0, 0 ) );
  WNDPARAMS
    parms = { WPM_CTLDATA,
              0,
              0,
              0,
              0,
              ((VSCDATA*)(char*)ctlData)->cbSize,
              (char*)ctlData };
  if ( sendEvent( WM_QUERYWINDOWPARAMS, &parms ) != 0 )
    {
    VSCDATA
     *p = (VSCDATA*)( parms.pCtlData );
    result = ISize( p->usColumnCount, p->usRowCount );
    }
  else
    ITHROWGUIERROR( "WM_QUERYWINDOWPARAMS" );
  return result;
  }

unsigned long ValueSet :: numberOfRows ( ) const
  {
  return this->dimensions().height();
  }

unsigned long ValueSet :: numberOfColumns ( ) const
  {
  return this->dimensions().width();
  }

ValueSet &ValueSet :: setDimensions ( const ISize &dimensions )
  {
  IString
    ctlData = ValueSet::controlData( dimensions );
  WNDPARAMS
    parms = { WPM_CTLDATA,
              0,
              0,
              0,
              0,
              0,
              (char*)ctlData };
  if ( sendEvent( WM_SETWINDOWPARAMS, &parms ) == 0 )
    ITHROWGUIERROR( "WM_SETWINDOWPARAMS" );
  return *this;
  }

ValueSet &ValueSet :: setNumberOfRows ( unsigned long rows )
  {
  return this->setDimensions( this->dimensions().setHeight( rows ) );
  }

ValueSet &ValueSet :: setNumberOfColumns ( unsigned long columns )
  {
  return this->setDimensions( this->dimensions().setWidth( columns ) );
  }

ValueSet::Item ValueSet :: item ( unsigned long row,
                                  unsigned long column ) const
  {
  Item
    result;
  IEventParameter1
    rowAndCol( row, column );
  unsigned short
    attr = sendEvent( VM_QUERYITEMATTR, rowAndCol );
  if ( attr == VSERR_INVALID_PARAMETERS )
    ITHROWGUIERROR( "VM_QUERYITEMATTR" );
  else if ( attr & VIA_BITMAP )
    result = Item( IBitmapHandle( itemHandle( row, column ) ),
                   ItemStyle( attr & ~VIA_BITMAP ) );
  else if ( attr & VIA_ICON )
    result = Item( IPointerHandle( itemHandle( row, column ) ),
                   ItemStyle( attr & ~VIA_ICON ) );
  else if ( attr & VIA_TEXT )
    {
    VSTEXT
      vstext = { 0, 0 };
    unsigned
      size = sendEvent( VM_QUERYITEM, rowAndCol, &vstext );
    if ( size == VSERR_INVALID_PARAMETERS )
      ITHROWGUIERROR( "VM_QUERYITEM" );
    IString
      text( 0, size );
    vstext.ulBufLen = size + 1;
    vstext.pszItemText = text;
    unsigned
      rc = sendEvent( VM_QUERYITEM, rowAndCol, &vstext );
    if ( rc == VSERR_INVALID_PARAMETERS )
      ITHROWGUIERROR( "VM_QUERYITEM" );
    result = Item( text, ItemStyle( attr & ~VIA_TEXT ) );
    }
  else 
    {
    unsigned
      index = itemHandle( row, column );
    if ( attr & VIA_RGB )
      {
      unsigned
        red   = index >> 16,
        green = ( index >> 8 ) % 256,
        blue  = index % 256;
      result = Item( IColor( red, green, blue ),
                     ItemStyle( attr & ~VIA_RGB ) );
      }
    else
      {
      IPresSpaceHandle
        hps = presSpace();
      long
        rgbIndex = GpiQueryRGBColor( hps, 0, index );
      releasePresSpace( hps );
      if ( rgbIndex >= 0 )
        {
        unsigned
          red   = rgbIndex >> 16,
          green = ( rgbIndex >> 8 ) % 256,
          blue  = rgbIndex % 256;
        result = Item( IColor( red, green, blue ),
                       ItemStyle( attr & ~VIA_COLORINDEX ) );
        }
      else
        ITHROWSYSTEMERROR( rgbIndex, 
                           "GpiQueryRGBColor", 
                           ISystemErrorInfo::accessError,
                           recoverable );
      }
    }
  return result;
  }

ValueSet &ValueSet :: setItem ( unsigned long  row,
                                unsigned long  column,
                                const Item    &item )
  {
  unsigned long
    attr = item.style().asUnsignedLong();
  IEventParameter2
    mp2 = 0;
  IString
    text = item.text();
  if ( item.containsBitmap() )
    {
    attr |= VIA_BITMAP;
    mp2 = IEventParameter2( item.bitmap() );
    }
  else if ( item.containsIcon() )
    {
    attr |= VIA_ICON;
    mp2 = IEventParameter2( item.icon() );
    }
  else if ( item.containsText() )
    {
    attr |= VIA_TEXT;
    mp2 = (char*)text;
    }
  else if ( item.containsColor() )
    {
    attr |= VIA_RGB;
    mp2 = (int)( item.color().asRGBLong() );
    }
  else
    return *this;

  // Turn off all zero bits:
  setItemAttributes( row, 
                     column,
                     IEventParameter2( ~attr & 0x1e0, false ) );
  // Turn on all one bits.
  setItemAttributes( row, 
                     column,
                     IEventParameter2( attr, true ) );
  // Set item contents.
  setItem( row, column, mp2 );

  return *this;
  }

ValueSet &ValueSet :: setItemContents ( unsigned long      row,
                                        unsigned long      column,
                                        const IResourceId &resId,
                                        ItemType           type )
  {
  const IResourceLibrary
   &resLib = resId.resourceLibrary();
  switch ( type )
    {
    case bitmapItem:
      setItemContents( row, column, resLib.loadBitmap( resId.id() ) );
      break;
    case iconItem:
      setItemContents( row, column, resLib.loadIcon( resId.id() ) );
      break;
    case textItem:
      setItemContents( row, column, resLib.loadString( resId.id() ) );
      break;
    }
  return *this;
  }

ValueSet &ValueSet :: setItemContents ( unsigned long row,
                                        unsigned long column,
                                        const IBitmapHandle &bmp )
  {
  setItemAttributes( row,
                     column,
                     IEventParameter2( VIA_BITMAP, true ) );
  setItem( row,
           column,
           IEventParameter2( bmp ) );
  return *this;
  }

ValueSet &ValueSet :: setItemContents ( unsigned long row,
                                        unsigned long column,
                                        const IPointerHandle &icon )
  {
  setItemAttributes( row,
                     column,
                     IEventParameter2( VIA_ICON, true ) );
  setItem( row,
           column,
           IEventParameter2( icon ) );
  return *this;
  }

ValueSet &ValueSet :: setItemContents ( unsigned long  row,
                                        unsigned long  column,
                                        const IString &text )
  {
  setItemAttributes( row,
                     column,
                     IEventParameter2( VIA_TEXT, true ) );
  setItem( row,
           column,
           (char*)text );
  return *this;
  }

ValueSet &ValueSet :: setItemContents ( unsigned long row,
                                        unsigned long column,
                                        const IColor &color )
  {
  setItemAttributes( row,
                     column,
                     IEventParameter2( VIA_RGB, true ) );
  setItem( row,
           column,
           (int)( color.asRGBLong() ) );
  return *this;
  }

ValueSet &ValueSet :: setItemStyle ( unsigned long row,
                                     unsigned long column,
                                     const ItemStyle &style )
  {
  unsigned long
    attr = style.asUnsignedLong();
  // Turn off all zero bits.
  setItemAttributes( row,
                     column,
                     IEventParameter2( ~attr & 0x1e0, false ) );
  // Turn on all one bits.
  setItemAttributes( row,
                     column,
                     IEventParameter2( attr, true ) );
  return *this;
  }

Boolean ValueSet :: hasSelection ( ) const
  {
  return selection() != IPoint( 0, 0 );
  }

ValueSet &ValueSet :: setSelection ( unsigned row,
                                     unsigned column )
  {
  unsigned long
    rc = sendEvent( VM_SELECTITEM,
                    IEventParameter1( row, column ) );
  if ( !rc )
    ITHROWGUIERROR( "VM_SELECTITEM" );
  return *this;
  }

ValueSet::Item ValueSet :: selectedItem ( ) const
  {
  IPoint
    pt = selection();
  return item( pt.y(), pt.x() );
  }

IPoint ValueSet :: selection ( ) const
  {
  unsigned long
    rowAndCol = sendEvent( VM_QUERYSELECTEDITEM );
  return IPoint( rowAndCol >> 16,
                 rowAndCol & 0xffffU );
  }

unsigned long ValueSet :: selectedRow ( ) const
  {
  return selection().y();
  }

unsigned long ValueSet :: selectedColumn ( ) const
  {
  return selection().x();
  }

ISize ValueSet :: itemSize ( ) const
  {
  return metrics( VMA_ITEMSIZE );
  }

ISize ValueSet :: itemSpacing ( ) const
  {
  return metrics( VMA_ITEMSPACING );
  }

ValueSet &ValueSet :: setItemSize ( const ISize &size )
  {
  setMetrics( VMA_ITEMSIZE,
              size );
  return *this;
  }

ValueSet &ValueSet :: setItemSpacing ( const ISize &size )
  {
  setMetrics( VMA_ITEMSPACING,
              size );
  return *this;
  }

IColor ValueSet :: color ( ColorArea area ) const
  {
  unsigned long
    colorArea;
  IGUIColor
    defaultColor( IGUIColor::windowBgnd );
  switch ( area )
    {
    case borders:
      colorArea    = PP_BORDERCOLOR;
      defaultColor = IGUIColor::frameBorder;
      break;
    case foreground:
      colorArea    = PP_FOREGROUNDCOLOR;
      defaultColor = IGUIColor::windowText;
      break;
    case background:
      colorArea    = PP_BACKGROUNDCOLOR;
      defaultColor = IGUIColor::windowBgnd;
      break;
    case highlightBackground:
      colorArea    = PP_HILITEBACKGROUNDCOLOR;
      defaultColor = IGUIColor::hiliteBgnd;
      break;
    }
  return IWindow::color( colorArea, defaultColor );
  }

ValueSet &ValueSet :: setColor ( ColorArea     area,
                                 const IColor &color )
  {
  unsigned long
    colorArea;
  switch ( area )
    {
    case borders:
      colorArea    = PP_BORDERCOLOR;
      break;
    case foreground:
      colorArea    = PP_FOREGROUNDCOLOR;
      break;
    case background:
      colorArea    = PP_BACKGROUNDCOLOR;
      break;
    case highlightBackground:
      colorArea    = PP_HILITEBACKGROUNDCOLOR;
      break;
    }
  IWindow::setColor( colorArea, color );
  return *this;
  }

void ValueSet :: initialize ( const ISize      &size,
                              unsigned long     id,
                              IWindow          *parent,
                              IWindow          *owner,
                              const IRectangle &initial,
                              const Style      &style )
  {
  IString
    ctlData = ValueSet::controlData( size );
  IWindowHandle
    hwnd = this -> create( id,
                           0,
                           style.asUnsignedLong(),
                           WC_VALUESET,
                           parent->handle(),
                           owner ? owner->handle() : IWindowHandle(0),
                           initial,
                           (char*)ctlData,
                           0 );
  this -> startHandlingEventsFor( hwnd );
  }

void ValueSet :: initialize ( const IWindowHandle &hwnd )
  {
  IASSERTPARM( hwnd.isValid() );
  IString
    className( "#nn" );
  WinQueryClassName( hwnd, 4, className );
  IASSERTSTATE( className == "#39" );
  this -> startHandlingEventsFor( hwnd );
  this -> setAutoDestroyWindow( false );
  }

void ValueSet :: setItemAttributes ( unsigned long           row,
                                     unsigned long           column,
                                     const IEventParameter2 &attr )
  {
  IEventParameter1
    coord( row, column );
  if ( sendEvent( VM_SETITEMATTR,
                  coord,
                  attr ) == 0 )
    ITHROWGUIERROR( "VM_SETITEMATTR" );
  }

void ValueSet :: setItem ( unsigned long           row,
                           unsigned long           column,
                           const IEventParameter2 &contents )
  {
  IEventParameter1
    coord( row, column );
  if ( sendEvent( VM_SETITEM,
                  coord,
                  contents ) == 0 )
    ITHROWGUIERROR( "VM_SETITEM" );
  }

void ValueSet :: setMetrics ( const IEventParameter1 &mp1,
                              const ISize            &size )
  {
  unsigned long
    rc = sendEvent( VM_SETMETRICS,
                    mp1,
                    IEventParameter2( size.width(), size.height() ) );
  if ( !rc )
    ITHROWGUIERROR( "VM_SETMETRICS" );
  }

IString ValueSet :: controlData ( const ISize &size )
  {
  IString
    result( 0, sizeof( VSCDATA ) );
  VSCDATA
   *p = (VSCDATA*)(char*)result;
  p->cbSize = sizeof( VSCDATA );
  p->usRowCount = size.height();
  p->usColumnCount = size.width();
  return result;
  }

unsigned long ValueSet :: itemHandle ( unsigned long row,
                                       unsigned long column ) const
  {
  IEventParameter1
    rowAndCol( row, column );
  unsigned long
    rc = sendEvent( VM_QUERYITEM, rowAndCol, 0 );
  IASSERTSTATE( rc != VSERR_INVALID_PARAMETERS );
  return rc;
  }

ISize ValueSet :: metrics ( const IEventParameter1 &mp1 ) const
  {
  unsigned long
    rc = sendEvent( VM_QUERYMETRICS,
                    mp1 );
  if ( rc == VSERR_INVALID_PARAMETERS )
    ITHROWGUIERROR( "VM_QUERYMETRICS" );
  return ISize( rc & 0xffffU,
                rc >> 16 );
  }

ISize ValueSet :: calcMinimumSize ( ) const
  {
  ISize
    dim = dimensions();
  // Find widest and tallest items...
  unsigned
    widest  = 0,
    tallest = 0;
  for ( unsigned row = 0; row < dim.height(); row++ )
    for ( unsigned col = 0; col < dim.width(); col++ )
      {
      Item
        cell = item( row+1, col+1 );
      ISize
        size;
      switch ( cell.itemType )
        {
        case ValueSet::Item::emptyItem:
          // Empty items must be at least 2x2.
          size = ISize( 2, 2 );
          break;
        case ValueSet::Item::colorItem:
          // We'll make color items at least 5x5.
          size = ISize( 5, 5 );
          break;
        case ValueSet::Item::bitmapItem:
          // We'll make bitmap items at least 50x50.
          size = ISize( 50, 50 );
          break;
        case ValueSet::Item::iconItem:
          // We'll make icon items at least 32x32.
          size = ISize( 32, 32 );
          break;
        case ValueSet::Item::textItem:
          // We'll make text items average char size * length of text.
          size = ((ValueSet*)this)->characterSize()
                   .scaledBy( cell.text().length(), 1 );
          break;
        }
      // Update maximums if this item is bigger...
      if ( size.width() > widest )
        widest = size.width();
      if ( size.height() > tallest )
        tallest = size.height();
      }
  // Calculate size that will hold all items + 12 for border:
  ISize
    min = ISize( widest  * dim.width() + 12,
                 tallest * dim.height() + 12 );
  ISize
    space = itemSpacing();
  // Add horizontal space, including 7 for border/highlighting:
  if ( dim.width() > 1 )
    min.setWidth( min.width() 
                  + 
                  (dim.width()-1)*( space.width() + 7 ) );
  // Add vertical space, including 7 for border/highlighting:
  if ( dim.height() > 1 )
    min.setHeight( min.height() 
                   + 
                   (dim.height()-1)*( space.height() + 7 ) );
  return min;
  }

//============================== ValueSet::Item ================================

ValueSet::Item :: Item ( )
  : itemType( emptyItem ),
    itemColor( IColor::white ),
    itemStyle( defaultStyle() )
  {
  }

ValueSet::Item :: Item ( const IResourceId &resId,
                         ItemType           type,
                         const ItemStyle   &style )
  : itemType( emptyItem ),
    itemColor( IColor::white ),
    itemStyle( style )
  {
  switch ( type )
    {
    case bitmapItem:
      itemBmpHandle = resId.resourceLibrary().loadBitmap( resId.id() );
      itemType = bitmapItem;
      break;
    case iconItem:
      itemPtrHandle = resId.resourceLibrary().loadPointer( resId.id() );
      itemType = iconItem;
      break;
    case textItem:
      itemText = resId.resourceLibrary().loadString( resId.id() );
      itemType = textItem;
      break;
    default:
      break;
    }
  }

ValueSet::Item :: Item ( const IBitmapHandle &bmp,
                         const ItemStyle     &style )
  : itemType( bitmapItem ),
    itemBmpHandle( bmp ),
    itemColor( IColor::white ),
    itemStyle( style )
  {
  }

ValueSet::Item :: Item ( const IPointerHandle &ptr,
                         const ItemStyle      &style )
  : itemType( iconItem ),
    itemPtrHandle( ptr ),
    itemColor( IColor::white ),
    itemStyle( style )
  {
  }

ValueSet::Item :: Item ( const IString   &text,
                         const ItemStyle &style )
  : itemType( textItem ),
    itemText( text ),
    itemColor( IColor::white ),
    itemStyle( style )
  {
  }

ValueSet::Item :: Item ( const IColor    &color,
                         const ItemStyle &style )
  : itemType( colorItem ),
    itemColor( color ),
    itemStyle( style )
  {
  }

ValueSet::Item :: Item ( const Item &item )
  : itemType     ( item.itemType ),
    itemBmpHandle( item.itemBmpHandle ),
    itemPtrHandle( item.itemPtrHandle ),
    itemColor    ( item.itemColor ),
    itemText     ( item.itemText  ),
    itemStyle    ( item.itemStyle )
  {
  }

ValueSet::Item :: ~Item ( )
  {
  }

ValueSet::ItemStyle ValueSet::Item :: style ( ) const
  {
  return itemStyle;
  }

ValueSet::Item &ValueSet::Item :: setStyle ( const ItemStyle &style )
  {
  itemStyle = style;
  return *this;
  }

ValueSet::ItemStyle ValueSet::Item :: defaultStyle ( )
  {
  return dfltStyle;
  }

void ValueSet::Item :: setDefaultStyle ( const ItemStyle &style )
  {
  dfltStyle = style;
  }

Boolean ValueSet::Item :: isDisabled ( ) const
  {
  return itemStyle & disabled;
  }

Boolean ValueSet::Item :: isEnabled ( ) const
  {
  return !isDisabled();
  }

Boolean ValueSet::Item :: canBeDragged ( ) const
  {
  return itemStyle & dragSource;
  }

Boolean ValueSet::Item :: canBeDroppedOn ( ) const
  {
  return itemStyle & dropTarget;
  }

Boolean ValueSet::Item :: isOwnerDraw ( ) const
  {
  return itemStyle & itemOwnerDraw;
  }

ValueSet::Item &ValueSet::Item :: enable ( Boolean enable )
  {
  if ( enable )
    setStyle( style() | disabled );
  else
    setStyle( style() & ~disabled );
  return *this;
  }

ValueSet::Item &ValueSet::Item :: disable ( )
  {
  return enable( false );
  }

ValueSet::Item &ValueSet::Item :: enableDrag ( Boolean enable )
  {
  if ( enable )
    setStyle( style() | dragSource );
  else
    setStyle( style() & ~dragSource );
  return *this;
  }

ValueSet::Item &ValueSet::Item :: disableDrag ( )
  {
  return enableDrag( false );
  }

ValueSet::Item &ValueSet::Item :: enableDrop ( Boolean enable )
  {
  if ( enable )
    setStyle( style() | dropTarget );
  else
    setStyle( style() & ~dropTarget );
  return *this;
  }

ValueSet::Item &ValueSet::Item :: disableDrop ( )
  {
  return enableDrop( false );
  }

ValueSet::Item &ValueSet::Item :: setOwnerDraw ( Boolean setting )
  {
  if ( enable )
    setStyle( style() | itemOwnerDraw );
  else
    setStyle( style() & ~itemOwnerDraw );
  return *this;
  }

Boolean ValueSet::Item :: isEmpty ( ) const
  {
  return itemType == emptyItem;
  }

Boolean ValueSet::Item :: containsBitmap ( ) const
  {
  return itemType == bitmapItem;
  }

Boolean ValueSet::Item :: containsIcon   ( ) const
  {
  return itemType == iconItem;
  }

Boolean ValueSet::Item :: containsText   ( ) const 
  {
  return itemType == textItem;
  }

Boolean ValueSet::Item :: containsColor  ( ) const
  {
  return itemType == colorItem;
  }

IBitmapHandle ValueSet::Item :: bitmap ( ) const
  {
  return itemBmpHandle;
  }

IPointerHandle ValueSet::Item :: icon ( ) const
  {
  return itemPtrHandle;
  }

IString ValueSet::Item :: text ( ) const
  {
  return itemText;
  }

IColor ValueSet::Item :: color ( ) const
  {
  return itemColor;
  }
