extern void _Optlink service( void * );

IWindowHandle
  objWindow[3];

IThread
  serviceThread[3];

for ( int i = 0; i < 3; i++ )
  serviceThread[i].start( service, &objWindow[i] );

IFrameWindow
  frame( "Main Window" );

frame.showModally();

for( i = 0; i < 3; i++ )
  objWindow[i].postEvent( WM_QUIT );

IThread::current().waitForAllThreads();

