//************************************************************
// Container Control - Help in the Container
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include "devmodel.hpp"

Developer::Developer   ( const IString&      name,
                         const IString&      address,
                         unsigned long age)
     : IContainerObject(name),
       strAddress(address),
       strAge(age)

{}

IString Developer:: name ( ) const
{ 
  return iconText();
}

IString Developer:: address ( ) const
{ 
  return strAddress;
}

IString Developer:: age ( ) const
{ 
  return strAge;
}


Developer& Developer::setHelpId ( unsigned long helpId)
{ 
  ulHelpId = helpId;
  return *this;
}


unsigned long Developer::helpId ( ) const
{ 
  return ulHelpId;
}


unsigned long Developer::addressOffset ( )
{ 
  return offsetof(Developer, strAddress);
}

unsigned long Developer::ageOffset ( )
{   
  return offsetof(Developer, strAge);
}


