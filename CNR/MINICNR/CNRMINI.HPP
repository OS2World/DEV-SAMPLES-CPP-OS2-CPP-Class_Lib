#ifndef _CNRMINI_
#define _CNRMINI_
//************************************************************
// Container Control - Mini-icon Container                    
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <icnrctl.hpp>

class MiniIconContainer : public IContainerControl
{
public:

INESTEDBITFLAGCLASSDEF3( Style, MiniIconContainer, IWindow,
                         IControl, IContainerControl);

static const Style
  classDefaultStyle;

INESTEDBITFLAGCLASSDEF1( Attribute, MiniIconContainer,
                        IContainerControl);

static Style
  defaultStyle    ( );
static void
  setDefaultStyle ( Style style);

  MiniIconContainer (unsigned long id,
                     IWindow*      parent,
                     IWindow*      owner,
                     const IRectangle& initRect =
                         IRectangle(),
                     const Style& style =
                             defaultStyle(),
                     const IContainerControl::Attribute& attr =
                             defaultAttribute());

MiniIconContainer
 &showMiniIcons    ( Boolean mini= true);

private:
static Style
  currentDefaultStyle;
MiniIconContainer (const MiniIconContainer&);
MiniIconContainer& operator=(const MiniIconContainer&);
};

INESTEDBITFLAGCLASSFUNCS(Style, MiniIconContainer);

#endif // _CNRMINI_
