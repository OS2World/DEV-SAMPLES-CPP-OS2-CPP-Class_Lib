class PiCalc {
public: 
IString
  pi ( unsigned );
//...some other stuff...
void
  update ( )
    {
    IString
      result = pi( digits );
    ef->setText( result );
    }
private:
unsigned
  digits;
IEntryField
  ef;
};


PiCalc
  calculator;

IThread
  thread( new IThreadMemberFn<PiCalc>( calculator,
                                             PiCalc::update ) );
