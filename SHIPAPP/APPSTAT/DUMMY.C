extern "C" {

void ADummyFunction()
{
}

#pragma export(isValid, "isValid", 1)
// The following is added to test procaddr
int isValid( int number)
{

  if (number<10) 
     return 1;
  else
     return 0;
}

}
