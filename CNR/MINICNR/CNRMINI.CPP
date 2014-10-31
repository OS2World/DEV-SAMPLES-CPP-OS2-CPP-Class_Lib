//************************************************************
// Container Control - Mini-icon Container                    
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************

#define INCL_WINSTDCNR
#include <iframe.hpp>
#include <icnrctl.hpp>
#include <iapp.hpp>
#include <os2.h>
#include "cnrmini.hpp"
#include "minicnr.h"

const MiniIconContainer::Style
  MiniIconContainer::classDefaultStyle(WS_VISIBLE | 
                        CCS_SINGLESEL | 0x00000800L);

MiniIconContainer::Style
  MiniIconContainer::currentDefaultStyle(WS_VISIBLE |
                        CCS_SINGLESEL | 0x00000800L);

MiniIconContainer ::  MiniIconContainer ( unsigned long id,
                        IWindow*          parent,
                        IWindow*          owner,
                        const IRectangle& initRect,
                        const Style&      style,
      const IContainerControl::Attribute& attr)
                  : IContainerControl (id,
                                       parent,
                                       owner,
                                       initRect,
      (const IContainerControl::Style&)style,
                                       attr)
  { }

MiniIconContainer& 
MiniIconContainer:: showMiniIcons ( Boolean mini)
{
  if (mini)
    setContainerAttributes(0, CV_MINI);
  else
    setContainerAttributes(CV_MINI, 0);
  return *this;
}

MiniIconContainer::Style  
MiniIconContainer :: defaultStyle()
{ return currentDefaultStyle; }

void  
MiniIconContainer :: setDefaultStyle(MiniIconContainer::Style cnrStyle)
{ currentDefaultStyle = cnrStyle; }
