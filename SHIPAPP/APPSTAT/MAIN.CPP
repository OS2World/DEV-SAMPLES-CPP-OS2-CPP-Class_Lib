#include <iostream.h>
#include <istring.hpp>
#include "appstat.hpp"
#include "mytext.h"

void main ( )
{
  IString str = AppStatics::englishDLL().loadString(MY_TEXT);

  cout << "The resource text is [" << str << "]" << endl;
}
