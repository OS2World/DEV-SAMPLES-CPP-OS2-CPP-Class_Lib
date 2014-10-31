#ifndef _VALUESET_
#define _VALUESET_
//************************************************************
// Extending the Library - Value Set Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************

#ifndef _ICONTROL_
  #include <icontrol.hpp>
#endif

#ifndef _ISTRING_
  #include <istring.hpp>
#endif

#ifndef _IRECT_
  #include <irect.hpp>
#endif

#ifndef _ICOLOR_
  #include <icolor.hpp>
#endif

class IResourceId;


class ValueSet : public IControl {
typedef IControl
  Inherited;
public:
class Style;
/*------------------------------- Constructors ---------------------------------
| Constructors provide for creating ValueSets:                                 |
|   o from a specification of the value set attibutes, including the           |
|     "dimensions" (number of rows and columns);                               |
|   o from a parent window and id of a value set child control,                |
|     this constructor is used to wrapper a control on a dialog loaded         |
|     from a dialog template;                                                  |
|   o from the window handle of a previously created WC_VALUESET window.       |
------------------------------------------------------------------------------*/
  ValueSet ( unsigned long        id,
             IWindow             *parent,
             IWindow             *owner,
             const ISize         &dimensions,
             const IRectangle    &sizeAndPosition = IRectangle(),
             const Style         &style = defaultStyle() );
  ValueSet ( unsigned long        id,
             IWindow             *parent,
             IWindow             *owner,
             const IRectangle    &sizeAndPosition = IRectangle(),
             const Style         &style = defaultStyle() );
  ValueSet ( IWindow             *parent,
             unsigned long        id );
  ValueSet ( const IWindowHandle &hwnd );
virtual
  ~ValueSet ();

/*---------------------------------- Style -------------------------------------
| Style - Nested class defining the type of the value set style flags.         |
|         These style values can be mixed with IControl::Style and             |
|         IWindow::Style values.                                               |
------------------------------------------------------------------------------*/
INESTEDBITFLAGCLASSDEF2( Style, ValueSet, IWindow, IControl);

static const Style
  border,
  itemBorder,
  rightToLeft,
  scaleBitmaps,
  drawItem,
  classDefaultStyle;

/*------------------------- Style Get/Set Functions ----------------------------
| These functions let you query or set the various style attributes.  Note     |
| that the "right to left" style can only be set at creation time.             |
------------------------------------------------------------------------------*/
static Style
   defaultStyle();
static void
   setDefaultStyle( const Style &style );

Boolean
  hasBorder        ( ) const,
  hasItemBorder    ( ) const,
  isRightToLeft    ( ) const,
  willScaleBitmaps ( ) const,
  isDrawItem       ( ) const;
                          
virtual ValueSet
 &enableBorder         ( Boolean flag = true ),
 &disableBorder        ( ),
 &enableItemBorder     ( Boolean flag = true ),
 &disableItemBorder    ( ),
 &enableBitmapScaling  ( Boolean flag = true ),
 &disableBitmapScaling ( ),
 &enableDrawItem       ( Boolean flag = true ),
 &disableDrawItem      ( );

/*-------------------------------- Dimensions ----------------------------------
| Use these functions to query or set the value set dimensions (number of      |
| rows and number of columns).                                                 |
------------------------------------------------------------------------------*/
virtual ISize
  dimensions ( ) const;

virtual unsigned long
  numberOfRows    ( ) const,
  numberOfColumns ( ) const;

virtual ValueSet
 &setDimensions      ( const ISize &dimensions ),
 &setNumberOfRows    ( unsigned long rows ),
 &setNumberOfColumns ( unsigned long columns );

/*---------------------------- ItemStyle/ItemType ------------------------------
| The ItemStyle nested class defines the type of values used to represent      |
| the style of specific value set items.                                       |
|                                                                              |
| The ItemType enumeration provides an argument to distinguish the type        |
| of resource identified by an IResourceId on various ValueSet and             |
| ValueSet::Item functions.                                                    |
------------------------------------------------------------------------------*/
INESTEDBITFLAGCLASSDEF0( ItemStyle, ValueSet );

static const ItemStyle
  noItemStyle,
  disabled,
  dragSource,
  dropTarget,
  itemOwnerDraw;

enum ItemType
  {
  bitmapItem,
  iconItem,
  textItem
  };

class Item {
/*******************************************************************************
* Objects of the ValueSet::Item class represent the individual items that      *
* are contained in a ValueSet.  You can get and set these items and the        *
* attributes of these items using various ValueSet functions (see below).      *
*******************************************************************************/
public:
/*------------------------------- Constructors ---------------------------------
| There are 5 kinds of Items:                                                  |
|   o empty (default constructor)                                              |
|   o a bitmap (constructed from a bitmap handle or bitmap resource).          |
|   o an icon (constructed from a pointer handle or pointer resource).         |
|   o text (constructed from a char* pointer or string resource).              |
|   o a color (constructed from an IColor)                                     |
| Each constructor also accepts an optional ItemStyle argument.  If not        |
| specified, the item style defaults to ValueSet::Item::defaultStyle().        |
|                                                                              |
| This class also provides a copy constructor.                                 |
------------------------------------------------------------------------------*/
  Item ( );
  Item ( const IResourceId    &resId,
         ItemType              type,
         const ItemStyle      &style );
  Item ( const IBitmapHandle  &bmp,
         const ItemStyle      &style = Item::defaultStyle() );
  Item ( const IPointerHandle &ptr,
         const ItemStyle      &style = Item::defaultStyle() );
  Item ( const IString        &text,
         const ItemStyle      &style = Item::defaultStyle() );
  Item ( const IColor         &color,
         const ItemStyle      &style = Item::defaultStyle() );
  Item ( const Item           &item );
  ~Item ( );

/*---------------------------------- Style -------------------------------------
| You can use these functions to query or change the style of an item:         |
|   style        - Returns the item's style                                    |
|   setStyle     - Sets the item's style                                       |
|   defaultStyle - Returns the default item style.                             |
|   setDefaultStyle - Sets the default style.                                  |
|   isDisabled      - Returns true if the item is disabled.                    |
|   isEnabled       - Returns true if the item is enabled.                     |
|   canBeDragged    - Returns true if the item has the dragSource style.       |
|   canBeDroppedOn  - Returns true if the item has the dropTarget style.       |
|   isOwnerDraw     - Returns true if the item has the ownerDraw style.        |
|   enable          - Turns the disable style off (or on).                     |
|   disable         - Turns the disable style on.                              |
|   enableDrag  - Turns on (or off) the dragSource style.                      |
|   disableDrag - Turns off the dragSource style.                              |
|   enableDrop  - Turns on (or off) the dropTarget style.                      |
|   disableDrop - Turns off the dropTarget style.                              |
|   setOwnerDraw - Turns on (or off) the ownerDraw style.                      |
------------------------------------------------------------------------------*/
ItemStyle
  style ( ) const;

Item
 &setStyle ( const ItemStyle &style );

static ItemStyle
  defaultStyle ( );

static void
  setDefaultStyle ( const ItemStyle &style );

Boolean
  isDisabled ( ) const,
  isEnabled ( ) const,
  canBeDragged ( ) const,
  canBeDroppedOn ( ) const,
  isOwnerDraw ( ) const;

Item
 &enable ( Boolean enable = true ),
 &disable ( ),
 &enableDrag ( Boolean enable = true ),
 &disableDrag ( ),
 &enableDrop ( Boolean enable = true ),
 &disableDrop ( ),
 &setOwnerDraw ( Boolean setting = true );

/*--------------------------------- Contents -----------------------------------
| You call these functions to query the type of the item contents and the      |
| item contents themselves.  If the item doesn't have the corresponding type   |
| then the content query function will return 0 (or its equivalent).           |
|   isEmpty        - Returns true if the item is empty.                        |
|   containsBitmap - Returns true if the item contains a bitmap.               |
|   containsIcon   - Returns true if the item contains an icon.                |
|   containsText   - Returns true if the item contains text.                   |
|   containsColor  - Returns true if the item contains a color.                |
|   bitmap         - Returns the item's bitmap handle (0 if not a bitmap).     |
|   icon           - Returns the item's pointer handle (0 if not an icon).     |
|   text           - Returns the item's text (a null string if not a text      |
|                    item).  Note that the item's text might also be null.     |
|   color          - Returns the item's color (0 if not a color).              |
------------------------------------------------------------------------------*/
Boolean
  isEmpty ( ) const,
  containsBitmap ( ) const,
  containsIcon   ( ) const,
  containsText   ( ) const,
  containsColor  ( ) const;

IBitmapHandle
  bitmap ( ) const;

IPointerHandle
  icon ( ) const;

IString
  text ( ) const;

IColor
  color ( ) const;

private:
enum Type { emptyItem, bitmapItem, iconItem, textItem, colorItem };
Type
  itemType;
IBitmapHandle
  itemBmpHandle;
IPointerHandle
  itemPtrHandle;
IColor
  itemColor;
IString
  itemText;
ItemStyle
  itemStyle;
static ItemStyle
  dfltStyle;
friend class ValueSet;
}; // class ValueSet::Item

/*------------------------------- Item Get/Set ---------------------------------
| You use these functions to query or modify the individual items contained    |
| by the value set.                                                            |
------------------------------------------------------------------------------*/
Item
  item ( unsigned long row, 
         unsigned long column ) const;

ValueSet
 &setItem ( unsigned long  row,
            unsigned long  column,
            const Item    &item ),

