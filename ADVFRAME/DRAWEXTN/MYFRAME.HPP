#ifndef _MYFRAME_
#define _MYFRAME_
//************************************************************
// Advanced Frame - Frame Extension Drawing Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iframe.hpp>
#include <iframext.hpp>
#include <icmdhdr.hpp>
#include <istring.hpp>
#include <ilistbox.hpp>
#include <ientryfd.hpp>
#include <ipushbut.hpp>

class MyFrame;
class MyExtension;

class ColorList : public IListBox {
public:
  ColorList ( IWindow *owner );
long
  color ( );
private:
ColorList (const ColorList&);
ColorList& operator= (const ColorList&);
};


class MyHandler : public ICommandHandler {
public:
  MyHandler ( MyFrame &frame );
protected:
virtual Boolean
  command ( ICommandEvent &cmd );
private:
IFrameWindow
 &frame;
MyHandler(const MyHandler&);
MyHandler& operator=(const MyHandler&);
};

class MyFrame : public IFrameWindow {
public:
  MyFrame ( );

virtual IFrameWindow
 &update ( );

private:
MyFrame
 &addMyExtension( MyExtension *pExt );

ColorList
  colorList;
IEntryField
  extSize;
IPushButton
  drawButton;
MyHandler
  handler;
MyFrame ( const MyFrame& );
MyFrame& operator= ( const MyFrame& );
};

#endif // _MYFRAME_
