#ifndef _TREEDETH_
#define _TREEDETH_
//************************************************************
// Container - Combined Tree and Details View
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************
#include <icnrhdr.hpp>

class DetailsTreeContainer;
class IContainerObject;
class IContainerControl;

class DetailsTreeHandler : public ICnrHandler
{
typedef ICnrHandler
  Inherited;

public:
  DetailsTreeHandler      (DetailsTreeContainer* treeContainer );

protected:
virtual Boolean
  dispatchHandlerEvent ( IEvent& event);

virtual Boolean
  treeCollapsed        ( IContainerObject* collapsedObject,
                         IContainerControl* container),
  treeExpanded         ( IContainerObject* expandedObject,
                         IContainerControl* container),
  inuseChanged         ( ICnrEmphasisEvent& event),
  cursoredChanged      ( ICnrEmphasisEvent& event),
  windowScrolled       ( ICnrScrollEvent& event),
  fontChanged          ( IEvent& event);

private:
DetailsTreeContainer
 *treeCnr;

};

#endif // _TREEDETH_

