//************************************************************
// Data Types - Using an IStringTest  
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//
//************************************************************
#include <iostream.h>

#include <istring.hpp>
#include <istrtest.hpp>

class MyTest : public IStringTest {     
    public:
      MyTest ( )
        : IStringTest( user, 0 )
        {
        }
    virtual int
      test ( int c ) const
        {
        return isspace( c ) || ispunct( c );
        }
    };

void main( int argc, char *argv[] )
  {
  if ( argc > 1 )
    {
    IString
      input( argv[1] );
    cout << "The position of the first blank or punctuation is "
         << input.indexOf( MyTest() ) << endl;
    }
  else
    cout << "Enter string to test/a/n";
  }
