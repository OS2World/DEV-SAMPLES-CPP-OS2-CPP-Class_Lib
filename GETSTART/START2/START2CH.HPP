#ifndef _START2CH_
#define _START2CH_
//***********************************************************
// Getting Started - Simple Program Version 2
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//***********************************************************
#include <icmdhdr.hpp>

class CutCopyPasteHandler : public ICommandHandler {
protected:
virtual Boolean
  command ( ICommandEvent& event );
};

#endif  // _START2CH_
