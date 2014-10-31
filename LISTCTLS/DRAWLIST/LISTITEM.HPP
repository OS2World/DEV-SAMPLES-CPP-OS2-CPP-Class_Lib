#ifndef _LISTITEM_
#define _LISTITEM_
//************************************************************
// List Controls - List Box Custom Drawing           
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <ivbase.hpp>
#include <istring.hpp>

// ListItem represents the data for each item
// in the listbox.  This includes:
//  1) the class name
//  2) the number of inherited classes
//  3) the existance of inheriting classes
//  4) an indication that inheriting classes
//     are collapsed or showing
class ListItem : public IVBase
{
public:
 ListItem (const char*   className,
           unsigned long inheritedClasses=0,
           Boolean       children=true,
           Boolean       collapsedTree=false)
        : _text (className),
          _inheritedClasses(inheritedClasses),
          _children(children),
          _collapsed (collapsedTree) {}

IString
  text             ( ) { return _text;}
unsigned long
  inheritedClasses ( ) { return _inheritedClasses;}
Boolean
  collapsed        ( ) { return _collapsed;  }
Boolean
  children         ( ) { return _children;  }

private:
unsigned long 
  _inheritedClasses;
IString
  _text;
Boolean
  _collapsed,
  _children;
};

#endif // _LISTITEM_
