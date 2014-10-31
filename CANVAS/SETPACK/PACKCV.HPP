#ifndef _PACKCV_
#define _PACKCV_
//************************************************************
// Canvas - ISetCanvas Desks Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <icmdhdr.hpp>
#include <iframe.hpp>
#include <igraphbt.hpp>
#include <iiconctl.hpp>
#include <ioutlbox.hpp>
#include <ipoint.hpp>
#include <irect.hpp>
#include <isetcv.hpp>
#include <isizehdr.hpp>

#include "packcv.h"

class PackCanvas : public ISetCanvas {
public:
  PackCanvas ( unsigned long id,
               IWindow* parentAndOwner,
               ISetCanvas::PackType pack );
private:
IOutlineBox
  first,
  second,
  third,
  fourth,
  fifth,
  sixth;
PackCanvas ( const PackCanvas&);
PackCanvas& operator= ( const PackCanvas&);
};

class PackAlignTest : public IFrameWindow {
public:
  PackAlignTest      ( );
PackAlignTest
 &alignGrandChildren ( ISetCanvas::Alignment align );
private:
class CmdHandler : public ICommandHandler {
  public:
    CmdHandler ( PackAlignTest* window )
      : clWindow( window )
    { }
  protected:
  virtual Boolean
    command    ( ICommandEvent& event );
  private:
  PackAlignTest
   *clWindow;
  };

class GraphicSizer : public IResizeHandler {
  protected:
  virtual Boolean
    windowResize ( IResizeEvent& event );
  };
ISetCanvas
  packClient;
PackCanvas
  tight,
  even,
  expanded;
CmdHandler
  cmdHdr;
GraphicSizer
  sizHdr;
ISetCanvas
  buttons;
IGraphicPushButton
  topLeft,
  topCenter,
  topRight,
  centerLeft,
  centerCenter,
  centerRight,
  bottomLeft,
  bottomCenter,
  bottomRight;
PackAlignTest( const PackAlignTest& );
PackAlignTest& operator=( const PackAlignTest& );
};
#endif // _PACKCV_
