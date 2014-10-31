#ifndef _START2W_
#define _START2W_
//***********************************************************
// Getting Started - Simple Program Version 2
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//***********************************************************
#include <iframe.hpp>
#include <imle.hpp>
#include "start2ch.hpp"      // For CutCopyPasteHandler.

class CodeWindow : public IFrameWindow {
public:
  CodeWindow ( const char* title,
               unsigned long id = IC_DEFAULT_FRAME_ID );
virtual Boolean
  cut               ( ),
  copy              ( ),
  paste             ( );
private:
IMultiLineEdit
  mle;
CutCopyPasteHandler
  cmdHandler;

// Disallow copy and assignment.
CodeWindow ( const CodeWindow& );
CodeWindow& operator= ( const CodeWindow& );
};

#endif  // _START2W_
