#ifndef _CUSTEXCP_
#define _CUSTEXCP_
//************************************************************
// Error Handling - New Exception Class
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <iexcbase.hpp>

class CustomException : public IException
{
public:

  CustomException ( const char*   errorText,
                    unsigned long errorId = 0,
                    Severity      sev = unrecoverable );

virtual
 ~CustomException ( );

  CustomException ( const CustomException& excp);

virtual const char
 *name ( ) const;

private:
operator = ( const CustomException& );
};
#endif // _CUSTEXCP_
