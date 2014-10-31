#ifndef _TABLE_
#define _TABLE_
//************************************************************
// Container Control - Dynamic Creation Of Objects            
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <icnrobj.hpp>
#include <istring.hpp>

class TableObject : public IContainerObject
{
public:
  TableObject      ( unsigned long fieldCount);
  TableObject      ( TableObject&  objectToCopy);
    ~TableObject   ( );

void
 *operator new     ( size_t        size,
                     unsigned long fieldCount);

IContainerObject
 *objectCopy       ( );

Boolean
  setFieldText     ( const IString& strText,
                     unsigned long fieldIndex);

IString
  fieldText        ( unsigned long fieldIndex) const;
unsigned long
  fieldCount       ( );


static unsigned long
  fieldOffset(unsigned long fieldNumber);

private:
void
 *operator new      ( size_t size)  {  return 0; }

unsigned long
  fieldNumber;
IString
  strArray[1];
};

#endif // _TABLE_
