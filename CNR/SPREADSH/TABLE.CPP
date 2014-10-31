//************************************************************
// Container Control - Spreadsheet Behavior
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <ipoint.hpp>
#include <new.h>
#include "table.hpp"

// Primary Constructor
TableObject::TableObject(unsigned long count)
             : IContainerObject(0)
{
  this->fieldNumber = count;
  unsigned long s;
   // Call global operator new using placement syntax.
   // This will result in no storage being allocated but
   // the constructor gets called.
   for(s=1; s<fieldNumber; s++)
   {
        new(&strArray[s]) IString();
   }
}

// Copy Constructor
TableObject::TableObject(TableObject& oldObject)
                  : IContainerObject (oldObject)
{
   this->fieldNumber = oldObject.fieldNumber;
   unsigned long s;
   // Call global operator new using placement syntax.
   for(s=1; s<this->fieldNumber; s++)
   {
       new (this->strArray+s) IString(oldObject.strArray[s]);
   }

}

// Derived class required function to make a copy.
IContainerObject* TableObject::objectCopy()
{
   TableObject* pObject = new(fieldCount()) TableObject(*this);
   return (IContainerObject*)pObject;
}

// Operator new for variable number of fields.
void* TableObject :: operator new(size_t        size,
                                  unsigned long count)
{


  void* pobject = IContainerObject::operator new( size +
                     count*sizeof(IString));
  return(pobject);
}

// Destructor
TableObject::~TableObject()
{
   // Since the first field is handled by destruction
   // of the IString Array, we delete here from the
   // second IString. Note that we are explicitly
   // calling the destructor since we don't want any
   // storage freed.
   unsigned long s;
   for(s=1; s<this->fieldNumber; s++)
  {
      this->strArray[s].~IString();
  }
}


// Function to replace the text in a field.
// We return a Boolean but an exception is more
// appropriate
Boolean TableObject::setFieldText(const IString& strText,
                                  unsigned long fieldIndex)
{
  if (fieldIndex < this->fieldNumber)
  {
    strArray[fieldIndex] = strText;
    return true;
  }
  return false;
}

// Return the text at a field index
IString TableObject::fieldText( unsigned long fieldIndex) const
{
  return this->strArray[fieldIndex];
}

// Return the number of fields
unsigned long TableObject::fieldCount( )
{
  return this->fieldNumber;
}

// static function to calculate the offset of the field
// for the column record
unsigned long TableObject::fieldOffset(unsigned long
                                       fieldIndex)
{
  return offsetof(TableObject,strArray[0])
     + fieldIndex*(sizeof(IString));
}
