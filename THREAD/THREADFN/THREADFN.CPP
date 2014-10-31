class PiOnAThread : public IThreadFn {
public:
  PiOnAThread ( unsigned digits,
                const IWindowHandle &window )
    : arg( digits ),
      win( window )
    {
    }
virtual void
  run ( )
    {
    IString
      result = pi( digits );
    win.sendEvent( WM_USER, (char*)result );
    }
private:
unsigned
  arg;
IWindowHandle
  win;
};


IWindowHandle
  handle;

IThread
  calculatePi( new PiOnAThread( 100, handle ) );

