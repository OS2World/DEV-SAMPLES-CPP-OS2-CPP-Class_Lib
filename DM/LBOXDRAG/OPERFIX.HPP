#ifndef _OPERFIX_
#define _OPERFIX_

class OperFix : private IDMSourceOperation {
public:
static unsigned long
  dropOperation ( IDMSourceEndEvent &event )
    {
    OperFix
     *p = (OperFix*)( event.dragItem()->sourceOperation() );
    return p->dragInfo()->usOperation;
    }
private:
  OperFix ( );
}; 

#endif // _OPERFIX_
