//************************************************************
// Data Types - Using an IString as a Data Buffer
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//
// DESCRIPTION:                                                              
//   This program implements a simplistic file encryption/decryption scheme. 
//   It simply XORs the contents of cin using the argument "key" string and  
//   writes the result to cout.                                              
//                                                                           
//   Usage:      cipher "secret key" < input > output                        
//                                                                           
//************************************************************
#include <istring.hpp>
#include <iostream.h>
#include <stdio.h>

int main ( int argc, char *argv[] )
  {
  int
    result = 0;

  /*----------------------------------------------------------------------------
  | Get key.                                                                   |
  ----------------------------------------------------------------------------*/
  IString
    key( argv[1] );

  /*----------------------------------------------------------------------------
  | Ensure key was specified.                                                  |
  ----------------------------------------------------------------------------*/
  if ( key.length() )
    {
    /*--------------------------------------------------------------------------
    | Put input and output files in binary mode.                               |
    --------------------------------------------------------------------------*/
    if ( !freopen( "", "rb", stdin )
         ||
         !freopen( "", "wb", stdout ) )
      {
      cerr << "Error opening input/output files.\a" << endl;
      result = 2;
      }
    else
      {
      /*------------------------------------------------------------------------
      | Read from stdin, XOR the bytes with the key, and write to stdout.      |
      ------------------------------------------------------------------------*/
      IString
        buffer( 0, 4096 ); // Allocate 4K buffer.
      while ( true )
        {
        size_t
          n = fread( (char*)buffer, 1, buffer.length(), stdin );
        buffer ^= key;
        fwrite( (char*)buffer, 1, n, stdout );
        if ( n < buffer.length() )
          break;
        }
      }
    }
  else
    {
    cerr << "You must specify a key!\a" << endl;
    result = 1;
    }
  return result;
  }
