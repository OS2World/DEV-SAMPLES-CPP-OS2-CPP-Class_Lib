//************************************************************
// Advanced Frame - Profile Viewer Example
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <imle.hpp>
#include <ifont.hpp>
#include "keyview.hpp"
#include "profview.h"

ProfileKeyObject :: ProfileKeyObject ( ProfileApplication &app,
                                       const IString      &keyName,
                                       IContainerControl  *cnr )
  : ProfileObject( keyName, KEY_ICON_ID, cnr ),
    profKey( app, keyName )
  {
  }

ProfileObjectView *ProfileKeyObject :: newView ( )
  {
  return new KeyView( *this );
  }

ProfileKey &ProfileKeyObject :: key ( )
  {
  return profKey;
  }

KeyView :: KeyView ( ProfileKeyObject &keyObj )
  : ProfileObjectView( clientWindow(),
                       keyObj,
                       "Contents View" ),
    keyObj( keyObj )
  {
  populate();
  }

KeyView &KeyView :: populate ( )
  {
  IMultiLineEdit
   *mle = (IMultiLineEdit*)( client() );
  (*mle)
    .addLineAsLast( "Profile: " + keyObj.key().application().profile().name() )
    .addLineAsLast( "Application: " + keyObj.key().application().name() )
    .addLineAsLast( "Key: " + keyObj.key().name() )
    .addLineAsLast( keyObj.key().formatted(), mle->noTran );
  return *this;
  }

IMultiLineEdit *KeyView :: clientWindow ( )
  {
  IMultiLineEdit
   *p = new IMultiLineEdit( 0,
                            IWindow::objectWindow(),
                            IWindow::objectWindow(),
                            IRectangle(),
                            IMultiLineEdit::classDefaultStyle | 
                            IMultiLineEdit::readOnly );
  IFont
    font( "System Monospaced", 12 );
  (*p)
    .setFont( font )
    .setAutoDeleteObject( true );
  return p;
  }
