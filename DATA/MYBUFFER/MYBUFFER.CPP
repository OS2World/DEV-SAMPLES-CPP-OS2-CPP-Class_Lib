//************************************************************
// Data Types - Replacing the IString's IBuffer Object
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//
//************************************************************
#include <iostream.h>
#include <istring.hpp>
#include <ibuffer.hpp>

class MyBuffer : public IBuffer {
public:
  MyBuffer( unsigned len )
    : IBuffer( len )
    {
    }
virtual IBuffer
 *allocate ( unsigned len ) const
    {
    return new (len) MyBuffer( len );
    }
virtual const char
 *className ( ) const
    {
    return (const char*)"MyBuffer";
    }
};

void main()
  {
  IString
    withDefault( "withDefault" );
  cout << withDefault.asDebugInfo() << endl;
  MyBuffer
    root(0); // Allocate null buffer.
  IBuffer::setDefaultBuffer( &root );
  IString
    withMyBuffer("withMyBuffer");
  cout << withMyBuffer.asDebugInfo() << endl;
  }
