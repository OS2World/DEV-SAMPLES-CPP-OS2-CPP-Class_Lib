//************************************************************
// Container Control - Tree Icon View                         
//
// Copyright (C) 1994, Law, Leong, Love, Olson, Tsuji.
// All Rights Reserved.
//************************************************************

#include <iframe.hpp>
#include <icnrctl.hpp>
#include <iapp.hpp>
#include "treeicov.h"

void main ()
{

IFrameWindow cnrFrame("Tree Icon View");
cnrFrame.sizeTo(ISize(300,350));

IContainerControl cnr(0x101,        
                      &cnrFrame,    
                      &cnrFrame);

// Put container in client area
cnrFrame.setClient(&cnr);

// Create the root objects
IContainerObject* root1 = new IContainerObject("Root 1", 
                                  ICON_FOLDER);
IContainerObject* root2 = new IContainerObject("Root 2",
                                  ICON_FOLDER);
IContainerObject* root3 = new IContainerObject("Root 3",
                                  ICON_FOLDER);

// Create a few Child objects
IContainerObject* root1Child1 = new
    IContainerObject("Root 1 - Child 1", ICON_FOLDER);
IContainerObject* root1Child2 = new
    IContainerObject("Root 1 - Child 2", ICON_FOLDER);
IContainerObject* root1Child3 = new
    IContainerObject("Root 1 - Child 3", ICON_FOLDER);

// Add the root objects
cnr.addObject(root1);
cnr.addObject(root2);
cnr.addObject(root3);

// Add Two of Root1's children
cnr.addObject(root1Child2, root1);
cnr.addObject(root1Child3, root1);

// Now add a Root1 Child as first child
cnr.addObjectAfter(root1Child1, 0, root1);

// Show the Tree Icon view
cnr.showTreeIconView();

// Expand the tree
cnr.expandTree();

// Make the frame visible and give it focus
cnrFrame.show();
cnrFrame.setFocus();

// Start the message loop
IApplication::current().run();
}
