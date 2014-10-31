#ifndef _TUTORHDR_
#define _TUTORHDR_
/*************************************************************/
/* Basic help program.                                       */
/*                                                           */
/* Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.       */
/* All Rights Reserved.                                      */
/*************************************************************/
#include <ihelphdr.hpp>

class TutorialHandler : public IHelpHandler {
protected:
virtual Boolean
  showTutorial ( IHelpTutorialEvent& event );
};

#endif // _TUTORHDR_
