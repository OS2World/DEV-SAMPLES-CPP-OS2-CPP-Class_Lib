//************************************************************
// Error Handling - New Exception Class
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include "custexcp.hpp"

CustomException::CustomException ( const char*   errorText,
                                   unsigned long errorId,
                                   Severity      sev )
         : IException(errorText, errorId, sev)
{ }

CustomException::~CustomException ( )    
{ }

CustomException::CustomException ( const CustomException& excp)
         : IException(excp)
{ }

const char* CustomException::name ( ) const
{ 
   return "CustomException"; 
}