 &setItemContents ( unsigned long         row,
                    unsigned long         column,
                    const IResourceId    &resId,
                    ItemType              type ),
 &setItemContents ( unsigned long         row,
                    unsigned long         column,
                    const IBitmapHandle  &bmp ),
 &setItemContents ( unsigned long         row,
                    unsigned long         column,
                    const IPointerHandle &icon ),
 &setItemContents ( unsigned long         row,
                    unsigned long         column,
                    const IString        &text ),
 &setItemContents ( unsigned long         row,
                    unsigned long         column,
                    const IColor         &color ),

 &setItemStyle ( unsigned long            row,
                 unsigned long            column,
                 const ItemStyle         &style );

/*-------------------------------- Selection -----------------------------------
| You use these functions to query or set the selected item in the value set.  |
------------------------------------------------------------------------------*/
Boolean
  hasSelection ( ) const;

ValueSet
 &setSelection ( unsigned row, unsigned column );

Item
  selectedItem ( ) const;

IPoint
  selection ( ) const;

unsigned long
  selectedRow    ( ) const,
  selectedColumn ( ) const;

/*-------------------------- Item Size and Spacing -----------------------------
| You can call these functions to query or set the value set's item size       |
| or item spacing.                                                             |
------------------------------------------------------------------------------*/
ISize
  itemSize    ( ) const,
  itemSpacing ( ) const;

ValueSet
 &setItemSize    ( const ISize &size ),
 &setItemSpacing ( const ISize &size );

/*---------------------------------- Colors ------------------------------------
| You use these functions to query and set the colors that the value set       |
| uses.                                                                        |
------------------------------------------------------------------------------*/
enum ColorArea
  {
  borders,
  foreground,
  background,
  highlightBackground
  };

IColor
  color ( ColorArea area ) const;

ValueSet
 &setColor ( ColorArea     area,
             const IColor &color );

protected:
/*------------------------------ Implementation --------------------------------
| These functions provide services used to implement this class.               |
------------------------------------------------------------------------------*/
void 
  initialize ( const IWindowHandle &hwnd ),
  initialize ( const ISize         &size,
               unsigned long        id,
               IWindow             *parent,
               IWindow             *owner,
               const IRectangle    &initial,
               const Style         &style ),

  setItemAttributes ( unsigned long row,
                      unsigned long column,
                      const IEventParameter2 &attr ),

  setItem ( unsigned long row,
            unsigned long column,
            const IEventParameter2 &contents ),

  setMetrics ( const IEventParameter1 &mp1,
               const ISize            &size );

static IString
  controlData ( const ISize &size );

unsigned long
  itemHandle ( unsigned long row,
               unsigned long column ) const;

ISize
  metrics         ( const IEventParameter1 &mp1 ) const,
  calcMinimumSize ( ) const;

private:
static Style
  dfltStyle;
ValueSet (const ValueSet&);
ValueSet& operator= (const ValueSet&);
}; // class ValueSet


INESTEDBITFLAGCLASSFUNCS( Style, ValueSet );

#endif // _VALUESET_
