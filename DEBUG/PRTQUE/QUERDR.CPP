//************************************************************
// Problem Determination  - Trace Queue Browser
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#define INCL_DOSQUEUES
#define INCL_DOSPROCESS
#include <os2.h>
#include <iexcept.hpp>
#include <icnrobj.hpp>
#include <ihandle.hpp>
#include <ithread.hpp>
#include "querdr.hpp"
#include "trbrowse.h"

// Set up the queue for reading
QueueReader::QueueReader ( const char*           queueName,
                           const IWindowHandle&  targetWindow)
               : target(targetWindow),
                 qHandle (0)
{
  unsigned long rc = DosCreateQueue(
                       &qHandle,
                       QUE_FIFO | QUE_CONVERT_ADDRESS,
                       queueName);
  if (rc!=0)
    ITHROWSYSTEMERROR(rc, "DosCreateQueue",
                      IErrorInfo::accessError,
                      IException::recoverable );
}

QueueReader::~QueueReader ( )
{
  DosCloseQueue(queueHandle());
}

// Our Thread function that reads the queue
void QueueReader::run ( )
{
  unsigned long rc;
  REQUESTDATA request;
  char* queueData;
  unsigned long dataLength;
  IContainerObject* pobj;
  BYTE priority = 0;

  request.pid = IThread::current().id();
  while(1) {
    rc = DosReadQueue (queueHandle(), &request, &dataLength,
                       (void**)&queueData, 0, 0, &priority, 0);
    if(rc!=0)
      ITHROWSYSTEMERROR(rc, "DosReadQueue",
                        IErrorInfo::accessError,
                        IException::recoverable );

    // Create an object and post a request to the main
    // thread to add it to the container.
    pobj = new IContainerObject(queueData);
    DosFreeMem(queueData);
    Boolean loop = true;
    while(loop) {
       try {
         loop = false;
         targetHandle().postEvent(ADD_OBJECT, pobj);
       } catch (IException& ) {
         // If we can't post (message queue full?),
         // Wait a bit and try again
         loop = true;
         DosSleep(100);
       }
    }
  }
}
