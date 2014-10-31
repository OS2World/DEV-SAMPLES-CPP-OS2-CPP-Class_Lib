#include <ireslib.hpp>
#include "appstat.hpp"

// Static instance of AppStatics
AppStatics appStatics;

//  Static data in AppStatics
IDynamicLinkLibrary* AppStatics::engDLL = 0;

// Destructor to close the DLL
AppStatics::~AppStatics ( )
{
  if(engDLL != 0)
    delete engDLL;
}

// Static accessor for the DLL
IDynamicLinkLibrary& AppStatics :: englishDLL( )
{
   if(!engDLL)
     engDLL = new IDynamicLinkLibrary("myeng");
   return *engDLL;
}

