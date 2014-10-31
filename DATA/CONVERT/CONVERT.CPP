//************************************************************
// Data Types - Using the IString Conversion Functions 
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//
//************************************************************
#include <istring.hpp>
#include <stream.h>

typedef IString String;

typedef String& (String::*pStringConversionMember)();
typedef String (*pStringConversionFunction)(const String &);

static pStringConversionMember
  members[] = { String::b2c,
                String::b2d,
                String::b2x,
                String::c2b,
                String::c2d,
                String::c2x,
                String::d2b,
                String::d2c,
                String::d2x,
                String::x2b,
                String::x2c,
                String::x2d };

static pStringConversionFunction
  functions[] = { IString::b2c,
                  IString::b2d,
                  IString::b2x,
                  IString::c2b,
                  IString::c2d,
                  IString::c2x,
                  IString::d2b,
                  IString::d2c,
                  IString::d2x,
                  IString::x2b,
                  IString::x2c,
                  IString::x2d };

static String
  options( "b2c "
           "b2d "
           "b2x "
           "c2b "
           "c2d "
           "c2x "
           "d2b "
           "d2c "
           "d2x "
           "x2b "
           "x2c "
           "x2d " );

int main( int argc, char *argv[] )
  {
  if ( argc == 3 )
    {
    String opt( argv[1] );
    String arg( argv[2] );
    unsigned int i = options.wordIndexOfPhrase( opt );
    if ( i )
      {
      String opt = options.word(i--);
      String input  = arg;
      String result = functions[i](arg);
      cout << opt << "(\"" << input << "\")   \t=\t" << result << "\n";
      cout << "(\"" << input << "\")." << opt << "()\t=\t";
      (input.*members[i])();
      cout << input << "\n";
      opt.reverse();
      i = options.wordIndexOfPhrase( opt ) - 1;
      result = functions[i](input);
      cout << opt << "(\"" << input << "\")   \t=\t" << result << "\n";
      cout << "(\"" << input << "\")." << opt << "()\t=\t";
      (input.*members[i])();
      cout << input << "\n";
      if ( result != arg || result != input )
         cout << "Something is wrong with this!\a\n";
      else
         cout << "This seemed to work OK!\n";
      }
    else
      cout << "Invalid conversion function\nChoose one of:\n\t"
           << options << '\n';
    }
  else
    cout << "Invalid input\nSyntax is:   convert opt input\n";

  return 0;
  }
