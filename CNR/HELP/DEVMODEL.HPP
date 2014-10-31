#ifndef _DEVMODEL_
#define _DEVMODEL_
//************************************************************
// Container Control - Help in the Container                    
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <icnrobj.hpp>
#include <istring.hpp>

class Developer : public IContainerObject
{
public:
 Developer    ( const IString& name,
                const IString& address,
                unsigned long  age);

IString
  name                  ( ) const,
  address               ( ) const,
  age                   ( ) const;

Developer
 &setHelpId            ( unsigned long helpId);

virtual unsigned long
  helpId               ( ) const;

static unsigned long
  addressOffset        ( ),
  ageOffset            ( );

private:
IString
  strAddress,
  strAge;
unsigned long
  ulHelpId;
};
#endif // _DEVMODEL_
