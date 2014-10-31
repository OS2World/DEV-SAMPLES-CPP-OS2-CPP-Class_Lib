#ifndef _CHDHIDER_
#define _CHDHIDER_
//************************************************************
// Frame Window Basics - Minimize/Maximize Handler Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************

#include "minmaxh.hpp"

class ChildHider : public MinMaxHandler {
public:
void
  showChildren ( IWindow *parent,
                 Boolean show = true );
Boolean
  minimized ( IEvent &event ),
  maximized ( IEvent &event ),
  restored ( IEvent &event );
};
#endif // _CHDHIDER_
