//************************************************************
// Data Types - Using IString::isLike    
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//
// DESCRIPTION:                                                                  
//   This program searches the argument file for lines that contain an argument  
//   IString::isLike "pattern".                                                  
//                                                                               
//   Usage:   igrep <file> <pattern>                                             
//                                                                               
//
//************************************************************
#include <istring.hpp>
#include <fstream.h>

int main ( int argc, char *argv[] )
  {
  int
    result = 0;

  // Validate the input arguments.
  if ( argc != 3 )
    {
    cerr << "Usage:  igrep  <file>  <pattern>\a" << endl;
    return 0;
    }

  IString
    file( argv[1] ),
    pattern( argv[2] );

  // Pad the pattern at both ends with wildcards (so the pattern
  // is found anywhere in an input line).                                                            |
  pattern = IString( 0, 1, 
                     (char*)pattern, pattern.length(), 
                     0, 1, 
                     '*' );

  // Open the input file.                                            
  ifstream
    input( file );

  if ( !input )
    {
    cerr << "Error opening file.\a" << endl;
    return 0;
    }

  // Read lines, looking for a pattern.                                           
  unsigned
    lineNo = 0;
  while ( input )
    {
    IString
      line = IString::lineFrom( input );
    lineNo++;
    if ( line.isLike( pattern ) )
      {
      result++;
      cout << IString( lineNo ).rightJustify( 4 ) << " "
           << line << endl;
      }
    }
  return result;
  }
